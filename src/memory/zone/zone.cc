/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2017 Yanzheng Li

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/
#include "zone.h"
#include "common/constants.h"
#include "common/util.h"
#include "corevm/macros.h"
#include "segment.h"
#include "segment_allocator.h"

#include <cstring>
#include <limits>

namespace corevm {
namespace memory {

// -----------------------------------------------------------------------------

const size_t Zone::kAlignmentInBytes = 8;
const size_t Zone::kMinimumSegmentSize = 8 * KB;
const size_t Zone::kMaximumSegmentSize = 1 * MB;
const size_t Zone::kExcessLimit = 256 * MB;

// -----------------------------------------------------------------------------

Zone::Zone(SegmentAllocator* allocator)
  : m_allocation_size(0),
    m_segment_bytes_allocated(0),
    m_pos(0),
    m_limit(0),
    m_allocator(allocator),
    m_segment_head(nullptr)
{
}

// -----------------------------------------------------------------------------

Zone::~Zone()
{
  delete_all();

  ASSERT(m_segment_bytes_allocated == 0);
}

// -----------------------------------------------------------------------------

bool
Zone::excess_allocation() const
{
  return m_segment_bytes_allocated > kExcessLimit;
}

// -----------------------------------------------------------------------------

size_t
Zone::allocation_size() const
{
  return m_allocation_size;
}

// -----------------------------------------------------------------------------

SegmentAllocator*
Zone::allocator() const
{
  return m_allocator;
}

// -----------------------------------------------------------------------------

void*
Zone::allocate(size_t size)
{
  // Round up the requested size to fit the alignment.
  size = RoundUp(size, kAlignmentInBytes);

  // Check if the requested size is available without expanding.
  uint8_t* result = m_pos;

  const uintptr_t limit = reinterpret_cast<uintptr_t>(m_limit);
  const uintptr_t position = reinterpret_cast<uintptr_t>(m_pos);

  // m_pos > m_limit can be true after the alignment correction above.
  if (limit < position || size > limit - position) {
    result = this->expand(size);
  } else {
    m_pos += size;
  }

  uint8_t* redzone_position = result + size;
  ASSERT(redzone_position == m_pos);

  // Check that the result has the proper alignment and return it.
  ASSERT(IsAddressAligned(result, kAlignmentInBytes, 0));
  m_allocation_size += size;

  return reinterpret_cast<void*>(result);
}

// -----------------------------------------------------------------------------

void
Zone::delete_all()
{
  // Traverse the chained list of segments and return them all to the allocator.
  for (Segment* current = m_segment_head; current;) {
    Segment* next = current->next();
    size_t size = current->size();

    m_segment_bytes_allocated -= size;
    m_allocator->return_segment(current);
    current = next;
  }

  m_pos = m_limit = 0;
  m_allocation_size = 0;
  m_segment_head = nullptr;
}

// -----------------------------------------------------------------------------

// Creates a new segment, sets it size, and pushes it to the front
// of the segment chain. Returns the new segment.
Segment*
Zone::create_new_segment(size_t requested_size)
{
  Segment* result = m_allocator->get_segment(requested_size);

  if (result != nullptr) {
#if __DEBUG__
    ASSERT(result->size() >= requested_size);
#endif
    m_segment_bytes_allocated += result->size();
    result->set_zone(this);
    result->set_next(m_segment_head);
    m_segment_head = result;
  }

  return result;
}

// -----------------------------------------------------------------------------

uint8_t*
Zone::expand(size_t size)
{
// Make sure the requested size is already properly aligned and that
// there isn't enough room in the Zone to satisfy the request.
#if __DEBUG__
  ASSERT(size == RoundDown(size, kAlignmentInBytes));
#endif
  ASSERT(m_limit < m_pos || (reinterpret_cast<uintptr_t>(m_limit) -
                             reinterpret_cast<uintptr_t>(m_pos)) < size);

  // Compute the new segment size. We use a 'high water mark'
  // strategy, where we increase the segment size every time we expand
  // except that we employ a maximum segment size when we delete. This
  // is to avoid excessive malloc() and free() overhead.
  Segment* head = m_segment_head;
  const size_t old_size = (head == nullptr) ? 0 : head->size();
  static const size_t kSegmentOverhead = sizeof(Segment) + kAlignmentInBytes;
  const size_t new_size_no_overhead = size + (old_size << 1);
  size_t new_size = kSegmentOverhead + new_size_no_overhead;
  const size_t min_new_size = kSegmentOverhead + size;

  // Guard against integer overflow.
  if (new_size_no_overhead < size || new_size < kSegmentOverhead) {
    return nullptr;
  }

  if (new_size < kMinimumSegmentSize) {
    new_size = kMinimumSegmentSize;
  } else if (new_size > kMaximumSegmentSize) {
    // Limit the size of new segments to avoid growing the segment size
    // exponentially, thus putting pressure on contiguous virtual address space.
    // All the while making sure to allocate a segment large enough to hold the
    // requested size.
    new_size = std::max(min_new_size, kMaximumSegmentSize);
  }

  if (new_size > std::numeric_limits<size_t>::max()) {
    return nullptr;
  }

  Segment* segment = create_new_segment(new_size);
  if (segment == nullptr) {
    return nullptr;
  }

  // Recompute 'top' and 'limit' based on the new segment.
  uint8_t* result = RoundUp(segment->start(), kAlignmentInBytes);
  m_pos = result + size;

  // Check for address overflow.
  // (Should not happen since the segment is guaranteed to accomodate
  // size bytes + header and alignment padding)
  ASSERT(reinterpret_cast<uintptr_t>(m_pos) >=
         reinterpret_cast<uintptr_t>(result));
  m_limit = segment->end();
  ASSERT(m_pos <= m_limit);
  return result;
}

// -----------------------------------------------------------------------------

} /* end namespace memory */
} /* end namespace corevm */

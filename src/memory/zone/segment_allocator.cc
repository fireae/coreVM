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
#include "segment_allocator.h"
#include "common/constants.h"
#include "corevm/macros.h"
#include "segment.h"

#include <algorithm>
#include <cstdlib>

namespace corevm {
namespace memory {

// -----------------------------------------------------------------------------

const size_t SegmentAllocator::kMaxPoolSize = 8ul * KB;

// -----------------------------------------------------------------------------

SegmentAllocator::SegmentAllocator()
  : m_unused_segments_heads(),
    m_unused_segments_sizes(),
    m_unused_segments_max_sizes(),
    m_current_memory_usage(0),
    m_max_memory_usage(0),
    m_current_pool_size(0)
{
  static const size_t kDefaultBucketMaxSize = 5;

  std::fill(m_unused_segments_heads, m_unused_segments_heads + kNumberBuckets,
            nullptr);
  std::fill(m_unused_segments_sizes, m_unused_segments_sizes + kNumberBuckets,
            0);
  std::fill(m_unused_segments_max_sizes,
            m_unused_segments_max_sizes + kNumberBuckets,
            kDefaultBucketMaxSize);
}

// -----------------------------------------------------------------------------

SegmentAllocator::~SegmentAllocator()
{
  clear_pool();
}

// -----------------------------------------------------------------------------

void
SegmentAllocator::configure_segment_pool(size_t max_pool_size)
{
  // The sum of the bytes of one segment of each size.
  static const size_t full_size = (size_t(1) << (kMaxSegmentSizePower + 1)) -
                                  (size_t(1) << kMinSegmentSizePower);
  size_t fits_fully = max_pool_size / full_size;

  // We assume few zones (less than 'fits_fully' many) to be active at the same
  // time. When zones grow regularly, they will keep requesting segments of
  // increasing size each time. Therefore we try to get as many segments with an
  // equal number of segments of each size as possible.
  // The remaining space is used to make more room for an 'incomplete set' of
  // segments beginning with the smaller ones.
  // This code will work best if the max_pool_size is a multiple of the
  // full_size. If max_pool_size is no sum of segment sizes the actual pool
  // size might be smaller then max_pool_size. Note that no actual memory gets
  // wasted though.
  //
  // TODO: Determine better strategy generating a segment sizes
  // distribution that is closer to real/benchmark usecases and uses the given
  // max_pool_size more efficiently.
  size_t total_size = fits_fully * full_size;

  for (size_t power = 0; power < kNumberBuckets; ++power) {
    if (total_size + (size_t(1) << (power + kMinSegmentSizePower)) <=
        max_pool_size) {
      m_unused_segments_max_sizes[power] = fits_fully + 1;
      total_size += size_t(1) << power;
    } else {
      m_unused_segments_max_sizes[power] = fits_fully;
    }
  }
}

// -----------------------------------------------------------------------------

Segment*
SegmentAllocator::get_segment(size_t bytes)
{
  Segment* result = get_segment_from_pool(bytes);
  if (result == nullptr) {
    result = allocate_segment(bytes);
  }

  return result;
}

// -----------------------------------------------------------------------------

Segment*
SegmentAllocator::allocate_segment(size_t bytes)
{
  void* mem = malloc(bytes);
  if (mem) {
    m_current_memory_usage += bytes;
    m_max_memory_usage = std::max(m_max_memory_usage, m_current_memory_usage);
  }
  return new (mem) Segment(bytes);
}

// -----------------------------------------------------------------------------

void
SegmentAllocator::return_segment(Segment* segment)
{
  segment->clear_contents();
  free_segment(segment);
}

// -----------------------------------------------------------------------------

void
SegmentAllocator::free_segment(Segment* segment)
{
  m_current_memory_usage -= segment->size();
  segment->clear_header();
  free(segment);
}

// -----------------------------------------------------------------------------

size_t
SegmentAllocator::current_memory_usage() const
{
  return m_current_memory_usage;
}

// -----------------------------------------------------------------------------

size_t
SegmentAllocator::max_memory_usage() const
{
  return m_max_memory_usage;
}

// -----------------------------------------------------------------------------

size_t
SegmentAllocator::current_pool_size() const
{
  return m_current_pool_size;
}

// -----------------------------------------------------------------------------

Segment*
SegmentAllocator::get_segment_from_pool(size_t requested_size)
{
  if (requested_size > (1 << kMaxSegmentSizePower)) {
    return nullptr;
  }

  size_t power = kMinSegmentSizePower;
  while (requested_size > (static_cast<size_t>(1) << power)) {
    power++;
  }

  power -= kMinSegmentSizePower;

  Segment* segment = m_unused_segments_heads[power];

  if (segment != nullptr) {
    m_unused_segments_heads[power] = segment->next();
    segment->set_next(nullptr);

    m_unused_segments_sizes[power]--;
    m_current_pool_size -= segment->size();
  }

  if (segment) {
#if __DEBUG__
    ASSERT(segment->size() >= requested_size);
#endif
  }

  return segment;
}

// -----------------------------------------------------------------------------

bool
SegmentAllocator::add_segment(Segment* segment)
{
  size_t size = segment->size();

  if (size >= (1 << (kMaxSegmentSizePower + 1))) {
    return false;
  }

  if (size < (1 << kMinSegmentSizePower)) {
    return false;
  }

  size_t power = kMaxSegmentSizePower;

  while (size < (static_cast<size_t>(1) << power)) {
    power--;
  }

#if __DEBUG__
  ASSERT(power >= kMinSegmentSizePower);
#endif

  power -= kMinSegmentSizePower;

  if (m_unused_segments_sizes[power] >= m_unused_segments_max_sizes[power]) {
    return false;
  }

  segment->set_next(m_unused_segments_heads[power]);
  m_unused_segments_heads[power] = segment;
  m_current_pool_size += size;
  m_unused_segments_sizes[power]++;

  return true;
}

// -----------------------------------------------------------------------------

void
SegmentAllocator::clear_pool()
{
  for (size_t power = 0; power <= kMaxSegmentSizePower - kMinSegmentSizePower;
       power++) {
    Segment* current = m_unused_segments_heads[power];
    while (current) {
      Segment* next = current->next();
      free_segment(current);
      current = next;
    }
    m_unused_segments_heads[power] = nullptr;
  }
}

// -----------------------------------------------------------------------------

} /* end namespace memory */
} /* end namespace corevm */

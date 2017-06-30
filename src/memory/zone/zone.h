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
#ifndef COREVM_ZONE_H_
#define COREVM_ZONE_H_

#include "corevm/macros.h"
#include <cstdint>
#include <limits>

namespace corevm {
namespace memory {

/** Forward declarations. */
class Segment;
class SegmentAllocator;

/**
 * The Zone supports very fast allocation of small chunks of memory.
 * The chunks cannot be deallocated individually, but instead
 * the Zone supports deallocating all chunks in one fast operation.
 *
 * Note: There is no need to initialize the Zone; the first time an
 * allocation is attempted, a segment of memory will be requested
 * through the allocator.
 */
class Zone {
public:
  explicit Zone(SegmentAllocator* allocator);

  ~Zone();

  /**
   * Allocate 'size' bytes of memory in the Zone; expands the Zone by
   * allocating new segments of memory on demand using malloc().
   */
  void* allocate(size_t size);

  /**
   * Allocates memories for `n` numbers of type `T`.
   */
  template <typename T>
  T*
  allocate_n(size_t n)
  {
#if __DEBUG__
    ASSERT(n < std::numeric_limits<size_t>::max() / sizeof(T));
#endif
    return static_cast<T*>(this->allocate(n * sizeof(T)));
  }

  /**
   * Returns true if more memory has been allocated in zones than
   * the limit allows.
   */
  bool excess_allocation() const;

  size_t allocation_size() const;

  SegmentAllocator* allocator() const;

private:
  /**
   * All pointers returned from `allocate()` are 8-byte aligned.
   */
  static const size_t kAlignmentInBytes;

  /**
   * Never allocate segments smaller than this size in bytes.
   */
  static const size_t kMinimumSegmentSize;

  /**
   * Never allocate segments larger than this size in bytes.
   */
  static const size_t kMaximumSegmentSize;

  /**
   * Report zone excess when allocation exceeds this limit.
   */
  static const size_t kExcessLimit;

  /**
   * Deletes all objects and free all memory allocated in the Zone.
   */
  void delete_all();

  /**
   * The number of bytes allocated in this zone so far.
   */
  size_t m_allocation_size;

  /**
   * The number of bytes allocated in segments.
   *
   * Note that this number includes memory allocated from the OS
   * but not yet allocated from the zone.
   */
  size_t m_segment_bytes_allocated;

  /**
   * Expand the Zone to hold at least 'size' more bytes and allocate
   * the bytes. Returns the address of the newly allocated chunk of
   * memory in the Zone. Should only be called if there isn't enough
   * room in the Zone already.
   */
  uint8_t* expand(size_t size);

  /**
   * Creates a new segment, sets it size, and pushes it to the front
   * of the segment chain. Returns the new segment.
   */
  inline Segment* create_new_segment(size_t requested_size);

  /**
   * The free region in the current (front) segment is represented as
   * the half-open interval [position, limit). The 'position' variable
   * is guaranteed to be aligned as dictated by kAlignment.
   */
  uint8_t* m_pos;
  uint8_t* m_limit;

  SegmentAllocator* m_allocator;

  Segment* m_segment_head;
};

} /* end namespace memory */
} /* end namespace corevm */

#endif /* COREVM_ZONE_H_ */

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
#ifndef COREVM_SEGMENT_ALLOCATOR_H_
#define COREVM_SEGMENT_ALLOCATOR_H_

#include <cstring>

namespace corevm {
namespace memory {

/** Forward declaration. */
class Segment;

class SegmentAllocator {
public:
  static const size_t kMaxPoolSize;

  SegmentAllocator();
  ~SegmentAllocator();

  /** Disable copy. */
  SegmentAllocator(const SegmentAllocator&) = delete;
  SegmentAllocator& operator=(const SegmentAllocator&) = delete;

  /**
   * Gets an empty segment from the pool or creates a new one.
   */
  Segment* get_segment(size_t bytes);

  /**
   * Return unneeded segments to either insert them into the pool or
   * release them if the pool is already full or memory pressure is high.
   */
  void return_segment(Segment* memory);

  size_t current_memory_usage() const;
  size_t max_memory_usage() const;

  size_t current_pool_size() const;

  /**
   * Configures the zone segment pool size limits so the pool does not
   * grow bigger than max_pool_size.
   *
   * TODO: Do not accept segments to pool that are larger than
   * their size class requires. Sometimes the zones generate weird segments.
   */
  void configure_segment_pool(size_t max_pool_size);

private:
  static const size_t kMinSegmentSizePower = 13;
  static const size_t kMaxSegmentSizePower = 18;
  static const size_t kNumberBuckets =
    1 + kMaxSegmentSizePower - kMinSegmentSizePower;

  /**
   * Allocates a new segment. Returns nullptr on failed allocation.
   */
  Segment* allocate_segment(size_t bytes);

  void free_segment(Segment* memory);

  /**
   * Returns a segment from the pool of at least the requested size.
   */
  Segment* get_segment_from_pool(size_t requested_size);

  /**
   * Trys to add a segment to the pool.
   * Returns false if the pool is full.
   */
  bool add_segment(Segment* segment);

  /**
   * Empties the pool and puts all its contents onto the garbage stack.
   */
  void clear_pool();

  Segment* m_unused_segments_heads[kNumberBuckets];

  size_t m_unused_segments_sizes[kNumberBuckets];
  size_t m_unused_segments_max_sizes[kNumberBuckets];

  size_t m_current_memory_usage;
  size_t m_max_memory_usage;
  size_t m_current_pool_size;
};

} /* end namespace memory */
} /* end namespace corevm */

#endif /* COREVM_SEGMENT_ALLOCATOR_H_ */

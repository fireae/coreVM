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
#ifndef COREVM_RECYCLING_ZONE_ALLOCATOR_H_
#define COREVM_RECYCLING_ZONE_ALLOCATOR_H_

#include "corevm/macros.h"
#include "zone_allocator.h"
#include <cstddef>

namespace corevm {
namespace memory {

/**
 * Recycling zone allocator that maintains a free list of deallocated chunks
 * to reuse on subsequent allocations.
 *
 * The free list management is purposely very simple and works best for data
 * structures which regularly allocate and free blocks of similar sized memory.
 */
template <typename T> class RecyclingZoneAllocator : public ZoneAllocator<T> {
public:
  template <class O> struct rebind {
    typedef RecyclingZoneAllocator<O> other;
  };

  explicit RecyclingZoneAllocator(Zone* zone)
    : ZoneAllocator<T>(zone), m_free_list(nullptr)
  {
  }

  explicit RecyclingZoneAllocator(const RecyclingZoneAllocator& other)
    : ZoneAllocator<T>(other), m_free_list(nullptr)
  {
  }

  template <typename U>
  RecyclingZoneAllocator(const RecyclingZoneAllocator<U>& other)
    : ZoneAllocator<T>(other), m_free_list(nullptr)
  {
  }

  T*
  allocate(size_t n, const void* hint = 0)
  {
    // Only check top block in free list, since this will be equal to or larger
    // than the other blocks in the free list.
    if (m_free_list && m_free_list->size >= n) {
      T* return_val = reinterpret_cast<T*>(m_free_list);
      m_free_list = m_free_list->next;
      return return_val;
    } else {
      return ZoneAllocator<T>::allocate(n, hint);
    }
  }

  void
  deallocate(T* p, size_t n)
  {
    if ((sizeof(T) * n < sizeof(_freeblock_t))) {
      return;
    }

    // Only add block to free_list if it is equal or larger than previous block
    // so that allocation stays O(1) only having to look at the top block.
    if (!m_free_list || m_free_list->size <= n) {
      // Store the free-list within the block being deallocated.
      ASSERT((sizeof(T) * n >= sizeof(_freeblock_t)));
      _freeblock_t* new_block = reinterpret_cast<_freeblock_t*>(p);

      new_block->size = n;
      new_block->next = m_free_list;
      m_free_list = new_block;
    }
  }

private:
  template <typename U> friend class RecyclingZoneAllocator;

  struct _freeblock_t {
    _freeblock_t* next;
    size_t size;
  };

  _freeblock_t* m_free_list;
};

} /* end namespace memory */
} /* end namespace corevm */

#endif /* COREVM_RECYCLING_ZONE_ALLOCATOR_H_ */

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
#ifndef COREVM_ZONE_ALLOCATOR_H_
#define COREVM_ZONE_ALLOCATOR_H_

#include "zone.h"

#include <limits>

namespace corevm {
namespace memory {

/**
 * Abstraction of region-based memory allocator.
 *
 * Encapsulates all the necessary components to achieve region-based
 * memory allocations that are efficient for allocation requests of
 * small chunks.
 *
 * NOTE: This class is currently NOT thread-safe. In order to make it thread
 * safe, all of its substituient components need to be made thread-safe.
 */
template <class T> class ZoneAllocator {
public:
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T value_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  template <class U> struct rebind {
    typedef ZoneAllocator<U> other;
  };

  explicit ZoneAllocator(Zone* zone) : m_zone(zone)
  {
  }

  explicit ZoneAllocator(const ZoneAllocator<T>& other)
    : ZoneAllocator<T>(other.m_zone)
  {
  }

  template <typename U>
  ZoneAllocator(const ZoneAllocator<U>& other) : ZoneAllocator<T>(other.m_zone)
  {
  }

  template <typename U> friend class ZoneAllocator;

  T*
  address(T& v) const
  {
    return &v;
  }

  const T*
  address(const T& v) const
  {
    return &v;
  }

  T*
  allocate(size_t n, const void* /* hint */ = 0)
  {
    return static_cast<T*>(m_zone->allocate_n<T>(static_cast<int>(n)));
  }

  void
  deallocate(T* /* p */, size_t)
  {
  }

  size_t
  max_size() const
  {
    return std::numeric_limits<int>::max() / sizeof(T);
  }

  template <typename U, typename... Args>
  void
  construct(U* p, Args&&... args)
  {
    void* ptr = const_cast<void*>(static_cast<const void*>(p));
    new (ptr) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void
  destroy(U* p)
  {
    p->~U();
  }

  bool
  operator==(ZoneAllocator const& other) const
  {
    return m_zone == other.m_zone;
  }

  bool
  operator!=(ZoneAllocator const& other) const
  {
    return !operator==(this, other);
  }

  Zone*
  zone()
  {
    return m_zone;
  }

private:
  Zone* m_zone;
};

} /* end namespace memory */
} /* end namespace corevm */

#endif /* COREVM_ZONE_ALLOCATOR_H_ */

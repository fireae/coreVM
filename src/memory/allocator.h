/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2015 Yanzheng Li

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
#ifndef COREVM_MEMORY_ALLOCATOR_H_
#define COREVM_MEMORY_ALLOCATOR_H_

#include "corevm/macros.h"

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <new>

#include <sys/types.h>


namespace corevm {


namespace memory {


template<class allocation_scheme>
class allocator
{
public:
  explicit allocator(uint64_t);

  ~allocator();

  /* Allocators should not be copyable. */
  allocator(const allocator&) = delete;
  allocator& operator=(const allocator&) = delete;

  void* allocate(size_t) noexcept;

  /**
   * Allocates `N` chunks of memory each of size `size`.
   * Each chunk of memory can be deallocated individually.
   */
  void* allocate_n(size_t N, size_t size) noexcept;

  int deallocate(void*) noexcept;

  void debug_print() const noexcept;

  uint64_t base_addr() const noexcept;

  uint64_t total_size() const noexcept;

private:
  uint64_t m_total_size;
  uint64_t m_allocated_size;
  void* m_heap;
  allocation_scheme m_allocation_scheme;
};


// -----------------------------------------------------------------------------

template<class allocation_scheme>
corevm::memory::allocator<allocation_scheme>::allocator(uint64_t total_size):
  m_total_size(total_size),
  m_allocated_size(0),
  m_heap(nullptr),
  m_allocation_scheme(allocation_scheme(m_total_size))
{
  void* mem = malloc(m_total_size);

  if (!mem)
  {
    THROW(std::bad_alloc());
  }

  m_heap = mem;
}

// -----------------------------------------------------------------------------

template<class allocation_scheme>
corevm::memory::allocator<allocation_scheme>::~allocator()
{
  if (m_heap)
  {
    free(m_heap);
    m_heap = nullptr;
  }
}

// -----------------------------------------------------------------------------

template<class allocation_scheme>
uint64_t
corevm::memory::allocator<allocation_scheme>::base_addr() const noexcept
{
  return static_cast<uint64_t>((uint8_t*)m_heap - (uint8_t*)NULL);
}

// -----------------------------------------------------------------------------

template<class allocation_scheme>
uint64_t
corevm::memory::allocator<allocation_scheme>::total_size() const noexcept
{
  return m_total_size;
}

// -----------------------------------------------------------------------------

template<class allocation_scheme>
void*
corevm::memory::allocator<allocation_scheme>::allocate(size_t size) noexcept
{
  void* ptr = nullptr;

  if (size > m_total_size)
  {
    return ptr;
  }

  if (!(size > 0))
  {
    return ptr;
  }

  ssize_t offset = m_allocation_scheme.malloc(size);

  if (offset >= 0)
  {
    uint8_t* base = static_cast<uint8_t*>(m_heap);
    ptr = base + static_cast<uint32_t>(offset);
    m_allocated_size += static_cast<uint64_t>(size);

#if __DEBUG__
    ASSERT(m_allocated_size <= m_total_size);
#endif
  }

  return ptr;
}

// -----------------------------------------------------------------------------

template<class allocation_scheme>
void*
corevm::memory::allocator<allocation_scheme>::allocate_n(size_t num, size_t size) noexcept
{
  void* ptr = nullptr;

  size_t alloc_size = size * num;

  if (alloc_size > m_total_size)
  {
    return ptr;
  }

  if (!(alloc_size > 0))
  {
    return ptr;
  }

  ssize_t offset = m_allocation_scheme.calloc(num, size);

  if (offset >= 0)
  {
    uint8_t* base = static_cast<uint8_t*>(m_heap);
    ptr = base + static_cast<uint32_t>(offset);
    m_allocated_size += static_cast<uint64_t>(alloc_size);

#if __DEBUG__
    ASSERT(m_allocated_size <= m_total_size);
#endif
  }

  return ptr;
}

// -----------------------------------------------------------------------------

template<class allocation_scheme>
int
corevm::memory::allocator<allocation_scheme>::deallocate(void* ptr) noexcept
{
  int res = -1;

  if (ptr == nullptr)
  {
    return res;
  }

  uint8_t* ptr_ = static_cast<uint8_t*>(ptr);
  uint8_t* heap_ = static_cast<uint8_t*>(m_heap);

  size_t offset = static_cast<size_t>(ptr_ - heap_);
  ssize_t size = m_allocation_scheme.free(offset);

  if (size > 0)
  {
    memset(ptr, 0, static_cast<uint32_t>(size));
    m_allocated_size -= static_cast<uint64_t>(size);

#if __DEBUG__
    ASSERT(m_allocated_size <= m_total_size);
#endif

    res = 1;
  }

  return res;
}

// -----------------------------------------------------------------------------

template<class allocation_scheme>
void
corevm::memory::allocator<allocation_scheme>::debug_print() const noexcept
{
  uint32_t base = static_cast<uint8_t*>(m_heap) - static_cast<uint8_t*>(NULL);
  m_allocation_scheme.debug_print(base);
}

// -----------------------------------------------------------------------------


} /* end namespace memory */


} /* end namespace corevm */


#endif /* COREVM_MEMORY_ALLOCATOR_H_ */

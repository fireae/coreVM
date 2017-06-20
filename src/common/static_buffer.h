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
#ifndef COREVM_STATIC_BUFFER_H_
#define COREVM_STATIC_BUFFER_H_

#include <cstdlib>
#include <cstring>
#include <utility>

namespace corevm {
namespace common {

template <typename T, size_t capacity> class static_buffer {
public:
  explicit static_buffer(void* ptr) : m_ptr(ptr), m_size(0)
  {
  }

  inline size_t
  size() const
  {
    return m_size;
  }

  inline bool
  empty() const
  {
    return m_size == 0;
  }

  inline bool
  full() const
  {
    return m_size == capacity;
  }

  T*
  push(const T& val)
  {
    if (full()) {
      return nullptr;
    }

    T* slot = (reinterpret_cast<T*>(m_ptr) + sizeof(T) * (m_size++));

    T tmp(val);
    *(slot) = tmp;

    return slot;
  }

  T*
  push(T&& val)
  {
    if (full()) {
      return nullptr;
    }

    T* slot = (reinterpret_cast<T*>(m_ptr) + sizeof(T) * (m_size++));

    T tmp(std::move(val));
    *(slot) = tmp;

    return slot;
  }

  T*
  back() const
  {
    return reinterpret_cast<T*>(m_ptr) + sizeof(T) * (m_size - 1);
  }

  T*
  pop()
  {
    if (empty()) {
      return nullptr;
    }

    T* popped = (reinterpret_cast<T*>(m_ptr) + sizeof(T) * (--m_size));
    return popped;
  }

  void
  swap_top_two()
  {
    T* ptr = (reinterpret_cast<T*>(m_ptr) + sizeof(T) * m_size);
    ptr -= sizeof(T);
    T* ptr1 = ptr;
    ptr -= sizeof(T);
    T* ptr2 = ptr;
    std::swap(*ptr1, *ptr2);
  }

  T*
  element_at(size_t i)
  {
    return reinterpret_cast<T*>(m_ptr) + sizeof(T) * i;
  }

private:
  void* m_ptr;
  size_t m_size;
};

} /* end namespace common */
} /* end namespace corevm */

#endif /* COREVM_STATIC_BUFFER_H_ */

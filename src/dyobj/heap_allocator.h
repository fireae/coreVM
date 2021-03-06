/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2016 Yanzheng Li

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
#ifndef COREVM_HEAP_ALLOCATOR_H_
#define COREVM_HEAP_ALLOCATOR_H_

#include "dyobj/common.h"
#include "memory/allocation_policy.h"

#include <sneaker/allocator/object_traits.h>

#include <cstdint>

namespace corevm {
namespace dyobj {

using sneaker::allocator::object_traits;

template <typename T, typename CoreAllocatorType>
class HeapAllocator : public memory::AllocationPolicy<T, CoreAllocatorType>,
                      public object_traits<T> {
private:
  using AllocationPolicyType = memory::AllocationPolicy<T, CoreAllocatorType>;

public:
  using value_type = typename AllocationPolicyType::value_type;
  using pointer = typename AllocationPolicyType::pointer;
  using const_pointer = typename AllocationPolicyType::const_pointer;
  using reference = typename AllocationPolicyType::reference;
  using const_reference = typename AllocationPolicyType::const_reference;
  using size_type = typename AllocationPolicyType::size_type;
  using difference_type = typename AllocationPolicyType::difference_type;

  HeapAllocator();
  explicit HeapAllocator(uint64_t);
  ~HeapAllocator();

  HeapAllocator(HeapAllocator const&);

  template <typename U, typename OtherCoreAllocatorType>
  HeapAllocator(HeapAllocator<U, OtherCoreAllocatorType> const&) = delete;
};

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType>
HeapAllocator<T, CoreAllocatorType>::HeapAllocator()
  : AllocationPolicyType(COREVM_DEFAULT_HEAP_SIZE)
{
  // Do nothing here.
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType>
HeapAllocator<T, CoreAllocatorType>::HeapAllocator(uint64_t total_size)
  : AllocationPolicyType(total_size)
{
  // Do nothing here.
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType>
HeapAllocator<T, CoreAllocatorType>::~HeapAllocator()
{
  // Do nothing here.
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType>
HeapAllocator<T, CoreAllocatorType>::HeapAllocator(
  HeapAllocator<T, CoreAllocatorType> const& other)
  : AllocationPolicyType(other.total_size())
{
  // Do nothing here.
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType>
inline bool
operator==(HeapAllocator<T, CoreAllocatorType> const& lhs,
           HeapAllocator<T, CoreAllocatorType> const& rhs)
{
  return operator==(
           static_cast<memory::AllocationPolicy<T, CoreAllocatorType>>(lhs),
           static_cast<memory::AllocationPolicy<T, CoreAllocatorType>>(rhs)) &&
         lhs.total_size() == rhs.total_size();
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType, typename U,
          typename OtherCoreAllocatorType>
inline bool
operator==(HeapAllocator<T, CoreAllocatorType> const& lhs,
           HeapAllocator<U, OtherCoreAllocatorType> const& rhs)
{
  return operator==(
    static_cast<memory::AllocationPolicy<T, CoreAllocatorType>>(lhs),
    static_cast<memory::AllocationPolicy<U, OtherCoreAllocatorType>>(rhs));
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType, typename other_allocator_type>
inline bool
operator==(HeapAllocator<T, CoreAllocatorType> const& lhs,
           other_allocator_type const& rhs)
{
  return operator==(
    static_cast<memory::AllocationPolicy<T, CoreAllocatorType>>(lhs), rhs);
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType>
inline bool
operator!=(HeapAllocator<T, CoreAllocatorType> const& lhs,
           HeapAllocator<T, CoreAllocatorType> const& rhs)
{
  return !operator==(lhs, rhs);
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType, typename U,
          typename OtherCoreAllocatorType>
inline bool
operator!=(HeapAllocator<T, CoreAllocatorType> const& lhs,
           HeapAllocator<U, OtherCoreAllocatorType> const& rhs)
{
  return !operator==(lhs, rhs);
}

// -----------------------------------------------------------------------------

template <typename T, typename CoreAllocatorType, typename OtherAllocatorType>
inline bool
operator!=(HeapAllocator<T, CoreAllocatorType> const& lhs,
           OtherAllocatorType const& rhs)
{
  return !operator==(lhs, rhs);
}

// -----------------------------------------------------------------------------

} /* end namespace dyobj */
} /* end namespace corevm */

#endif /* COREVM_HEAP_ALLOCATOR_H_ */

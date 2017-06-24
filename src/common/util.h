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
#ifndef COREVM_COMMON_UTILS_
#define COREVM_COMMON_UTILS_

#include "corevm/macros.h"

#define IS_POWER_OF_TWO(x) ((x) != 0 && (((x) & ((x)-1)) == 0))

/**
 * Compute the 0-relative offset of some absolute value x of type T.
 * This allows conversion of Addresses and integral types into
 * 0-relative int offsets.
 */
template <typename T>
inline intptr_t
OffsetFrom(T x)
{
  return x - static_cast<T>(0);
}

/**
 * Compute the absolute value of type T for some 0-relative offset x.
 * This allows conversion of 0-relative int offsets into addresses (uint8_t*)
 * and integral types.
 */
template <typename T>
inline T
AddressFrom(intptr_t x)
{
  return static_cast<T>(static_cast<T>(0) + x);
}

/**
 * Return the largest multiple of m which is <= x.
 */
template <typename T>
inline T
RoundDown(T x, intptr_t m)
{
#if __DEBUG__
  ASSERT(IS_POWER_OF_TWO(m));
#endif
  return AddressFrom<T>(OffsetFrom(x) & -m);
}

/**
 * Return the smallest multiple of m which is >= x.
 */
template <typename T>
inline T
RoundUp(T x, intptr_t m)
{
  return RoundDown<T>(static_cast<T>(x + m - 1), m);
}

/**
 * Checks if a given value satisfies the specified alignment.
 */
template <typename T, typename U>
inline bool
IsAligned(T value, U alignment)
{
  return (value & (alignment - 1)) == 0;
}

/**
 * Returns true if (addr + offset) is aligned.
 */
inline bool
IsAddressAligned(uint8_t* addr, intptr_t alignment, int offset = 0)
{
  intptr_t offs = OffsetFrom(addr + offset);
  return IsAligned(offs, alignment);
}

#endif /* COREVM_COMMON_UTILS_ */

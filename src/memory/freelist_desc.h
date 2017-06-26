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
#ifndef COREVM_FREELIST_DESC_H_
#define COREVM_FREELIST_DESC_H_

#include <cstddef>
#include <cstdint>

namespace corevm {
namespace memory {

typedef struct FreeListDescriptor {
  FreeListDescriptor(uint32_t start_index_, uint32_t end_index_,
                     uint32_t current_index_);

  uint32_t start_index;
  uint32_t end_index;
  uint32_t current_index; // index points to the first free block in the list.
} FreeListDescriptor;

// -----------------------------------------------------------------------------

/**
 * Determines if the given freelist is large enough to hold
 * `n` blocks.
 *
 * `n` has to be greater than 0.
 */
inline bool
is_free_list_available(const FreeListDescriptor& descriptor, size_t n)
{
  return descriptor.current_index + (n - 1) <= descriptor.end_index;
}

// -----------------------------------------------------------------------------

/**
 * Determines if the given index has been allocated in the freelist provided.
 */
inline bool
is_allocated_in_free_list(const FreeListDescriptor& descriptor, uint32_t index)
{
  return index >= descriptor.start_index && index < descriptor.current_index;
}

// -----------------------------------------------------------------------------

/**
 * Determines if the given freelist is empty.
 */
inline bool
is_empty_free_list(const FreeListDescriptor& descriptor)
{
  return descriptor.current_index == descriptor.start_index;
}

// -----------------------------------------------------------------------------

} /* end namespace memory */
} /* end namespace corevm */

#endif /* COREVM_FREELIST_DESC_H_ */

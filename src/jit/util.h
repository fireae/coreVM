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
#ifndef COREVM_JIT_UTIL_H_
#define COREVM_JIT_UTIL_H_

#include "runtime_value.h"
#include "runtime_value_type.h"

#include <llvm/ExecutionEngine/GenericValue.h>

namespace corevm {
namespace jit {

/**
 * Convert an instance of `RuntimeValue` to the `llvm::GenericValue` equivalent,
 * given its type specification.
 */
llvm::GenericValue convert_to_llvm_generic_value(const RuntimeValue&,
                                                 const RuntimeValueType&);

/**
 * Convert an instance of `llvm::GenericValue` to the `RuntimeValue` equivalent,
 * given its type specification.
 */
RuntimeValue convert_to_runtime_value(const llvm::GenericValue&,
                                      const RuntimeValueType&);

} /* end namespace jit */
} /* end namespace corevm */

#endif /* COREVM_JIT_UTIL_H_ */

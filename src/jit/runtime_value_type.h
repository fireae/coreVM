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
#ifndef COREVM_RUNTIME_VALUE_TYPE_H_
#define COREVM_RUNTIME_VALUE_TYPE_H_

#include "types/variant/variant.h"
#include <cstdint>
#include <vector>


namespace corevm {
namespace jit {

/**
 * Represents type of primitive runtime values.
 */
enum class ValueType : uint8_t
{
  ValueTypePtr = 0x01,
  ValueTypeInt8,
  ValueTypeInt16,
  ValueTypeInt32,
  ValueTypeInt64,
  ValueTypeUInt8,
  ValueTypeUInt16,
  ValueTypeUInt32,
  ValueTypeUInt64,
  ValueTypeSPF,
  ValueTypeDPF
};

struct AggregateType;

/**
 * Represents type of generic runtime values.
 */
typedef corevm::types::variant::variant<ValueType, AggregateType> RuntimeValueType;

/**
 * Represents type of aggregate runtime values.
 */
struct AggregateType
{
  // TODO: consider using `llvm::SmallVector<>` here.
  std::vector<RuntimeValueType> types;
};

/**
 * Evaluates the equality between two instances of `AggregateType`.
 */
bool operator==(const AggregateType& lhs, const AggregateType& rhs);

/**
 * Evaluates the inequality between two instances of `AggregateType`.
 */
bool operator!=(const AggregateType& lhs, const AggregateType& rhs);

} /* end namespace jit */
} /* end namespace corevm */

#endif /* COREVM_RUNTIME_VALUE_TYPE_H_ */

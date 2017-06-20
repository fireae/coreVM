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
#include "util.h"

#if defined(__clang__) and __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

namespace corevm {
namespace jit {

// -----------------------------------------------------------------------------

static llvm::APInt
create_integer_value(const llvm::APInt& src, const jit::ValueType value_type)
{
  switch (value_type) {
  case ValueType::ValueTypeInt8:
    return llvm::APInt(8, *src.getRawData(), true);
  case ValueType::ValueTypeInt16:
    return llvm::APInt(16, *src.getRawData(), true);
  case ValueType::ValueTypeInt32:
    return llvm::APInt(32, *src.getRawData(), true);
  case ValueType::ValueTypeInt64:
    return llvm::APInt(64, *src.getRawData(), true);
  case ValueType::ValueTypeUInt8:
    return llvm::APInt(8, *src.getRawData(), false);
  case ValueType::ValueTypeUInt16:
    return llvm::APInt(16, *src.getRawData(), false);
  case ValueType::ValueTypeUInt32:
    return llvm::APInt(32, *src.getRawData(), false);
  case ValueType::ValueTypeUInt64:
    return llvm::APInt(64, *src.getRawData(), false);
  default:
    return llvm::APInt(64, 0, false);
  }
}

// -----------------------------------------------------------------------------

static void
convert_to_llvm_generic_value(const RuntimeValue& runtime_value,
                              const RuntimeValueType& runtime_value_type,
                              llvm::GenericValue& generic_value)
{
  if (runtime_value_type.is<jit::ValueType>()) {
    const auto value_type = runtime_value_type.get<jit::ValueType>();

    switch (value_type) {
    case ValueType::ValueTypePtr:
      generic_value.PointerVal = runtime_value.PointerVal;
      break;
    case ValueType::ValueTypeInt8:
    case ValueType::ValueTypeInt16:
    case ValueType::ValueTypeInt32:
    case ValueType::ValueTypeInt64:
    case ValueType::ValueTypeUInt8:
    case ValueType::ValueTypeUInt16:
    case ValueType::ValueTypeUInt32:
    case ValueType::ValueTypeUInt64:
      generic_value.IntVal =
        create_integer_value(runtime_value.IntVal, value_type);
      break;
    case ValueType::ValueTypeSPF:
      generic_value.DoubleVal = runtime_value.FloatVal;
      break;
    case ValueType::ValueTypeDPF:
      generic_value.DoubleVal = runtime_value.DoubleVal;
      break;
    default:
      generic_value.IntVal = 0;
      break;
    }
  } else if (runtime_value_type.is<jit::AggregateType>()) {
    const auto& aggregate_val = runtime_value.AggregateVal;
    const auto& aggregate_type = runtime_value_type.get<jit::AggregateType>();
    generic_value.AggregateVal.resize(aggregate_val.size());

    for (size_t i = 0; i < aggregate_val.size(); ++i) {
      convert_to_llvm_generic_value(aggregate_val[i],
                                    aggregate_type.types.at(i),
                                    generic_value.AggregateVal[i]);
    }
  }
}

// -----------------------------------------------------------------------------

static void
convert_to_runtime_value(const llvm::GenericValue& generic_value,
                         const RuntimeValueType& runtime_value_type,
                         RuntimeValue& runtime_value)
{
  if (runtime_value_type.is<jit::ValueType>()) {
    const auto value_type = runtime_value_type.get<jit::ValueType>();

    switch (value_type) {
    case ValueType::ValueTypePtr:
      runtime_value.PointerVal = generic_value.PointerVal;
      break;
    case ValueType::ValueTypeInt8:
    case ValueType::ValueTypeInt16:
    case ValueType::ValueTypeInt32:
    case ValueType::ValueTypeInt64:
    case ValueType::ValueTypeUInt8:
    case ValueType::ValueTypeUInt16:
    case ValueType::ValueTypeUInt32:
    case ValueType::ValueTypeUInt64:
      runtime_value.IntVal =
        create_integer_value(generic_value.IntVal, value_type);
      break;
    case ValueType::ValueTypeSPF:
      runtime_value.FloatVal = static_cast<float>(generic_value.DoubleVal);
      break;
    case ValueType::ValueTypeDPF:
      runtime_value.DoubleVal = generic_value.DoubleVal;
      break;
    default:
      runtime_value.IntVal = 0;
      break;
    }
  } else if (runtime_value_type.is<jit::AggregateType>()) {
    const auto& aggregate_val = generic_value.AggregateVal;
    const auto& aggregate_type = runtime_value_type.get<jit::AggregateType>();
    runtime_value.AggregateVal.resize(aggregate_val.size());

    for (size_t i = 0; i < aggregate_val.size(); ++i) {
      convert_to_runtime_value(aggregate_val[i], aggregate_type.types.at(i),
                               runtime_value.AggregateVal[i]);
    }
  }
}

// -----------------------------------------------------------------------------

llvm::GenericValue
convert_to_llvm_generic_value(const RuntimeValue& runtime_value,
                              const RuntimeValueType& runtime_value_type)
{
  llvm::GenericValue res;
  convert_to_llvm_generic_value(runtime_value, runtime_value_type, res);
  return res;
}

// -----------------------------------------------------------------------------

RuntimeValue
convert_to_runtime_value(const llvm::GenericValue& generic_value,
                         const RuntimeValueType& runtime_value_type)
{
  RuntimeValue res;
  convert_to_runtime_value(generic_value, runtime_value_type, res);
  return res;
}

// -----------------------------------------------------------------------------

} /* end namespace jit */
} /* end namespace corevm */

#if defined(__clang__) and __clang__
#pragma clang diagnostic pop
#endif

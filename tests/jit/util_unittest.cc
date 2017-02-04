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
#include "jit/util.h"

#include <gtest/gtest.h>


// -----------------------------------------------------------------------------

class JITUtilUnitTest : public ::testing::Test {};

// -----------------------------------------------------------------------------

using namespace corevm;

// -----------------------------------------------------------------------------

TEST_F(JITUtilUnitTest, TestConvertSimpleTypeValueToLLVMEquivalent)
{
  jit::RuntimeValueType runtime_value_type(jit::ValueType::ValueTypeUInt64);
  jit::RuntimeValue runtime_value;
  const int int_val = 1;
  runtime_value.IntVal = int_val;

  const llvm::GenericValue generic_value = jit::convert_to_llvm_generic_value(
    runtime_value, runtime_value_type);

  ASSERT_EQ(int_val, generic_value.IntVal);
}

// -----------------------------------------------------------------------------

TEST_F(JITUtilUnitTest, TestConvertLLVMTypeValueToRuntimeValueEquivalent)
{
  jit::RuntimeValueType runtime_value_type(jit::ValueType::ValueTypeUInt64);
  llvm::GenericValue generic_value;
  const int int_val = 1;
  generic_value.IntVal = int_val;

  const jit::RuntimeValue runtime_value = jit::convert_to_runtime_value(
    generic_value, runtime_value_type);

  ASSERT_EQ(int_val, runtime_value.IntVal);
}

// -----------------------------------------------------------------------------

TEST_F(JITUtilUnitTest, TestConvertAggregateTypeValueToLLVMEquivalent)
{
  jit::AggregateType aggregate_type;

  aggregate_type.types.push_back(jit::ValueType::ValueTypeUInt64);
  aggregate_type.types.push_back(jit::ValueType::ValueTypeDPF);

  jit::RuntimeValueType runtime_value_type(aggregate_type);

  jit::RuntimeValue runtime_value;
  runtime_value.AggregateVal.resize(2);
  runtime_value.AggregateVal[0].IntVal = 1;
  runtime_value.AggregateVal[1].DoubleVal = 3.14;

  const llvm::GenericValue generic_value = jit::convert_to_llvm_generic_value(
    runtime_value, runtime_value_type);

  ASSERT_EQ(aggregate_type.types.size(), generic_value.AggregateVal.size());

  ASSERT_EQ(1, generic_value.AggregateVal[0].IntVal);
  ASSERT_EQ(3.14, generic_value.AggregateVal[1].DoubleVal);
}

// -----------------------------------------------------------------------------

TEST_F(JITUtilUnitTest, TestConvertLLVMAggregateTypeValueToRuntimeValueEquivalent)
{
  jit::AggregateType aggregate_type;

  aggregate_type.types.push_back(jit::ValueType::ValueTypeUInt64);
  aggregate_type.types.push_back(jit::ValueType::ValueTypeDPF);

  jit::RuntimeValueType runtime_value_type(aggregate_type);

  llvm::GenericValue generic_value;

  generic_value.AggregateVal.resize(2);
  generic_value.AggregateVal[0].IntVal = 1;
  generic_value.AggregateVal[1].DoubleVal = 3.14;

  const jit::RuntimeValue runtime_value = jit::convert_to_runtime_value(
    generic_value, runtime_value_type);

  ASSERT_EQ(aggregate_type.types.size(), runtime_value.AggregateVal.size());

  ASSERT_EQ(1, runtime_value.AggregateVal[0].IntVal);
  ASSERT_EQ(3.14, runtime_value.AggregateVal[1].DoubleVal);
}

// -----------------------------------------------------------------------------

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
#include "jit/runtime_value.h"
#include "jit/runtime_value_type.h"

#include <gtest/gtest.h>


// -----------------------------------------------------------------------------

class RuntimeValueUnitTest : public ::testing::Test {};

// -----------------------------------------------------------------------------

using namespace corevm;

// -----------------------------------------------------------------------------

TEST_F(RuntimeValueUnitTest, TestRuntimeValueTypeDefaultInitialization)
{
  jit::RuntimeValueType value_type;
}

// -----------------------------------------------------------------------------

TEST_F(RuntimeValueUnitTest, TestRuntimeValueTypeInitializeByValueType)
{
  jit::ValueType expected_value_type = jit::ValueType::ValueTypeUInt64;

  jit::RuntimeValueType value_type(expected_value_type);

  ASSERT_EQ(true, value_type.is<jit::ValueType>());

  jit::ValueType actual_value_type = value_type.get<jit::ValueType>();

  ASSERT_EQ(expected_value_type, actual_value_type);
}

// -----------------------------------------------------------------------------

TEST_F(RuntimeValueUnitTest, TestRuntimeValueTypeSetOnValueType)
{
  jit::ValueType expected_value_type = jit::ValueType::ValueTypeUInt64;

  jit::RuntimeValueType value_type;

  value_type = expected_value_type;

  ASSERT_EQ(true, value_type.is<jit::ValueType>());

  jit::ValueType actual_value_type = value_type.get<jit::ValueType>();

  ASSERT_EQ(expected_value_type, actual_value_type);
}

// -----------------------------------------------------------------------------

TEST_F(RuntimeValueUnitTest, TestRuntimeValueTypeInitializeByAggregateType)
{
  jit::AggregateType aggregate_type;

  aggregate_type.types.push_back(jit::ValueType::ValueTypeUInt64);
  aggregate_type.types.push_back(jit::ValueType::ValueTypePtr);

  jit::RuntimeValueType value_type(aggregate_type);

  ASSERT_EQ(true, value_type.is<jit::AggregateType>());

  jit::AggregateType actual_aggregate_type = value_type.get<jit::AggregateType>();

  ASSERT_EQ(aggregate_type, actual_aggregate_type);
}

// -----------------------------------------------------------------------------

TEST_F(RuntimeValueUnitTest, TestRuntimeValueTypeSetOnAggregateType)
{
  jit::AggregateType aggregate_type;

  aggregate_type.types.push_back(jit::ValueType::ValueTypeUInt64);
  aggregate_type.types.push_back(jit::ValueType::ValueTypePtr);

  jit::RuntimeValueType value_type;

  value_type = aggregate_type;

  ASSERT_EQ(true, value_type.is<jit::AggregateType>());

  jit::AggregateType actual_aggregate_type = value_type.get<jit::AggregateType>();

  ASSERT_EQ(aggregate_type, actual_aggregate_type);
}

// -----------------------------------------------------------------------------

TEST_F(RuntimeValueUnitTest, TestRuntimeValueTypeAsNestedAggregateType)
{
  jit::AggregateType parent_aggregate_type;

  jit::AggregateType child1_aggregate_type;
  jit::AggregateType child2_aggregate_type;

  const auto simple_type_1 = jit::ValueType::ValueTypeUInt64;
  const auto simple_type_2 = jit::ValueType::ValueTypePtr;

  child1_aggregate_type.types.push_back(jit::ValueType::ValueTypeUInt64);
  child2_aggregate_type.types.push_back(simple_type_2);

  parent_aggregate_type.types.push_back(child1_aggregate_type);
  parent_aggregate_type.types.push_back(child2_aggregate_type);

  jit::RuntimeValueType value_type(parent_aggregate_type);

  ASSERT_EQ(true, value_type.is<jit::AggregateType>());

  jit::AggregateType actual_parent_aggregate_type =
    value_type.get<jit::AggregateType>();

  ASSERT_EQ(2, actual_parent_aggregate_type.types.size());

  ASSERT_EQ(true, actual_parent_aggregate_type.types[0].is<jit::AggregateType>());
  ASSERT_EQ(true, actual_parent_aggregate_type.types[1].is<jit::AggregateType>());

  auto actual_child1_aggregate_type =
    actual_parent_aggregate_type.types[0].get<jit::AggregateType>();

  ASSERT_EQ(child1_aggregate_type, actual_child1_aggregate_type);

  auto actual_child2_aggregate_type =
    actual_parent_aggregate_type.types[1].get<jit::AggregateType>();

  ASSERT_EQ(child2_aggregate_type, actual_child2_aggregate_type);

  ASSERT_EQ(1, actual_child1_aggregate_type.types.size());

  const auto& grandchild_type_1 = actual_child1_aggregate_type.types[0];
  ASSERT_EQ(true, grandchild_type_1.is<jit::ValueType>());
  ASSERT_EQ(simple_type_1, grandchild_type_1.get<jit::ValueType>());

  ASSERT_EQ(1, actual_child2_aggregate_type.types.size());

  const auto& grandchild_type_2 = actual_child2_aggregate_type.types[0];
  ASSERT_EQ(true, grandchild_type_2.is<jit::ValueType>());
  ASSERT_EQ(simple_type_2, grandchild_type_2.get<jit::ValueType>());
}

// -----------------------------------------------------------------------------

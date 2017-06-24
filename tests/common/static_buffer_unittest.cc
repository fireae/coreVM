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
#include "common/static_buffer.h"
#include <gtest/gtest.h>
#include <cstdint>

#define TEST_WITH_NATIVE_TYPE_VALUE 0

#if TEST_WITH_NATIVE_TYPE_VALUE
#include "types/types.h"
#include "types/native_type_value.h"
#endif


class StaticBufferUnitTest : public ::testing::Test
{
protected:
  struct MyObject {
    uint32_t ival;
    float fval;
  };

  struct scoped_malloc_guard {
    explicit scoped_malloc_guard(void* ptr) : m_ptr(ptr) {}
    ~scoped_malloc_guard() { if (m_ptr) free(m_ptr); }
  private:
    void* m_ptr;
  };
};

// -----------------------------------------------------------------------------

TEST_F(StaticBufferUnitTest, TestInitialization)
{
  corevm::common::static_buffer<MyObject, 1> buffer(NULL);

  ASSERT_EQ(true, buffer.empty());
  ASSERT_EQ(false, buffer.full());
  ASSERT_EQ(0, buffer.size());
}

// -----------------------------------------------------------------------------

// TODO: [COREVM-614] Fix static buffer unittest
#if 0
TEST_F(StaticBufferUnitTest, TestPushAndPop)
{
  #define BUFFR_CAPACITY 2

  void* ptr = malloc(sizeof(MyObject) * BUFFR_CAPACITY);
  scoped_malloc_guard guard(ptr);

  corevm::common::static_buffer<MyObject, BUFFR_CAPACITY> buffer(ptr);

  ASSERT_EQ(true, buffer.empty());
  ASSERT_EQ(false, buffer.full());
  ASSERT_EQ(0, buffer.size());

  MyObject obj1 { .ival = 1, .fval = 3.14 };
  buffer.push(obj1);

  ASSERT_EQ(1, buffer.size());

  MyObject obj2 { .ival = 2, .fval = 2.718f };
  buffer.push(obj2);

  ASSERT_EQ(false, buffer.empty());
  ASSERT_EQ(true, buffer.full());
  ASSERT_EQ(2, buffer.size());

  MyObject* res = buffer.pop();
  ASSERT_NE(nullptr, res);

  ASSERT_EQ(obj2.ival, res->ival);
  ASSERT_EQ(obj2.fval, res->fval);

  res = buffer.pop();

  ASSERT_EQ(obj1.ival, res->ival);
  ASSERT_EQ(obj1.fval, res->fval);

  ASSERT_EQ(true, buffer.empty());
  ASSERT_EQ(false, buffer.full());
  ASSERT_EQ(0, buffer.size());
}

// -----------------------------------------------------------------------------

TEST_F(StaticBufferUnitTest, TestSwapTopTwo)
{
  #define BUFFR_CAPACITY 2

  void* ptr = malloc(sizeof(MyObject) * BUFFR_CAPACITY);
  scoped_malloc_guard guard(ptr);

  corevm::common::static_buffer<MyObject, BUFFR_CAPACITY> buffer(ptr);

  MyObject obj1 { .ival = 1, .fval = 3.14 };
  buffer.push(obj1);

  MyObject obj2 { .ival = 2, .fval = 2.718f };
  buffer.push(obj2);

  ASSERT_EQ(false, buffer.empty());
  ASSERT_EQ(true, buffer.full());
  ASSERT_EQ(2, buffer.size());

  buffer.swap_top_two();

  MyObject* res = buffer.pop();
  ASSERT_NE(nullptr, res);

  ASSERT_EQ(obj1.ival, res->ival);
  ASSERT_EQ(obj1.fval, res->fval);

  res = buffer.pop();
  ASSERT_NE(nullptr, res);

  ASSERT_EQ(obj2.ival, res->ival);
  ASSERT_EQ(obj2.fval, res->fval);

  ASSERT_EQ(true, buffer.empty());
  ASSERT_EQ(false, buffer.full());
  ASSERT_EQ(0, buffer.size());
}
#endif

// -----------------------------------------------------------------------------

#if TEST_WITH_NATIVE_TYPE_VALUE
TEST_F(StaticBufferUnitTest, TestWithNativeTypeValue)
{
  #define BUFFR_CAPACITY 2

  void* ptr = malloc(sizeof(corevm::types::NativeTypeValue) * BUFFR_CAPACITY);
  scoped_malloc_guard guard(ptr);

  corevm::common::static_buffer<corevm::types::NativeTypeValue, BUFFR_CAPACITY> buffer(ptr);

  corevm::types::NativeTypeValue val1(corevm::types::uint32(32));
  buffer.push(val1);

  corevm::types::NativeTypeValue val2(corevm::types::decimal2(3.14));
  buffer.push(val2);

  ASSERT_EQ(false, buffer.empty());
  ASSERT_EQ(true, buffer.full());
  ASSERT_EQ(2, buffer.size());

  buffer.pop();
  buffer.pop();

  buffer.push(val2);
  buffer.push(val1);
}
#endif

// -----------------------------------------------------------------------------

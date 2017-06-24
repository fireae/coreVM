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
#include <gtest/gtest.h>

#include "memory/zone/zone.h"
#include "memory/zone/zone_allocator.h"
#include "memory/zone/segment_allocator.h"


class ZoneAllocatorUnitTest : public ::testing::Test {
protected:
  class TestClass
  {
  public:
    TestClass(int i, float f) :
     ival(i), fval(f) {}
    int ival;
    float fval;
  };
};


using namespace corevm::memory;

// -----------------------------------------------------------------------------

TEST_F(ZoneAllocatorUnitTest, TestInitialization)
{
  SegmentAllocator accounting_allocator;
  Zone zone(&accounting_allocator);
  ZoneAllocator<int> zone_allocator(&zone);
}

// -----------------------------------------------------------------------------

TEST_F(ZoneAllocatorUnitTest, TestAllocate)
{
  SegmentAllocator accounting_allocator;
  Zone zone(&accounting_allocator);
  ZoneAllocator<ZoneAllocatorUnitTest::TestClass> zone_allocator(&zone);

  auto *ptr = zone_allocator.allocate();

  ASSERT_NE(nullptr, ptr);

  int ival = 8;
  float fval = 3.14f;
  zone_allocator.construct(ptr, ival, fval);

  ASSERT_EQ(ival, ptr->ival);
  ASSERT_EQ(fval, ptr->fval);
}

// -----------------------------------------------------------------------------

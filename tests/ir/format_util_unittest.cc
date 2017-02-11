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
#include "ir/format_util.h"

#include <gtest/gtest.h>

#include <cstdint>


// -----------------------------------------------------------------------------

class IRFormatUtilUnitTest : public ::testing::Test {};

// -----------------------------------------------------------------------------

using namespace corevm;

// -----------------------------------------------------------------------------

TEST_F(IRFormatUtilUnitTest, Test_is_func_defn_option_enabled)
{
  constexpr int64_t val = 1;
  ASSERT_EQ(true,
    ir::is_func_defn_option_enabled(val, ir::FuncDefnOption::CONSTEXPR));

  constexpr int64_t val2 = 0;
  ASSERT_EQ(false,
    ir::is_func_defn_option_enabled(val2, ir::FuncDefnOption::CONSTEXPR));
}

// -----------------------------------------------------------------------------

TEST_F(IRFormatUtilUnitTest, Test_interpret_func_defn_option)
{
  ASSERT_EQ(ir::FuncDefnOption::CONSTEXPR,
    static_cast<ir::FuncDefnOption>(ir::interpret_func_defn_option("constexpr")));

  ASSERT_EQ(ir::FuncDefnOption::INLINE,
    static_cast<ir::FuncDefnOption>(ir::interpret_func_defn_option("inline")));

  ASSERT_EQ(0, ir::interpret_func_defn_option("unknown-option"));
}

// -----------------------------------------------------------------------------

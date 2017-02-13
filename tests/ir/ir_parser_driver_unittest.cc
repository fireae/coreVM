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
#include "ir/ir_parser_driver.h"

#include <gtest/gtest.h>

#include <fstream>


// -----------------------------------------------------------------------------

class IRParserDriverUnitTest : public ::testing::Test
{
protected:
  static const char* IR_STRING;

  void validate_parsed_module(const corevm::IRModule& module)
  {
    ASSERT_EQ("Dummy_IR", module.meta.name); 
    ASSERT_EQ(3, module.types.size());
    ASSERT_EQ("Person", module.types.front().name);
    ASSERT_EQ(3, module.closures.size());
    ASSERT_EQ("createPerson", module.closures.front().name);
  }
};

const char* IRParserDriverUnitTest::IR_STRING = 
  "\"timestamp\" : \"1472959465\""
  "\"author\" : \"Yanzheng Li\""
  "\"format version\" : \"1000\""
  "\"module name\" : \"Dummy_IR\""
  "\"path\" : \"./dummy_ir.ir\""
  "\"target version\" : \"10\""
  ""
  "declare i8 corevm.foundation.memove(i8* dst, i8* src, i64 num)"
  ""
  "type Person {"
    "string name;"
    "ui8 age;"
    "Person* sibling;"
    "Location* address;"
    "array [ 10 * Person ] friends;"
  "}"
  ""
  "def Person* createPerson(string* name, ui8 age) {"
  "entry:"
    "%person = alloca [ auto ] Person*;"
    "setattr string \"age\" %age %person;"
    "%isOld = gte %age ui8 100;"
    "br %isOld [ label #end, label #end ];"
  "end:"
    "ret Person* %person;"
  "}"
  ""
  "[model=cplusplus]"
  "type Location {"
    "string street_address;"
    "string* country;"
    "string zipcode;"
  "}"
  ""
  "def void compute(ui32 lhs_val, dpf rhs_val, array [ 4 * dpf* ]* values) : createPerson [constexpr inline] {"
  "entry:"
    "%sum = add ui64 %lhs_val %rhs_val;"
    "putelement dpf 3.14 %values ui32 2;"
  "}"
  ""
  "def void doNothing(*args, **kwargs) {"
  "}"
  ""
  "type NullType {"
  "}"
  "";

// -----------------------------------------------------------------------------

class IRParserDriverFileBasedUnitTest : public IRParserDriverUnitTest
{
protected:
  static const char* PATH;

  virtual void SetUp()
  {
    std::ofstream f(PATH, std::ios::binary);
    f << IRParserDriverUnitTest::IR_STRING;
    f.close();
  }

  virtual void TearDown()
  {
    remove(PATH);
  }
};

const char* IRParserDriverFileBasedUnitTest::PATH = "Dummy_IR.txt";

// -----------------------------------------------------------------------------

TEST_F(IRParserDriverUnitTest, TestParseFromString)
{
  corevm::ir::IRParserDriver driver;
  const int res = driver.parse_from_string(IR_STRING);

  ASSERT_EQ(0, res);

  const corevm::IRModule& module = driver.module();
  validate_parsed_module(module); 
}

// -----------------------------------------------------------------------------

TEST_F(IRParserDriverFileBasedUnitTest, TestParseFromFile)
{
  corevm::ir::IRParserDriver driver;
  const int res = driver.parse_from_file(PATH);
  ASSERT_EQ(0, res);

  const corevm::IRModule& module = driver.module();
  validate_parsed_module(module); 
}

// -----------------------------------------------------------------------------

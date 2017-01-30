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
#include "ir/disassembler.h"
#include "ir/format.h"
#include "ir/ir_parser_driver.h"

#include <gtest/gtest.h>

#include <string>
#include <sstream>


// -----------------------------------------------------------------------------

class DisassemblerUnitTest : public ::testing::Test
{
protected:
  void assert_ir_disassembling_successful(const char* IR_STRING) const
  {
    corevm::ir::IRParserDriver parser;
    const int res = parser.parse_from_string(IR_STRING);

    ASSERT_EQ(0, res);

    const corevm::IRModule& module = parser.module();

    corevm::ir::Disassembler::Options opts;
    opts.emit_newlines = false;
    corevm::ir::Disassembler disassembler(opts);

    std::stringstream stream;
    disassembler.disassemble(module, stream);

    // NOTE: double-quotes have to be removed for the strings to compare equally.

    std::string actual_str = stream.str();
    actual_str.erase(std::remove(actual_str.begin(), actual_str.end(), '\"'),
      actual_str.end());

    std::string expected_str(IR_STRING);
    expected_str.erase(std::remove(expected_str.begin(), expected_str.end(), '"'),
      expected_str.end());

    ASSERT_EQ(expected_str, actual_str);
  }
};

// -----------------------------------------------------------------------------

TEST_F(DisassemblerUnitTest, TestDisassemble)
{
  const char* IR_STRING =
    "type Person {"
    "    string name;"
    "    ui32 age;"
    "    Location* location;"
    "}"
    ""
    "type Location {"
    "    string address;"
    "    dpf lat;"
    "    dpf lon;"
    "    array [ 10 * Address ] addresses;"
    "}"
    ""
    "type Address {"
    "    string street;"
    "    string city;"
    "    string state;"
    "    string country;"
    "    array [ 2 * string ]* zipcodes;"
    "}"
    ""
    "def Person* main() {"
    "entry:"
    "    %person = call Person* string \"createPerson\" ui32 21;"
    "    ret Person* %person;"
    "}"
    ""
    "def Person* createPerson(ui32 age) {"
    "entry:"
    "    %person = alloca [ auto ] Person*;"
    "    setattr string \"age\" %age %person;"
    "    ret Person* %person;"
    "}";

  assert_ir_disassembling_successful(IR_STRING);
}

// -----------------------------------------------------------------------------

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
#include "ir/ir_builder.h"
#include "ir/format.h"
#include "ir/disassembler.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <memory>
#include <string>
#include <sstream>


// -----------------------------------------------------------------------------

#define CHECK_INVALID_SSA_VAR(var) \
  ASSERT_NE(NULL, (var).value)

// -----------------------------------------------------------------------------

using namespace corevm;

// -----------------------------------------------------------------------------

class IRBuilderUnitTest : public ::testing::Test
{
protected:
  void assert_construction_successful(ir::IRBuilder& builder,
    const char* expected_IR_string) const
  {
    std::unique_ptr<IRModule> actual_module;
    std::string msg;
    bool res = builder.finalize(actual_module, msg);

    if (!res)
    {
      printf("%s\n", msg.c_str());
    }

    ASSERT_EQ(true, res);
    ASSERT_NE(nullptr, actual_module);

    // Compare string representation of actual and expected module.
    ir::Disassembler::Options opts;
    opts.emit_newlines = false;
    ir::Disassembler disassebler(opts);
    std::stringstream stream;
    disassebler.disassemble(*actual_module, stream);

    std::string actual_IR_string = stream.str();

    // NOTE: double-quotes have to be removed for the strings to compare equally.
    actual_IR_string.erase(std::remove(actual_IR_string.begin(),
      actual_IR_string.end(), '\"'), actual_IR_string.end());

    ASSERT_EQ(expected_IR_string, actual_IR_string);
  }
};

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestInitialization)
{
  ir::IRBuilder builder;
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddType)
{
  ir::IRBuilder builder;

  std::string type_name("Person");
  std::string type_name2("Location");

  ir::TypeDecl type_decl = builder.add_type(type_name);
  ir::TypeDecl type_decl2 = builder.add_type(type_name2);

  const char* actual_type_name = builder.get_type_decl_name(type_decl);
  ASSERT_NE(nullptr, actual_type_name);
  ASSERT_STREQ(type_name.c_str(), actual_type_name);

  const char* actual_type_name2 = builder.get_type_decl_name(type_decl2);
  ASSERT_NE(nullptr, actual_type_name2);
  ASSERT_STREQ(type_name2.c_str(), actual_type_name2);
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddTypeField)
{
  ir::IRBuilder builder;

  ir::TypeDecl type_decl = builder.add_type("Person");

  builder.add_type_field(type_decl, ir::ValueTypeInt8,
    ir::ValueRefTypeByValue, "age");

  builder.add_type_field(type_decl, type_decl,
    ir::ValueRefTypeByReference, "friend");

  ASSERT_EQ(true, builder.has_field(type_decl, "age"));
  ASSERT_EQ(true, builder.has_field(type_decl, "friend"));

  ASSERT_EQ(false, builder.has_field(type_decl, "blah"));
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddArrayType)
{
  ir::IRBuilder builder;

  // Create an array of ten 32-bit unsigned integers.
  auto array_type = builder.add_array_type(10, ir::ValueTypeUInt32,
    ir::ValueRefTypeByValue);

  bool res = builder.has_array_type(array_type);

  ASSERT_EQ(res, true);

  // Create an array of two of the first array type.
  auto array_type2 = builder.add_array_type(10, array_type,
    ir::ValueRefTypeByReference); 

  res = builder.has_array_type(array_type2);

  ASSERT_EQ(res, true);

  // Create another array type that is exact identical to the first type,
  // and asserts that it is created.
  auto array_type3 = builder.add_array_type(10, ir::ValueTypeUInt32,
    ir::ValueRefTypeByValue);

  res = builder.has_array_type(array_type3);

  ASSERT_EQ(res, true);
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddModuleMetadata)
{
  ir::IRBuilder builder;

  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100";

  assert_construction_successful(builder, expected_IR_string); 
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddEmptyTypeAndAssert)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  ir::TypeDecl type_decl = builder.add_type("Person");
  ASSERT_NE(nullptr, type_decl);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "type Person {}";

  assert_construction_successful(builder, expected_IR_string); 
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddTypeAndAssert)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  ir::TypeDecl car_type = builder.add_type("Car");

  ir::TypeDecl type_decl = builder.add_type("Person");

  builder.add_type_field(type_decl, ir::ValueTypeInt8,
    ir::ValueRefTypeByValue, "age");

  builder.add_type_field(type_decl, type_decl,
    ir::ValueRefTypeByReference, "friend");

  builder.add_type_field(type_decl, car_type,
    ir::ValueRefTypeByReference, "car");

  ir::ArrayType array_type = builder.add_array_type(10, type_decl,
    ir::ValueRefTypeByValue);

  builder.add_type_field(type_decl, array_type,
    ir::ValueRefTypeByValue, "relatives");

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    ""
    "type Car {}"
    ""
    "type Person {"
    "    i8 age;"
    "    Person* friend;"
    "    Car* car;"
    "    array [ 10 * Person ] relatives;"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddEmptyFuncDefinition)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  ir::TypeDecl type_decl = builder.add_type("Person");

  ir::FuncDefn func_defn = builder.create_func_defn("createPerson", type_decl,
    ir::ValueRefTypeByValue);

  ASSERT_NE(NULL, func_defn);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "type Person {"
    "}"
    "def Person createPerson() {"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddFuncDefinitionWithParameters)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  ir::TypeDecl type_decl = builder.add_type("Person");

  ir::FuncDefn func_defn = builder.create_func_defn("checkPerson",
    ir::ValueTypeBoolean, ir::ValueRefTypeByValue);

  ASSERT_NE(NULL, func_defn);

  builder.add_func_parameter(func_defn, "person",
    type_decl, ir::ValueRefTypeByValue);

  builder.add_func_parameter(func_defn, "id",
    ir::ValueTypeUInt32, ir::ValueRefTypeByValue);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "type Person {"
    "}"
    "def bool checkPerson(Person person, ui32 id) {"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddFuncDefinitionWithParametersAndParent)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  ir::TypeDecl type_decl = builder.add_type("Person");

  builder.create_func_defn("main", ir::ValueTypeVoid, ir::ValueRefTypeByValue);

  ir::FuncDefn func_defn = builder.create_func_defn("checkPerson",
    ir::ValueTypeBoolean, ir::ValueRefTypeByValue, "main");

  ASSERT_NE(NULL, func_defn);

  builder.add_func_parameter(func_defn, "person",
    type_decl, ir::ValueRefTypeByValue);

  builder.add_func_parameter(func_defn, "id",
    ir::ValueTypeUInt32, ir::ValueRefTypeByValue);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "type Person {"
    "}"
    "def bool checkPerson(Person person, ui32 id) : main {"
    "}"
    "def void main() {}";

  assert_construction_successful(builder, expected_IR_string); 
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddAllocaSimple)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  const ir::FuncDefn func_defn = builder.create_func_defn("main",
    ir::ValueTypeVoid, ir::ValueRefTypeByValue);
  const ir::BasicBlock basic_block = builder.create_basic_block(func_defn);

  builder.add_alloca(func_defn, basic_block, ir::AllocaTypeAuto,
    ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "def void main() {"
    "label0:"
    "    %1 = alloca [ auto ] ui64;"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// -----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddAllocaComplex)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  ir::TypeDecl type_decl = builder.add_type("Person");

  const ir::FuncDefn func_defn = builder.create_func_defn("main",
    ir::ValueTypeVoid, ir::ValueRefTypeByValue);
  const ir::BasicBlock basic_block = builder.create_basic_block(func_defn);

  builder.add_alloca(func_defn, basic_block, ir::AllocaTypeAuto,
    type_decl, ir::ValueRefTypeByValue);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "type Person {"
    "}"
    ""
    "def void main() {"
    "label0:"
    "    %1 = alloca [ auto ] Person;"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// ----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddBinaryArithmeticInstr)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  const ir::FuncDefn func_defn = builder.create_func_defn("main",
    ir::ValueTypeVoid, ir::ValueRefTypeByValue);
  const ir::BasicBlock basic_block = builder.create_basic_block(func_defn);

  ir::SSAVariable var1 = builder.add_alloca(func_defn, basic_block,
    ir::AllocaTypeAuto, ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  CHECK_INVALID_SSA_VAR(var1);

  ir::SSAVariable var2 = builder.add_alloca(func_defn, basic_block,
    ir::AllocaTypeAuto, ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  CHECK_INVALID_SSA_VAR(var2);

  ir::SSAVariable var3 = builder.add_binary_instr(func_defn,
    basic_block, ir::InstrOpcodeADD, ir::ValueTypeUInt64, var1, var2);

  CHECK_INVALID_SSA_VAR(var3);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "" 
    "def void main() {"
    "label0:"
    "    %1 = alloca [ auto ] ui64;"
    "    %2 = alloca [ auto ] ui64;"
    "    %3 = add ui64 %1 %2;"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// ----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddBinaryArithmeticInstrWithParametersAsOperands)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  const ir::FuncDefn func_defn = builder.create_func_defn("main",
    ir::ValueTypeVoid, ir::ValueRefTypeByValue);
  const ir::BasicBlock basic_block = builder.create_basic_block(func_defn);

  ir::FuncParam param1 = builder.add_func_parameter(func_defn, "a",
    ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  ir::FuncParam param2 = builder.add_func_parameter(func_defn, "b",
    ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  ir::SSAVariable res = builder.add_binary_instr(func_defn,
    basic_block, ir::InstrOpcodeADD, ir::ValueTypeUInt64, param1, param2);

  CHECK_INVALID_SSA_VAR(res);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "" 
    "def void main(ui64 a, ui64 b) {"
    "label0:"
    "    %1 = add ui64 %a %b;"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// ----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestAddConditionalBranch)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  const ir::FuncDefn func_defn = builder.create_func_defn("main",
    ir::ValueTypeVoid, ir::ValueRefTypeByValue);
  const ir::BasicBlock basic_block = builder.create_basic_block(func_defn);

  const ir::BasicBlock bb1 = builder.create_basic_block(func_defn);

  ir::SSAVariable var1 = builder.add_alloca(func_defn, bb1,
    ir::AllocaTypeAuto, ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  CHECK_INVALID_SSA_VAR(var1);

  const ir::BasicBlock bb2 = builder.create_basic_block(func_defn);

  ir::SSAVariable var2 = builder.add_alloca(func_defn, bb2,
    ir::AllocaTypeAuto, ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  CHECK_INVALID_SSA_VAR(var2);

  ir::SSAVariable predicate = builder.add_alloca(func_defn, basic_block,
    ir::AllocaTypeAuto, ir::ValueTypeBoolean, ir::ValueRefTypeByValue);
 
  CHECK_INVALID_SSA_VAR(predicate);

  builder.add_conditional_branch(func_defn, basic_block, predicate, bb1, bb2); 

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    "" 
    "def void main() {"
    "label0:"
    "    %3 = alloca [ auto ] bool;"
    "    br %3 [ label #label1, label #label2 ];"
    "label1:"
    "    %1 = alloca [ auto ] ui64;"
    "    br bool 1 [ label #label0, label #label0 ];"
    "label2:"
    "    %2 = alloca [ auto ] ui64;"
    "    br bool 1 [ label #label0, label #label0 ];"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// ----------------------------------------------------------------------------

TEST_F(IRBuilderUnitTest, TestLoadAndStore)
{
  ir::IRBuilder builder;
  builder.add_author("Yanzheng Li");
  builder.add_target_version(100);  
  builder.add_timestamp(100);

  const ir::FuncDefn func_defn = builder.create_func_defn("main",
    ir::ValueTypeVoid, ir::ValueRefTypeByValue);
  const ir::BasicBlock basic_block = builder.create_basic_block(func_defn);

  ir::FuncParam param1 = builder.add_func_parameter(func_defn, "a",
    ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  ir::FuncParam param2 = builder.add_func_parameter(func_defn, "b",
    ir::ValueTypeUInt64, ir::ValueRefTypeByValue);

  ir::SSAVariable var1 = builder.add_load(func_defn, basic_block,
    ir::ValueTypeUInt32, ir::ValueRefTypeByValue, param1);

  CHECK_INVALID_SSA_VAR(var1);

  builder.add_store(func_defn, basic_block, ir::ValueTypeUInt32,
    ir::ValueRefTypeByValue, var1, param2);

  const char* expected_IR_string =
    "module name : N/A"
    "format version : 100"
    "target version : 100"
    "author : Yanzheng Li"
    "timestamp : 100"
    ""
    "def void main(ui64 a, ui64 b) {"
    "label0:"
    "    %1 = load ui32 %a;"
    "    store ui32 %1 %b;"
    "}";

  assert_construction_successful(builder, expected_IR_string); 
}

// ----------------------------------------------------------------------------

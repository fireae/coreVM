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
#include "jit/jit_compiler_llvmmcjit_backend.h"

#include <llvm/Analysis/Verifier.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/DataTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include <gtest/gtest.h>

#include <cstdint>
#include <cassert>


// -----------------------------------------------------------------------------

using namespace llvm;
using namespace corevm;

// -----------------------------------------------------------------------------

static const char* FUNC_NAME = "func";

// -----------------------------------------------------------------------------

static const int32_t FUNC_VALUE = 24;

// -----------------------------------------------------------------------------

// Current version of LLVM (3.4) does not support integer function parameters.
// Therefor for simplicity we will just create a parameter-less function for now.
static
void CreateFunction(Module* M, LLVMContext& context)
{
  FunctionType* Ty = FunctionType::get(IntegerType::get(context, 32), false);
  Constant* c = M->getOrInsertFunction(FUNC_NAME, Ty);
 
  Function* func = cast<Function>(c);
  func->setCallingConv(CallingConv::C);

  BasicBlock* block = BasicBlock::Create(context, "entry", func);
  IRBuilder<> builder(block);

  builder.CreateRet(ConstantInt::get(Type::getInt32Ty(context), FUNC_VALUE));
}

// -----------------------------------------------------------------------------

class LLVMMCJITBackendUnitTest : public ::testing::Test {};

// -----------------------------------------------------------------------------

TEST_F(LLVMMCJITBackendUnitTest, TestRunBackend)
{
  // Initialize dummy LLVM module.
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();
  LLVMContext context;
  llvm::OwningPtr<llvm::Module> M(new llvm::Module("test", context));
  CreateFunction(M.get(), context);

  // `verifyModule returns 0 on success.
  assert(!verifyModule(*M));

  // Properly initialize and finalize backend.
  jit::JITCompilerLLVMMCJITBackend backend(*M);

  // NOTE: need to call this at the beginning, to simulate use of JIT backend in
  // JIT compiler.
  backend.init();

  std::vector<jit::RuntimeValue> args;
  std::vector<jit::RuntimeValueType> arg_types;

  auto result_type = jit::ValueType::ValueTypeUInt64;

  bool res = backend.run(FUNC_NAME);
  ASSERT_EQ(true, res);

  jit::RuntimeValue result_value;
  res = backend.eval_func(args, arg_types, result_type, result_value);

  ASSERT_EQ(true, res);

  ASSERT_EQ(FUNC_VALUE, *result_value.IntVal.getRawData());

  // NOTE: need to call this at the end, to simulate use of JIT backend in
  // JIT compiler.
  backend.finalize();
}

// -----------------------------------------------------------------------------

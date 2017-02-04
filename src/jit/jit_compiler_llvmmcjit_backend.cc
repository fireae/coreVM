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
#include "jit_compiler_llvmmcjit_backend.h"
#include "util.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>


namespace corevm {
namespace jit {

// -----------------------------------------------------------------------------

JITCompilerLLVMMCJITBackend::JITCompilerLLVMMCJITBackend(ModuleType& module)
  :
  JITCompilerBackend(),
  m_module(module),
  m_func(nullptr),
  m_engine(llvm::EngineBuilder(&module).setUseMCJIT(true).setEngineKind(
    llvm::EngineKind::JIT).create())
{
}

// -----------------------------------------------------------------------------

JITCompilerLLVMMCJITBackend::~JITCompilerLLVMMCJITBackend()
{
}

// -----------------------------------------------------------------------------

/* virtual */
bool JITCompilerLLVMMCJITBackend::init()
{
  return (m_engine.get() != nullptr);
}

// -----------------------------------------------------------------------------

/* virtual */
bool JITCompilerLLVMMCJITBackend::run(const std::string& func_name)
{
  m_func = m_engine->FindFunctionNamed(func_name.c_str());
  m_engine->finalizeObject();
  return m_func != nullptr;
}

// -----------------------------------------------------------------------------

/* virtual */
bool JITCompilerLLVMMCJITBackend::eval_func(
  const std::vector<RuntimeValue>& args,
  const std::vector<RuntimeValueType>& arg_types,
  const RuntimeValueType& result_type, RuntimeValue& result_value)
{
  assert(m_func && "Function should be initialized");

  std::vector<llvm::GenericValue> llvm_args(args.size());
  for (size_t i = 0; i < args.size(); ++i)
  {
    llvm_args[i] = convert_to_llvm_generic_value(args[i], arg_types.at(i));
  }

  llvm::GenericValue llvm_result = m_engine->runFunction(m_func, llvm_args);

  result_value = convert_to_runtime_value(llvm_result, result_type);

  return true;
}

// -----------------------------------------------------------------------------

/* virtual */
bool JITCompilerLLVMMCJITBackend::finalize()
{
  // NOTE: This step is important. Without it segfault will occur.
  m_engine->removeModule(&m_module);
  return true;
}

// -----------------------------------------------------------------------------

} /* end namespace jit */
} /* end namespace corevm */

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
#ifndef COREVM_IR_MODULE_INDEX_H_
#define COREVM_IR_MODULE_INDEX_H_

#include "format.h"
#include <string>
#include <unordered_map>

// TODO: [COREVM-601] Optimize IR module index and verifier

namespace corevm {
namespace ir {

/**
 * Class encapsulates the index storage of an IR module's entities.
 *
 * The primary purpose of this class is to facilitate IR module verification
 * through the interfaces of the `Verifier` class, as well as other IR
 * optimization operations.
 */
struct IRModuleIndex {
  typedef std::unordered_map<std::string, const IRTypeDecl* const> TypeIndex;

  struct FunctionDefIndex {
    const IRClosure* closure;
    typedef std::unordered_map<std::string, const IRParameter* const>
      ParameterIndex;
    typedef std::unordered_map<std::string, const IRInstruction* const>
      InstructionIndex;
    typedef std::unordered_map<std::string, IRIdentifierType>
      IdentifierTypeIndex;
    typedef std::unordered_map<std::string, InstructionIndex> BasicBlockIndex;
    IdentifierTypeIndex identifier_type_index;
    ParameterIndex parameter_index;
    BasicBlockIndex bb_index;
  };

  typedef std::unordered_map<std::string, FunctionDefIndex> FunctionIndex;

  /**
   * Determines whether a function definition with the specified name exists
   * in the module.
   */
  bool has_func_def(const std::string&) const;

  /**
   * Constructor. Takes an instance of the module to be indexed.
   */
  explicit IRModuleIndex(const IRModule&);

  /**
   * Pointer to the indexed module.
   */
  const IRModule* const module_indexed;

  /**
   * Index of the set of type definitions defined in the module.
   */
  TypeIndex type_index;

  /**
   * Index of the set of function definitions defined in the module.
   */
  FunctionIndex function_index;

private:
  void init(const IRModule&);
  void init_type_index(const IRModule&);
  void init_function_index(const IRModule&);
  FunctionDefIndex create_func_def_index(const IRClosure&) const;
  FunctionDefIndex::IdentifierTypeIndex
  create_identifier_type_index(const IRClosure&) const;
  FunctionDefIndex::ParameterIndex
  create_parameter_index(const IRClosure&) const;
  FunctionDefIndex::BasicBlockIndex create_bb_index(const IRClosure&) const;
  FunctionDefIndex::InstructionIndex
  create_instr_index(const IRBasicBlock&) const;
};

} /* end namespace ir */
} /* end namespace corevm */

#endif /* COREVM_IR_MODULE_INDEX_H_ */

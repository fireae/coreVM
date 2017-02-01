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
#ifndef COREVM_IR_BUILDER_H_
#define COREVM_IR_BUILDER_H_

#include "types/variant/variant.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

/** Forward declaration. */
namespace corevm {
struct IRModule;
} /* end namespace corevm */


namespace corevm {
namespace ir {

/** Forward declarations. */
typedef struct _TypeDecl* TypeDecl;
typedef uint64_t ArrayType;
typedef uint64_t FuncDefn;
typedef uint64_t FuncParamType;
typedef uint64_t BasicBlock;
typedef uint64_t SSAVariableImpl;
struct IRBuilderImpl;

enum ValueRefType
{
  ValueRefTypeByValue = 0x01,
  ValueRefTypeByReference
};

enum ValueType
{
  ValueTypeVoid = 0x01,
  ValueTypeBoolean,
  ValueTypeInt8,
  ValueTypeUInt8,
  ValueTypeInt16,
  ValueTypeUInt16,
  ValueTypeInt32,
  ValueTypeUInt32,
  ValueTypeInt64,
  ValueTypeUInt64,
  ValueTypeSPF,
  ValueTypeDPF,
  ValueTypeString,
  ValueTypeObject
};

enum AllocaType
{
  AllocaTypeStatic = 0x00,
  AllocaTypeAuto
};

enum InstrOpcode
{
  InstrOpcodeALLOCA = 0x01,
  InstrOpcodeLOAD,
  InstrOpcodeSTORE,
  InstrOpcodeGETATTR,
  InstrOpcodeSETATTR,
  InstrOpcodeDELATTR,
  InstrOpcodeGETELEMENT,
  InstrOpcodePUTELEMENT,
  InstrOpcodeLEN,
  InstrOpcodeRET,
  InstrOpcodeBR,
  InstrOpcodeSWITCH2,
  InstrOpcodePOS,
  InstrOpcodeNEG,
  InstrOpcodeINC,
  InstrOpcodeDEC,
  InstrOpcodeADD,
  InstrOpcodeSUB,
  InstrOpcodeMUL,
  InstrOpcodeDIV,
  InstrOpcodeMOD,
  InstrOpcodeBNOT,
  InstrOpcodeBAND,
  InstrOpcodeBOR,
  InstrOpcodeBXOR,
  InstrOpcodeBLS,
  InstrOpcodeBRS,
  InstrOpcodeEQ,
  InstrOpcodeNEQ,
  InstrOpcodeGT,
  InstrOpcodeLT,
  InstrOpcodeGTE,
  InstrOpcodeLTE,
  InstrOpcodeLNOT,
  InstrOpcodeLAND,
  InstrOpcodeLOR,
  InstrOpcodeCMP,
  InstrOpcodeCALL
};

struct FuncParam
{
  FuncParamType value;

  FuncParam(FuncParamType);
};

struct SSAVariable
{
  SSAVariableImpl value;

  SSAVariable(SSAVariableImpl);
};

typedef corevm::types::variant::variant<
  bool,
  uint8_t,
  int8_t,
  uint16_t,
  int16_t,
  uint32_t,
  int32_t,
  uint64_t,
  int64_t,
  float,
  double,
  std::string,
  FuncParam,
  SSAVariable
> OperandValue;


/**
 * Class encapsulating a set of interfaces for facilitating programmatic
 * construction of an IR module.
 *
 * The interfaces of this class are designed in a way such that they are meant
 * to easily facilitate IR module construction by mechanisms of language parsers
 * and interpreters as they “walk through” the abstract syntax tree of their
 * target languages. Consequently, by design, the class currently does not allow
 * "undo" actions or modifications to elements that are previously added to
 * the module. Future work are needed in order to extend the flexibility
 * of this class.
 *
 * The interfaces for adding instructions have names that are prefixed by "add_"
 * followed by the instruction names as suffix. They each take the appropriate
 * number and types of arguments for each specific instruction, with the goal of
 * reducing the likelihood of producing an invalid module by misuse.
 * In addition, the interfaces abstract away the details of the inner workings
 * of IR construction and the internals of the class.
 *
 * Finally, the constructed IR goes through whole-module verification before it
 * can be released through the `IRBuilder::finalize` method. This, however,
 * can be disabled.
 *
 * Final word on the use of this class: This class is currently not exception
 * free. Misuses of the interfaces of this class will result in exceptions being
 * thrown. It is the users’ responsibilities to make sure proper usages and
 * handle potential errors accordingly. Whether or not the use of exceptions
 * merits other error reporting mechanisms is left for future debates.
 */
class IRBuilder
{
public:
  /**
   * Default constructor.
   */
  IRBuilder();

  /**
   * Constructor. Takes the name of the module to be constructed.
   */
  explicit IRBuilder(const char*);

  /**
   * Copy constructor. Disabled.
   */
  IRBuilder(const IRBuilder&) = delete;

  /**
   * Add the module author name to the module metadata.
   */
  void add_author(const char*);

  /**
   * Add the coreVM target version to the module metadata.
   * If not specified, the target version to be used is the current version
   * of coreVM.
   */
  void add_target_version(uint64_t);

  /**
   * Add the timestamp of module creation to the module metadata.
   * If not specified, the current UNIX timestamp is to be used.
   */
  void add_timestamp(uint64_t);

  /**
   * Add a type definition to the module.
   * This method is idempotent. Calling it with the same argument more
   * than once will return the same type declaration.
   */
  TypeDecl add_type(const std::string&);

  /**
   * Get the name of a previously added type definition.
   * Returns an empty string if the specified type has not been previously
   * added.
   */
  const char* get_type_decl_name(TypeDecl) const;

  /**
   * Add a value type field to a type definition.
   */
  void add_type_field(TypeDecl, ValueType, ValueRefType, const std::string&);

  /**
   * Add an aggregate type field to a type definition.
   */
  void add_type_field(TypeDecl, TypeDecl, ValueRefType, const std::string&);

  /**
   * Add an array type field to a type definition.
   */
  void add_type_field(TypeDecl, ArrayType, ValueRefType, const std::string&);

  /**
   * Determines if a field with the specified name exists in a given
   * type definition.
   */
  bool has_field(TypeDecl, const std::string&);

  /**
   * Create a fixed-size array type of an aggregate type elements.
   */
  ArrayType add_array_type(size_t, TypeDecl, ValueRefType);

  /**
   * Create a fixed-size array type of value type elements.
   */
  ArrayType add_array_type(size_t, ValueType, ValueRefType);

  /**
   * Create a fixed-size array type of array type elements.
   */
  ArrayType add_array_type(size_t, ArrayType, ValueRefType);

  /**
   * Determines if the specified array type has been created.
   */
  bool has_array_type(ArrayType);

  /**
   * Create a function definition with the specified name, return type,
   * and return value reference type, and an optional parent name.
   *
   * NOTE: currently function definitions with the same name are not allowed.
   */
  FuncDefn create_func_defn(const std::string&, TypeDecl, ValueRefType,
    const char* parent = NULL);

  /**
   * Create a function definition with the specified name, return type,
   * and return value reference type, and an optional parent name.
   *
   * NOTE: currently function definitions with the same name are not allowed.
   */
  FuncDefn create_func_defn(const std::string&, ValueType, ValueRefType,
    const char* parent = NULL);

  /**
   * Create a function definition with the specified name, return type,
   * and return value reference type, and an optional parent name.
   *
   * NOTE: currently function definitions with the same name are not allowed.
   */
  FuncDefn create_func_defn(const std::string&, ArrayType, ValueRefType,
    const char* parent = NULL);

  /**
   * Add a function parameter with the specified parameter name, type and value
   * reference type.
   *
   * Returns a reference to the added parameter.
   */
  FuncParam add_func_parameter(FuncDefn, const std::string&, TypeDecl,
    ValueRefType);

  /**
   * Add a function parameter with the specified parameter name, type and value
   * reference type.
   *
   * Returns a reference to the added parameter.
   */
  FuncParam add_func_parameter(FuncDefn, const std::string&, ValueType,
    ValueRefType);

  /**
   * Add a function parameter with the specified parameter name, type and value
   * reference type.
   *
   * Returns a reference to the added parameter.
   */
  FuncParam add_func_parameter(FuncDefn, const std::string&, ArrayType,
    ValueRefType);

  /**
   * Creates a basic block in the specified function definition.
   */
  BasicBlock create_basic_block(FuncDefn);

  /**
   * Insert variable initialization instruction, a.k.a. 'alloca', for
   * initialization of a value type.
   */
  SSAVariable add_alloca(FuncDefn, BasicBlock, AllocaType, ValueType,
    ValueRefType);

  /**
   * Insert variable initialization instruction, a.k.a. 'alloca', for
   * initialization of an array type.
   */
  SSAVariable add_alloca(FuncDefn, BasicBlock, AllocaType, ArrayType,
    ValueRefType);

  /**
   * Insert variable initialization instruction, a.k.a. 'alloca', for
   * initialization of an aggregate type.
   */
  SSAVariable add_alloca(FuncDefn, BasicBlock, AllocaType, TypeDecl,
    ValueRefType);

  /**
   * Insert variable initialization instruction, a.k.a. 'alloca', for
   * initialization of an aggregate type.
   */
  SSAVariable add_alloca(FuncDefn, BasicBlock, AllocaType,
    const std::string&, ValueRefType);

  /**
   * Insert 'load' instruction.
   */
  SSAVariable add_load(FuncDefn, BasicBlock, ValueType, ValueRefType,
    OperandValue);

  /**
   * Insert 'load' instruction.
   */
  SSAVariable add_load(FuncDefn, BasicBlock, ArrayType, ValueRefType,
    OperandValue);

  /**
   * Insert 'load' instruction.
   */
  SSAVariable add_load(FuncDefn, BasicBlock, TypeDecl, ValueRefType,
    OperandValue);

  /**
   * Insert 'store' instruction.
   */
  void add_store(FuncDefn, BasicBlock, ValueType, ValueRefType, OperandValue,
    OperandValue);

  /**
   * Insert 'store' instruction.
   */
  void add_store(FuncDefn, BasicBlock, ArrayType, ValueRefType, OperandValue,
    OperandValue);

  /**
   * Insert 'store' instruction.
   */
  void add_store(FuncDefn, BasicBlock, TypeDecl, ValueRefType, OperandValue,
    OperandValue);

  /**
   * Insert "attribute getting" instruction, a.k.a. 'getattr'.
   */
  SSAVariable add_get_attribute(FuncDefn, BasicBlock, OperandValue,
    const std::string&);

  /**
   * Insert "attribute setting" instruction, a.k.a. 'setattr'.
   */
  void add_set_attribute(FuncDefn, BasicBlock, OperandValue, OperandValue,
    const std::string&);

  /**
   * Insert "attribute deletion" instruction, a.k.a. 'delattr'.
   */
  void add_delete_attribute(FuncDefn, BasicBlock, OperandValue,
    const std::string&);

  /**
   * Insert "get element" instruction, a.k.a. 'getelement'.
   */
  SSAVariable add_get_element(FuncDefn, BasicBlock, ValueType, ValueRefType,
    OperandValue, OperandValue);

  /**
   * Insert "get element" instruction, a.k.a. 'getelement'.
   */
  SSAVariable add_get_element(FuncDefn, BasicBlock, ArrayType, ValueRefType,
    OperandValue, OperandValue);

  /**
   * Insert "get element" instruction, a.k.a. 'getelement'.
   */
  SSAVariable add_get_element(FuncDefn, BasicBlock, TypeDecl, ValueRefType,
    OperandValue, OperandValue);

  /**
   * Insert 'putelement' instruction.
   */
  void add_put_element(FuncDefn, BasicBlock, OperandValue, OperandValue,
    OperandValue);

  /**
   * Insert 'len' instruction.
   */
  SSAVariable add_len(FuncDefn, BasicBlock, OperandValue);

  /**
   * Insert 'ret' instruction.
   */
  SSAVariable add_ret(FuncDefn, BasicBlock, ValueType, ValueRefType,
    OperandValue);

  /**
   * Insert 'ret' instruction.
   */
  SSAVariable add_ret(FuncDefn, BasicBlock, ArrayType, ValueRefType,
    OperandValue);

  /**
   * Insert 'ret' instruction.
   */
  SSAVariable add_ret(FuncDefn, BasicBlock, TypeDecl, ValueRefType,
    OperandValue);

  /**
   * Insert an instruction for unary expressions.
   */
  SSAVariable add_unary_instr(FuncDefn, BasicBlock, InstrOpcode,
    ValueType, OperandValue);

  /**
   * Insert an instruction for binary expressions.
   */
  SSAVariable add_binary_instr(FuncDefn, BasicBlock, InstrOpcode,
    ValueType, OperandValue, OperandValue);

  /**
   * Insert unary bitwise instruction.
   */
  SSAVariable add_unary_bitwise_instr(FuncDefn, BasicBlock, InstrOpcode,
    OperandValue);

  /**
   * Insert binary bitwise instruction.
   */
  SSAVariable add_binary_bitwise_instr(FuncDefn, BasicBlock, InstrOpcode,
    OperandValue, OperandValue);

  /**
   * Insert unary logical instruction.
   */
  SSAVariable add_unary_logical_instr(FuncDefn, BasicBlock, InstrOpcode,
    OperandValue);

  /**
   * Insert binary logical instruction.
   */
  SSAVariable add_binary_logical_instr(FuncDefn, BasicBlock, InstrOpcode,
    OperandValue, OperandValue);

  /**
   * Insert an instruction for equality comparison expression.
   */
  SSAVariable add_equality_instr(FuncDefn, BasicBlock, InstrOpcode,
    OperandValue, OperandValue);

  /**
   * Insert equality comparison instruction 'cmp', for
   * value comparisons of two values.
   */
  SSAVariable add_cmp(FuncDefn, BasicBlock, OperandValue, OperandValue);

  /**
   * Insert 'call' instruction.
   */
  SSAVariable add_call(FuncDefn, BasicBlock, ValueType, ValueRefType,
    const std::string&, const std::vector<OperandValue>&);

  /**
   * Add a conditional statement inside the current basic block.
   */
  void add_conditional_branch(FuncDefn, BasicBlock, OperandValue, BasicBlock,
    BasicBlock);

  /**
   * Add a switch statement construct.
   *
   * Note that the number of cases and target blocks must equal.
   */
  void add_switch(FuncDefn, BasicBlock, OperandValue predicate,
    const std::vector<OperandValue>& cases,
    const std::vector<BasicBlock>& target_blocks);

  /**
   * Finalizes module construction.
   * Relinquishes the constructed module to caller. Module verification is
   * performed to check for well-formedness and correctness.
   * Returns a boolean value indicating whether the constructed module passes
   * verification, and updates the caller the reason of failure through the
   * specified string.
   */
  bool finalize(std::unique_ptr<IRModule>&, std::string&, bool verify=true);

private:
  std::shared_ptr<IRBuilderImpl> m_impl;
};

} /* end namespace ir */
} /* end namespace corevm */

#endif /* COREVM_IR_BUILDER_H_ */

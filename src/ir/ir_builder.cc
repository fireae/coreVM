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
#include "ir_builder.h"
#include "format.h"
#include "verifier.h"
#include "api/ir/version.h"

#include <boost/optional.hpp>

#include <unordered_map>
#include <utility>
#include <vector>


#if defined(__clang__) and __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wcovered-switch-default"
#endif

namespace corevm {
namespace ir {

// -----------------------------------------------------------------------------

FuncParam::FuncParam(FuncParamType value_)
  :
  value(value_)
{
}

// -----------------------------------------------------------------------------

SSAVariable::SSAVariable(SSAVariableImpl value_)
  :
  value(value_)
{
}

// -----------------------------------------------------------------------------

typedef uint64_t type_id_t;

// -----------------------------------------------------------------------------

/**
 * Abstraction representing an identifiable type in an IR module.
 */
struct IdentifierType
{
  typedef common::variant::variant<ValueType, ArrayType, TypeDecl> Value;

  ValueRefType ref_type;
  Value value;
};

// -----------------------------------------------------------------------------

IRValueRefType translate_ValueRefType(ValueRefType ref_type)
{
  switch (ref_type)
  {
  case ValueRefTypeByValue:
    return corevm::value;
  case ValueRefTypeByReference:
    return corevm::pointer;
  default:
    break;
  }

  return corevm::value;
}

// -----------------------------------------------------------------------------

IRValueType translate_ValueType(ValueType value_type)
{
  switch (value_type)
  {
  case ValueTypeVoid:
    return corevm::voidtype;
  case ValueTypeBoolean:
    return corevm::boolean;
  case ValueTypeInt8:
    return corevm::i8;
  case ValueTypeUInt8:
    return corevm::ui8;
  case ValueTypeInt16:
    return corevm::i16;
  case ValueTypeUInt16:
    return corevm::ui16;
  case ValueTypeInt32:
    return corevm::i32;
  case ValueTypeUInt32:
    return corevm::ui32;
  case ValueTypeInt64:
    return corevm::i64;
  case ValueTypeUInt64:
    return corevm::ui64;
  case ValueTypeSPF:
    return corevm::spf;
  case ValueTypeDPF:
    return corevm::dpf;
  case ValueTypeString:
    return corevm::string;
  case ValueTypeObject:
    return corevm::object;
  }

  return corevm::voidtype;
}

// -----------------------------------------------------------------------------

IROpcode translate_InstrOpcode(InstrOpcode opcode)
{
  switch (opcode)
  {
  case InstrOpcodeALLOCA:
    return corevm::alloca;
  case InstrOpcodeLOAD:
    return corevm::load;
  case InstrOpcodeSTORE:
    return corevm::store;
  case InstrOpcodeGETATTR:
    return corevm::getattr;
  case InstrOpcodeSETATTR:
    return corevm::setattr;
  case InstrOpcodeDELATTR:
    return corevm::delattr;
  case InstrOpcodeGETELEMENT:
    return corevm::getelement;
  case InstrOpcodePUTELEMENT:
    return corevm::putelement;
  case InstrOpcodeLEN:
    return corevm::len;
  case InstrOpcodeRET:
    return corevm::ret;
  case InstrOpcodeBR:
    return corevm::br;
  case InstrOpcodeSWITCH2:
    return corevm::switch2;
  case InstrOpcodePOS:
    return corevm::pos;
  case InstrOpcodeNEG:
    return corevm::neg;
  case InstrOpcodeINC:
    return corevm::inc;
  case InstrOpcodeDEC:
    return corevm::dec;
  case InstrOpcodeADD:
    return corevm::add;
  case InstrOpcodeSUB:
    return corevm::sub;
  case InstrOpcodeMUL:
    return corevm::mul;
  case InstrOpcodeDIV:
    return corevm::div;
  case InstrOpcodeMOD:
    return corevm::mod;
  case InstrOpcodeBNOT:
    return corevm::bnot;
  case InstrOpcodeBAND:
    return corevm::band;
  case InstrOpcodeBOR:
    return corevm::bor;
  case InstrOpcodeBXOR:
    return corevm::bxor;
  case InstrOpcodeBLS:
    return corevm::bls;
  case InstrOpcodeBRS:
    return corevm::brs;
  case InstrOpcodeEQ:
    return corevm::eq;
  case InstrOpcodeNEQ:
    return corevm::neq; 
  case InstrOpcodeGT:
    return corevm::gt;
  case InstrOpcodeLT:
    return corevm::lt;
  case InstrOpcodeGTE:
    return corevm::gte;
  case InstrOpcodeLTE:
    return corevm::lte;
  case InstrOpcodeLNOT:
    return corevm::lnot;
  case InstrOpcodeLAND:
    return corevm::land;
  case InstrOpcodeLOR:
    return corevm::lor;
  case InstrOpcodeCMP:
    return corevm::cmp;
  case InstrOpcodeCALL:
    return corevm::call;
  }

  return corevm::alloca;
}

// -----------------------------------------------------------------------------

static const char* ALLOCA_OPTIONS[] {
  "static",
  "auto"
};

// -----------------------------------------------------------------------------

struct _TypeDecl
{
  type_id_t id;
};

// -----------------------------------------------------------------------------

/**
 * Class that encapsulates the logic and data needed for a single aggregate
 * type declaration used during IR construction.
 */
struct TypeDeclImpl
{
  std::string name;
  struct TypeDeclField
  {
    std::string name;
    IdentifierType type;
  };
  typedef std::vector<TypeDeclField> FieldSet;
  typedef std::unordered_map<std::string, size_t> FieldSetMap;
  FieldSet fields;
  FieldSetMap fields_map;

  void
  add_field(const std::string& field_name, const IdentifierType& field_type)
  {
    auto itr = fields_map.find(field_name);
    if (itr != fields_map.end())
    {
      return;
    }

    fields.push_back(TypeDeclField{field_name, field_type});
    fields_map.insert(std::make_pair(field_name, fields.size() - 1));
  }
};

// -----------------------------------------------------------------------------

/**
 * Class that encapsulates the logic and data needed for a single array
 * type declaration used during IR construction.
 */
struct ArrayTypeImpl
{
  size_t len;
  IdentifierType type;
};

// -----------------------------------------------------------------------------

/**
 * Encapsulation that implements the storage mechanisms of aggregate
 * type declarations used during IR construction.
 */
struct TypeDeclStore
{
  type_id_t type_id;
  std::vector<TypeDeclImpl> storage;
  std::unordered_map<std::string, _TypeDecl> type_decls_map;

  TypeDeclStore() : type_id(0), storage(), type_decls_map() {}

  // ---------------------------------------------------------------------------

  TypeDecl add_type(const std::string& type_name)
  {
    const auto itr = type_decls_map.find(type_name);
    if (itr != type_decls_map.cend())
    {
      return &itr->second;
    }

    storage.push_back(TypeDeclImpl{type_name, TypeDeclImpl::FieldSet()});
    type_decls_map.insert(std::make_pair(type_name, _TypeDecl{type_id}));
    ++type_id;

    return &type_decls_map.at(type_name);
  }

  // ---------------------------------------------------------------------------

  const char* get_type_decl_name(TypeDecl type_decl) const
  {
    const auto& type_decl_impl = storage.at(type_decl->id);
    return type_decl_impl.name.c_str();
  }

  // ---------------------------------------------------------------------------

  TypeDecl get_type_decl_by_name(const std::string& type_decl_name)
  {
    return &type_decls_map.at(type_decl_name);
  }

  // ---------------------------------------------------------------------------

  void add_type_field(TypeDecl type_decl, IdentifierType field_type,
    const std::string& field_name)
  {
    auto& type_decl_impl = storage.at(type_decl->id);
    type_decl_impl.add_field(field_name, field_type);
  }

  // ---------------------------------------------------------------------------

  bool has_field(TypeDecl type_decl, const std::string& field_name)
  {
    if (type_decl->id >= storage.size())
    {
      return false;
    }

    auto& type_decl_impl = storage.at(type_decl->id);
    return type_decl_impl.fields_map.find(field_name) !=
      type_decl_impl.fields_map.end();
  }

  // ---------------------------------------------------------------------------

}; /* end `struct TypeDeclStore` */

// -----------------------------------------------------------------------------

/**
 * Encapsulation that implements the storage mechanisms of array type
 * declarations used during IR construction.
 */
struct ArrayTypeStore
{
  type_id_t type_id;
  std::vector<ArrayTypeImpl> store;

  ArrayTypeStore() : type_id(0), store(0) {}

  // ---------------------------------------------------------------------------

  ArrayType add_array_type(const ArrayTypeImpl& array_type)
  {
    store.push_back(array_type);
    ArrayType val = type_id;
    type_id++;
    return val;
  }

  // ---------------------------------------------------------------------------

  bool has_array_type(ArrayType array_type)
  {
    return array_type < store.size();
  }

  // ---------------------------------------------------------------------------

}; /* end `struct ArrayTypeStore` */

// -----------------------------------------------------------------------------

/**
 * Encapsulation that implements the storage mechanisms of function
 * parameters of a single function definition used during IR construction.
 */
struct FuncParamStore
{
  /**
   * Class that encapsulates the logic and data needed for a function parameter
   * used during IR construction.
   */
  struct FuncParamImpl
  {
    std::string name;
    IdentifierType type;
  };

  type_id_t type_id;
  std::vector<FuncParamImpl> storage;
  std::unordered_map<std::string, FuncParamType> params_map;

  // ---------------------------------------------------------------------------

  FuncParamStore() : type_id(0), storage(), params_map() {}

  // ---------------------------------------------------------------------------

  FuncParamType add_func_parameter(const std::string& param_name,
    IdentifierType param_type)
  {
    const auto itr = params_map.find(param_name);
    if (itr != params_map.cend())
    {
      return itr->second;
    }

    storage.push_back(FuncParamImpl{param_name, param_type});
    params_map.insert(std::make_pair(param_name, type_id));
    ++type_id;

    return params_map.at(param_name);
  }

  // ---------------------------------------------------------------------------

}; /* end `struct FuncParamStore` */

// -----------------------------------------------------------------------------

/**
 * Class that encapsulates the logic and data needed for an instruction
 * used during IR construction.
 */
struct InstructionImpl
{
  SSAVariableImpl target;
  InstrOpcode opcode;
  boost::optional<IdentifierType> type;
  std::vector<std::string> options;
  std::vector<OperandValue> oprds;
  std::vector<BasicBlock> labels;

  InstructionImpl(InstrOpcode opcode_, const IdentifierType& type_)
    :
    target(0),
    opcode(opcode_),
    type(type_),
    options(),
    oprds(),
    labels()
  {
  }

  InstructionImpl(InstrOpcode opcode_, const std::vector<std::string>& options_,
    const IdentifierType& type_, SSAVariableImpl target_)
    :
    target(target_),
    opcode(opcode_),
    type(type_),
    options(options_),
    oprds(),
    labels()
  {
  }

  InstructionImpl(InstrOpcode opcode_, const IdentifierType& type_,
    SSAVariableImpl target_)
    :
    target(target_),
    opcode(opcode_),
    type(type_),
    options(),
    oprds(),
    labels()
  {
  }

  InstructionImpl(InstrOpcode opcode_, const IdentifierType& type_,
    SSAVariableImpl target_, const std::vector<OperandValue>& oprds_)
    :
    target(target_),
    opcode(opcode_),
    type(type_),
    options(),
    oprds(oprds_),
    labels()
  {
  }

  InstructionImpl(InstrOpcode opcode_, const IdentifierType& type_,
    const std::vector<OperandValue>& oprds_)
    :
    target(0),
    opcode(opcode_),
    type(type_),
    options(),
    oprds(oprds_),
    labels()
  {
  }

  InstructionImpl(InstrOpcode opcode_, SSAVariableImpl target_,
    const std::vector<OperandValue>& oprds_)
    :
    target(target_),
    opcode(opcode_),
    type(),
    options(),
    oprds(oprds_),
    labels()
  {
  }

  InstructionImpl(InstrOpcode opcode_, const std::vector<OperandValue>& oprds_)
    :
    target(0),
    opcode(opcode_),
    type(),
    options(),
    oprds(oprds_),
    labels()
  {
  }

  InstructionImpl(InstrOpcode opcode_, const std::vector<OperandValue>& oprds_,
    const std::vector<BasicBlock>& labels_)
    :
    target(0),
    opcode(opcode_),
    type(),
    options(),
    oprds(oprds_),
    labels(labels_)
  {
  }
};

// -----------------------------------------------------------------------------

/**
 * Encapsulation that implements the storage mechanisms of basic blocks
 * of a single function definition used during IR construction.
 */
struct BasicBlockStore
{
  struct BasicBlockImpl
  {
    std::string name;
    typedef std::vector<InstructionImpl> InstructionStore;
    InstructionStore instr_store;
  };

  SSAVariableImpl var_id;
  std::vector<BasicBlockImpl> storage;

  // ---------------------------------------------------------------------------

  BasicBlockStore() : var_id(0), storage()
  {
  }

  // ---------------------------------------------------------------------------

  BasicBlock create_block()
  {
    const static std::string bb_name_prefix("label"); 
    storage.push_back(BasicBlockImpl{
      bb_name_prefix + std::to_string(storage.size()),
      BasicBlockImpl::InstructionStore()});
    return storage.size() - 1;
  }

  // ---------------------------------------------------------------------------

  SSAVariableImpl add_instruction_with_target(BasicBlock basic_block,
    InstrOpcode opcode, const IdentifierType& type)
  {
    storage.at(basic_block).instr_store.push_back(InstructionImpl{opcode, type,
      ++var_id});

    return var_id;
  } 

  // ---------------------------------------------------------------------------

  SSAVariableImpl add_instruction_with_target_and_options(
    BasicBlock basic_block, InstrOpcode opcode,
    const std::vector<std::string>& options, const IdentifierType& type)
  {
    storage.at(basic_block).instr_store.push_back(InstructionImpl{
      opcode, options, type, ++var_id});

    return var_id;
  } 

  // ---------------------------------------------------------------------------

  SSAVariableImpl add_instruction_with_target_and_oprds(BasicBlock basic_block,
    InstrOpcode opcode, const IdentifierType& type,
    const std::vector<OperandValue>& oprds)
  {
    storage.at(basic_block).instr_store.push_back(InstructionImpl{opcode, type,
      ++var_id, oprds});

    return var_id;
  }

  // ---------------------------------------------------------------------------

  SSAVariableImpl add_instruction_with_target_and_oprds(BasicBlock basic_block,
    InstrOpcode opcode, const std::vector<OperandValue>& oprds)
  {
    storage.at(basic_block).instr_store.push_back(InstructionImpl{opcode,
      ++var_id, oprds});

    return var_id;
  }

  // ---------------------------------------------------------------------------

  void add_instruction_with_oprds(BasicBlock basic_block,
    InstrOpcode opcode, const std::vector<OperandValue>& oprds)
  {
    storage.at(basic_block).instr_store.push_back(
      InstructionImpl{opcode, oprds});
  }

  // ---------------------------------------------------------------------------

  void add_instruction_with_oprds(BasicBlock basic_block,
    InstrOpcode opcode, IdentifierType value_type,
    const std::vector<OperandValue>& oprds)
  {
    storage.at(basic_block).instr_store.push_back(
      InstructionImpl{opcode, value_type, oprds});
  }

  // ---------------------------------------------------------------------------

  void add_instruction_with_oprds_and_labels(BasicBlock basic_block,
    InstrOpcode opcode, const std::vector<OperandValue>& oprds,
    const std::vector<BasicBlock>& labels)
  {
    storage.at(basic_block).instr_store.push_back(
      InstructionImpl{opcode, oprds, labels});
  }

  // ---------------------------------------------------------------------------

}; /* end `struct BasicBlockStore` */

// -----------------------------------------------------------------------------

/**
 * Encapsulation that implements the storage mechanisms of function definitions
 * in an IR module used during IR construction.
 */
struct FuncDefnStore
{
  /**
   * Class encapsulating the logic and data needed to represent and store
   * a single function definition in an IR module used during IR construction.
   */
  struct FuncDefnImpl
  {
    IdentifierType ret_type;
    FuncParamStore param_store;
    BasicBlockStore bb_store;
    std::string parent;

    FuncDefnImpl(IdentifierType ret_type_, const char* parent_)
      :
      ret_type(ret_type_),
      param_store(),
      bb_store(),
      parent(parent_ ? parent_ : "")
    {
    }
  };

  // ---------------------------------------------------------------------------

  type_id_t type_id;
  std::unordered_map<type_id_t, FuncDefnImpl> func_defns_store;
  std::unordered_map<std::string, FuncDefn> func_defns_map;

  FuncDefnStore() : type_id(0), func_defns_store(), func_defns_map()
  {
  }

  // ---------------------------------------------------------------------------

  FuncDefn create_func_defn(const std::string& func_name,
    IdentifierType ret_type, const char* parent)
  {
    const auto itr = func_defns_map.find(func_name);
    if (itr != func_defns_map.cend())
    {
      return itr->second;
    }

    func_defns_store.insert(std::make_pair(++type_id,
      FuncDefnImpl{ret_type, parent}));
    func_defns_map.insert(std::make_pair(func_name, type_id));

    return func_defns_map.at(func_name);
  }

  // ---------------------------------------------------------------------------

  FuncParamType add_func_parameter(FuncDefn func_defn,
    const std::string& param_name, IdentifierType param_type)
  {
    auto& func_defn_impl = func_defns_store.at(func_defn);
    return func_defn_impl.param_store.add_func_parameter(param_name,
      param_type);
  }

  // ---------------------------------------------------------------------------

  FuncDefnImpl& get_func_defn(FuncDefn func_defn)
  {
    return func_defns_store.at(func_defn);
  }

  // ---------------------------------------------------------------------------

}; /* end `struct FuncDefnStore` */

// -----------------------------------------------------------------------------

/**
 * Class encapsulating the logic and data needed to implement whole-module
 * IR construction.
 */
struct IRBuilderImpl
{
  IRBuilderImpl();

  /**
   * Add the module name to the module metadata.
   */
  void add_module_name(const char*);

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
  void add_type_field(TypeDecl, IdentifierType, const std::string&);

  /**
   * Determines if a field with the specified name exists in a given
   * type definition.
   */
  bool has_field(TypeDecl, const std::string&);

  /**
   * Create a fixed-size array type.
   */
  ArrayType add_array_type(const ArrayTypeImpl&);

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
  FuncDefn create_func_defn(const std::string&, IdentifierType,
    const char* parent);

  /**
   * Add a function parameter with the specified parameter name, type and value
   * reference type.
   *
   * Returns a reference to the added parameter.
   */
  FuncParam add_func_parameter(FuncDefn, const std::string&, IdentifierType);

  /**
   * Creates a basic block in the specified function definition.
   */
  BasicBlock create_basic_block(FuncDefn);

  /**
   * Insert variable initialization instruction, a.k.a. 'alloca', for
   * initialization of a value type.
   */
  SSAVariable add_alloca(FuncDefn, BasicBlock, AllocaType, IdentifierType);

  /**
   * Insert variable initialization instruction, a.k.a. 'alloca', for
   * initialization of an aggregate type.
   */
  SSAVariable add_alloca(FuncDefn, BasicBlock, AllocaType, const std::string&,
    ValueRefType);

  /**
   * Insert 'load' instruction.
   */
  SSAVariable add_load(FuncDefn, BasicBlock, IdentifierType,
    OperandValue);

  /**
   * Insert 'store' instruction.
   */
  void add_store(FuncDefn, BasicBlock, IdentifierType,
    OperandValue, OperandValue);

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
  SSAVariable add_get_element(FuncDefn, BasicBlock, IdentifierType,
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
  SSAVariable add_ret(FuncDefn, BasicBlock, IdentifierType, OperandValue);

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
  SSAVariable add_call(FuncDefn, BasicBlock, IdentifierType,
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
  bool finalize(std::unique_ptr<IRModule>&, std::string&, bool verify);

private:
  void finalize_metadata(std::unique_ptr<IRModule>&);
  void finalize_type_decls(std::unique_ptr<IRModule>&);
  void finalize_func_defns(std::unique_ptr<IRModule>&);

  IRTypeDecl finalize_type_decl(const TypeDeclImpl&);

  IRClosure finalize_func_defn(const std::string&,
    const FuncDefnStore::FuncDefnImpl&);

  void translate_IdentifierType(const IdentifierType&, IRIdentifierType&) const;

  IRInstruction translate_InstructionImpl(
    const FuncDefnStore::FuncDefnImpl&, const InstructionImpl&) const;

private:
  std::string module_name;
  std::string author_name;
  uint64_t target_version;
  uint64_t timestamp;

  TypeDeclStore type_decl_store;
  ArrayTypeStore array_type_store;
  FuncDefnStore func_defn_store;
}; /* end `struct IRBuilderImpl` */

// -----------------------------------------------------------------------------

IRBuilderImpl::IRBuilderImpl()
  :
  module_name(),
  author_name(),
  target_version(0),
  timestamp(0),
  type_decl_store(),
  array_type_store(),
  func_defn_store()
{
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_module_name(const char* name)
{
  module_name.assign(name);
}

// -----------------------------------------------------------------------------

void IRBuilderImpl::add_author(const char* name)
{
  author_name.assign(name);
}

// -----------------------------------------------------------------------------

void IRBuilderImpl::add_target_version(uint64_t val)
{
  target_version = val;
}

// -----------------------------------------------------------------------------

void IRBuilderImpl::add_timestamp(uint64_t val)
{
  timestamp = val;
}

// -----------------------------------------------------------------------------

TypeDecl
IRBuilderImpl::add_type(const std::string& type_name)
{
  return type_decl_store.add_type(type_name);
}

// -----------------------------------------------------------------------------

const char*
IRBuilderImpl::get_type_decl_name(TypeDecl type_decl) const
{
  return type_decl_store.get_type_decl_name(type_decl);
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_type_field(TypeDecl type_decl, IdentifierType field_type,
  const std::string& field_name)
{
  type_decl_store.add_type_field(type_decl, field_type, field_name);
}

// -----------------------------------------------------------------------------

bool
IRBuilderImpl::has_field(TypeDecl type_decl, const std::string& field_name)
{
  return type_decl_store.has_field(type_decl, field_name);
}

// -----------------------------------------------------------------------------

ArrayType
IRBuilderImpl::add_array_type(const ArrayTypeImpl& array_type)
{
  return array_type_store.add_array_type(array_type);
}

// -----------------------------------------------------------------------------

bool
IRBuilderImpl::has_array_type(ArrayType array_type)
{
  return array_type_store.has_array_type(array_type);
}

// -----------------------------------------------------------------------------

FuncDefn
IRBuilderImpl::create_func_defn(const std::string& func_name,
  IdentifierType rettype, const char* parent)
{
  return func_defn_store.create_func_defn(func_name, rettype, parent);
}

// -----------------------------------------------------------------------------

FuncParam
IRBuilderImpl::add_func_parameter(FuncDefn func_defn,
  const std::string& param_name, IdentifierType param_type)
{
  return func_defn_store.add_func_parameter(func_defn, param_name, param_type);
}

// -----------------------------------------------------------------------------

BasicBlock
IRBuilderImpl::create_basic_block(FuncDefn func_defn)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.create_block();
}

// -----------------------------------------------------------------------------


SSAVariable
IRBuilderImpl::add_alloca(FuncDefn func_defn, BasicBlock basic_block,
  AllocaType alloca_type, IdentifierType target_type)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_options(
    basic_block, InstrOpcodeALLOCA,
    std::vector<std::string> { ALLOCA_OPTIONS[alloca_type] }, target_type);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_alloca(FuncDefn func_defn, BasicBlock basic_block,
  AllocaType alloca_type, const std::string& target_type_name,
  ValueRefType ref_type)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  auto target_type_decl = type_decl_store.get_type_decl_by_name(
    target_type_name);
  return func_defn_impl.bb_store.add_instruction_with_target_and_options(
    basic_block, InstrOpcodeALLOCA,
    std::vector<std::string> { ALLOCA_OPTIONS[alloca_type] },
    IdentifierType{ref_type, target_type_decl});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_load(FuncDefn func_defn, BasicBlock basic_block,
  IdentifierType value_type, OperandValue oprd)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, InstrOpcodeLOAD, value_type,
    std::vector<OperandValue>{oprd});
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_store(FuncDefn func_defn, BasicBlock basic_block,
  IdentifierType value_type, OperandValue src, OperandValue dst)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  func_defn_impl.bb_store.add_instruction_with_oprds(basic_block,
    InstrOpcodeSTORE, value_type, std::vector<OperandValue>{src,dst});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_get_attribute(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue source, const std::string& attr_name)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, InstrOpcodeGETATTR,
    std::vector<OperandValue> {attr_name, source});
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_set_attribute(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue target, OperandValue source, const std::string& attr_name)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  func_defn_impl.bb_store.add_instruction_with_oprds(basic_block,
    InstrOpcodeSETATTR, std::vector<OperandValue> {attr_name, source, target});
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_delete_attribute(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue source, const std::string& attr_name)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  func_defn_impl.bb_store.add_instruction_with_oprds(basic_block,
    InstrOpcodeDELATTR, std::vector<OperandValue> {attr_name, source });
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_get_element(FuncDefn func_defn, BasicBlock basic_block,
  IdentifierType value_type, OperandValue source, OperandValue idx)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, InstrOpcodeGETELEMENT, value_type,
    std::vector<OperandValue> {source, idx});
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_put_element(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue src, OperandValue dst, OperandValue idx)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_oprds(basic_block,
    InstrOpcodePUTELEMENT, std::vector<OperandValue> {src, dst, idx});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_len(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue oprd)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, InstrOpcodeLEN,
    IdentifierType{ValueRefTypeByValue, ValueTypeUInt64},
    std::vector<OperandValue> {oprd});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_ret(FuncDefn func_defn, BasicBlock basic_block,
  IdentifierType value_type, OperandValue value)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, InstrOpcodeRET, value_type, std::vector<OperandValue> {value});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_unary_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, ValueType value_type, OperandValue source)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, opcode, IdentifierType{ValueRefTypeByValue, value_type},
    std::vector<OperandValue> {source});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_binary_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, ValueType value_type, OperandValue lhs, OperandValue rhs)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, opcode, IdentifierType{ValueRefTypeByValue, value_type},
    std::vector<OperandValue> {lhs, rhs});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_equality_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, OperandValue lhs, OperandValue rhs)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, opcode, IdentifierType{ValueRefTypeByValue, ValueTypeBoolean},
    std::vector<OperandValue> {lhs, rhs});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_cmp(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue lhs, OperandValue rhs)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, InstrOpcodeCMP,
    IdentifierType{ValueRefTypeByValue, ValueTypeInt32},
    std::vector<OperandValue> {lhs, rhs});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilderImpl::add_call(FuncDefn func_defn, BasicBlock basic_block,
  IdentifierType ret_type, const std::string& callee,
  const std::vector<OperandValue>& args)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);
  std::vector<OperandValue> oprds {callee};
  oprds.insert(oprds.end(), args.begin(), args.end());
  return func_defn_impl.bb_store.add_instruction_with_target_and_oprds(
    basic_block, InstrOpcodeCALL, ret_type, oprds);
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_conditional_branch(FuncDefn func_defn,
  BasicBlock basic_block, OperandValue predicate, BasicBlock bb1,
  BasicBlock bb2)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);

  // Add instruction to branch to either blocks.
  func_defn_impl.bb_store.add_instruction_with_oprds_and_labels(basic_block,
    InstrOpcodeBR,
    std::vector<OperandValue> {predicate},
    std::vector<BasicBlock> {bb1, bb2});

  // Add unconditional branch in each block to go back to current block.
  func_defn_impl.bb_store.add_instruction_with_oprds_and_labels(bb1,
    InstrOpcodeBR,
    std::vector<OperandValue> {bool(true)},
    std::vector<BasicBlock> {basic_block, basic_block});

  // Add unconditional branch in each block to go back to current block.
  func_defn_impl.bb_store.add_instruction_with_oprds_and_labels(bb2,
    InstrOpcodeBR,
    std::vector<OperandValue> {bool(true)},
    std::vector<BasicBlock> {basic_block, basic_block});
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::add_switch(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue predicate, const std::vector<OperandValue>& cases,
  const std::vector<BasicBlock>& target_blocks)
{
  auto& func_defn_impl = func_defn_store.get_func_defn(func_defn);

  std::vector<OperandValue> oprds;
  oprds.resize(cases.size() + 1);

  oprds.push_back(predicate);
  oprds.insert(oprds.end(), cases.begin(), cases.end());

  // Add instruction to branch to either blocks.
  func_defn_impl.bb_store.add_instruction_with_oprds_and_labels(basic_block,
    InstrOpcodeSWITCH2, oprds, target_blocks);

  // Add unconditional branch in each block to go back to current block.
  for (const auto& target_block : target_blocks)
  {
    func_defn_impl.bb_store.add_instruction_with_oprds_and_labels(target_block,
      InstrOpcodeBR,
      std::vector<OperandValue> {bool(true)},
      std::vector<BasicBlock> {basic_block, basic_block});
  }
}

// -----------------------------------------------------------------------------

bool
IRBuilderImpl::finalize(std::unique_ptr<IRModule>& module, std::string& msg,
  bool verify)
{
  std::unique_ptr<IRModule> constructed_module(new IRModule);

  finalize_metadata(constructed_module);
  finalize_type_decls(constructed_module);
  finalize_func_defns(constructed_module);

  if (verify)
  {
    Verifier verifier(*constructed_module);
    std::string err;
    if (!verifier.run(err))
    {
      msg.assign("Module verification failed: ");
      msg += err;
      return false;
    }
  }

  constructed_module.swap(module);

  return true;
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::finalize_metadata(std::unique_ptr<IRModule>& module)
{
  module->meta.name.assign(module_name.empty() ? "N/A" : module_name);
  module->meta.author.assign(author_name.empty() ? "N/A" : author_name);
  module->meta.target_version = target_version;
  module->meta.format_version = api::ir::IR_VERSION;

  const int64_t timestamp_val = timestamp ?
    timestamp : static_cast<int64_t>(std::time(nullptr));
  module->meta.timestamp = timestamp_val;
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::finalize_type_decls(std::unique_ptr<IRModule>& module)
{
  module->types.reserve(type_decl_store.storage.size());
  for (const auto& type_decl_impl : type_decl_store.storage)
  {
    module->types.push_back(finalize_type_decl(type_decl_impl));
  }
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::finalize_func_defns(std::unique_ptr<IRModule>& module)
{
  module->closures.reserve(func_defn_store.func_defns_map.size());
  for (const auto& pair : func_defn_store.func_defns_map)
  {
    const auto& func_name = pair.first;
    const auto& func_defn_impl =
      func_defn_store.func_defns_store.at(pair.second);

    module->closures.push_back(finalize_func_defn(func_name, func_defn_impl));
  }
}

// -----------------------------------------------------------------------------

IRClosure
IRBuilderImpl::finalize_func_defn(const std::string& func_name,
  const FuncDefnStore::FuncDefnImpl& func_defn_impl)
{
  IRClosure closure;

  // Return type and name.
  closure.name = func_name;
  translate_IdentifierType(func_defn_impl.ret_type, closure.rettype);

  // Parameters.
  closure.parameters.reserve(func_defn_impl.param_store.params_map.size());
  for (const auto& param_impl : func_defn_impl.param_store.storage)
  {
    IRParameter ir_param;
    ir_param.identifier = param_impl.name;
    translate_IdentifierType(param_impl.type, ir_param.type);

    closure.parameters.push_back(ir_param);
  }

  // Parent.
  if (func_defn_impl.parent.empty())
  {
    closure.parent.set_null();
  }
  else
  {
    closure.parent.set_string(func_defn_impl.parent);
  }

  // Basic blocks.
  closure.blocks.reserve(func_defn_impl.bb_store.storage.size());
  for (const auto& basic_block_impl : func_defn_impl.bb_store.storage)
  {
    IRBasicBlock ir_basic_block;
    ir_basic_block.label = basic_block_impl.name;
    ir_basic_block.body.reserve(basic_block_impl.instr_store.size());

    for (const auto& instr_impl : basic_block_impl.instr_store)
    {
      ir_basic_block.body.push_back(
        translate_InstructionImpl(func_defn_impl, instr_impl));
    }

    closure.blocks.push_back(ir_basic_block);
  }

  return closure;
}

// -----------------------------------------------------------------------------

IRTypeDecl
IRBuilderImpl::finalize_type_decl(const TypeDeclImpl& type_decl_impl)
{
  IRTypeDecl ir_type_decl;

  // Type name.
  ir_type_decl.name = type_decl_impl.name;

  // Fields.
  ir_type_decl.fields.reserve(type_decl_impl.fields.size());
  for (const auto& field : type_decl_impl.fields)
  {
    IRTypeField ir_type_field;

    // Field name.
    ir_type_field.identifier = field.name;

    // Field type.
    translate_IdentifierType(field.type, ir_type_field.type);

    ir_type_decl.fields.push_back(ir_type_field);
  }

  return ir_type_decl;
}

// -----------------------------------------------------------------------------

void
IRBuilderImpl::translate_IdentifierType(const IdentifierType& src,
  IRIdentifierType& dst) const
{
  dst.ref_type = translate_ValueRefType(src.ref_type);

  if (src.value.is<ValueType>())
  {
    dst.type = IdentifierType_ValueType;
    dst.value.set_IRValueType(translate_ValueType(src.value.get<ValueType>()));
  }
  else if (src.value.is<ArrayType>())
  {
    ArrayType array_type = src.value.get<ArrayType>();
    const ArrayTypeImpl& array_type_impl =
      array_type_store.store.at(array_type);

    IRArrayType ir_array_type;
    ir_array_type.len = array_type_impl.len;
    translate_IdentifierType(array_type_impl.type, ir_array_type.type);

    dst.type = IdentifierType_Array;
    dst.value.set_IRArrayType(ir_array_type);
  }
  else if (src.value.is<TypeDecl>())
  {
    TypeDecl type_decl = src.value.get<TypeDecl>();
    const TypeDeclImpl& type_decl_impl =
      type_decl_store.storage.at(type_decl->id);

    dst.type = IdentifierType_Identifier;
    dst.value.set_string(type_decl_impl.name);
  }
}

// -----------------------------------------------------------------------------

IRInstruction
IRBuilderImpl::translate_InstructionImpl(
  const FuncDefnStore::FuncDefnImpl& func_defn_impl,
  const InstructionImpl& instr_impl) const
{
  IRInstruction ir_instr;

  // Target.
  if (instr_impl.target)
  {
    ir_instr.target.set_string(std::to_string(instr_impl.target));
  }

  // Opcode.
  ir_instr.opcode = translate_InstrOpcode(instr_impl.opcode);

  // Type.
  if (instr_impl.type.is_initialized())
  {
    IRIdentifierType instr_type;
    translate_IdentifierType(instr_impl.type.get(), instr_type);
    ir_instr.type.set_IRIdentifierType(instr_type);
  }

  // Options.
  ir_instr.options = instr_impl.options;

  // Operands.
  ir_instr.oprds.reserve(instr_impl.oprds.size());
  for (const auto& oprd : instr_impl.oprds)
  {
    IROperand ir_oprd;

    if (oprd.is<bool>())
    {
      IRValue ir_value;
      ir_value.type = corevm::boolean;
      ir_value.value.set_bool(oprd.get<bool>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<uint8_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::ui8;
      ir_value.value.set_int(oprd.get<uint8_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<int8_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::i8;
      ir_value.value.set_int(oprd.get<int8_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<uint16_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::ui16;
      ir_value.value.set_int(oprd.get<uint16_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<int16_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::i16;
      ir_value.value.set_int(oprd.get<int16_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<uint32_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::ui32;
      ir_value.value.set_int(oprd.get<uint32_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<int32_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::i32;
      ir_value.value.set_int(oprd.get<int32_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<uint64_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::ui64;
      ir_value.value.set_long(oprd.get<uint64_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<int64_t>())
    {
      IRValue ir_value;
      ir_value.type = corevm::i64;
      ir_value.value.set_long(oprd.get<int64_t>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<float>())
    {
      IRValue ir_value;
      ir_value.type = corevm::spf;
      ir_value.value.set_float(oprd.get<float>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<double>())
    {
      IRValue ir_value;
      ir_value.type = corevm::dpf;
      ir_value.value.set_double(oprd.get<double>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<std::string>())
    {
      IRValue ir_value;
      ir_value.type = corevm::string;
      ir_value.value.set_string(oprd.get<std::string>());
      ir_oprd.value.set_IRValue(ir_value);
      ir_oprd.type = corevm::constant;
    }
    else if (oprd.is<FuncParam>())
    {
      FuncParam param_wrapper = oprd.get<FuncParam>();
      const FuncParamStore::FuncParamImpl& param_impl =
        func_defn_impl.param_store.storage.at(param_wrapper.value); 

      ir_oprd.value.set_string(param_impl.name);
      ir_oprd.type = corevm::ref;
    }
    else if (oprd.is<SSAVariable>())
    {
      SSAVariable var_wrapper = oprd.get<SSAVariable>();

      ir_oprd.value.set_string(std::to_string(var_wrapper.value));
      ir_oprd.type = corevm::ref;
    }

    ir_instr.oprds.push_back(ir_oprd);
  }

  // Labels.
  if (!instr_impl.labels.empty())
  {
    std::vector<corevm::IRLabel> ir_labels;
    ir_labels.reserve(instr_impl.labels.size());

    for (const auto& basic_block : instr_impl.labels)
    {
      const auto& bb_impl = func_defn_impl.bb_store.storage.at(basic_block);
      IRLabel ir_label;
      ir_label.name = bb_impl.name;
      ir_labels.push_back(ir_label);
    }
    ir_instr.labels.set_array(ir_labels);
  }
  else
  {
    ir_instr.labels.set_null();
  }

  return ir_instr;
}

// -----------------------------------------------------------------------------

IRBuilder::IRBuilder()
  :
  m_impl(new IRBuilderImpl())
{
}

// -----------------------------------------------------------------------------

IRBuilder::IRBuilder(const char* module_name)
  :
  m_impl(new IRBuilderImpl())
{
  m_impl->add_module_name(module_name);
}

// -----------------------------------------------------------------------------

void IRBuilder::add_author(const char* author_name)
{
  m_impl->add_author(author_name);
}

// -----------------------------------------------------------------------------

void IRBuilder::add_target_version(uint64_t target_version)
{
  m_impl->add_target_version(target_version);
}

// -----------------------------------------------------------------------------

void IRBuilder::add_timestamp(uint64_t timestamp)
{
  m_impl->add_timestamp(timestamp);
}

// -----------------------------------------------------------------------------

TypeDecl
IRBuilder::add_type(const std::string& type_name)
{
  return m_impl->add_type(type_name);
}

// -----------------------------------------------------------------------------

const char*
IRBuilder::get_type_decl_name(TypeDecl type_decl) const
{
  return m_impl->get_type_decl_name(type_decl);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_type_field(TypeDecl type_decl, ValueType field_type,
  ValueRefType ref_type, const std::string& field_name)
{
  m_impl->add_type_field(type_decl, IdentifierType{ref_type, field_type},
    field_name);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_type_field(TypeDecl type_decl, TypeDecl field_type,
  ValueRefType ref_type, const std::string& field_name)
{
  m_impl->add_type_field(type_decl, IdentifierType{ref_type, field_type},
    field_name);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_type_field(TypeDecl type_decl, ArrayType field_type,
  ValueRefType ref_type, const std::string& field_name)
{
  m_impl->add_type_field(type_decl, IdentifierType{ref_type, field_type},
    field_name);
}

// -----------------------------------------------------------------------------

bool
IRBuilder::has_field(TypeDecl type_decl, const std::string& field_name)
{
  return m_impl->has_field(type_decl, field_name);
}

// -----------------------------------------------------------------------------

ArrayType
IRBuilder::add_array_type(size_t len, TypeDecl element_type,
  ValueRefType ref_type)
{
  return m_impl->add_array_type(
    ArrayTypeImpl{len, IdentifierType{ref_type, element_type}});
}

// -----------------------------------------------------------------------------

ArrayType
IRBuilder::add_array_type(size_t len, ValueType element_type,
  ValueRefType ref_type)
{
  return m_impl->add_array_type(
    ArrayTypeImpl{len, IdentifierType{ref_type, element_type}});
}

// -----------------------------------------------------------------------------

ArrayType
IRBuilder::add_array_type(size_t len, ArrayType element_type,
  ValueRefType ref_type)
{
  return m_impl->add_array_type(
    ArrayTypeImpl{len, IdentifierType{ref_type, element_type}});
}

// -----------------------------------------------------------------------------

bool
IRBuilder::has_array_type(ArrayType array_type)
{
  return m_impl->has_array_type(array_type);
}

// -----------------------------------------------------------------------------

FuncDefn
IRBuilder::create_func_defn(const std::string& func_name, TypeDecl rettype,
  ValueRefType ref_type, const char* parent)
{
  return m_impl->create_func_defn(func_name,
    IdentifierType{ref_type, rettype}, parent);
}

// -----------------------------------------------------------------------------

FuncDefn
IRBuilder::create_func_defn(const std::string& func_name, ValueType rettype,
  ValueRefType ref_type, const char* parent)
{
  return m_impl->create_func_defn(func_name,
    IdentifierType{ref_type, rettype}, parent);
}

// -----------------------------------------------------------------------------

FuncDefn
IRBuilder::create_func_defn(const std::string& func_name, ArrayType rettype,
  ValueRefType ref_type, const char* parent)
{
  return m_impl->create_func_defn(func_name,
    IdentifierType{ref_type, rettype}, parent);
}

// -----------------------------------------------------------------------------

FuncParam
IRBuilder::add_func_parameter(FuncDefn func_defn, const std::string& param_name,
  TypeDecl param_type, ValueRefType ref_type)
{
  return m_impl->add_func_parameter(func_defn, param_name,
    IdentifierType{ref_type, param_type});
}

// -----------------------------------------------------------------------------

FuncParam
IRBuilder::add_func_parameter(FuncDefn func_defn, const std::string& param_name,
  ValueType param_type, ValueRefType ref_type)
{
  return m_impl->add_func_parameter(func_defn, param_name,
    IdentifierType{ref_type, param_type});
}

// -----------------------------------------------------------------------------

FuncParam
IRBuilder::add_func_parameter(FuncDefn func_defn, const std::string& param_name,
  ArrayType param_type, ValueRefType ref_type)
{
  return m_impl->add_func_parameter(func_defn, param_name,
    IdentifierType{ref_type, param_type});
}

// -----------------------------------------------------------------------------

BasicBlock
IRBuilder::create_basic_block(FuncDefn func_defn)
{
  return m_impl->create_basic_block(func_defn);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_alloca(FuncDefn func_defn, BasicBlock basic_block,
  AllocaType alloca_type, ValueType target_type, ValueRefType ref_type)
{
  return m_impl->add_alloca(func_defn, basic_block, alloca_type,
    IdentifierType{ref_type, target_type});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_alloca(FuncDefn func_defn, BasicBlock basic_block,
  AllocaType alloca_type, ArrayType target_type, ValueRefType ref_type)
{
  return m_impl->add_alloca(func_defn, basic_block, alloca_type,
    IdentifierType{ref_type, target_type});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_alloca(FuncDefn func_defn, BasicBlock basic_block,
  AllocaType alloca_type, TypeDecl target_type, ValueRefType ref_type)
{
  return m_impl->add_alloca(func_defn, basic_block, alloca_type,
    IdentifierType{ref_type, target_type});
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_alloca(FuncDefn func_defn, BasicBlock basic_block,
  AllocaType alloca_type, const std::string& target_type_name,
  ValueRefType ref_type)
{
  return m_impl->add_alloca(func_defn, basic_block, alloca_type,
    target_type_name, ref_type);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_load(FuncDefn func_defn, BasicBlock basic_block,
  ValueType value_type, ValueRefType ref_type, OperandValue oprd)
{
  return m_impl->add_load(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, oprd);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_load(FuncDefn func_defn, BasicBlock basic_block,
  ArrayType value_type, ValueRefType ref_type, OperandValue oprd)
{
  return m_impl->add_load(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, oprd);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_load(FuncDefn func_defn, BasicBlock basic_block,
  TypeDecl value_type, ValueRefType ref_type, OperandValue oprd)
{
  return m_impl->add_load(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, oprd);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_store(FuncDefn func_defn, BasicBlock basic_block,
  ValueType value_type, ValueRefType ref_type, OperandValue src,
  OperandValue dst)
{
  return m_impl->add_store(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, src, dst);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_store(FuncDefn func_defn, BasicBlock basic_block,
  ArrayType value_type, ValueRefType ref_type, OperandValue src,
  OperandValue dst)
{
  return m_impl->add_store(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, src, dst);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_store(FuncDefn func_defn, BasicBlock basic_block,
  TypeDecl value_type, ValueRefType ref_type, OperandValue src,
  OperandValue dst)
{
  return m_impl->add_store(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, src, dst);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_get_attribute(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue source, const std::string& attr_name)
{
  return m_impl->add_get_attribute(func_defn, basic_block, source, attr_name);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_set_attribute(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue target, OperandValue source, const std::string& attr_name)
{
  m_impl->add_set_attribute(func_defn, basic_block, target, source, attr_name);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_delete_attribute(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue source, const std::string& attr_name)
{
  m_impl->add_delete_attribute(func_defn, basic_block, source, attr_name);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_get_element(FuncDefn func_defn, BasicBlock basic_block,
  ValueType value_type, ValueRefType ref_type, OperandValue source,
  OperandValue idx)
{
  return m_impl->add_get_element(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, source, idx);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_get_element(FuncDefn func_defn, BasicBlock basic_block,
  ArrayType value_type, ValueRefType ref_type, OperandValue source,
  OperandValue idx)
{
  return m_impl->add_get_element(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, source, idx);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_get_element(FuncDefn func_defn, BasicBlock basic_block,
  TypeDecl value_type, ValueRefType ref_type, OperandValue source,
  OperandValue idx)
{
  return m_impl->add_get_element(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, source, idx);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_put_element(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue src, OperandValue dst, OperandValue idx)
{
  m_impl->add_put_element(func_defn, basic_block, src, dst, idx);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_len(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue oprd)
{
  return m_impl->add_len(func_defn, basic_block, oprd);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_ret(FuncDefn func_defn, BasicBlock basic_block,
  ValueType value_type, ValueRefType ref_type, OperandValue value)
{
  return m_impl->add_ret(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, value);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_ret(FuncDefn func_defn, BasicBlock basic_block,
  ArrayType value_type, ValueRefType ref_type, OperandValue value)
{
  return m_impl->add_ret(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, value);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_ret(FuncDefn func_defn, BasicBlock basic_block,
  TypeDecl value_type, ValueRefType ref_type, OperandValue value)
{
  return m_impl->add_ret(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, value);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_unary_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, ValueType value_type, OperandValue source)
{
  return m_impl->add_unary_instr(func_defn, basic_block, opcode,
    value_type, source);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_binary_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, ValueType value_type, OperandValue lhs, OperandValue rhs)
{
  return m_impl->add_binary_instr(func_defn, basic_block, opcode,
    value_type, lhs, rhs);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_unary_bitwise_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, OperandValue oprd)
{
  // NOTE: return type for bitwise instructions is ui64 according to spec.
  return add_unary_instr(func_defn, basic_block, opcode,
    ValueTypeUInt64, oprd);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_binary_bitwise_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, OperandValue lhs, OperandValue rhs)
{
  // NOTE: return type for bitwise instructions is ui64 according to spec.
  return add_binary_instr(func_defn, basic_block, opcode,
    ValueTypeUInt64, lhs, rhs);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_unary_logical_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, OperandValue oprd)
{
  // NOTE: return type for logical instructions is boolean according to spec.
  return add_unary_instr(func_defn, basic_block, opcode,
    ValueTypeBoolean, oprd);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_binary_logical_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, OperandValue lhs, OperandValue rhs)
{
  // NOTE: return type for logical instructions is boolean according to spec.
  return add_binary_instr(func_defn, basic_block, opcode,
    ValueTypeBoolean, lhs, rhs);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_equality_instr(FuncDefn func_defn, BasicBlock basic_block,
  InstrOpcode opcode, OperandValue lhs, OperandValue rhs)
{
  return m_impl->add_equality_instr(func_defn, basic_block, opcode, lhs, rhs);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_cmp(FuncDefn func_defn, BasicBlock basic_block, OperandValue lhs,
  OperandValue rhs)
{
  return m_impl->add_cmp(func_defn, basic_block, lhs, rhs);
}

// -----------------------------------------------------------------------------

SSAVariable
IRBuilder::add_call(FuncDefn func_defn, BasicBlock basic_block,
  ValueType value_type, ValueRefType ref_type, const std::string& callee,
  const std::vector<OperandValue>& args)
{
  return m_impl->add_call(func_defn, basic_block,
    IdentifierType{ref_type, value_type}, callee, args);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_conditional_branch(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue predicate, BasicBlock bb1, BasicBlock bb2)
{
  m_impl->add_conditional_branch(func_defn, basic_block, predicate, bb1, bb2);
}

// -----------------------------------------------------------------------------

void
IRBuilder::add_switch(FuncDefn func_defn, BasicBlock basic_block,
  OperandValue predicate, const std::vector<OperandValue>& cases,
  const std::vector<BasicBlock>& target_blocks)
{
  m_impl->add_switch(func_defn, basic_block, predicate, cases, target_blocks);
}

// -----------------------------------------------------------------------------

bool
IRBuilder::finalize(std::unique_ptr<IRModule>& module, std::string& msg,
  bool verify)
{
  return m_impl->finalize(module, msg, verify);
}

// -----------------------------------------------------------------------------

} /* end namespace ir */
} /* end namespace corevm */

#if defined(__clang__) and __clang__
  #pragma clang diagnostic pop
#endif

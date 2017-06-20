/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2016 Yanzheng Li

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
#ifndef COREVM_FORMAT_UTIL_H_
#define COREVM_FORMAT_UTIL_H_

#include "common/variant/variant.h"
#include "format.h"
#include <array>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

/** Utilities for handling coreVM IR entities. */

namespace corevm {
namespace ir {

/**
 * Type representing the set of allowed values for IR function definition
 * options.
 */
enum class FuncDefnOption : int64_t {
  CONSTEXPR = (0x01 << 0),
  INLINE = (0x01 << 1),
  TAIL_DUPLICATION = (0x01 << 2),
  LOOP_SIMPLIFY = (0x01 << 3),
};

/**
 * FuncDefnOption <--> string representation map.
 */
extern std::array<std::tuple<FuncDefnOption, const char*>, 4>
  FuncDefnOptionToStrArray;

/**
 * Add a function definition option to an value set.
 * Returns the new value set.
 */
inline constexpr int64_t
add_func_defn_option(int64_t val, int64_t new_val)
{
  return (val | new_val);
}

/**
 * Determine if a particular function definition option has been set.
 */
inline constexpr bool
is_func_defn_option_enabled(int64_t val, FuncDefnOption opt)
{
  return (val & static_cast<int64_t>(opt)) == static_cast<int64_t>(opt);
}

/**
 * Determine the function definition option from its string representation.
 * Return 0 if it cannot be determined.
 */
int64_t interpret_func_defn_option(const std::string&);

/**
 * Convert IR opcode string representation to enum value.
 */
corevm::IROpcode string_to_IROpcode(const std::string& val);

/**
 * Convert IR opcode to string representation.
 */
const char* IROpcode_to_string(corevm::IROpcode);

/**
 * Convert an instance of `IRValueType` to its string representation.
 */
const char* IRValueType_to_string(IRValueType value);

/**
 * Convert an instance of `IRValueRefType` to its string representation.
 */
const char* IRValueRefType_to_string(IRValueRefType val);

/**
 * Generic type representing an IR definition, it can be either a type
 * or function definition.
 */
using IRDefn = common::variant::variant<corevm::IRClosure, corevm::IRTypeDecl,
                                        corevm::IRIntrinsicDecl>;

/**
 * IR module metadata key-value pair.
 */
typedef std::pair<std::string, std::string> MetadataPair;

/**
 * Set metadata and definitions to an IR module.
 */
void set_metadata_and_definitions(const std::vector<MetadataPair>&,
                                  const std::vector<IRDefn>&,
                                  corevm::IRModule&);

/**
 * Add a metadata key-value pair to a IR module.
 */
void set_metadata(const MetadataPair&, corevm::IRModule&);

/**
 * Set a set of metadata key-value pair to a IR module.
 */
void set_metadata(const std::vector<MetadataPair>&, corevm::IRModule&);

/**
 * Determines if two IR identifier types are compatible.
 *
 * In the current implementation, two types are compatibility
 * if both are of numeric or boolean types.
 */
bool are_compatible_types(const corevm::IRIdentifierType&,
                          const corevm::IRIdentifierType&);

/**
 * Equality check between two IR identifier types.
 */
bool operator==(const corevm::IRIdentifierType&,
                const corevm::IRIdentifierType&);

/**
 * Equality check between two IR identifier types.
 */
bool operator!=(const corevm::IRIdentifierType&,
                const corevm::IRIdentifierType&);

/**
 * Equality check between two IR array types.
 */
bool operator==(const corevm::IRArrayType&, const corevm::IRArrayType&);

/**
 * Equality check between two IR array types.
 */
bool operator!=(const corevm::IRArrayType&, const corevm::IRArrayType&);

/**
 * Determines if the specified IR value type is of 'boolean' value type.
 */
bool is_ir_value_boolean_type(const corevm::IRValueType&);

/**
 * Determines if the specified IR value type is of integer value type.
 */
bool is_ir_value_integer_type(const corevm::IRValueType&);

/**
 * Determines if the specified IR value type is of integer or float-point
 * value type.
 */
bool is_ir_value_numeric_type(const corevm::IRValueType&);

/**
 * Determines if the specified IR value type is of numeric or 'boolean'
 * value type.
 */
bool is_ir_value_numeric_or_boolean_type(const corevm::IRValueType&);

/**
 * Determines if the specified IR value type is of 'string' value type.
 */
bool is_ir_value_string_type(const corevm::IRValueType&);

/**
 * Determines if the specified IR value type is of 'object' value type.
 */
bool is_ir_value_object_type(const corevm::IRValueType&);

/**
 * Get the target identifier type of the specified instruction.
 */
corevm::IRIdentifierType get_type_of_instr(const corevm::IRInstruction&);

/**
 * Creates an instance of identifier type of the specified value type.
 */
corevm::IRIdentifierType create_ir_value_type(IRValueType);

/**
 * Creates an instance of identifier type of 'boolean' value type.
 */
corevm::IRIdentifierType create_ir_boolean_value_type();

/**
 * Creates an instance of identifier type of 'i32' value type.
 */
corevm::IRIdentifierType create_ir_i32_value_type();

/**
 * Creates an instance of identifier type of 'void' value type.
 */
corevm::IRIdentifierType create_ir_void_value_type();

/**
 * Determines whether a type declaration has the specified field.
 */
bool type_decl_has_field(const corevm::IRTypeDecl&, const std::string&);

/**
 * Get the identifier type of a type field.
 */
corevm::IRIdentifierType get_type_decl_field_type(const corevm::IRTypeDecl&,
                                                  const std::string&);

} /* end namespace ir */
} /* end namespace corevm */

#endif /* COREVM_FORMAT_UTIL_H_ */

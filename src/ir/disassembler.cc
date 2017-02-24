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
#include "disassembler.h"
#include "format.h"
#include "format_util.h"
#include <iostream>


namespace corevm {
namespace ir {

// -----------------------------------------------------------------------------

Disassembler::Options::Options()
  :
  emit_newlines(true)
{
}

// -----------------------------------------------------------------------------

Disassembler::Disassembler(Options opts)
  :
  m_opts(opts)
{
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRModule& module, std::ostream& stream) const
{
  disassemble(module.meta, stream);

  for (const auto& val : module.types)
  {
    disassemble(val, stream);
  }

  for (const auto& val : module.intrinsic_decls)
  {
    disassemble(val, stream);
  }

  for (const auto& val : module.closures)
  {
    disassemble(val, stream);
  }
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRModuleMeta& meta,
  std::ostream& stream) const
{
  if (!meta.name.empty())
  {
    stream << "\"module name\" : \"" << meta.name << '\"';
    emit_newline(stream);
  }

  if (meta.format_version)
  {
    stream << "\"format version\" : \"" << meta.format_version << '\"';
    emit_newline(stream);
  }

  if (meta.target_version)
  {
    stream << "\"target version\" : \"" << meta.target_version << '\"';
    emit_newline(stream);
  }

  if (!meta.path.empty())
  {
    stream << "\"path\" : \"" << meta.path << '\"';
    emit_newline(stream);
  }

  if (!meta.author.empty())
  {
    stream << "\"author\" : \"" << meta.author << '\"';
    emit_newline(stream);
  }

  if (meta.timestamp)
  {
    stream << "\"timestamp\" : \"" << meta.timestamp << '\"';
    emit_newline(stream);
  }

  emit_newline(stream);
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRTypeDecl& decl, std::ostream& stream) const
{
  if (!decl.attributes.empty())
  {
    stream << '[';

    for (size_t i = 0; i < decl.attributes.size(); ++i)
    {
      disassemble(decl.attributes[i], stream);
      if (i + 1 < decl.attributes.size())
      {
        stream << ", ";
      }
    }

    stream << ']';
    stream << std::endl;
  }

  stream << "type " << decl.name << " {";
  emit_newline(stream);

  for (const auto& field : decl.fields)
  {
    stream << "    ";
    disassemble(field, stream);
  }
  stream << '}';

  emit_newline(stream);
  emit_newline(stream);
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRTypeField& field, std::ostream& stream) const
{
  disassemble(field.type, stream);
  stream << " " << field.identifier << ';';
  emit_newline(stream);
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRTypeAttribute& attribute,
  std::ostream& stream) const
{
  stream << attribute.name << '=' << attribute.value;
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRIntrinsicDecl& intrinsic_decl,
  std::ostream& stream) const
{
  stream << "declare ";
  disassemble(intrinsic_decl.rettype, stream);
  stream << " " << intrinsic_decl.name << "(";

  // Parameters.
  size_t len = intrinsic_decl.parameters.size();
  for (const auto& parameter : intrinsic_decl.parameters)
  {
    disassemble(parameter, stream);
    if (len-- > 1)
    {
      stream << ", ";
    }
  }
  stream << ")";
  stream << std::endl;
  stream << std::endl;
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRClosure& closure, std::ostream& stream) const
{
  stream << "def ";
  disassemble(closure.rettype, stream);
  stream << " " << closure.name << "(";

  size_t len = closure.parameters.size();
  bool hasPrevArg = false;

  // Parameters.
  for (const auto& parameter : closure.parameters)
  {
    disassemble(parameter, stream);
    if (len-- > 1)
    {
      stream << ", ";
    }
    hasPrevArg = true;
  }

  // Positional arguments.
  if (!closure.positional_args.empty())
  {
    if (hasPrevArg)
    {
      stream << ", ";
    }
    stream << '*' << closure.positional_args;
    hasPrevArg = true;
  }

  // Keyword arguments.
  if (!closure.keyword_args.empty())
  {
    if (hasPrevArg)
    {
      stream << ", ";
    }
    stream << "**" << closure.keyword_args;
  }
  stream << ")";

  if (!closure.parent.empty())
  {
    stream <<  " : " << closure.parent;
  }

  if (closure.options)
  {
    std::vector<const char*> options;

    for (size_t i = 0; i < FuncDefnOptionToStrArray.size(); ++i)
    {
      if (is_func_defn_option_enabled(closure.options,
          std::get<0>(FuncDefnOptionToStrArray[i])))
      {
        options.push_back(std::get<1>(FuncDefnOptionToStrArray[i]));
      }
    } 

    if (!options.empty())
    {
      stream << " [";
      for (size_t i = 0; i < options.size(); ++i)
      {
        stream << options[i];
        if (i + 1 < options.size())
        {
          stream << ' ';
        }
      }
      stream << ']';
    }
  }

  stream << " {";
  emit_newline(stream);

  for (const auto& block : closure.blocks)
  {
    disassemble(block, stream);
  }
  stream << '}';

  emit_newline(stream);
  emit_newline(stream);
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRParameter& parameter,
  std::ostream& stream) const
{
  disassemble(parameter.type, stream);
  stream << " " << parameter.identifier;
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRBasicBlock& block, std::ostream& stream) const
{
  stream << block.label << ":";
  emit_newline(stream);

  for (const auto& instr : block.body)
  {
    stream << "    ";
    disassemble(instr, stream);
  }
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRInstruction& instr,
  std::ostream& stream) const
{
  if (!instr.target.is_null())
  {
    stream << "%" << instr.target.get_string() << " = ";
  }
  stream << IROpcode_to_string(instr.opcode);

  if (!instr.options.empty())
  {
    stream << " [ ";
    for (const auto& option : instr.options)
    {
      stream << option << ' ';
    }
    stream << "]";
  }

  if (!instr.type.is_null())
  {
    stream << " ";
    disassemble(instr.type.get_IRIdentifierType(), stream);
  }

  if (!instr.oprds.empty())
  {
    stream << " ";
    for (size_t i = 0; i < instr.oprds.size(); ++i)
    {
      disassemble(instr.oprds[i], stream);
      if (i < instr.oprds.size() - 1)
      {
        stream << " ";
      }
    }
  }

  if (!instr.labels.is_null())
  {
    const auto& labels = instr.labels.get_array();
    if (!labels.empty())
    {
      size_t len = labels.size();
      stream << " [ ";
      for (const auto& label : labels)
      {
        disassemble(label, stream);
        if (len-- > 1)
        {
          stream << ", ";
        }
      }
      stream << " ]";
    }
  }
  stream << ';';
  emit_newline(stream);
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRIdentifierType& identifier_type,
  std::ostream& stream) const
{
  switch (identifier_type.type)
  {
  case IdentifierType_Identifier:
    stream << identifier_type.value.get_string();
    break;
  case IdentifierType_Array:
    disassemble(identifier_type.value.get_IRArrayType(), stream);
    break;
  case IdentifierType_ValueType:
    stream << IRValueType_to_string(identifier_type.value.get_IRValueType());
    break;
  }

  stream << IRValueRefType_to_string(identifier_type.ref_type);
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRArrayType& array_type,
  std::ostream& stream) const
{
  stream << "array ";
  stream << "[ " << array_type.len << " * ";
  disassemble(array_type.type, stream);
  stream << " ]";
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRValue& val, std::ostream& stream) const
{
  stream << IRValueType_to_string(val.type) << " ";

  switch (val.value.idx())
  {
  case 0:
    // do nothing.
    stream << val.value.get_bool();
    break;
  case 1:
    stream << val.value.get_bool();
    break;
  case 2:
    stream << val.value.get_int();
    break;
  case 3:
    stream << val.value.get_long();
    break;
  case 4:
    stream << val.value.get_float();
    break;
  case 5:
    stream << val.value.get_double();
    break;
  case 6:
    stream << '"' << val.value.get_string() << '"';
    break;
  }
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IROperand& oprd, std::ostream& stream) const
{
  if (oprd.type == IROperandType::constant)
  {
    disassemble(oprd.value.get_IRValue(), stream);
  }
  else
  {
    stream << "%" << oprd.value.get_string();
  }
}

// -----------------------------------------------------------------------------

void
Disassembler::disassemble(const IRLabel& label, std::ostream& stream) const
{
  stream << "label #" << label.name;
}

// -----------------------------------------------------------------------------

void Disassembler::emit_newline(std::ostream& stream) const
{
  if (m_opts.emit_newlines)
  {
    stream << std::endl;
  }
}

// -----------------------------------------------------------------------------

} /* end namespace ir */
} /* end namespace corevm */

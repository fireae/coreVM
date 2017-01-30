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
#ifndef COREVM_IR_DISASSEMBLER_H_
#define COREVM_IR_DISASSEMBLER_H_

#include "fwd.h"
#include <iosfwd>

namespace corevm {
namespace ir {

class Disassembler
{
public:
  struct Options
  {
    bool emit_newlines;

    Options();
  };

  explicit Disassembler(Options);

  void disassemble(const IRModule&, std::ostream&) const;

private:

  void disassemble(const IRModuleMeta&, std::ostream&) const;

  void disassemble(const IRTypeDecl&, std::ostream&) const;

  void disassemble(const IRTypeField&, std::ostream&) const;

  void disassemble(const IRClosure&, std::ostream&) const;

  void disassemble(const IRParameter&, std::ostream&) const;

  void disassemble(const IRBasicBlock&, std::ostream&) const;

  void disassemble(const IRInstruction&, std::ostream&) const;

  void disassemble(const IRIdentifierType&, std::ostream&) const;

  void disassemble(const IRArrayType&, std::ostream&) const;

  void disassemble(const IRValue&, std::ostream&) const;

  void disassemble(const IROperand&, std::ostream&) const;

  void disassemble(const IRLabel&, std::ostream&) const;

private:
  void emit_newline(std::ostream&) const;

private:
  const Options m_opts;
};

} /* end namespace ir */
} /* end namespace corevm */

#endif /* COREVM_IR_DISASSEMBLER_H_ */

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
#include "ir/reader.h"
#include "ir/format.h"
#include "ir/verifier.h"
#include "ir/disassembler.h"

#include <sneaker/utility/cmdline_program.h>

#include <cstdio>
#include <string>

#include <cassert>
#include <fstream>
#include <iostream>


// -----------------------------------------------------------------------------

class IRDisassembler : public sneaker::utility::cmdline_program
{
public:
  IRDisassembler();

  virtual ~IRDisassembler() {}

protected:
  virtual int do_run();

  virtual bool check_parameters() const;

private:
  std::string m_input;
  std::string m_output;
};

// -----------------------------------------------------------------------------

IRDisassembler::IRDisassembler()
  :
  sneaker::utility::cmdline_program("coreVM IR disassembler"),
  m_input(),
  m_output()
{
  add_positional_parameter("input", 1);
  add_string_parameter("input", "input file", &m_input);
  add_string_parameter("output", "output file", &m_output);
}

// -----------------------------------------------------------------------------

bool
IRDisassembler::check_parameters() const
{
  return !m_input.empty();
}

// -----------------------------------------------------------------------------

int
IRDisassembler::do_run()
{
  corevm::IRModule module;
  std::string err;

  bool res = corevm::ir::read_module_from_file(
    m_input.c_str(), module, err);

  if (!res)
  {
    printf("Error while reading from %s :\n", m_input.c_str());
    printf("%s\n", err.c_str());
    return -1;
  }

  corevm::ir::Verifier verifier(module);
  res = verifier.run(err);

  if (!res)
  {
    printf("Invalid module read from %s :\n", m_input.c_str());
    printf("%s\n", err.c_str());
    return -1;
  }

  corevm::ir::Disassembler::Options opts;
  corevm::ir::Disassembler disassembler(opts);

  if (m_output.empty())
  {
    disassembler.disassemble(module, std::cout);
  }
  else
  {
    std::ofstream stream(m_output.c_str(), std::ofstream::out);
    if (!stream.good())
    {
      printf("Error writing file to : %s\n", m_output.c_str());
      return -1;
    }
    else
    {
      disassembler.disassemble(module, stream);
    }
  }

  return 0;
}

// -----------------------------------------------------------------------------

int main(int argc, char** argv)
{
  IRDisassembler program;
  return program.run(argc, argv);
}

// -----------------------------------------------------------------------------

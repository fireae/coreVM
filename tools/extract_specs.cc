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
#include "dyobj/flags.h"
#include "runtime/common.h"
#include "runtime/instr_info.h"

#include <sneaker/utility/cmdline_program.h>

#include <fstream>
#include <ostream>
#include <ios>
#include <string>

/**
 * Command-line tool that extracts the coreVM runtime specification.
 * Runtime specification may include the opcode values of the coreVM
 * instruction set, and the flag values for managing dynamic objects.
 */
class ExtractSpecs : public sneaker::utility::cmdline_program
{
public:
  /**
   * Default constructor.
   */
  ExtractSpecs();

  /**
   * Default destructor.
   */
  virtual ~ExtractSpecs();

protected:
  virtual int do_run();

  virtual bool check_parameters() const;

private:
  void extract_instrs(std::ostream&) const;
  void extract_instr_info(std::ostream&) const;
  void extract_flags_info(std::ostream&) const;

  std::string m_output;
};


// -----------------------------------------------------------------------------

static const char* INDENTATION = "    ";
static const char* DOUBLE_QUOTE= "\"";
static const char* INSTRS = "INSTRS";
static const char* INSTR_STR_TO_CODE_MAP = "INSTR_STR_TO_CODE_MAP";
static const char* DYOBJ_FLAG_STR_TO_VALUE_MAP = "DYOBJ_FLAG_STR_TO_VALUE_MAP";

// -----------------------------------------------------------------------------

ExtractSpecs::ExtractSpecs()
  :
  sneaker::utility::cmdline_program("Extract coreVM runtime specification"),
  m_output()
{
  add_positional_parameter("output", 1);
  add_string_parameter("output", "Output file", &m_output);
}

// -----------------------------------------------------------------------------

/* virtual */
ExtractSpecs::~ExtractSpecs()
{
  // Do nothing here.
}

// -----------------------------------------------------------------------------

bool
ExtractSpecs::check_parameters() const
{
  return true;
}

// -----------------------------------------------------------------------------

int
ExtractSpecs::do_run()
{
  std::streambuf* buf = nullptr;
  std::ofstream fd(m_output.c_str(), std::ios::out);

  if (fd.is_open())
  {
    buf = fd.rdbuf();
  }
  else
  {
    buf = std::cout.rdbuf();
  }

  std::ostream stream(buf);

  stream << "{" << std::endl;

  stream << INDENTATION << DOUBLE_QUOTE << INSTRS
    << DOUBLE_QUOTE << ": ";
  extract_instrs(stream);
  stream << "," << std::endl;

  stream << INDENTATION << DOUBLE_QUOTE << INSTR_STR_TO_CODE_MAP
    << DOUBLE_QUOTE << ": ";
  extract_instr_info(stream);
  stream << "," << std::endl;

  stream << INDENTATION << DOUBLE_QUOTE << DYOBJ_FLAG_STR_TO_VALUE_MAP
    << DOUBLE_QUOTE << ": ";
  extract_flags_info(stream);
  stream << std::endl;

  stream << "}" << std::endl;

  fd.close();

  return 0;
}

// -----------------------------------------------------------------------------

void
ExtractSpecs::extract_instrs(std::ostream& stream) const
{
  stream << "[" << std::endl;

  for (size_t i = 0; i < corevm::runtime::InstrEnum::INSTR_CODE_MAX; ++i)
  {
    const auto code = static_cast<corevm::runtime::instr_code_t>(i);
    const auto& info = corevm::runtime::InstrSetInfo::instr_infos[code];

    stream << INDENTATION << INDENTATION << DOUBLE_QUOTE << info.name
      << DOUBLE_QUOTE;

    if (i + 1 != corevm::runtime::InstrEnum::INSTR_CODE_MAX)
    {
      stream << ",";
    }

    stream << std::endl;
  }

  stream << INDENTATION << "]";
}

// -----------------------------------------------------------------------------

void
ExtractSpecs::extract_instr_info(std::ostream& stream) const
{
  stream << "{" << std::endl;

  for (size_t i = 0; i < corevm::runtime::InstrEnum::INSTR_CODE_MAX; ++i)
  {
    const auto code = static_cast<corevm::runtime::instr_code_t>(i);
    const auto& info = corevm::runtime::InstrSetInfo::instr_infos[code];

    stream << INDENTATION << INDENTATION << DOUBLE_QUOTE << info.name
      << DOUBLE_QUOTE << ": " << code;

    if (i + 1 != corevm::runtime::InstrEnum::INSTR_CODE_MAX)
    {
      stream << ",";
    }

    stream << std::endl;
  }

  stream << INDENTATION << "}";
}

// -----------------------------------------------------------------------------

void
ExtractSpecs::extract_flags_info(std::ostream& stream) const
{
  auto array_size = corevm::dyobj::DYOBJ_FLAG_VALUES_ARRAY.size();

  stream << "{" << std::endl;

  for (size_t i = 0; i < array_size; ++i)
  {
    size_t flag_value = i;
    const char* flag_str = corevm::dyobj::DYOBJ_FLAG_VALUES_ARRAY[i];

    stream << INDENTATION << INDENTATION << DOUBLE_QUOTE << std::string(flag_str)
      << DOUBLE_QUOTE << ": " << flag_value;

    if (i + 1 != array_size)
    {
      stream << ",";
    }

    stream << std::endl;
  }

  stream << INDENTATION << "}";
}

// -----------------------------------------------------------------------------

int main(int argc, char** argv)
{
  ExtractSpecs program;
  return program.run(argc, argv);
}

// -----------------------------------------------------------------------------

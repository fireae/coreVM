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
#include "writer.h"
#include "format.h"

#include <avro/Compiler.hh>
#include <avro/DataFile.hh>
#include <avro/Decoder.hh>
#include <avro/Encoder.hh>
#include <avro/ValidSchema.hh>

#include <cstdio>
#include <fstream>

namespace corevm {
namespace ir {

// -----------------------------------------------------------------------------

bool
write_module_to_file(const IRModule& module, const char* schema_path,
                     const char* output_path, std::string& err)
{
  std::ifstream schema_ifs(schema_path);

  if (!(schema_ifs.good() && schema_ifs.is_open())) {
    char buf[256] = {0};
    snprintf(buf, sizeof(buf), "Cannot open schema file: %s", output_path);
    err.assign(buf);
    return false;
  }

  try {
    avro::ValidSchema schema;
    avro::compileJsonSchema(schema_ifs, schema);

    avro::DataFileWriter<corevm::IRModule> writer(output_path, schema);
    writer.write(module);
    writer.close();
  } catch (const std::exception& ex) {
    char buf[256] = {0};
    snprintf(buf, sizeof(buf), "Error: %s", ex.what());
    err.assign(buf);
  } catch (...) {
    err.assign("Unknown error during module serialization");
  }

  schema_ifs.close();

  return err.empty();
}

// -----------------------------------------------------------------------------

} /* end namespace ir */
} /* end namespace corevm */

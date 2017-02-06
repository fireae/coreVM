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
#ifndef COREVM_API_IR_VERSION_H_
#define COREVM_API_IR_VERSION_H_

#include <cstdint>

namespace corevm {
namespace api {
namespace ir {

/**
 * Denotes the current version of coreVM IR format.
 *
 * The integral value should be interpreted as follows:
 *
 *   * IR_VERSION % 100 is the patch level.
 *   * IR_VERSION / 100 % 1000 is the minor version.
 *   * IR_VERSION / 100000 is the major version.
 */
enum : uint32_t
{
  IR_VERSION = 100
};

} /* end namespace ir */
} /* end namespace api */
} /* end namespace corevm */

#endif /* COREVM_API_IR_VERSION_H_ */

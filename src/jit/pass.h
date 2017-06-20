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
#ifndef COREVM_JIT_PASS_H_
#define COREVM_JIT_PASS_H_

#include "ir/fwd.h"
#include <cstdint>

namespace corevm {
namespace jit {

/**
 * Abstraction of a generic "pass" used in the just-in-time compilation
 * pipeline.
 *
 * A "pass" is an entity that encapsulates the logic for performing a certain
 * type of operation on an input IR module, or any of its constituent entities.
 * There are currently two types of passes: analysis pass and transformation
 * pass.
 *
 * Analysis passes perform analyses on the input module and may generate
 * intermediate data that are used to facilitate transformation passes, hence
 * they take const-references to their inputs and do not modify the inputs.
 *
 * Transformation passes perform optimizations or other operations on the input
 * module or any of its constituent entities to facilitate just-in-time
 * compilation. Therefore, they take non-const references on their inputs and
 * may modify the inputs.
 *
 * All analysis and transformation passes work independently, as in they have no
 * obligated relations with other types of passes. However, it's desirable to
 * chain transformations in the right order in the JIT pipeline
 * (by using `PassManager`) for optimal results.
 */
class Pass {
public:
  /**
   * Types of passes. Denotes the granularity of the level of entities
   * that a particular pass may operate on.
   */
  enum PassType : uint32_t {
    PassType_Module = 0x01,
    PassType_Function,
    PassType_BasicBlock,
    PassType_Instr
  };

  /**
   * Default destructor.
   */
  virtual ~Pass()
  {
  }

  /**
   * Initialization steps before a pass gets run.
   * Default implementation does nothing, to be overriden in subclasses.
   */
  virtual void init(const IRModule&);

  /**
   * Clean up steps after a pass gets run.
   * Default implementation does nothing, to be overriden in subclasses.
   */
  virtual void finalize(const IRModule&);
};

} /* end namespace jit */
} /* end namespace corevm */

#endif /* COREVM_JIT_PASS_H_ */

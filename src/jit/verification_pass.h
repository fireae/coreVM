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
#ifndef COREVM_VERIFICATION_PASS_H_
#define COREVM_VERIFICATION_PASS_H_

#include "analysis_pass.h"


namespace corevm {

/** Forward declaration. */
namespace ir {
struct IRModuleIndex;
} /* end namespace ir */

namespace jit {

/**
 * A specialized type of `AnalysisResult` that holds the index of an IR module
 * as the result from running `VerificationPass`.
 */
struct IRModuleIndexAnalysisResult : public AnalysisResult
{
virtual ~IRModuleIndexAnalysisResult();
mutable std::unique_ptr<ir::IRModuleIndex> module_index;
};

/**
 * Class encapsulates the logic for running verification on an input IR module.
 */
class VerificationPass : public AnalysisPass
{
public:
  /**
   * Name of the pass.
   */
  static const char* Name;

  /**
   * Type of the pass.
   */
  static const Pass::PassType Type;

  /**
   * Default constructor.
   */
  VerificationPass();

  /**
   * Returns the analysis result of this pass, of type `AnalysisResult`.
   */
  virtual std::shared_ptr<const AnalysisResult> get_analysis_result() const;

  /**
   * Performs analysis operation on the specified IR module.
   *
   * Returns a boolean indicating whether the operation is successful.
   */
  virtual bool run(const IRModule&, const AnalysisResult* = nullptr);

private:
  std::shared_ptr<const IRModuleIndexAnalysisResult> m_analysis_result;
};

} /* end namespace jit */
} /* end namespace corevm */

#endif /* COREVM_VERIFICATION_PASS_H_ */

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
#include "jit/static_pass_runner.h"
#include "jit/analysis_pass.h"
#include "jit/transform_pass.h"
#include "ir/format.h"

#include <gtest/gtest.h>


// -----------------------------------------------------------------------------

class StaticPassRunnerUnitTest : public ::testing::Test
{
public:
  class DummyAnalysisPass : public corevm::jit::AnalysisPass
  {
  public:
    static const char* Name;

    virtual bool run(const corevm::IRModule&, const corevm::jit::AnalysisResult*)
    {
      StaticPassRunnerUnitTest::passed_count++;
      return true;
    }
  };

  class DummyTransformPass : public corevm::jit::TransformPass
  {
  public:
    static const char* Name;

    virtual bool run(corevm::IRModule&, const corevm::jit::AnalysisResult*)
    {
      StaticPassRunnerUnitTest::passed_count++;
      return true;
    }
  };

  class BadAnalysisPass : public corevm::jit::AnalysisPass
  {
  public:
    static const char* Name;

    virtual bool run(const corevm::IRModule&, const corevm::jit::AnalysisResult*)
    {
      return false;
    }
  };

  virtual void SetUp()
  {
    StaticPassRunnerUnitTest::passed_count = 0;
  }

  virtual void TearDown()
  {
    StaticPassRunnerUnitTest::passed_count = 0;
  }

  static uint32_t passed_count;
};

uint32_t StaticPassRunnerUnitTest::passed_count = 0;
const char* StaticPassRunnerUnitTest::DummyAnalysisPass::Name = "Dummy Analysis Pass";
const char* StaticPassRunnerUnitTest::DummyTransformPass::Name = "Dummy Transform Pass";
const char* StaticPassRunnerUnitTest::BadAnalysisPass::Name = "Bad Analysis Pass";

// -----------------------------------------------------------------------------

TEST_F(StaticPassRunnerUnitTest, TestAddPassAndRun)
{
  ASSERT_EQ(0, StaticPassRunnerUnitTest::passed_count);

  corevm::jit::StaticPassRunner manager;
  corevm::IRModule module;

  manager.run_pass<
    StaticPassRunnerUnitTest::DummyAnalysisPass>(module).
      run_pass<StaticPassRunnerUnitTest::DummyTransformPass>(module);
  
  ASSERT_EQ(2, StaticPassRunnerUnitTest::passed_count);

  ASSERT_EQ(true, manager.success());
}

// -----------------------------------------------------------------------------

TEST_F(StaticPassRunnerUnitTest, TestAddBadPassAndRun)
{
  ASSERT_EQ(0, StaticPassRunnerUnitTest::passed_count);

  corevm::jit::StaticPassRunner manager;
  corevm::IRModule module;

  manager.run_pass<
    StaticPassRunnerUnitTest::BadAnalysisPass>(module).
      run_pass<StaticPassRunnerUnitTest::DummyAnalysisPass>(module);
  
  ASSERT_EQ(0, StaticPassRunnerUnitTest::passed_count);

  ASSERT_EQ(false, manager.success()); 
  ASSERT_STREQ(StaticPassRunnerUnitTest::BadAnalysisPass::Name, manager.msg().c_str());
}

// -----------------------------------------------------------------------------

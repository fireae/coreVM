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
#include "frontend/configuration.h"

#include <gtest/gtest.h>

#include <fstream>
#include <string>


// -----------------------------------------------------------------------------

class ConfigurationUnitTest : public ::testing::Test
{
protected:
  static const char* PATH;

  virtual void SetUp()
  {
    std::ofstream f(PATH, std::ios::binary);
    f << this->content();
    f.close();
  }

  virtual void TearDown()
  {
    remove(PATH);
  }

  virtual const std::string content()
  {
    static const std::string content(
      "{"
        "\"heap-alloc-size\": 2048,"
        "\"pool-alloc-size\": 1024,"
        "\"gc-interval\": 100,"
        "\"gc-flag\": 1,"
        "\"format\": \"binary\","
        "\"logging\": \"stdout\""
      "}"
    );

    return content;
  }
};

// -----------------------------------------------------------------------------

const char* ConfigurationUnitTest::PATH = "./sample-config.config";

// -----------------------------------------------------------------------------

TEST_F(ConfigurationUnitTest, TestLoadSuccessful)
{
  auto configuration = corevm::frontend::Configuration::load_config(PATH);

  ASSERT_EQ(2048, configuration.heap_alloc_size());
  ASSERT_EQ(1024, configuration.pool_alloc_size());
  ASSERT_EQ(100, configuration.gc_interval());
  ASSERT_EQ(1, configuration.gc_flag());
  ASSERT_STREQ("stdout", configuration.log_mode().c_str());
}

// -----------------------------------------------------------------------------

TEST_F(ConfigurationUnitTest, TestLoadFailsWithInvalidPath)
{
  ASSERT_THROW(
    {
      corevm::frontend::Configuration::load_config("$%^some-invalid-path!@#");
    },
    corevm::frontend::ConfigurationLoadingError
  );
}

// -----------------------------------------------------------------------------

TEST_F(ConfigurationUnitTest, TestGetAndSet)
{
  corevm::frontend::Configuration configuration;

  ASSERT_EQ(0, configuration.heap_alloc_size());
  ASSERT_EQ(0, configuration.pool_alloc_size());
  ASSERT_EQ(0, configuration.gc_interval());
  ASSERT_EQ(0, configuration.gc_flag());
  ASSERT_STREQ("", configuration.log_mode().c_str());

  uint64_t expected_heap_alloc_size = 2048;
  uint64_t expected_pool_alloc_size = 1024;
  uint32_t expected_gc_interval = 32;
  uint8_t expected_gc_flag = 1;
  std::string expected_log_mode("stderr");

  configuration.set_heap_alloc_size(expected_heap_alloc_size);
  configuration.set_pool_alloc_size(expected_pool_alloc_size);
  configuration.set_gc_interval(expected_gc_interval);
  configuration.set_gc_flag(expected_gc_flag);
  configuration.set_log_mode(expected_log_mode);

  ASSERT_EQ(expected_heap_alloc_size, configuration.heap_alloc_size());
  ASSERT_EQ(expected_pool_alloc_size, configuration.pool_alloc_size());
  ASSERT_EQ(expected_gc_interval, configuration.gc_interval());
  ASSERT_EQ(expected_gc_flag, configuration.gc_flag());
  ASSERT_EQ(expected_log_mode, configuration.log_mode());
}

// -----------------------------------------------------------------------------

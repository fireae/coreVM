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
#ifndef COREVM_API_CONFIGURATION_H_
#define COREVM_API_CONFIGURATION_H_

#include <boost/optional.hpp>

#include <cstdint>
#include <string>

namespace corevm {
namespace api {
namespace core {

/**
 * An encapsulation of a set of configuration parameters for coreVM's
 * operations.
 */
class Configuration {
public:
  /**
   * Default constructor.
   */
  Configuration();

  /**
   * Helper member function that loads from a configuration file.
   */
  static bool load_config(const char*, Configuration&);

  /* Value accessors. */

  /**
   * Gets the amount of allocated storage for the heap, in bytes.
   */
  uint64_t heap_alloc_size() const;

  /**
   * Gets the amount of allocated storage for the native type pool, in bytes.
   */
  uint64_t pool_alloc_size() const;

  /**
   * Gets the number of milliseconds for GC interrupts.
   */
  uint32_t gc_interval() const;

  /**
   * Gets whether a flag value has been set for garbage collection.
   */
  bool has_gc_flag() const;

  /**
   * Gets the flag value for garbage collection, if it has been set.
   */
  uint8_t gc_flag() const;

  /**
   * Gets the log mode speficied.
   */
  const std::string& log_mode() const;

  /* Value setters. */

  /**
   * Sets the amount of allocated storage for the heap, in bytes.
   */
  void set_heap_alloc_size(uint64_t);

  /**
   * Sets the amount of allocated storage for the native type pool, in bytes.
   */
  void set_pool_alloc_size(uint64_t);

  /**
   * Sets the number of milliseconds for GC interrupts.
   */
  void set_gc_interval(uint32_t);

  /**
   * Sets the flag value for garbage collection.
   */
  void set_gc_flag(uint8_t);

  /**
   * Gets the log mode for the application.
   */
  void set_log_mode(const char*);

private:
  static const char* schema;

private:
  uint64_t m_heap_alloc_size;
  uint64_t m_pool_alloc_size;
  uint32_t m_gc_interval;
  boost::optional<uint8_t> m_gc_flag;
  std::string m_log_mode;
};

} /* end namespace core */
} /* end namespace api */
} /* end namespace corevm */

#endif /* COREVM_API_CONFIGURATION_H_ */

/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2014 Yanzheng Li

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
#ifndef COREVM_SIGHANDLER_REGISTRAR_H_
#define COREVM_SIGHANDLER_REGISTRAR_H_

#include <csignal>
#include <setjmp.h>
#include <unordered_map>
#include "process.h"
#include "sighandler.h"


namespace corevm {


namespace runtime {


typedef struct sighandler_wrapper {
  corevm::runtime::sighandler* handler;
} sighandler_wrapper;


class sighandler_registrar {
public:
  static void init(corevm::runtime::process*);

  static sigjmp_buf& get_sigjmp_env();

  // Must be called after `init`.
  static void ignore(sig_atomic_t);

  static void handle_signal(int);

  static bool sig_raised;

protected:
  static corevm::runtime::process* process;
  static const std::unordered_map<sig_atomic_t, sighandler_wrapper> handler_map;
};


} /* end namespace runtime */


} /* end namespace corevm */


#endif /* COREVM_SIGHANDLER_REGISTRAR_H_ */

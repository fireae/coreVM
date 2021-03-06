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
#ifndef COREVM_FRAME_H_
#define COREVM_FRAME_H_

#include "closure.h"
#include "closure_ctx.h"
#include "common.h"
#include "corevm/llvm_smallvector.h"
#include "corevm/macros.h"
#include "dyobj/common.h"
#include "errors.h"
#include "fwd.h"
#include "instr_fwd.h"
#include "linear_map.h"
#include "runtime_types.h"
#include "types/fwd.h"
#include "types/native_type_value.h"

#include <cstdint>
#include <vector>

#define DEFAULT_EVAL_STACK_CAPACITY 8
#define DEFAULT_VAR_TABLE_CAPACITY 32

namespace corevm {
namespace runtime {

/**
 * Abstraction of a stack frame.
 *
 * Each stack frame is consisted of:
 *
 * - Program counter.
 * - Return address.
 * - Evaluation stack.
 * - Visible local variables.
 * - Invisible local variables.
 * - Closure context.
 * - A pointer to the associated compartment.
 * - A pointer to the associated closure object.
 * - A pointer to the holding exception object, if one exists.
 * - A pointer to the parent frame, if one exists.
 */
class Frame {
public:
  typedef RuntimeTypes::dyobj_ptr_type dyobj_ptr;

  Frame(const ClosureCtx&, Compartment*, Closure*,
        instr_addr_t = NONESET_INSTR_ADDR);

  ~Frame();

  size_t eval_stack_size() const;

  instr_addr_t pc() const;

  void set_pc(instr_addr_t);

  void set_pc_safe(instr_addr_t);

  const Instr& current_instr() const;

  void inc_pc();

  bool can_execute() const;

  instr_addr_t return_addr() const;

  void set_return_addr(instr_addr_t);

  void push_eval_stack(const types::NativeTypeValue&);

  void push_eval_stack(types::NativeTypeValue&&);

  types::NativeTypeValue pop_eval_stack();

  types::NativeTypeValue& top_eval_stack();

  void swap_eval_stack();

  types::NativeTypeValue& eval_stack_element(size_t i);

  size_t visible_var_count() const;

  dyobj_ptr get_visible_var_with_index(size_t) const;

  dyobj_ptr get_visible_var(variable_key_t) const;

  bool get_visible_var_fast(variable_key_t, dyobj_ptr*) const;

  bool get_visible_var_through_ancestry(variable_key_t, dyobj_ptr*);

  dyobj_ptr pop_visible_var(variable_key_t);

  void set_visible_var(variable_key_t, dyobj_ptr);

  size_t invisible_var_count() const;

  dyobj_ptr get_invisible_var_with_index(size_t) const;

  dyobj_ptr get_invisible_var(variable_key_t) const;

  bool get_invisible_var_fast(variable_key_t, dyobj_ptr*) const;

  bool get_invisible_var_through_ancestry(variable_key_t, dyobj_ptr*);

  dyobj_ptr pop_invisible_var(variable_key_t);

  void set_invisible_var(variable_key_t, dyobj_ptr);

  std::vector<variable_key_t> visible_var_keys() const;

  std::vector<variable_key_t> invisible_var_keys() const;

  std::vector<dyobj_ptr> get_visible_objs() const;

  std::vector<dyobj_ptr> get_invisible_objs() const;

  ClosureCtx closure_ctx() const;

  Compartment* compartment() const;

  Closure* closure() const;

  Frame* parent() const;

  /**
   * Sets the optional parent of the frame in the process.
   */
  void set_parent(Frame*);

  dyobj_ptr exc_obj() const;

  void set_exc_obj(dyobj_ptr);

  void clear_exc_obj();

protected:
  typedef LinearMap<variable_key_t, dyobj_ptr,
                    llvm::SmallVector<std::pair<variable_key_t, dyobj_ptr>,
                                      DEFAULT_VAR_TABLE_CAPACITY>>
    VariableTable;

  instr_addr_t m_pc;
  const runtime::ClosureCtx m_closure_ctx;
  Compartment* m_compartment;
  Closure* m_closure;
  Frame* m_parent;
  instr_addr_t m_return_addr;
  VariableTable m_visible_vars;
  VariableTable m_invisible_vars;
  llvm::SmallVector<types::NativeTypeValue, DEFAULT_EVAL_STACK_CAPACITY>
    m_eval_stack;
  dyobj_ptr m_exc_obj;
};

} /* end namespace runtime */
} /* end namespace corevm */

#endif /* COREVM_FRAME_H_ */

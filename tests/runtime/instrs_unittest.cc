#include <algorithm>
#include <list>
#include <sneaker/testing/_unittest.h>
#include "../../include/runtime/process.h"
#include "../../include/types/interfaces.h"


class process_instrs_unittest : public ::testing::Test {};


class process_obj_instrs_test : public process_instrs_unittest {
protected:
  virtual void SetUp() {
    _process.push_frame(_frame);
  }

  template<typename InstrHandlerCls>
  void _execute_instr(corevm::runtime::instr instr, uint64_t expected_stack_size=1) {
    InstrHandlerCls instr_handler;

    instr_handler.execute(instr, _process);

    uint64_t actual_stack_size = _process.stack_size();

    ASSERT_EQ(expected_stack_size, actual_stack_size);
  }

  corevm::runtime::process _process;
  corevm::runtime::frame _frame;
};


TEST_F(process_obj_instrs_test, TestInstrNEW)
{
  corevm::runtime::instr instr;
  _execute_instr<corevm::runtime::instr_handler_new>(instr); 
}

TEST_F(process_obj_instrs_test, TestInstrLDOBJ)
{
  // TODO: to be implemented...
}

TEST_F(process_obj_instrs_test, TestInstrSTOBJ)
{
  corevm::runtime::instr instr = {.code=0, .oprd1=1, .oprd2=0};

  corevm::runtime::frame frame;
  _process.push_frame(frame);

  corevm::dyobj::dyobj_id id = 1;
  _process.push_stack(id);

  _execute_instr<corevm::runtime::instr_handler_stobj>(instr, 0);

  corevm::runtime::frame& actual_frame = _process.top_frame();

  ASSERT_TRUE(actual_frame.has_visible_var(1));

  corevm::dyobj::dyobj_id actual_id = actual_frame.get_visible_var(1);

  ASSERT_EQ(id, actual_id);
}

TEST_F(process_obj_instrs_test, TestInstrGETATTR)
{
  corevm::dyobj::attr_key attr_key = 333;
  corevm::runtime::instr instr = {.code=0, .oprd1=attr_key, .oprd2=0};

  corevm::dyobj::dyobj_id id1 = _process.__helper_create_dyobj();
  corevm::dyobj::dyobj_id id2 = _process.__helper_create_dyobj();

  auto &obj = _process.__helper_at(id1);
  obj.putattr(attr_key, id2);
  _process.push_stack(id1);

  _execute_instr<corevm::runtime::instr_handler_getattr>(instr, 1);

  corevm::dyobj::dyobj_id expected_id = id2;
  corevm::dyobj::dyobj_id actual_id = _process.top_stack();

  ASSERT_EQ(expected_id, actual_id);
}

TEST_F(process_obj_instrs_test, TestInstrSETATTR)
{
  corevm::dyobj::attr_key attr_key = 789;
  corevm::runtime::instr instr = {.code=0, .oprd1=attr_key, .oprd2=0};

  corevm::dyobj::dyobj_id id1 = _process.__helper_create_dyobj();
  corevm::dyobj::dyobj_id id2 = _process.__helper_create_dyobj();

  _process.push_stack(id1);
  _process.push_stack(id2);

  _execute_instr<corevm::runtime::instr_handler_setattr>(instr, 1);

  corevm::dyobj::dyobj_id expected_id = id1;
  corevm::dyobj::dyobj_id actual_id = _process.top_stack();

  ASSERT_EQ(expected_id, actual_id);

  auto &obj = _process.__helper_at(actual_id);

  ASSERT_TRUE(obj.hasattr(attr_key));

  ASSERT_EQ(id2, obj.getattr(attr_key));
}

TEST_F(process_obj_instrs_test, TestInstrDELATTR)
{
  corevm::dyobj::attr_key attr_key = 777;
  corevm::runtime::instr instr = {.code=0, .oprd1=attr_key, .oprd2=0};

  corevm::dyobj::dyobj_id id = _process.__helper_create_dyobj();
  corevm::dyobj::dyobj_id attr_id = _process.__helper_create_dyobj();

  auto& obj = _process.__helper_at(id);
  obj.putattr(attr_key, attr_id);

  ASSERT_TRUE(obj.hasattr(attr_key));

  _process.push_stack(id);

  _execute_instr<corevm::runtime::instr_handler_delattr>(instr, 1);

  corevm::dyobj::dyobj_id expected_id = id;
  corevm::dyobj::dyobj_id actual_id = _process.top_stack();

  ASSERT_EQ(expected_id, actual_id);

  auto &actual_obj = _process.__helper_at(actual_id);

  ASSERT_FALSE(actual_obj.hasattr(attr_key));
}

TEST_F(process_obj_instrs_test, TestInstrPOP)
{
  corevm::dyobj::dyobj_id id = _process.__helper_create_dyobj();
  _process.push_stack(id);

  corevm::runtime::instr instr;
  _execute_instr<corevm::runtime::instr_handler_pop>(instr, 0);

  ASSERT_THROW(
    { _process.top_stack(); },
    corevm::runtime::object_stack_empty_error
  );
}

TEST_F(process_obj_instrs_test, TestInstrLDOBJ2)
{
  // TODO: to be implemented...
}

TEST_F(process_obj_instrs_test, TestInstrSTOBJ2)
{
  corevm::runtime::instr instr = {.code=0, .oprd1=1, .oprd2=0};

  corevm::runtime::frame frame;
  _process.push_frame(frame);

  corevm::dyobj::dyobj_id id = 1;
  _process.push_stack(id);

  _execute_instr<corevm::runtime::instr_handler_stobj2>(instr, 0);

  corevm::runtime::frame& actual_frame = _process.top_frame();

  ASSERT_TRUE(actual_frame.has_invisible_var(1));

  corevm::dyobj::dyobj_id actual_id = actual_frame.get_invisible_var(1);

  ASSERT_EQ(id, actual_id);
}

TEST_F(process_obj_instrs_test, TestInstrDELOBJ)
{
  corevm::runtime::variable_key key = 1;
  corevm::dyobj::dyobj_id id = _process.__helper_create_dyobj();

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=static_cast<corevm::runtime::instr_oprd>(key), 
    .oprd2=0
  };

  corevm::runtime::frame frame;
  frame.set_visible_var(key, id);
  _process.push_frame(frame);

  _execute_instr<corevm::runtime::instr_handler_delobj>(instr, 0);

  corevm::runtime::frame& actual_frame = _process.top_frame();

  ASSERT_FALSE(actual_frame.has_visible_var(key));
}

TEST_F(process_obj_instrs_test, TestInstrDELOBJ2)
{
  corevm::runtime::variable_key key = 1;
  corevm::dyobj::dyobj_id id = _process.__helper_create_dyobj();

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=static_cast<corevm::runtime::instr_oprd>(key),
    .oprd2=0
  };

  corevm::runtime::frame frame;
  frame.set_invisible_var(key, id);
  _process.push_frame(frame);

  _execute_instr<corevm::runtime::instr_handler_delobj2>(instr, 0);

  corevm::runtime::frame& actual_frame = _process.top_frame();

  ASSERT_FALSE(actual_frame.has_invisible_var(key));
}

TEST_F(process_obj_instrs_test, TestInstrGETHNDL)
{
  uint32_t expected_value = 123;

  corevm::dyobj::dyobj_id id = _process.__helper_create_dyobj();
  _process.push_stack(id);

  corevm::runtime::frame frame;
  _process.push_frame(frame);

  corevm::types::native_type_handle hndl = corevm::types::uint32(expected_value);
  corevm::dyobj::ntvhndl_key ntvhndl_key = _process.insert_ntvhndl(hndl);

  auto &obj = _process.__helper_at(id);
  obj.set_ntvhndl_key(ntvhndl_key);

  corevm::runtime::instr instr;
  _execute_instr<corevm::runtime::instr_handler_gethndl>(instr, 1);

  corevm::runtime::frame& actual_frame = _process.top_frame();
  corevm::types::native_type_handle actual_handle = actual_frame.pop_eval_stack();

  uint32_t actual_value = corevm::types::get_value_from_handle<uint32_t>(
    actual_handle
  );

  ASSERT_EQ(expected_value, actual_value);
}

TEST_F(process_obj_instrs_test, TestInstrSETHNDL)
{
  uint32_t expected_value = 123;

  corevm::dyobj::dyobj_id id = _process.__helper_create_dyobj();
  _process.push_stack(id);

  corevm::runtime::frame frame;
  corevm::types::native_type_handle hndl = corevm::types::uint32(expected_value);
  frame.push_eval_stack(hndl);
  _process.push_frame(frame);

  corevm::runtime::instr instr;
  _execute_instr<corevm::runtime::instr_handler_sethndl>(instr, 1);

  auto &obj = _process.__helper_at(id);

  ASSERT_NE(corevm::dyobj::NONESET_NTVHNDL_KEY, obj.get_ntvhndl_key());
}

TEST_F(process_obj_instrs_test, TestInstrCLRHNDL)
{
  corevm::dyobj::dyobj_id id = _process.__helper_create_dyobj();
  _process.push_stack(id);

  corevm::types::native_type_handle hndl = corevm::types::uint32(123);
  corevm::dyobj::ntvhndl_key ntvhndl_key = _process.insert_ntvhndl(hndl);

  auto &obj = _process.__helper_at(id);
  obj.set_ntvhndl_key(ntvhndl_key);

  corevm::runtime::instr instr;
  _execute_instr<corevm::runtime::instr_handler_clrhndl>(instr, 1);

  obj = _process.__helper_at(id);
  ASSERT_EQ(corevm::dyobj::NONESET_NTVHNDL_KEY, obj.get_ntvhndl_key());

  ASSERT_FALSE(_process.has_ntvhndl(ntvhndl_key));
}

TEST_F(process_obj_instrs_test, TestInstrOBJEQ)
{
  corevm::dyobj::dyobj_id id1 = 1;
  corevm::dyobj::dyobj_id id2 = 1;

  _process.push_stack(id1);
  _process.push_stack(id2);

  corevm::runtime::frame frame;
  _process.push_frame(frame);

  corevm::runtime::instr instr;
  _execute_instr<corevm::runtime::instr_handler_objeq>(instr, 0);

  corevm::runtime::frame& actual_frame = _process.top_frame();
  corevm::types::native_type_handle result_handle = actual_frame.pop_eval_stack();

  bool expected_result = true;
  bool actual_result = corevm::types::get_value_from_handle<bool>(
    result_handle
  );

  ASSERT_EQ(expected_result, actual_result);
}

TEST_F(process_obj_instrs_test, TestInstrOBJNEQ)
{
  corevm::dyobj::dyobj_id id1 = 1;
  corevm::dyobj::dyobj_id id2 = 2;

  _process.push_stack(id1);
  _process.push_stack(id2);

  corevm::runtime::frame frame;
  _process.push_frame(frame);

  corevm::runtime::instr instr;
  _execute_instr<corevm::runtime::instr_handler_objneq>(instr, 0);

  corevm::runtime::frame& actual_frame = _process.top_frame();
  corevm::types::native_type_handle result_handle = actual_frame.pop_eval_stack();

  bool expected_result = true;
  bool actual_result = corevm::types::get_value_from_handle<bool>(
    result_handle
  );

  ASSERT_EQ(expected_result, actual_result);
}


class process_functions_instrs_test : public process_instrs_unittest {
protected:
  corevm::runtime::process _process;
};


TEST_F(process_functions_instrs_test, TestInstrFRM)
{
  ASSERT_THROW(
    { _process.top_frame(); },
    corevm::runtime::frame_not_found_error
  );

  corevm::runtime::instr instr;
  corevm::runtime::instr_handler_frm handler;
  handler.execute(instr, _process);

  ASSERT_NO_THROW(
    { _process.top_frame(); }
  );
}

TEST_F(process_functions_instrs_test, TestInstrPUTARG)
{
  corevm::runtime::frame frame;
  _process.push_frame(frame);

  corevm::dyobj::dyobj_id id = 1;
  _process.push_stack(id);

  corevm::runtime::frame& actual_frame = _process.top_frame();

  ASSERT_THROW(
    { actual_frame.pop_param(); },
    corevm::runtime::missing_parameter_error
  );

  corevm::runtime::instr instr;
  corevm::runtime::instr_handler_putarg handler;
  handler.execute(instr, _process);

  corevm::dyobj::dyobj_id actual_id = actual_frame.pop_param();

  ASSERT_EQ(id, actual_id);
}

TEST_F(process_functions_instrs_test, TestInstrPUTKWARG)
{
  corevm::runtime::frame frame;
  _process.push_frame(frame);

  corevm::runtime::variable_key key = 3;
  corevm::dyobj::dyobj_id id = 2;
  _process.push_stack(id);

  corevm::runtime::frame& actual_frame = _process.top_frame();

  ASSERT_THROW(
    { actual_frame.pop_param_value_pair(key); },
    corevm::runtime::missing_parameter_error
  );

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=static_cast<corevm::runtime::instr_oprd>(key),
    .oprd2=2
  };
  corevm::runtime::instr_handler_putkwarg handler;
  handler.execute(instr, _process);

  corevm::dyobj::dyobj_id actual_id = actual_frame.pop_param_value_pair(key);

  ASSERT_EQ(id, actual_id);
}

TEST_F(process_functions_instrs_test, TestInstrGETARG)
{
  corevm::dyobj::dyobj_id id = 1;
  corevm::runtime::frame frame;
  frame.put_param(id);

  _process.push_frame(frame);

  corevm::runtime::instr instr;
  corevm::runtime::instr_handler_getarg handler;
  handler.execute(instr, _process);

  corevm::dyobj::dyobj_id actual_id = _process.pop_stack();

  ASSERT_EQ(id, actual_id);
}

TEST_F(process_functions_instrs_test, TestInstrGETKWARG)
{
  corevm::runtime::variable_key key = 22;
  corevm::dyobj::dyobj_id id = 100;

  corevm::runtime::frame frame;
  frame.put_param_value_pair(key, id);
  _process.push_frame(frame);

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=static_cast<corevm::runtime::instr_oprd>(key),
    .oprd2=0
  };

  corevm::runtime::instr_handler_getkwarg handler;
  handler.execute(instr, _process);

  corevm::dyobj::dyobj_id actual_id = _process.pop_stack();

  ASSERT_EQ(id, actual_id);
}

TEST_F(process_functions_instrs_test, TestInstrGETARGS)
{
  corevm::dyobj::dyobj_id id1 = 100;
  corevm::dyobj::dyobj_id id2 = 200;
  corevm::dyobj::dyobj_id id3 = 300;

  corevm::runtime::frame frame;
  frame.put_param(id1);
  frame.put_param(id2);
  frame.put_param(id3);
  _process.push_frame(frame);

  ASSERT_EQ(true, frame.has_params());

  corevm::runtime::instr instr;
  corevm::runtime::instr_handler_getargs handler;
  handler.execute(instr, _process);

  corevm::runtime::frame actual_frame = _process.top_frame();

  ASSERT_EQ(false, actual_frame.has_params());

  corevm::types::native_type_handle hndl = actual_frame.pop_eval_stack();

  corevm::types::native_type_handle result_handle1;
  corevm::types::native_type_handle result_handle2;
  corevm::types::native_type_handle result_handle3;

  corevm::types::interface_array_back(hndl, result_handle1);
  corevm::types::interface_array_pop(hndl, hndl);

  corevm::types::interface_array_back(hndl, result_handle2);
  corevm::types::interface_array_pop(hndl, hndl);

  corevm::types::interface_array_back(hndl, result_handle3);
  corevm::types::interface_array_pop(hndl, hndl);

  corevm::dyobj::dyobj_id actual_id1 = corevm::types::get_value_from_handle<corevm::dyobj::dyobj_id>(result_handle1);
  corevm::dyobj::dyobj_id actual_id2 = corevm::types::get_value_from_handle<corevm::dyobj::dyobj_id>(result_handle2);
  corevm::dyobj::dyobj_id actual_id3 = corevm::types::get_value_from_handle<corevm::dyobj::dyobj_id>(result_handle3);

  ASSERT_EQ(id1, actual_id1);
  ASSERT_EQ(id2, actual_id2);
  ASSERT_EQ(id3, actual_id3);
}

TEST_F(process_functions_instrs_test, TestInstrGETKWARGS)
{
  corevm::runtime::variable_key key1 = 1;
  corevm::runtime::variable_key key2 = 22;
  corevm::runtime::variable_key key3 = 333;

  corevm::dyobj::dyobj_id id1 = 100;
  corevm::dyobj::dyobj_id id2 = 200;
  corevm::dyobj::dyobj_id id3 = 300;

  corevm::runtime::frame frame;
  frame.put_param_value_pair(key1, id1);
  frame.put_param_value_pair(key2, id2);
  frame.put_param_value_pair(key3, id3);
  _process.push_frame(frame);

  ASSERT_EQ(true, frame.has_param_value_pairs());

  corevm::runtime::instr instr;
  corevm::runtime::instr_handler_getkwargs handler;
  handler.execute(instr, _process);

  corevm::runtime::frame actual_frame = _process.top_frame();

  ASSERT_EQ(false, actual_frame.has_param_value_pairs());

  corevm::types::native_type_handle hndl = actual_frame.pop_eval_stack();

  corevm::types::native_type_handle key_handle1 = corevm::types::uint64(key1);
  corevm::types::native_type_handle key_handle2 = corevm::types::uint64(key2);
  corevm::types::native_type_handle key_handle3 = corevm::types::uint64(key3);
  corevm::types::native_type_handle result_handle1;
  corevm::types::native_type_handle result_handle2;
  corevm::types::native_type_handle result_handle3;

  corevm::types::interface_map_at(hndl, key_handle1, result_handle1);
  corevm::types::interface_map_at(hndl, key_handle2, result_handle2);
  corevm::types::interface_map_at(hndl, key_handle3, result_handle3);

  corevm::dyobj::dyobj_id actual_id1 = corevm::types::get_value_from_handle<corevm::dyobj::dyobj_id>(result_handle1);
  corevm::dyobj::dyobj_id actual_id2 = corevm::types::get_value_from_handle<corevm::dyobj::dyobj_id>(result_handle2);
  corevm::dyobj::dyobj_id actual_id3 = corevm::types::get_value_from_handle<corevm::dyobj::dyobj_id>(result_handle3);

  ASSERT_EQ(id1, actual_id1);
  ASSERT_EQ(id2, actual_id2);
  ASSERT_EQ(id3, actual_id3);
}


class process_control_instrs_test : public process_instrs_unittest {
public:
  static bool signal_fired;

protected:
  virtual void SetUp() {
    std::vector<corevm::runtime::instr> instrs = {
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
      corevm::runtime::instr(),
    };
    _process.append_instrs(instrs);
  }

  corevm::runtime::process _process;
};
bool process_control_instrs_test::signal_fired = false;


TEST_F(process_control_instrs_test, TestInstrRTRN)
{
  // TODO: to be implemented...
}

TEST_F(process_control_instrs_test, TestInstrJMP)
{
  corevm::runtime::frame frame;
  frame.set_start_addr(0);
  _process.push_frame(frame);

  corevm::runtime::instr_addr current_addr = _process.current_addr();
  ASSERT_EQ(0, current_addr);

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=static_cast<corevm::runtime::instr_oprd>(8),
    .oprd2=0
  };

  corevm::runtime::instr_handler_jmp handler;
  handler.execute(instr, _process);

  current_addr = _process.current_addr();

  ASSERT_EQ(8, current_addr);
}

TEST_F(process_control_instrs_test, TestInstrJMPIF)
{
  corevm::runtime::frame frame;
  frame.set_start_addr(0);

  corevm::types::native_type_handle hndl = corevm::types::boolean(true);
  frame.push_eval_stack(hndl);
  _process.push_frame(frame);

  corevm::runtime::instr_addr current_addr = _process.current_addr();
  ASSERT_EQ(0, current_addr);

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=static_cast<corevm::runtime::instr_oprd>(8),
    .oprd2=0
  };

  corevm::runtime::instr_handler_jmpif handler;
  handler.execute(instr, _process);

  current_addr = _process.current_addr();

  ASSERT_EQ(8, current_addr);
}

TEST_F(process_control_instrs_test, TestInstrJMPIF_OnFalseCondition)
{
  corevm::runtime::frame frame;
  frame.set_start_addr(0);

  corevm::types::native_type_handle hndl = corevm::types::boolean(false);
  frame.push_eval_stack(hndl);
  _process.push_frame(frame);

  corevm::runtime::instr_addr current_addr = _process.current_addr();
  ASSERT_EQ(0, current_addr);

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=static_cast<corevm::runtime::instr_oprd>(8),
    .oprd2=0
  };

  corevm::runtime::instr_handler_jmpif handler;
  handler.execute(instr, _process);

  current_addr = _process.current_addr();

  ASSERT_EQ(0, current_addr);
}

TEST_F(process_control_instrs_test, TestInstrEXC)
{
  // TODO: to be implemented...
}

TEST_F(process_control_instrs_test, TestInstrEXC2)
{
  // TODO: to be implemented...
}

TEST_F(process_control_instrs_test, TestInstrEXIT)
{
  auto sig_handler = [](int signum) {
    process_control_instrs_test::signal_fired = true;
    signal(SIGTERM, SIG_IGN);
  };
 
  signal(SIGTERM, sig_handler);
  ASSERT_EQ(false, process_control_instrs_test::signal_fired);

  corevm::runtime::instr instr = {
    .code=0,
    .oprd1=EXIT_SUCCESS,
    .oprd2=0
  };
  corevm::runtime::instr_handler_exit handler;
  handler.execute(instr, _process);

  ASSERT_EQ(true, process_control_instrs_test::signal_fired);
}


/*
 * For instructions that manipulate evaluation stacks.
 * */
class process_eval_stack_instrs_test : public process_instrs_unittest {
public:
  typedef uint32_t IntrinsicType;

  typedef corevm::types::uint32 NativeType;

  typedef std::list<corevm::types::native_type_handle> eval_oprds_list;

protected:
  void push_eval_stack_and_frame(const eval_oprds_list& elements) {
    std::for_each(
      elements.begin(),
      elements.end(),
      [this](corevm::types::native_type_handle oprd) {
        this->_frame.push_eval_stack(oprd);
      }
    );

    _process.push_frame(_frame);
  }

  template<typename InstrHandlerCls, typename IntrinsicType=uint32_t>
  void execute_instr_and_assert_result(IntrinsicType expected_result) {
    InstrHandlerCls instr_handler;

    corevm::runtime::instr instr;

    instr_handler.execute(instr, _process);

    corevm::runtime::frame& frame = _process.top_frame();
    ASSERT_EQ(_expected_eval_stack_size, frame.eval_stack_size());

    corevm::types::native_type_handle result_handle = frame.pop_eval_stack();

    IntrinsicType actual_result = corevm::types::get_value_from_handle<IntrinsicType>(
      result_handle
    );

    ASSERT_EQ(expected_result, actual_result);
  }

  uint32_t _expected_eval_stack_size = 1;
  corevm::runtime::frame _frame;
  corevm::runtime::process _process;
};


class process_arithmetic_instrs_test : public process_eval_stack_instrs_test {};


class process_unary_arithmetic_instrs_test : public process_arithmetic_instrs_test {
public:
  virtual void SetUp () {
    corevm::types::native_type_handle hndl = NativeType(_oprd);
    push_eval_stack_and_frame(eval_oprds_list{hndl});
  }

protected:
  IntrinsicType _oprd = 5;
};


TEST_F(process_unary_arithmetic_instrs_test, TestInstrPOS)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_pos>(+_oprd);
}

TEST_F(process_unary_arithmetic_instrs_test, TestInstrNEG)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_neg>(-_oprd);
}

TEST_F(process_unary_arithmetic_instrs_test, TestInstrINC)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_inc>(++_oprd);
}

TEST_F(process_unary_arithmetic_instrs_test, TestInstrDEC)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_dec>(--_oprd);
}

TEST_F(process_unary_arithmetic_instrs_test, TestInstrBNOT)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_bnot>(~_oprd);
}

TEST_F(process_unary_arithmetic_instrs_test, TestInstrLNOT)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_lnot>(!_oprd);
}


class process_binary_arithmetic_instrs_test : public process_arithmetic_instrs_test {
public:
  virtual void SetUp () {
    corevm::types::native_type_handle hndl1 = NativeType(_oprd1);
    corevm::types::native_type_handle hndl2 = NativeType(_oprd2);
    push_eval_stack_and_frame({hndl2, hndl1});
  }

protected:
  IntrinsicType _oprd1 = 10;
  IntrinsicType _oprd2 = 5;
};


TEST_F(process_binary_arithmetic_instrs_test, TestInstrADD)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_add>(_oprd1 + _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrSUB)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_sub>(_oprd1 - _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrMUL)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_mul>(_oprd1 * _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrDIV)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_div>(_oprd1 / _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrMOD)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_mod>(_oprd1 % _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrPOW)
{
  // TODO: to be implemented...
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrBAND)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_band>(_oprd1 & _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrBOR)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_bor>(_oprd1 | _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrBXOR)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_bxor>(_oprd1 ^ _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrBLS)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_bls>(_oprd1 << _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrBRS)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_brs>(_oprd1 >> _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrEQ)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_eq>(_oprd1 == _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrNEQ)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_neq>(_oprd1 != _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrGT)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_gt>(_oprd1 > _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrLT)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_lt>(_oprd1 < _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrGTE)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_gte>(_oprd1 >= _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrLTE)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_lte>(_oprd1 <= _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrLAND)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_land>(_oprd1 && _oprd2);
}

TEST_F(process_binary_arithmetic_instrs_test, TestInstrLOR)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_lor>(_oprd1 || _oprd2);
}


class process_native_type_instrs_test : public process_eval_stack_instrs_test {};


class process_native_type_creation_instrs_test : public process_native_type_instrs_test {
public:
  virtual void SetUp () {
    push_eval_stack_and_frame(eval_oprds_list{});
  }
};


TEST_F(process_native_type_creation_instrs_test, TestInstrINT8)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_int8, int8_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrUINT8)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_uint8, uint8_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrINT16)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_int16, int16_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrUINT16)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_uint16, uint16_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrINT32)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_int32, int32_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrUINT32)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_uint32, uint32_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrINT64)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_int64, int64_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrUINT64)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_uint64, uint64_t>(0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrBOOL)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_bool, bool>(true);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrDEC1)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_dec1, float>(0.0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrDEC2)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_dec2, double>(0.0);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrSTR)
{
  corevm::types::native_string expected_result;
  execute_instr_and_assert_result<corevm::runtime::instr_handler_str, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrARY)
{
  corevm::types::native_array expected_result;
  execute_instr_and_assert_result<corevm::runtime::instr_handler_ary, corevm::types::native_array>(expected_result);
}

TEST_F(process_native_type_creation_instrs_test, TestInstrMAP)
{
  corevm::types::native_map expected_result;
  execute_instr_and_assert_result<corevm::runtime::instr_handler_map, corevm::types::native_map>(expected_result);
}


class process_native_type_conversion_instrs_test : public process_native_type_instrs_test {
public:
  virtual void SetUp () {
    corevm::types::native_type_handle hndl = corevm::types::uint8(_oprd);
    push_eval_stack_and_frame(eval_oprds_list{hndl});
  }

  template<typename InstrHandlerCls>
  void execute_instr_and_assert_result() {
    // TODO: should have more concrete testing on the conversion.
    InstrHandlerCls instr_handler;

    corevm::runtime::instr instr;

    instr_handler.execute(instr, _process);

    corevm::runtime::frame& frame = _process.top_frame();
    ASSERT_EQ(_expected_eval_stack_size, frame.eval_stack_size());
  }

private:
  corevm::types::uint8 _oprd = 100;
};


TEST_F(process_native_type_conversion_instrs_test, TestInstr2INT8)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2int8>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2INT16)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2int16>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2UINT16)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2uint16>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2INT32)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2int32>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2UINT64)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2uint64>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2INT64)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2int64>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2BOOL)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2bool>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2DEC1)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2dec1>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2DEC2)
{
  execute_instr_and_assert_result<corevm::runtime::instr_handler_2dec2>();
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2STR)
{
  ASSERT_THROW(
    { execute_instr_and_assert_result<corevm::runtime::instr_handler_2str>(); },
    corevm::types::corevm_native_type_conversion_error
  );
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2ARY)
{
  ASSERT_THROW(
    { execute_instr_and_assert_result<corevm::runtime::instr_handler_2ary>(); },
    corevm::types::corevm_native_type_conversion_error
  );
}

TEST_F(process_native_type_conversion_instrs_test, TestInstr2MAP)
{
  ASSERT_THROW(
    { execute_instr_and_assert_result<corevm::runtime::instr_handler_2map>(); },
    corevm::types::corevm_native_type_conversion_error
  );
}


class process_native_type_complex_instrs_test : public process_native_type_instrs_test {
public:
  virtual void SetUp() {
    // Override this method to do nothing here.
  }
};


class process_native_type_complex_instrs_for_str_type_test : public process_native_type_complex_instrs_test {};


TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRLEN)
{
  corevm::types::native_string hello_world = "Hello world!";
  corevm::types::native_string::size_type expected_result = hello_world.size();
  corevm::types::native_type_handle oprd = corevm::types::string(hello_world);

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strlen, corevm::types::native_string::size_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRCLR)
{
  corevm::types::native_string hello_world = "Hello world!";
  corevm::types::native_string expected_result = "";
  corevm::types::native_type_handle oprd = hello_world;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strclr, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRAPD)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::native_string exclamation = "!";
  corevm::types::native_string expected_result = "Hello world!";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = exclamation;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strapd, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRPSH)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::int8 exclamation = static_cast<corevm::types::int8::value_type>('!');
  corevm::types::native_string expected_result = "Hello world!";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = exclamation;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strpsh, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRIST)
{
  corevm::types::native_string hello_world = "Helloworld";
  corevm::types::int8 pos = static_cast<corevm::types::int8::value_type>(5);
  corevm::types::native_string space = " ";
  corevm::types::native_string expected_result = "Hello world";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = pos;
  corevm::types::native_type_handle oprd3 = space;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strist, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRIST2)
{
  corevm::types::native_string hello_world = "Helloworld";
  corevm::types::int8 pos = static_cast<corevm::types::int8::value_type>(5);
  corevm::types::int8 space = static_cast<corevm::types::int8::value_type>(' ');
  corevm::types::native_string expected_result = "Hello world";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = pos;
  corevm::types::native_type_handle oprd3 = space;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strist2, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRERS)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::int8 pos = static_cast<corevm::types::int8::value_type>(5);
  corevm::types::native_string expected_result = "Hello";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = pos;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strers, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRERS2)
{
  corevm::types::native_string hello_world = "Hello  world";
  corevm::types::int8 pos = static_cast<corevm::types::int8::value_type>(5);
  corevm::types::int8 len = static_cast<corevm::types::int8::value_type>(1);
  corevm::types::native_string expected_result = "Hello world";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = pos;
  corevm::types::native_type_handle oprd3 = len;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strers2, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRRPLC)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::int8 pos = static_cast<corevm::types::int8::value_type>(5);
  corevm::types::int8 len = static_cast<corevm::types::int8::value_type>(6);
  corevm::types::native_string exclamation = "!!!!!!";
  corevm::types::native_string expected_result = "Hello!!!!!!";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = pos;
  corevm::types::native_type_handle oprd3 = len;
  corevm::types::native_type_handle oprd4 = exclamation;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3, oprd4});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strrplc, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRSWP)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::native_string okla = "OKLA!";
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = okla;
  corevm::types::native_string expected_result = okla;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strswp, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRSUB)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::int8 pos = 6;
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = pos;
  corevm::types::native_string expected_result = "world";

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strsub, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrSTRSUB2)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::int8 pos = 6;
  corevm::types::int8 len = 2;
  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = pos;
  corevm::types::native_type_handle oprd3 = len;
  corevm::types::native_string expected_result = "wo";

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strsub2, corevm::types::native_string>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrFND)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::native_string word = "world";
  corevm::types::native_string::size_type expected_result = 6;

  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = word;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strfnd, corevm::types::native_string::size_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrFND2)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::native_string word = "world";
  corevm::types::uint32 pos = 6;
  corevm::types::native_string::size_type expected_result = 6;

  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = word;
  corevm::types::native_type_handle oprd3 = pos;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strfnd2, corevm::types::native_string::size_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrRFND)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::native_string word = "world";
  corevm::types::native_string::size_type expected_result = 6;

  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = word;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strrfnd, corevm::types::native_string::size_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_str_type_test, TestInstrRFND2)
{
  corevm::types::native_string hello_world = "Hello world";
  corevm::types::native_string word = "world";
  corevm::types::uint32 pos = 6;
  corevm::types::native_string::size_type expected_result = 6;

  corevm::types::native_type_handle oprd1 = hello_world;
  corevm::types::native_type_handle oprd2 = word;
  corevm::types::native_type_handle oprd3 = pos;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_strrfnd2, corevm::types::native_string::size_type>(expected_result);
}


class process_native_type_complex_instrs_for_array_type_test : public process_native_type_complex_instrs_test {};


TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYLEN)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_array::size_type expected_result = array.size();
  corevm::types::native_type_handle oprd = array;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_arylen, corevm::types::native_array::size_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYEMP)
{
  corevm::types::native_array array = {1, 2, 3};
  bool expected_result = false;
  corevm::types::native_type_handle oprd = array;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_aryemp, bool>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYAT)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::uint32 index = 1;
  corevm::types::native_array::value_type expected_result = 2;

  corevm::types::native_type_handle oprd1 = array;
  corevm::types::native_type_handle oprd2 = index;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_aryat, corevm::types::native_array::value_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYFRT)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_array::value_type expected_result = 1;
  corevm::types::native_type_handle oprd = array;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_aryfrt, corevm::types::native_array::value_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYBAK)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_array::value_type expected_result = 3;
  corevm::types::native_type_handle oprd = array;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_arybak, corevm::types::native_array::value_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYAPND)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::uint64 data = 4;
  corevm::types::native_array expected_result = {1, 2, 3, 4};

  corevm::types::native_type_handle oprd1 = array;
  corevm::types::native_type_handle oprd2 = data;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_aryapnd, corevm::types::native_array>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYPOP)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_array expected_result = {1, 2};
  corevm::types::native_type_handle oprd = array;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_arypop, corevm::types::native_array>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYSWP)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_array other = {4, 5, 6};
  corevm::types::native_array expected_result = other;

  corevm::types::native_type_handle oprd1 = array;
  corevm::types::native_type_handle oprd2 = other;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_aryswp, corevm::types::native_array>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_array_type_test, TestInstrARYCLR)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_array expected_result;

  corevm::types::native_type_handle oprd = array;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_aryclr, corevm::types::native_array>(expected_result);
}


class process_native_type_complex_instrs_for_map_type_test : public process_native_type_complex_instrs_test {};


TEST_F(process_native_type_complex_instrs_for_map_type_test, TestInstrMAPLEN)
{
  corevm::types::native_map map;
  map[1] = 1;

  corevm::types::native_map::size_type expected_result = 1;
  corevm::types::native_type_handle oprd = map;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_maplen, corevm::types::native_map::size_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_map_type_test, TestInstrMAPEMP)
{
  corevm::types::native_map map;
  map[1] = 1;

  bool expected_result = false;
  corevm::types::native_type_handle oprd = map;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_mapemp, bool>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_map_type_test, TestInstrMAPAT)
{
  corevm::types::native_map map;
  map[1] = 100;

  corevm::types::uint64 key = 1;
  corevm::types::native_map::mapped_type expected_result = 100;
  corevm::types::native_type_handle oprd1 = map;
  corevm::types::native_type_handle oprd2 = key;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_mapat, corevm::types::native_map::mapped_type>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_map_type_test, TestInstrMAPPUT)
{
  corevm::types::native_map map;
  corevm::types::uint64 key = 1;
  corevm::types::uint64 value = 11;
  corevm::types::native_map expected_result;
  expected_result[1] = 11;

  corevm::types::native_type_handle oprd1 = map;
  corevm::types::native_type_handle oprd2 = key;
  corevm::types::native_type_handle oprd3 = value;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2, oprd3});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_mapput, corevm::types::native_map>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_map_type_test, TestInstrMAPERS)
{
  corevm::types::native_map map;
  map[1] = 11;
  map[2] = 22;

  corevm::types::uint64 key = 1;
  corevm::types::native_map expected_result;
  expected_result[2] = 22;

  corevm::types::native_type_handle oprd1 = map;
  corevm::types::native_type_handle oprd2 = key;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_mapers, corevm::types::native_map>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_map_type_test, TestInstrMAPCLR)
{
  corevm::types::native_map map;
  map[1] = 11;
  map[2] = 222;

  corevm::types::native_map expected_result;
  corevm::types::native_type_handle oprd = map;

  push_eval_stack_and_frame(eval_oprds_list{oprd});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_mapclr, corevm::types::native_map>(expected_result);
}

TEST_F(process_native_type_complex_instrs_for_map_type_test, TestInstrMAPSWP)
{
  corevm::types::native_map map;
  map[1] = 11;
  map[2] = 22;

  corevm::types::native_map other;
  other[1] = 22;
  other[2] = 11;

  corevm::types::native_map expected_result;
  expected_result[1] = 22;
  expected_result[2] = 11;

  corevm::types::native_type_handle oprd1 = map;
  corevm::types::native_type_handle oprd2 = other;

  push_eval_stack_and_frame(eval_oprds_list{oprd1, oprd2});

  execute_instr_and_assert_result<corevm::runtime::instr_handler_mapswp, corevm::types::native_map>(expected_result);
}
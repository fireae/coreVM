// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// First part of user declarations.

#line 37 "src/ir/ir_parser.tab.cc" // lalr1.cc:404

#ifndef YY_NULLPTR
#if defined __cplusplus && 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#endif

#include "ir_parser.tab.hh"

// User implementation prologue.

#line 51 "src/ir/ir_parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 35 "src/ir/ir_parser.yy" // lalr1.cc:413

#include "ir_parser_driver.h"

#line 57 "src/ir/ir_parser.tab.cc" // lalr1.cc:413

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#define YY_(msgid) dgettext("bison-runtime", msgid)
#endif
#endif
#ifndef YY_
#define YY_(msgid) msgid
#endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(Current, Rhs, N)                                        \
  do                                                                           \
    if (N) {                                                                   \
      (Current).begin = YYRHSLOC(Rhs, 1).begin;                                \
      (Current).end = YYRHSLOC(Rhs, N).end;                                    \
    } else {                                                                   \
      (Current).begin = (Current).end = YYRHSLOC(Rhs, 0).end;                  \
    }                                                                          \
  while (/*CONSTCOND*/ false)
#endif

// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void)(E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
#define YYCDEBUG                                                               \
  if (yydebug_)                                                                \
  (*yycdebug_)

#define YY_SYMBOL_PRINT(Title, Symbol)                                         \
  do {                                                                         \
    if (yydebug_) {                                                            \
      *yycdebug_ << Title << ' ';                                              \
      yy_print_(*yycdebug_, Symbol);                                           \
      *yycdebug_ << std::endl;                                                 \
    }                                                                          \
  } while (false)

#define YY_REDUCE_PRINT(Rule)                                                  \
  do {                                                                         \
    if (yydebug_)                                                              \
      yy_reduce_print_(Rule);                                                  \
  } while (false)

#define YY_STACK_PRINT()                                                       \
  do {                                                                         \
    if (yydebug_)                                                              \
      yystack_print_();                                                        \
  } while (false)

#else // !YYDEBUG

#define YYCDEBUG                                                               \
  if (false)                                                                   \
  std::cerr
#define YY_SYMBOL_PRINT(Title, Symbol) YYUSE(Symbol)
#define YY_REDUCE_PRINT(Rule) static_cast<void>(0)
#define YY_STACK_PRINT() static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok (yyerrstatus_ = 0)
#define yyclearin (yyla.clear())

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYRECOVERING() (!!yyerrstatus_)

namespace yy {
#line 143 "src/ir/ir_parser.tab.cc" // lalr1.cc:479

/* Return YYSTR after stripping away unnecessary quotes and
   backslashes, so that it's suitable for yyerror.  The heuristic is
   that double-quoting is unnecessary unless the string contains an
   apostrophe, a comma, or backslash (other than backslash-backslash).
   YYSTR is taken from yytname.  */
std::string
ir_parser::yytnamerr_(const char* yystr)
{
  if (*yystr == '"') {
    std::string yyr = "";
    char const* yyp = yystr;

    for (;;)
      switch (*++yyp) {
      case '\'':
      case ',':
        goto do_not_strip_quotes;

      case '\\':
        if (*++yyp != '\\')
          goto do_not_strip_quotes;
      // Fall through.
      default:
        yyr += *yyp;
        break;

      case '"':
        return yyr;
      }
  do_not_strip_quotes:;
  }

  return yystr;
}

/// Build a parser object.
ir_parser::ir_parser(corevm::ir::IRParserDriver& driver_yyarg,
                     void* yyscanner_yyarg)
  :
#if YYDEBUG
    yydebug_(false),
    yycdebug_(&std::cerr),
#endif
    driver(driver_yyarg),
    yyscanner(yyscanner_yyarg)
{
}

ir_parser::~ir_parser()
{
}

/*---------------.
| Symbol types.  |
`---------------*/

// by_state.
inline ir_parser::by_state::by_state() : state(empty_state)
{
}

inline ir_parser::by_state::by_state(const by_state& other) : state(other.state)
{
}

inline void
ir_parser::by_state::clear()
{
  state = empty_state;
}

inline void
ir_parser::by_state::move(by_state& that)
{
  state = that.state;
  that.clear();
}

inline ir_parser::by_state::by_state(state_type s) : state(s)
{
}

inline ir_parser::symbol_number_type
ir_parser::by_state::type_get() const
{
  if (state == empty_state)
    return empty_symbol;
  else
    return yystos_[state];
}

inline ir_parser::stack_symbol_type::stack_symbol_type()
{
}

inline ir_parser::stack_symbol_type::stack_symbol_type(state_type s,
                                                       symbol_type& that)
  : super_type(s, that.location)
{
  switch (that.type_get()) {
  case 26: // BOOLEAN_CONSTANT
    value.move<bool>(that.value);
    break;

  case 79: // ir_value_type_array
    value.move<corevm::IRArrayType>(that.value);
    break;

  case 64: // basic_block
    value.move<corevm::IRBasicBlock>(that.value);
    break;

  case 54: // function_def
    value.move<corevm::IRClosure>(that.value);
    break;

  case 76: // ir_identifier_type
    value.move<corevm::IRIdentifierType>(that.value);
    break;

  case 66: // instruction
  case 67: // expr
    value.move<corevm::IRInstruction>(that.value);
    break;

  case 52: // intrinsic_decl
    value.move<corevm::IRIntrinsicDecl>(that.value);
    break;

  case 72: // label
    value.move<corevm::IRLabel>(that.value);
    break;

  case 43: // input
    value.move<corevm::IRModule>(that.value);
    break;

  case 17: // OPCODE
    value.move<corevm::IROpcode>(that.value);
    break;

  case 74: // operand
    value.move<corevm::IROperand>(that.value);
    break;

  case 62: // function_arg
    value.move<corevm::IRParameter>(that.value);
    break;

  case 49: // type_attribute
    value.move<corevm::IRTypeAttribute>(that.value);
    break;

  case 47: // type_def
    value.move<corevm::IRTypeDecl>(that.value);
    break;

  case 51: // type_field
    value.move<corevm::IRTypeField>(that.value);
    break;

  case 77: // ir_value
    value.move<corevm::IRValue>(that.value);
    break;

  case 78: // ir_value_type
  case 80: // ir_value_type_string
  case 81: // ir_value_type_floating_numeric
  case 82: // ir_value_type_integer_numeric
  case 83: // ir_value_type_long_integer_numeric
  case 84: // ir_value_type_short_integer_numeric
    value.move<corevm::IRValueType>(that.value);
    break;

  case 45: // metadata_def
    value.move<corevm::ir::MetadataPair>(that.value);
    break;

  case 25: // FLOATINGNUM
    value.move<double>(that.value);
    break;

  case 24: // DECIMALINTEGER
  case 55: // function_def_option_list
  case 56: // function_def_option_list_core
  case 57: // function_def_option
    value.move<int64_t>(that.value);
    break;

  case 3:  // TYPE_NAME_I8
  case 4:  // TYPE_NAME_UI8
  case 5:  // TYPE_NAME_I16
  case 6:  // TYPE_NAME_UI16
  case 7:  // TYPE_NAME_I32
  case 8:  // TYPE_NAME_UI32
  case 9:  // TYPE_NAME_I64
  case 10: // TYPE_NAME_UI64
  case 11: // TYPE_NAME_SPF
  case 12: // TYPE_NAME_DPF
  case 13: // TYPE_NAME_BOOLEAN
  case 14: // TYPE_NAME_VOID
  case 15: // TYPE_NAME_STRING
  case 16: // TYPE_NAME_OBJECT
  case 18: // ARRAY
  case 19: // DEF
  case 20: // DECLARE
  case 21: // TYPE
  case 22: // IDENTIFIER
  case 23: // STRING_LITERAL
  case 27: // COMMA
  case 28: // DOT
  case 29: // COLON
  case 30: // SEMICOLON
  case 31: // PERCENT
  case 32: // STAR
  case 33: // POND
  case 34: // ASSIGN
  case 35: // LPAREN
  case 36: // RPAREN
  case 37: // LBRACKET
  case 38: // RBRACKET
  case 39: // LBRACE
  case 40: // RBRACE
  case 41: // LABEL
  case 53: // intrinsic_decl_name
  case 58: // closure_parent
  case 59: // keyword_args
  case 60: // position_args
  case 75: // identifier
    value.move<std::string>(that.value);
    break;

  case 63: // basic_block_list
    value.move<std::vector<corevm::IRBasicBlock>>(that.value);
    break;

  case 65: // instruction_group
    value.move<std::vector<corevm::IRInstruction>>(that.value);
    break;

  case 70: // label_list
  case 71: // label_list_core
    value.move<std::vector<corevm::IRLabel>>(that.value);
    break;

  case 73: // operand_list
    value.move<std::vector<corevm::IROperand>>(that.value);
    break;

  case 61: // function_arg_list
    value.move<std::vector<corevm::IRParameter>>(that.value);
    break;

  case 48: // type_attribute_list
    value.move<std::vector<corevm::IRTypeAttribute>>(that.value);
    break;

  case 50: // type_field_list
    value.move<std::vector<corevm::IRTypeField>>(that.value);
    break;

  case 46: // definition_list
    value.move<std::vector<corevm::ir::IRDefn>>(that.value);
    break;

  case 44: // metadata_def_list
    value.move<std::vector<corevm::ir::MetadataPair>>(that.value);
    break;

  case 68: // instruction_options
  case 69: // instruction_option_list
    value.move<std::vector<std::string>>(that.value);
    break;

  default:
    break;
  }

  // that is emptied.
  that.type = empty_symbol;
}

inline ir_parser::stack_symbol_type&
ir_parser::stack_symbol_type::operator=(const stack_symbol_type& that)
{
  state = that.state;
  switch (that.type_get()) {
  case 26: // BOOLEAN_CONSTANT
    value.copy<bool>(that.value);
    break;

  case 79: // ir_value_type_array
    value.copy<corevm::IRArrayType>(that.value);
    break;

  case 64: // basic_block
    value.copy<corevm::IRBasicBlock>(that.value);
    break;

  case 54: // function_def
    value.copy<corevm::IRClosure>(that.value);
    break;

  case 76: // ir_identifier_type
    value.copy<corevm::IRIdentifierType>(that.value);
    break;

  case 66: // instruction
  case 67: // expr
    value.copy<corevm::IRInstruction>(that.value);
    break;

  case 52: // intrinsic_decl
    value.copy<corevm::IRIntrinsicDecl>(that.value);
    break;

  case 72: // label
    value.copy<corevm::IRLabel>(that.value);
    break;

  case 43: // input
    value.copy<corevm::IRModule>(that.value);
    break;

  case 17: // OPCODE
    value.copy<corevm::IROpcode>(that.value);
    break;

  case 74: // operand
    value.copy<corevm::IROperand>(that.value);
    break;

  case 62: // function_arg
    value.copy<corevm::IRParameter>(that.value);
    break;

  case 49: // type_attribute
    value.copy<corevm::IRTypeAttribute>(that.value);
    break;

  case 47: // type_def
    value.copy<corevm::IRTypeDecl>(that.value);
    break;

  case 51: // type_field
    value.copy<corevm::IRTypeField>(that.value);
    break;

  case 77: // ir_value
    value.copy<corevm::IRValue>(that.value);
    break;

  case 78: // ir_value_type
  case 80: // ir_value_type_string
  case 81: // ir_value_type_floating_numeric
  case 82: // ir_value_type_integer_numeric
  case 83: // ir_value_type_long_integer_numeric
  case 84: // ir_value_type_short_integer_numeric
    value.copy<corevm::IRValueType>(that.value);
    break;

  case 45: // metadata_def
    value.copy<corevm::ir::MetadataPair>(that.value);
    break;

  case 25: // FLOATINGNUM
    value.copy<double>(that.value);
    break;

  case 24: // DECIMALINTEGER
  case 55: // function_def_option_list
  case 56: // function_def_option_list_core
  case 57: // function_def_option
    value.copy<int64_t>(that.value);
    break;

  case 3:  // TYPE_NAME_I8
  case 4:  // TYPE_NAME_UI8
  case 5:  // TYPE_NAME_I16
  case 6:  // TYPE_NAME_UI16
  case 7:  // TYPE_NAME_I32
  case 8:  // TYPE_NAME_UI32
  case 9:  // TYPE_NAME_I64
  case 10: // TYPE_NAME_UI64
  case 11: // TYPE_NAME_SPF
  case 12: // TYPE_NAME_DPF
  case 13: // TYPE_NAME_BOOLEAN
  case 14: // TYPE_NAME_VOID
  case 15: // TYPE_NAME_STRING
  case 16: // TYPE_NAME_OBJECT
  case 18: // ARRAY
  case 19: // DEF
  case 20: // DECLARE
  case 21: // TYPE
  case 22: // IDENTIFIER
  case 23: // STRING_LITERAL
  case 27: // COMMA
  case 28: // DOT
  case 29: // COLON
  case 30: // SEMICOLON
  case 31: // PERCENT
  case 32: // STAR
  case 33: // POND
  case 34: // ASSIGN
  case 35: // LPAREN
  case 36: // RPAREN
  case 37: // LBRACKET
  case 38: // RBRACKET
  case 39: // LBRACE
  case 40: // RBRACE
  case 41: // LABEL
  case 53: // intrinsic_decl_name
  case 58: // closure_parent
  case 59: // keyword_args
  case 60: // position_args
  case 75: // identifier
    value.copy<std::string>(that.value);
    break;

  case 63: // basic_block_list
    value.copy<std::vector<corevm::IRBasicBlock>>(that.value);
    break;

  case 65: // instruction_group
    value.copy<std::vector<corevm::IRInstruction>>(that.value);
    break;

  case 70: // label_list
  case 71: // label_list_core
    value.copy<std::vector<corevm::IRLabel>>(that.value);
    break;

  case 73: // operand_list
    value.copy<std::vector<corevm::IROperand>>(that.value);
    break;

  case 61: // function_arg_list
    value.copy<std::vector<corevm::IRParameter>>(that.value);
    break;

  case 48: // type_attribute_list
    value.copy<std::vector<corevm::IRTypeAttribute>>(that.value);
    break;

  case 50: // type_field_list
    value.copy<std::vector<corevm::IRTypeField>>(that.value);
    break;

  case 46: // definition_list
    value.copy<std::vector<corevm::ir::IRDefn>>(that.value);
    break;

  case 44: // metadata_def_list
    value.copy<std::vector<corevm::ir::MetadataPair>>(that.value);
    break;

  case 68: // instruction_options
  case 69: // instruction_option_list
    value.copy<std::vector<std::string>>(that.value);
    break;

  default:
    break;
  }

  location = that.location;
  return *this;
}

template <typename Base>
inline void
ir_parser::yy_destroy_(const char* yymsg, basic_symbol<Base>& yysym) const
{
  if (yymsg)
    YY_SYMBOL_PRINT(yymsg, yysym);
}

#if YYDEBUG
template <typename Base>
void
ir_parser::yy_print_(std::ostream& yyo, const basic_symbol<Base>& yysym) const
{
  std::ostream& yyoutput = yyo;
  YYUSE(yyoutput);
  symbol_number_type yytype = yysym.type_get();
  // Avoid a (spurious) G++ 4.8 warning about "array subscript is
  // below array bounds".
  if (yysym.empty())
    std::abort();
  yyo << (yytype < yyntokens_ ? "token" : "nterm") << ' ' << yytname_[yytype]
      << " (" << yysym.location << ": ";
  YYUSE(yytype);
  yyo << ')';
}
#endif

inline void
ir_parser::yypush_(const char* m, state_type s, symbol_type& sym)
{
  stack_symbol_type t(s, sym);
  yypush_(m, t);
}

inline void
ir_parser::yypush_(const char* m, stack_symbol_type& s)
{
  if (m)
    YY_SYMBOL_PRINT(m, s);
  yystack_.push(s);
}

inline void
ir_parser::yypop_(unsigned int n)
{
  yystack_.pop(n);
}

#if YYDEBUG
std::ostream&
ir_parser::debug_stream() const
{
  return *yycdebug_;
}

void
ir_parser::set_debug_stream(std::ostream& o)
{
  yycdebug_ = &o;
}

ir_parser::debug_level_type
ir_parser::debug_level() const
{
  return yydebug_;
}

void
ir_parser::set_debug_level(debug_level_type l)
{
  yydebug_ = l;
}
#endif // YYDEBUG

inline ir_parser::state_type
ir_parser::yy_lr_goto_state_(state_type yystate, int yysym)
{
  int yyr = yypgoto_[yysym - yyntokens_] + yystate;
  if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
    return yytable_[yyr];
  else
    return yydefgoto_[yysym - yyntokens_];
}

inline bool
ir_parser::yy_pact_value_is_default_(int yyvalue)
{
  return yyvalue == yypact_ninf_;
}

inline bool
ir_parser::yy_table_value_is_error_(int yyvalue)
{
  return yyvalue == yytable_ninf_;
}

int
ir_parser::parse()
{
  // State.
  int yyn;
  /// Length of the RHS of the rule being reduced.
  int yylen = 0;

  // Error handling.
  int yynerrs_ = 0;
  int yyerrstatus_ = 0;

  /// The lookahead symbol.
  symbol_type yyla;

  /// The locations where the error started and ended.
  stack_symbol_type yyerror_range[3];

  /// The return value of parse ().
  int yyresult;

  // FIXME: This shoud be completely indented.  It is not yet to
  // avoid gratuitous conflicts when merging into the master branch.
  try {
    YYCDEBUG << "Starting parse" << std::endl;

// User initialization code.
#line 27 "src/ir/ir_parser.yy" // lalr1.cc:745
    {
      // Initialize the initial location.
      if (!driver.input_file().empty()) {
        yyla.location.begin.filename = yyla.location.end.filename =
          &driver.input_file();
      }
    }

#line 769 "src/ir/ir_parser.tab.cc" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
   yynewstate, since the latter expects the semantical and the
   location values to have been already stored, initialize these
   stacks with a primary value.  */
    yystack_.clear();
    yypush_(YY_NULLPTR, 0, yyla);

  // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

  // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_(yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty()) {
      YYCDEBUG << "Reading a token: ";
      try {
        symbol_type yylookahead(yylex(driver, yyscanner));
        yyla.move(yylookahead);
      } catch (const syntax_error& yyexc) {
        error(yyexc);
        goto yyerrlab1;
      }
    }
    YY_SYMBOL_PRINT("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
   to detect an error, take that action.  */
    yyn += yyla.type_get();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0) {
      if (yy_table_value_is_error_(yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
   correct type. The default '$$ = $1' action is NOT applied
   when using variants.  */
      switch (yyr1_[yyn]) {
      case 26: // BOOLEAN_CONSTANT
        yylhs.value.build<bool>();
        break;

      case 79: // ir_value_type_array
        yylhs.value.build<corevm::IRArrayType>();
        break;

      case 64: // basic_block
        yylhs.value.build<corevm::IRBasicBlock>();
        break;

      case 54: // function_def
        yylhs.value.build<corevm::IRClosure>();
        break;

      case 76: // ir_identifier_type
        yylhs.value.build<corevm::IRIdentifierType>();
        break;

      case 66: // instruction
      case 67: // expr
        yylhs.value.build<corevm::IRInstruction>();
        break;

      case 52: // intrinsic_decl
        yylhs.value.build<corevm::IRIntrinsicDecl>();
        break;

      case 72: // label
        yylhs.value.build<corevm::IRLabel>();
        break;

      case 43: // input
        yylhs.value.build<corevm::IRModule>();
        break;

      case 17: // OPCODE
        yylhs.value.build<corevm::IROpcode>();
        break;

      case 74: // operand
        yylhs.value.build<corevm::IROperand>();
        break;

      case 62: // function_arg
        yylhs.value.build<corevm::IRParameter>();
        break;

      case 49: // type_attribute
        yylhs.value.build<corevm::IRTypeAttribute>();
        break;

      case 47: // type_def
        yylhs.value.build<corevm::IRTypeDecl>();
        break;

      case 51: // type_field
        yylhs.value.build<corevm::IRTypeField>();
        break;

      case 77: // ir_value
        yylhs.value.build<corevm::IRValue>();
        break;

      case 78: // ir_value_type
      case 80: // ir_value_type_string
      case 81: // ir_value_type_floating_numeric
      case 82: // ir_value_type_integer_numeric
      case 83: // ir_value_type_long_integer_numeric
      case 84: // ir_value_type_short_integer_numeric
        yylhs.value.build<corevm::IRValueType>();
        break;

      case 45: // metadata_def
        yylhs.value.build<corevm::ir::MetadataPair>();
        break;

      case 25: // FLOATINGNUM
        yylhs.value.build<double>();
        break;

      case 24: // DECIMALINTEGER
      case 55: // function_def_option_list
      case 56: // function_def_option_list_core
      case 57: // function_def_option
        yylhs.value.build<int64_t>();
        break;

      case 3:  // TYPE_NAME_I8
      case 4:  // TYPE_NAME_UI8
      case 5:  // TYPE_NAME_I16
      case 6:  // TYPE_NAME_UI16
      case 7:  // TYPE_NAME_I32
      case 8:  // TYPE_NAME_UI32
      case 9:  // TYPE_NAME_I64
      case 10: // TYPE_NAME_UI64
      case 11: // TYPE_NAME_SPF
      case 12: // TYPE_NAME_DPF
      case 13: // TYPE_NAME_BOOLEAN
      case 14: // TYPE_NAME_VOID
      case 15: // TYPE_NAME_STRING
      case 16: // TYPE_NAME_OBJECT
      case 18: // ARRAY
      case 19: // DEF
      case 20: // DECLARE
      case 21: // TYPE
      case 22: // IDENTIFIER
      case 23: // STRING_LITERAL
      case 27: // COMMA
      case 28: // DOT
      case 29: // COLON
      case 30: // SEMICOLON
      case 31: // PERCENT
      case 32: // STAR
      case 33: // POND
      case 34: // ASSIGN
      case 35: // LPAREN
      case 36: // RPAREN
      case 37: // LBRACKET
      case 38: // RBRACKET
      case 39: // LBRACE
      case 40: // RBRACE
      case 41: // LABEL
      case 53: // intrinsic_decl_name
      case 58: // closure_parent
      case 59: // keyword_args
      case 60: // position_args
      case 75: // identifier
        yylhs.value.build<std::string>();
        break;

      case 63: // basic_block_list
        yylhs.value.build<std::vector<corevm::IRBasicBlock>>();
        break;

      case 65: // instruction_group
        yylhs.value.build<std::vector<corevm::IRInstruction>>();
        break;

      case 70: // label_list
      case 71: // label_list_core
        yylhs.value.build<std::vector<corevm::IRLabel>>();
        break;

      case 73: // operand_list
        yylhs.value.build<std::vector<corevm::IROperand>>();
        break;

      case 61: // function_arg_list
        yylhs.value.build<std::vector<corevm::IRParameter>>();
        break;

      case 48: // type_attribute_list
        yylhs.value.build<std::vector<corevm::IRTypeAttribute>>();
        break;

      case 50: // type_field_list
        yylhs.value.build<std::vector<corevm::IRTypeField>>();
        break;

      case 46: // definition_list
        yylhs.value.build<std::vector<corevm::ir::IRDefn>>();
        break;

      case 44: // metadata_def_list
        yylhs.value.build<std::vector<corevm::ir::MetadataPair>>();
        break;

      case 68: // instruction_options
      case 69: // instruction_option_list
        yylhs.value.build<std::vector<std::string>>();
        break;

      default:
        break;
      }

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice(yystack_, yylen);
        YYLLOC_DEFAULT(yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT(yyn);
      try {
        switch (yyn) {
        case 2:
#line 131 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRModule>() = corevm::IRModule();
          corevm::ir::set_metadata_and_definitions(
            yystack_[1].value.as<std::vector<corevm::ir::MetadataPair>>(),
            yystack_[0].value.as<std::vector<corevm::ir::IRDefn>>(),
            yylhs.value.as<corevm::IRModule>());
          driver.set_module(std::move(yylhs.value.as<corevm::IRModule>()));
        }
#line 1057 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 3:
#line 140 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::ir::MetadataPair>>() =
            std::vector<corevm::ir::MetadataPair>();
        }
#line 1065 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 4:
#line 144 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::ir::MetadataPair>>() = std::move(
            yystack_[1].value.as<std::vector<corevm::ir::MetadataPair>>());
          yylhs.value.as<std::vector<corevm::ir::MetadataPair>>().push_back(
            yystack_[0].value.as<corevm::ir::MetadataPair>());
        }
#line 1074 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 5:
#line 152 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::ir::MetadataPair>() =
            std::make_pair(yystack_[2].value.as<std::string>(),
                           yystack_[0].value.as<std::string>());
        }
#line 1082 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 6:
#line 159 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::ir::IRDefn>>() =
            std::vector<corevm::ir::IRDefn>();
        }
#line 1090 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 7:
#line 163 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::ir::IRDefn>>() =
            std::move(yystack_[1].value.as<std::vector<corevm::ir::IRDefn>>());
          yylhs.value.as<std::vector<corevm::ir::IRDefn>>().push_back(
            yystack_[0].value.as<corevm::IRTypeDecl>());
        }
#line 1099 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 8:
#line 168 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::ir::IRDefn>>() =
            std::move(yystack_[1].value.as<std::vector<corevm::ir::IRDefn>>());
          yylhs.value.as<std::vector<corevm::ir::IRDefn>>().push_back(
            yystack_[0].value.as<corevm::IRClosure>());
        }
#line 1108 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 9:
#line 173 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::ir::IRDefn>>() =
            std::move(yystack_[1].value.as<std::vector<corevm::ir::IRDefn>>());
          yylhs.value.as<std::vector<corevm::ir::IRDefn>>().push_back(
            yystack_[0].value.as<corevm::IRIntrinsicDecl>());
        }
#line 1117 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 10:
#line 181 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRTypeDecl>() = corevm::IRTypeDecl();
          yylhs.value.as<corevm::IRTypeDecl>().name =
            std::move(yystack_[3].value.as<std::string>());
          yylhs.value.as<corevm::IRTypeDecl>().fields =
            std::move(yystack_[1].value.as<std::vector<corevm::IRTypeField>>());
        }
#line 1127 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 11:
#line 188 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRTypeDecl>() = corevm::IRTypeDecl();
          yylhs.value.as<corevm::IRTypeDecl>().attributes = std::move(
            yystack_[6].value.as<std::vector<corevm::IRTypeAttribute>>());
          yylhs.value.as<corevm::IRTypeDecl>().name =
            std::move(yystack_[3].value.as<std::string>());
          yylhs.value.as<corevm::IRTypeDecl>().fields =
            std::move(yystack_[1].value.as<std::vector<corevm::IRTypeField>>());
        }
#line 1138 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 12:
#line 198 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRTypeAttribute>>() =
            std::vector<corevm::IRTypeAttribute>();
          yylhs.value.as<std::vector<corevm::IRTypeAttribute>>().push_back(
            yystack_[0].value.as<corevm::IRTypeAttribute>());
        }
#line 1147 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 13:
#line 203 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRTypeAttribute>>() = std::move(
            yystack_[2].value.as<std::vector<corevm::IRTypeAttribute>>());
          yylhs.value.as<std::vector<corevm::IRTypeAttribute>>().push_back(
            yystack_[0].value.as<corevm::IRTypeAttribute>());
        }
#line 1156 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 14:
#line 211 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRTypeAttribute>() = corevm::IRTypeAttribute();
          yylhs.value.as<corevm::IRTypeAttribute>().name =
            std::move(yystack_[2].value.as<std::string>());
          yylhs.value.as<corevm::IRTypeAttribute>().value =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1166 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 15:
#line 220 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRTypeField>>() =
            std::vector<corevm::IRTypeField>();
        }
#line 1174 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 16:
#line 224 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRTypeField>>() =
            std::move(yystack_[1].value.as<std::vector<corevm::IRTypeField>>());
          yylhs.value.as<std::vector<corevm::IRTypeField>>().push_back(
            yystack_[0].value.as<corevm::IRTypeField>());
        }
#line 1183 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 17:
#line 232 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRTypeField>() = corevm::IRTypeField();
          yylhs.value.as<corevm::IRTypeField>().type =
            std::move(yystack_[2].value.as<corevm::IRIdentifierType>());
          yylhs.value.as<corevm::IRTypeField>().identifier =
            std::move(yystack_[1].value.as<std::string>());
        }
#line 1193 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 18:
#line 241 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIntrinsicDecl>() = corevm::IRIntrinsicDecl();
          yylhs.value.as<corevm::IRIntrinsicDecl>().rettype =
            std::move(yystack_[3].value.as<corevm::IRIdentifierType>());
          yylhs.value.as<corevm::IRIntrinsicDecl>().name =
            std::move(yystack_[2].value.as<std::string>());
        }
#line 1203 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 19:
#line 247 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIntrinsicDecl>() = corevm::IRIntrinsicDecl();
          yylhs.value.as<corevm::IRIntrinsicDecl>().rettype =
            std::move(yystack_[4].value.as<corevm::IRIdentifierType>());
          yylhs.value.as<corevm::IRIntrinsicDecl>().name =
            std::move(yystack_[3].value.as<std::string>());
          yylhs.value.as<corevm::IRIntrinsicDecl>().parameters =
            std::move(yystack_[1].value.as<std::vector<corevm::IRParameter>>());
        }
#line 1214 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 20:
#line 257 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::string>() =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1222 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 21:
#line 261 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          std::string name(std::move(yystack_[2].value.as<std::string>()));
          name += (yystack_[1].value.as<std::string>());
          name += (yystack_[0].value.as<std::string>());
          yylhs.value.as<std::string>() = std::move(name);
        }
#line 1233 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 22:
#line 271 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[8].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[7].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parent =
            std::move(yystack_[4].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1246 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 23:
#line 280 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[9].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[8].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parameters =
            std::move(yystack_[6].value.as<std::vector<corevm::IRParameter>>());
          yylhs.value.as<corevm::IRClosure>().parent =
            std::move(yystack_[4].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1260 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 24:
#line 290 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[11].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[10].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parameters =
            std::move(yystack_[8].value.as<std::vector<corevm::IRParameter>>());
          yylhs.value.as<corevm::IRClosure>().positional_args =
            std::move(yystack_[6].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parent =
            std::move(yystack_[4].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1275 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 25:
#line 301 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[11].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[10].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parameters =
            std::move(yystack_[8].value.as<std::vector<corevm::IRParameter>>());
          yylhs.value.as<corevm::IRClosure>().keyword_args =
            std::move(yystack_[6].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parent =
            std::move(yystack_[4].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1290 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 26:
#line 312 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[9].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[8].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().positional_args =
            std::move(yystack_[6].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parent =
            std::move(yystack_[4].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1304 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 27:
#line 322 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[9].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[8].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().keyword_args =
            std::move(yystack_[6].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parent =
            std::move(yystack_[4].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1318 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 28:
#line 332 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[11].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[10].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().positional_args =
            std::move(yystack_[8].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().keyword_args =
            std::move(yystack_[6].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parent =
            yystack_[4].value.as<std::string>();
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1333 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 29:
#line 343 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRClosure>() = corevm::IRClosure();
          yylhs.value.as<corevm::IRClosure>().rettype =
            yystack_[13].value.as<corevm::IRIdentifierType>();
          yylhs.value.as<corevm::IRClosure>().name =
            std::move(yystack_[12].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parameters = std::move(
            yystack_[10].value.as<std::vector<corevm::IRParameter>>());
          yylhs.value.as<corevm::IRClosure>().positional_args =
            std::move(yystack_[8].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().keyword_args =
            std::move(yystack_[6].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().parent =
            std::move(yystack_[4].value.as<std::string>());
          yylhs.value.as<corevm::IRClosure>().options =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRClosure>().blocks = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
        }
#line 1349 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 30:
#line 358 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<int64_t>() = 0;
        }
#line 1357 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 31:
#line 362 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<int64_t>() = yystack_[1].value.as<int64_t>();
        }
#line 1365 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 32:
#line 369 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<int64_t>() = yystack_[0].value.as<int64_t>();
        }
#line 1373 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 33:
#line 373 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<int64_t>() = corevm::ir::add_func_defn_option(
            yystack_[1].value.as<int64_t>(), yystack_[0].value.as<int64_t>());
        }
#line 1381 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 34:
#line 380 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<int64_t>() = corevm::ir::interpret_func_defn_option(
            yystack_[0].value.as<std::string>());
        }
#line 1389 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 35:
#line 387 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
        }
#line 1396 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 36:
#line 390 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::string>() =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1404 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 37:
#line 397 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::string>() =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1412 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 38:
#line 404 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::string>() =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1420 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 39:
#line 411 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRParameter>>() =
            std::vector<corevm::IRParameter>();
          yylhs.value.as<std::vector<corevm::IRParameter>>().push_back(
            yystack_[0].value.as<corevm::IRParameter>());
        }
#line 1429 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 40:
#line 416 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRParameter>>() =
            std::move(yystack_[2].value.as<std::vector<corevm::IRParameter>>());
          yylhs.value.as<std::vector<corevm::IRParameter>>().push_back(
            yystack_[0].value.as<corevm::IRParameter>());
        }
#line 1438 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 41:
#line 424 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRParameter>() = corevm::IRParameter();
          yylhs.value.as<corevm::IRParameter>().type =
            std::move(yystack_[1].value.as<corevm::IRIdentifierType>());
          yylhs.value.as<corevm::IRParameter>().identifier =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1448 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 42:
#line 433 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRBasicBlock>>() =
            std::vector<corevm::IRBasicBlock>();
        }
#line 1456 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 43:
#line 437 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRBasicBlock>>() = std::move(
            yystack_[1].value.as<std::vector<corevm::IRBasicBlock>>());
          yylhs.value.as<std::vector<corevm::IRBasicBlock>>().push_back(
            yystack_[0].value.as<corevm::IRBasicBlock>());
        }
#line 1465 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 44:
#line 445 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRBasicBlock>() = corevm::IRBasicBlock();
          yylhs.value.as<corevm::IRBasicBlock>().label =
            std::move(yystack_[2].value.as<std::string>());
          yylhs.value.as<corevm::IRBasicBlock>().body = std::move(
            yystack_[0].value.as<std::vector<corevm::IRInstruction>>());
        }
#line 1475 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 45:
#line 454 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRInstruction>>() =
            std::vector<corevm::IRInstruction>();
          yylhs.value.as<std::vector<corevm::IRInstruction>>().push_back(
            yystack_[0].value.as<corevm::IRInstruction>());
        }
#line 1484 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 46:
#line 459 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRInstruction>>() = std::move(
            yystack_[1].value.as<std::vector<corevm::IRInstruction>>());
          yylhs.value.as<std::vector<corevm::IRInstruction>>().push_back(
            yystack_[0].value.as<corevm::IRInstruction>());
        }
#line 1493 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 47:
#line 467 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() =
            std::move(yystack_[1].value.as<corevm::IRInstruction>());
          yylhs.value.as<corevm::IRInstruction>().target.set_string(
            yystack_[3].value.as<std::string>());
        }
#line 1502 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 48:
#line 472 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() =
            std::move(yystack_[1].value.as<corevm::IRInstruction>());
          yylhs.value.as<corevm::IRInstruction>().target.set_null();
        }
#line 1511 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 49:
#line 480 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() = corevm::IRInstruction();
          yylhs.value.as<corevm::IRInstruction>().opcode =
            yystack_[1].value.as<corevm::IROpcode>();
          yylhs.value.as<corevm::IRInstruction>().options =
            std::move(yystack_[0].value.as<std::vector<std::string>>());
          yylhs.value.as<corevm::IRInstruction>().type.set_null();
        }
#line 1522 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 50:
#line 487 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() = corevm::IRInstruction();
          yylhs.value.as<corevm::IRInstruction>().opcode =
            yystack_[2].value.as<corevm::IROpcode>();
          yylhs.value.as<corevm::IRInstruction>().options =
            std::move(yystack_[1].value.as<std::vector<std::string>>());
          yylhs.value.as<corevm::IRInstruction>().type.set_IRIdentifierType(
            yystack_[0].value.as<corevm::IRIdentifierType>());
        }
#line 1533 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 51:
#line 494 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() = corevm::IRInstruction();
          yylhs.value.as<corevm::IRInstruction>().opcode =
            yystack_[2].value.as<corevm::IROpcode>();
          yylhs.value.as<corevm::IRInstruction>().options =
            std::move(yystack_[1].value.as<std::vector<std::string>>());
          yylhs.value.as<corevm::IRInstruction>().oprds =
            std::move(yystack_[0].value.as<std::vector<corevm::IROperand>>());
          yylhs.value.as<corevm::IRInstruction>().type.set_null();
        }
#line 1545 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 52:
#line 502 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() = corevm::IRInstruction();
          yylhs.value.as<corevm::IRInstruction>().opcode =
            yystack_[3].value.as<corevm::IROpcode>();
          yylhs.value.as<corevm::IRInstruction>().options =
            std::move(yystack_[2].value.as<std::vector<std::string>>());
          yylhs.value.as<corevm::IRInstruction>().oprds =
            std::move(yystack_[1].value.as<std::vector<corevm::IROperand>>());
          yylhs.value.as<corevm::IRInstruction>().labels.set_array(
            yystack_[0].value.as<std::vector<corevm::IRLabel>>());
          yylhs.value.as<corevm::IRInstruction>().type.set_null();
        }
#line 1558 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 53:
#line 511 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() = corevm::IRInstruction();
          yylhs.value.as<corevm::IRInstruction>().opcode =
            yystack_[3].value.as<corevm::IROpcode>();
          yylhs.value.as<corevm::IRInstruction>().options =
            std::move(yystack_[2].value.as<std::vector<std::string>>());
          yylhs.value.as<corevm::IRInstruction>().type.set_IRIdentifierType(
            yystack_[1].value.as<corevm::IRIdentifierType>());
          yylhs.value.as<corevm::IRInstruction>().oprds =
            std::move(yystack_[0].value.as<std::vector<corevm::IROperand>>());
        }
#line 1570 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 54:
#line 519 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() = corevm::IRInstruction();
          yylhs.value.as<corevm::IRInstruction>().opcode =
            yystack_[4].value.as<corevm::IROpcode>();
          yylhs.value.as<corevm::IRInstruction>().options =
            std::move(yystack_[3].value.as<std::vector<std::string>>());
          yylhs.value.as<corevm::IRInstruction>().type.set_IRIdentifierType(
            yystack_[2].value.as<corevm::IRIdentifierType>());
          yylhs.value.as<corevm::IRInstruction>().oprds =
            std::move(yystack_[1].value.as<std::vector<corevm::IROperand>>());
          yylhs.value.as<corevm::IRInstruction>().labels.set_array(
            yystack_[0].value.as<std::vector<corevm::IRLabel>>());
        }
#line 1583 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 55:
#line 528 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRInstruction>() = corevm::IRInstruction();
          yylhs.value.as<corevm::IRInstruction>().opcode =
            yystack_[1].value.as<corevm::IROpcode>();
          yylhs.value.as<corevm::IRInstruction>().labels.set_array(
            yystack_[0].value.as<std::vector<corevm::IRLabel>>());
        }
#line 1593 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 56:
#line 537 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<std::string>>() =
            std::vector<std::string>();
        }
#line 1601 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 57:
#line 541 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<std::string>>() =
            std::move(yystack_[1].value.as<std::vector<std::string>>());
        }
#line 1609 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 58:
#line 548 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<std::string>>() =
            std::vector<std::string>();
          yylhs.value.as<std::vector<std::string>>().push_back(
            yystack_[0].value.as<std::string>());
        }
#line 1618 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 59:
#line 553 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<std::string>>() =
            std::move(yystack_[1].value.as<std::vector<std::string>>());
          yylhs.value.as<std::vector<std::string>>().push_back(
            yystack_[0].value.as<std::string>());
        }
#line 1627 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 60:
#line 561 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRLabel>>() =
            std::move(yystack_[1].value.as<std::vector<corevm::IRLabel>>());
        }
#line 1635 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 61:
#line 568 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRLabel>>() =
            std::vector<corevm::IRLabel>();
          yylhs.value.as<std::vector<corevm::IRLabel>>().push_back(
            yystack_[0].value.as<corevm::IRLabel>());
        }
#line 1644 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 62:
#line 573 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IRLabel>>() =
            std::move(yystack_[2].value.as<std::vector<corevm::IRLabel>>());
          yylhs.value.as<std::vector<corevm::IRLabel>>().push_back(
            yystack_[0].value.as<corevm::IRLabel>());
        }
#line 1653 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 63:
#line 581 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRLabel>() = corevm::IRLabel();
          yylhs.value.as<corevm::IRLabel>().name =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1662 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 64:
#line 589 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IROperand>>() =
            std::vector<corevm::IROperand>();
          yylhs.value.as<std::vector<corevm::IROperand>>().push_back(
            yystack_[0].value.as<corevm::IROperand>());
        }
#line 1671 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 65:
#line 594 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::vector<corevm::IROperand>>() =
            std::move(yystack_[1].value.as<std::vector<corevm::IROperand>>());
          yylhs.value.as<std::vector<corevm::IROperand>>().push_back(
            yystack_[0].value.as<corevm::IROperand>());
        }
#line 1680 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 66:
#line 602 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IROperand>() = corevm::IROperand();
          yylhs.value.as<corevm::IROperand>().type = corevm::constant;
          yylhs.value.as<corevm::IROperand>().value.set_IRValue(
            yystack_[0].value.as<corevm::IRValue>());
        }
#line 1690 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 67:
#line 608 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IROperand>() = corevm::IROperand();
          yylhs.value.as<corevm::IROperand>().type = corevm::ref;
          yylhs.value.as<corevm::IROperand>().value.set_string(
            yystack_[0].value.as<std::string>());
        }
#line 1700 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 68:
#line 617 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<std::string>() =
            std::move(yystack_[0].value.as<std::string>());
        }
#line 1708 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 69:
#line 624 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIdentifierType>() =
            corevm::IRIdentifierType();
          yylhs.value.as<corevm::IRIdentifierType>().type =
            corevm::IdentifierType_Identifier;
          yylhs.value.as<corevm::IRIdentifierType>().ref_type = corevm::value;
          yylhs.value.as<corevm::IRIdentifierType>().value.set_string(
            yystack_[0].value.as<std::string>());
        }
#line 1719 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 70:
#line 631 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIdentifierType>() =
            corevm::IRIdentifierType();
          yylhs.value.as<corevm::IRIdentifierType>().type =
            corevm::IdentifierType_ValueType;
          yylhs.value.as<corevm::IRIdentifierType>().ref_type = corevm::value;
          yylhs.value.as<corevm::IRIdentifierType>().value.set_IRValueType(
            yystack_[0].value.as<corevm::IRValueType>());
        }
#line 1730 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 71:
#line 638 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIdentifierType>() =
            corevm::IRIdentifierType();
          yylhs.value.as<corevm::IRIdentifierType>().type =
            corevm::IdentifierType_Array;
          yylhs.value.as<corevm::IRIdentifierType>().ref_type = corevm::value;
          yylhs.value.as<corevm::IRIdentifierType>().value.set_IRArrayType(
            yystack_[0].value.as<corevm::IRArrayType>());
        }
#line 1741 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 72:
#line 645 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIdentifierType>() =
            corevm::IRIdentifierType();
          yylhs.value.as<corevm::IRIdentifierType>().type =
            corevm::IdentifierType_Identifier;
          yylhs.value.as<corevm::IRIdentifierType>().ref_type = corevm::pointer;
          yylhs.value.as<corevm::IRIdentifierType>().value.set_string(
            yystack_[1].value.as<std::string>());
        }
#line 1752 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 73:
#line 652 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIdentifierType>() =
            corevm::IRIdentifierType();
          yylhs.value.as<corevm::IRIdentifierType>().type =
            corevm::IdentifierType_ValueType;
          yylhs.value.as<corevm::IRIdentifierType>().ref_type = corevm::pointer;
          yylhs.value.as<corevm::IRIdentifierType>().value.set_IRValueType(
            yystack_[1].value.as<corevm::IRValueType>());
        }
#line 1763 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 74:
#line 659 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRIdentifierType>() =
            corevm::IRIdentifierType();
          yylhs.value.as<corevm::IRIdentifierType>().type =
            corevm::IdentifierType_Array;
          yylhs.value.as<corevm::IRIdentifierType>().ref_type = corevm::pointer;
          yylhs.value.as<corevm::IRIdentifierType>().value.set_IRArrayType(
            yystack_[1].value.as<corevm::IRArrayType>());
        }
#line 1774 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 75:
#line 669 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValue>() = corevm::IRValue();
          yylhs.value.as<corevm::IRValue>().type =
            yystack_[1].value.as<corevm::IRValueType>();
          yylhs.value.as<corevm::IRValue>().value.set_int(
            yystack_[0].value.as<int64_t>());
        }
#line 1784 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 76:
#line 675 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValue>() = corevm::IRValue();
          yylhs.value.as<corevm::IRValue>().type =
            yystack_[1].value.as<corevm::IRValueType>();
          yylhs.value.as<corevm::IRValue>().value.set_long(
            yystack_[0].value.as<int64_t>());
        }
#line 1794 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 77:
#line 681 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValue>() = corevm::IRValue();
          yylhs.value.as<corevm::IRValue>().type = corevm::spf;
          yylhs.value.as<corevm::IRValue>().value.set_float(
            yystack_[0].value.as<double>());
        }
#line 1804 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 78:
#line 687 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValue>() = corevm::IRValue();
          yylhs.value.as<corevm::IRValue>().type = corevm::dpf;
          yylhs.value.as<corevm::IRValue>().value.set_double(
            yystack_[0].value.as<double>());
        }
#line 1814 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 79:
#line 693 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValue>() = corevm::IRValue();
          yylhs.value.as<corevm::IRValue>().type =
            yystack_[1].value.as<corevm::IRValueType>();
          yylhs.value.as<corevm::IRValue>().value.set_string(
            yystack_[0].value.as<std::string>());
        }
#line 1824 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 80:
#line 699 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValue>() = corevm::IRValue();
          yylhs.value.as<corevm::IRValue>().type = corevm::boolean;
          yylhs.value.as<corevm::IRValue>().value.set_bool(
            yystack_[0].value.as<bool>());
        }
#line 1834 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 81:
#line 705 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValue>() = corevm::IRValue();
          yylhs.value.as<corevm::IRValue>().type = corevm::boolean;
          yylhs.value.as<corevm::IRValue>().value.set_bool(
            static_cast<bool>(yystack_[0].value.as<int64_t>()));
        }
#line 1844 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 82:
#line 713 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() =
            yystack_[0].value.as<corevm::IRValueType>();
        }
#line 1850 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 83:
#line 714 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() =
            yystack_[0].value.as<corevm::IRValueType>();
        }
#line 1856 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 84:
#line 715 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() =
            yystack_[0].value.as<corevm::IRValueType>();
        }
#line 1862 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 85:
#line 716 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::voidtype;
        }
#line 1868 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 86:
#line 717 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::boolean;
        }
#line 1874 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 87:
#line 718 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::object;
        }
#line 1880 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 88:
#line 723 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRArrayType>() = corevm::IRArrayType();
          yylhs.value.as<corevm::IRArrayType>().len =
            yystack_[3].value.as<int64_t>();
          yylhs.value.as<corevm::IRArrayType>().type =
            std::move(yystack_[1].value.as<corevm::IRIdentifierType>());
        }
#line 1890 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 89:
#line 731 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::string;
        }
#line 1896 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 90:
#line 735 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::spf;
        }
#line 1902 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 91:
#line 736 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::dpf;
        }
#line 1908 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 92:
#line 740 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() =
            yystack_[0].value.as<corevm::IRValueType>();
        }
#line 1914 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 93:
#line 741 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() =
            yystack_[0].value.as<corevm::IRValueType>();
        }
#line 1920 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 94:
#line 745 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::i64;
        }
#line 1926 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 95:
#line 746 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::ui64;
        }
#line 1932 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 96:
#line 750 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::i8;
        }
#line 1938 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 97:
#line 751 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::ui8;
        }
#line 1944 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 98:
#line 752 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::i16;
        }
#line 1950 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 99:
#line 753 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::ui16;
        }
#line 1956 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 100:
#line 754 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::i32;
        }
#line 1962 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

        case 101:
#line 755 "src/ir/ir_parser.yy" // lalr1.cc:859
        {
          yylhs.value.as<corevm::IRValueType>() = corevm::ui32;
        }
#line 1968 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        break;

#line 1972 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
        default:
          break;
        }
      } catch (const syntax_error& yyexc) {
        error(yyexc);
        YYERROR;
      }
      YY_SYMBOL_PRINT("-> $$ =", yylhs);
      yypop_(yylen);
      yylen = 0;
      YY_STACK_PRINT();

      // Shift the result of the reduction.
      yypush_(YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_) {
      ++yynerrs_;
      error(yyla.location, yysyntax_error_(yystack_[0].state, yyla));
    }

    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3) {
      /* If just tried and failed to reuse lookahead token after an
   error, discard it.  */

      // Return failure if at end of input.
      if (yyla.type_get() == yyeof_)
        YYABORT;
      else if (!yyla.empty()) {
        yy_destroy_("Error: discarding", yyla);
        yyla.clear();
      }
    }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;

  /*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
   YYERROR and the label yyerrorlab therefore never appears in user
   code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
   this YYERROR.  */
    yypop_(yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3; // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;) {
        yyn = yypact_[yystack_[0].state];
        if (!yy_pact_value_is_default_(yyn)) {
          yyn += yyterror_;
          if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_) {
            yyn = yytable_[yyn];
            if (0 < yyn)
              break;
          }
        }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size() == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_("Error: popping", yystack_[0]);
        yypop_();
        YY_STACK_PRINT();
      }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT(error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_("Shifting", error_token);
    }
    goto yynewstate;

  // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

  // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty())
      yy_destroy_("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
   this YYABORT or YYACCEPT.  */
    yypop_(yylen);
    while (1 < yystack_.size()) {
      yy_destroy_("Cleanup: popping", yystack_[0]);
      yypop_();
    }

    return yyresult;
  } catch (...) {
    YYCDEBUG << "Exception caught: cleaning lookahead and stack" << std::endl;
    // Do not try to display the values of the reclaimed symbols,
    // as their printer might throw an exception.
    if (!yyla.empty())
      yy_destroy_(YY_NULLPTR, yyla);

    while (1 < yystack_.size()) {
      yy_destroy_(YY_NULLPTR, yystack_[0]);
      yypop_();
    }
    throw;
  }
}

void
ir_parser::error(const syntax_error& yyexc)
{
  error(yyexc.location, yyexc.what());
}

// Generate an error message.
std::string
ir_parser::yysyntax_error_(state_type yystate, const symbol_type& yyla) const
{
  // Number of reported tokens (one for the "unexpected", one per
  // "expected").
  size_t yycount = 0;
  // Its maximum.
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  // Arguments of yyformat.
  char const* yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

  /* There are many possibilities here to consider:
   - If this state is a consistent state with a default action, then
     the only way this function was invoked is if the default action
     is an error action.  In that case, don't check for expected
     tokens because there are none.
   - The only way there can be no lookahead present (in yyla) is
     if this state is a consistent state with a default action.
     Thus, detecting the absence of a lookahead is sufficient to
     determine that there is no unexpected or expected token to
     report.  In that case, just report a simple "syntax error".
   - Don't assume there isn't a lookahead just because this state is
     a consistent state with a default action.  There might have
     been a previous inconsistent state, consistent state with a
     non-default action, or user semantic action that manipulated
     yyla.  (However, yyla is currently not documented for users.)
   - Of course, the expected token list depends on states to have
     correct lookahead information, and it depends on the parser not
     to perform extra reductions after fetching a lookahead from the
     scanner and before detecting a syntax error.  Thus, state
     merging (from LALR or IELR) and default reductions corrupt the
     expected token list.  However, the list is correct for
     canonical LR with one exception: it will still contain any
     token that will not be accepted due to an error action in a
     later state.
*/
  if (!yyla.empty()) {
    int yytoken = yyla.type_get();
    yyarg[yycount++] = yytname_[yytoken];
    int yyn = yypact_[yystate];
    if (!yy_pact_value_is_default_(yyn)) {
      /* Start YYX at -YYN if negative to avoid negative indexes in
   YYCHECK.  In other words, skip the first -YYN actions for
   this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      // Stay within bounds of both yycheck and yytname.
      int yychecklim = yylast_ - yyn + 1;
      int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
      for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_ &&
            !yy_table_value_is_error_(yytable_[yyx + yyn])) {
          if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM) {
            yycount = 1;
            break;
          } else
            yyarg[yycount++] = yytname_[yyx];
        }
    }
  }

  char const* yyformat = YY_NULLPTR;
  switch (yycount) {
#define YYCASE_(N, S)                                                          \
  case N:                                                                      \
    yyformat = S;                                                              \
    break
    YYCASE_(0, YY_("syntax error"));
    YYCASE_(1, YY_("syntax error, unexpected %s"));
    YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
    YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
    YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
    YYCASE_(5,
            YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
  }

  std::string yyres;
  // Argument number.
  size_t yyi = 0;
  for (char const* yyp = yyformat; *yyp; ++yyp)
    if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount) {
      yyres += yytnamerr_(yyarg[yyi++]);
      ++yyp;
    } else
      yyres += *yyp;
  return yyres;
}

const short int ir_parser::yypact_ninf_ = -164;

const signed char ir_parser::yytable_ninf_ = -1;

const short int ir_parser::yypact_[] = {
  -164, 18,   24,   -164, 22,   -164, 100,  32,   277,  277,  37,   106,  -164,
  -164, -164, -164, -164, -164, -164, -164, -164, -164, -164, -164, -164, -164,
  -164, -164, -164, -164, 96,   111,  110,  112,  113,  -164, -164, -164, -164,
  -164, 124,  108,  114,  0,    -164, 125,  -164, 115,  -164, -164, -164, -14,
  -164, 129,  106,  152,  145,  150,  153,  184,  62,   -164, -164, 159,  277,
  109,  154,  138,  140,  142,  -164, 162,  -164, -164, 143,  -164, -164, 163,
  164,  166,  -164, 179,  183,  181,  154,  205,  154,  218,  154,  -164, 277,
  -164, 208,  -164, -164, -164, -164, 217,  202,  181,  210,  207,  181,  209,
  144,  -164, 181,  -164, 83,   -164, 2,    -164, -164, 226,  154,  228,  154,
  205,  154,  229,  -164, -164, -164, 6,    -164, 181,  -164, 181,  211,  181,
  -164, 215,  -164, -164, 9,    230,  39,   232,  154,  233,  41,   107,  -164,
  -164, -164, -164, 181,  -164, -164, 212,  224,  107,  -164, 243,  214,  42,
  63,   235,  82,   -11,  248,  -164, -164, -164, -164, 258,  -164, -164, -164,
  -164, -164, 244,  104,  98,   -164, 251,  253,  -7,   103,  -164, -164, 204,
  -164, 271,  272,  273,  268,  95,   278,  -164, -164, 260,  -164, -164, -164,
  -164, -164, 251,  253,  -7,   260,  -164, -164, 271,  272,  273,  103,  -164,
  -164, -164, -164, -164, -164, -164, -164};

const unsigned char ir_parser::yydefact_[] = {
  3,  0,  6,   1,   0,  4,  2,  0,  0,  0,  0,  0,  7,  9,  8,  5,  96, 97,
  98, 99, 100, 101, 94, 95, 90, 91, 86, 85, 89, 87, 0,  69, 0,  70, 71, 84,
  83, 82, 93,  92,  0,  0,  0,  0,  12, 0,  72, 0,  73, 74, 20, 0,  15, 0,
  0,  0,  0,   0,   0,  0,  0,  14, 13, 0,  0,  0,  35, 0,  0,  0,  39, 0,
  21, 18, 0,   10,  16, 0,  0,  0,  38, 0,  0,  30, 35, 0,  35, 0,  35, 41,
  0,  19, 0,   15,  88, 37, 36, 0,  0,  30, 0,  0,  30, 0,  0,  40, 30, 17,
  0,  34, 0,   32,  42, 0,  35, 0,  35, 0,  35, 0,  11, 31, 33, 0,  42, 30,
  42, 30, 0,   30,  42, 0,  22, 43, 0,  0,  0,  0,  35, 0,  0,  0,  27, 42,
  26, 42, 30,  42,  23, 56, 0,  44, 45, 0,  0,  0,  0,  0,  0,  0,  49, 55,
  68, 46, 48,  0,   28, 25, 42, 24, 58, 0,  0,  0,  61, 90, 91, 86, 51, 64,
  67, 50, 66,  84,  93, 92, 0,  0,  0,  59, 57, 0,  60, 77, 78, 81, 80, 0,
  0,  0,  0,   52,  65, 0,  0,  0,  53, 79, 76, 75, 47, 29, 63, 62, 54};

const short int ir_parser::yypgoto_[] = {
  -164, -164, -164, -164, -164, -164, -164, 249,  213,  -164, -164,
  -164, -164, -93,  -164, 192,  -81,  -75,  220,  245,  40,   -85,
  -164, -164, 157,  146,  -164, -164, -163, -164, 118,  131,  -162,
  -12,  -8,   -164, -164, -164, -158, -164, -164, -156, -152};

const short int ir_parser::yydefgoto_[] = {
  -1,  1,   2,   5,   6,  12,  43,  44,  60,  76,  13,  51,  14,  98,  110,
  111, 83,  67,  68,  69, 70,  123, 133, 151, 152, 153, 160, 172, 161, 173,
  174, 178, 179, 180, 71, 182, 33,  34,  35,  36,  37,  38,  39};

const unsigned char ir_parser::yytable_[] = {
  32,  40,  183, 99,  184, 102, 113, 106, 185, 115, 101, 170, 103, 119, 58,
  201, 202, 195, 3,   196, 203, 59,  204, 203, 109, 204, 205, 54,  131, 205,
  171, 131, 135, 125, 137, 127, 139, 129, 55,  134, 121, 136, 128, 214, 202,
  140, 132, 4,   203, 142, 204, 7,   77,  157, 205, 15,  79,  146, 155, 41,
  156, 131, 158, 131, 131, 16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
  26,  27,  28,  29,  144, 30,  148, 166, 187, 31,  131, 16,  17,  18,  19,
  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  77,  30,  75,  167, 131,
  31,  16,  17,  18,  19,  20,  21,  22,  23,  197, 198, 199, 131, 28,  8,
  9,   10,  169, 120, 149, 191, 189, 105, 42,  154, 105, 80,  47,  45,  150,
  211, 192, 11,  150, 154, 200, 81,  190, 46,  48,  49,  50,  52,  53,  56,
  57,  61,  181, 16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,
  28,  29,  85,  30,  87,  90,  117, 31,  63,  84,  72,  86,  64,  88,  91,
  118, 78,  65,  82,  89,  92,  66,  16,  17,  18,  19,  20,  21,  22,  23,
  24,  25,  26,  27,  28,  29,  95,  30,  93,  94,  96,  31,  16,  17,  18,
  19,  20,  21,  22,  23,  197, 198, 199, 97,  28,  73,  16,  17,  18,  19,
  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  150, 30,  100, 107, 109,
  31,  112, 81,  114, 141, 116, 162, 138, 165, 159, 65,  16,  17,  18,  19,
  20,  21,  22,  23,  175, 176, 177, 27,  28,  29,  124, 30,  126, 130, 143,
  31,  145, 147, 164, 168, 149, 193, 188, 194, 150, 16,  17,  18,  19,  20,
  21,  22,  23,  24,  25,  26,  27,  28,  29,  207, 30,  208, 209, 210, 31,
  212, 171, 122, 62,  74,  0,   108, 104, 163, 213, 0,   186, 206};

const short int ir_parser::yycheck_[] = {
  8,   9,   160, 84,  160, 86,  99,  88,  160, 102, 85,  22,  87,  106, 28,
  178, 178, 24,  0,   26,  178, 35,  178, 181, 22,  181, 178, 27,  22,  181,
  41,  22,  125, 114, 127, 116, 129, 118, 38,  124, 38,  126, 117, 206, 206,
  130, 40,  23,  206, 40,  206, 29,  60,  146, 206, 23,  64,  138, 143, 22,
  145, 22,  147, 22,  22,  3,   4,   5,   6,   7,   8,   9,   10,  11,  12,
  13,  14,  15,  16,  40,  18,  40,  40,  168, 22,  22,  3,   4,   5,   6,
  7,   8,   9,   10,  11,  12,  13,  14,  15,  16,  108, 18,  40,  40,  22,
  22,  3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  22,  15,  19,
  20,  21,  40,  40,  17,  27,  22,  87,  22,  141, 90,  22,  22,  37,  31,
  40,  38,  37,  31,  151, 37,  32,  38,  32,  32,  32,  22,  39,  34,  24,
  35,  22,  160, 3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,
  15,  16,  27,  18,  27,  27,  27,  22,  21,  36,  22,  36,  32,  36,  36,
  36,  22,  32,  29,  22,  22,  36,  3,   4,   5,   6,   7,   8,   9,   10,
  11,  12,  13,  14,  15,  16,  22,  18,  39,  38,  22,  22,  3,   4,   5,
  6,   7,   8,   9,   10,  11,  12,  13,  37,  15,  36,  3,   4,   5,   6,
  7,   8,   9,   10,  11,  12,  13,  14,  15,  16,  31,  18,  32,  30,  22,
  22,  39,  32,  36,  29,  36,  22,  36,  34,  37,  32,  3,   4,   5,   6,
  7,   8,   9,   10,  11,  12,  13,  14,  15,  16,  39,  18,  39,  39,  39,
  22,  39,  39,  30,  39,  17,  25,  33,  25,  31,  3,   4,   5,   6,   7,
  8,   9,   10,  11,  12,  13,  14,  15,  16,  23,  18,  24,  24,  30,  22,
  22,  41,  110, 54,  59,  -1,  93,  87,  151, 191, -1,  165, 181};

const unsigned char ir_parser::yystos_[] = {
  0,  43, 44, 0,  23, 45, 46, 29, 19, 20, 21, 37, 47, 52, 54, 23, 3,  4,
  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 18, 22, 76, 78, 79, 80,
  81, 82, 83, 84, 76, 22, 22, 48, 49, 37, 32, 22, 32, 32, 22, 53, 39, 34,
  27, 38, 24, 35, 28, 35, 50, 22, 49, 21, 32, 32, 36, 59, 60, 61, 62, 76,
  22, 36, 61, 40, 51, 76, 22, 76, 22, 32, 29, 58, 36, 27, 36, 27, 36, 22,
  27, 36, 22, 39, 38, 22, 22, 37, 55, 58, 32, 59, 58, 59, 60, 62, 58, 30,
  50, 22, 56, 57, 39, 55, 36, 55, 36, 27, 36, 55, 40, 38, 57, 63, 39, 58,
  39, 58, 59, 58, 39, 22, 40, 64, 63, 55, 63, 55, 36, 55, 63, 29, 40, 39,
  40, 39, 58, 39, 40, 17, 31, 65, 66, 67, 75, 63, 63, 55, 63, 37, 68, 70,
  22, 66, 30, 34, 40, 40, 39, 40, 22, 41, 69, 71, 72, 11, 12, 13, 73, 74,
  75, 76, 77, 80, 83, 84, 67, 63, 33, 22, 38, 27, 38, 25, 25, 24, 26, 11,
  12, 13, 37, 70, 74, 80, 83, 84, 73, 23, 24, 24, 30, 40, 22, 72, 70};

const unsigned char ir_parser::yyr1_[] = {
  0,  42, 43, 44, 44, 45, 46, 46, 46, 46, 47, 47, 48, 48, 49, 50, 50,
  51, 52, 52, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 56, 56,
  57, 58, 58, 59, 60, 61, 61, 62, 63, 63, 64, 65, 65, 66, 66, 67, 67,
  67, 67, 67, 67, 67, 68, 68, 69, 69, 70, 71, 71, 72, 73, 73, 74, 74,
  75, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78,
  78, 78, 78, 79, 80, 81, 81, 82, 82, 83, 83, 84, 84, 84, 84, 84, 84};

const unsigned char ir_parser::yyr2_[] = {
  0, 2,  2,  0,  2,  3,  0,  2,  2,  2, 5, 8, 1, 3, 3, 0, 2, 3, 5, 6, 1,
  3, 10, 11, 13, 13, 11, 11, 13, 15, 0, 3, 1, 2, 1, 0, 2, 3, 2, 1, 3, 2,
  0, 2,  3,  1,  2,  4,  2,  2,  3,  3, 4, 4, 5, 2, 0, 3, 1, 2, 3, 1, 3,
  3, 1,  2,  1,  1,  2,  1,  1,  1,  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1,
  1, 1,  1,  1,  6,  1,  1,  1,  1,  1, 1, 1, 1, 1, 1, 1, 1, 1};

// YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
// First, the terminals, then, starting at \a yyntokens_, nonterminals.
const char* const ir_parser::yytname_[] = {
  "\"end of file\"",
  "error",
  "$undefined",
  "TYPE_NAME_I8",
  "TYPE_NAME_UI8",
  "TYPE_NAME_I16",
  "TYPE_NAME_UI16",
  "TYPE_NAME_I32",
  "TYPE_NAME_UI32",
  "TYPE_NAME_I64",
  "TYPE_NAME_UI64",
  "TYPE_NAME_SPF",
  "TYPE_NAME_DPF",
  "TYPE_NAME_BOOLEAN",
  "TYPE_NAME_VOID",
  "TYPE_NAME_STRING",
  "TYPE_NAME_OBJECT",
  "OPCODE",
  "ARRAY",
  "DEF",
  "DECLARE",
  "TYPE",
  "IDENTIFIER",
  "STRING_LITERAL",
  "DECIMALINTEGER",
  "FLOATINGNUM",
  "BOOLEAN_CONSTANT",
  "COMMA",
  "DOT",
  "COLON",
  "SEMICOLON",
  "PERCENT",
  "STAR",
  "POND",
  "ASSIGN",
  "LPAREN",
  "RPAREN",
  "LBRACKET",
  "RBRACKET",
  "LBRACE",
  "RBRACE",
  "LABEL",
  "$accept",
  "input",
  "metadata_def_list",
  "metadata_def",
  "definition_list",
  "type_def",
  "type_attribute_list",
  "type_attribute",
  "type_field_list",
  "type_field",
  "intrinsic_decl",
  "intrinsic_decl_name",
  "function_def",
  "function_def_option_list",
  "function_def_option_list_core",
  "function_def_option",
  "closure_parent",
  "keyword_args",
  "position_args",
  "function_arg_list",
  "function_arg",
  "basic_block_list",
  "basic_block",
  "instruction_group",
  "instruction",
  "expr",
  "instruction_options",
  "instruction_option_list",
  "label_list",
  "label_list_core",
  "label",
  "operand_list",
  "operand",
  "identifier",
  "ir_identifier_type",
  "ir_value",
  "ir_value_type",
  "ir_value_type_array",
  "ir_value_type_string",
  "ir_value_type_floating_numeric",
  "ir_value_type_integer_numeric",
  "ir_value_type_long_integer_numeric",
  "ir_value_type_short_integer_numeric",
  YY_NULLPTR};

#if YYDEBUG
const unsigned short int ir_parser::yyrline_[] = {
  0,   130, 130, 140, 143, 151, 159, 162, 167, 172, 180, 187, 197, 202, 210,
  220, 223, 231, 240, 246, 256, 260, 270, 279, 289, 300, 311, 321, 331, 342,
  358, 361, 368, 372, 379, 387, 389, 396, 403, 410, 415, 423, 433, 436, 444,
  453, 458, 466, 471, 479, 486, 493, 501, 510, 518, 527, 537, 540, 547, 552,
  560, 567, 572, 580, 588, 593, 601, 607, 616, 623, 630, 637, 644, 651, 658,
  668, 674, 680, 686, 692, 698, 704, 713, 714, 715, 716, 717, 718, 722, 731,
  735, 736, 740, 741, 745, 746, 750, 751, 752, 753, 754, 755};

// Print the state stack on the debug stream.
void
ir_parser::yystack_print_()
{
  *yycdebug_ << "Stack now";
  for (stack_type::const_iterator i = yystack_.begin(), i_end = yystack_.end();
       i != i_end; ++i)
    *yycdebug_ << ' ' << i->state;
  *yycdebug_ << std::endl;
}

// Report on the debug stream that the rule \a yyrule is going to be reduced.
void
ir_parser::yy_reduce_print_(int yyrule)
{
  unsigned int yylno = yyrline_[yyrule];
  int yynrhs = yyr2_[yyrule];
  // Print the symbols being reduced, and their result.
  *yycdebug_ << "Reducing stack by rule " << yyrule - 1 << " (line " << yylno
             << "):" << std::endl;
  // The symbols being reduced.
  for (int yyi = 0; yyi < yynrhs; yyi++)
    YY_SYMBOL_PRINT("   $" << yyi + 1 << " =", yystack_[(yynrhs) - (yyi + 1)]);
}
#endif // YYDEBUG

} // yy
#line 2518 "src/ir/ir_parser.tab.cc" // lalr1.cc:1167
#line 758 "src/ir/ir_parser.yy"      // lalr1.cc:1168

void
yy::ir_parser::error(const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

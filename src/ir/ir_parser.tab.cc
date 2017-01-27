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

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "ir_parser.tab.hh"

// User implementation prologue.

#line 51 "src/ir/ir_parser.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "src/ir/ir_parser.yy" // lalr1.cc:413

# include "ir_parser_driver.h"

#line 57 "src/ir/ir_parser.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 143 "src/ir/ir_parser.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ir_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
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
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  ir_parser::ir_parser (corevm::ir::IRParserDriver& driver_yyarg, void* yyscanner_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg),
      yyscanner (yyscanner_yyarg)
  {}

  ir_parser::~ir_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  ir_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  ir_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  ir_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  ir_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  ir_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  ir_parser::symbol_number_type
  ir_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  ir_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  ir_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 25: // BOOLEAN_CONSTANT
        value.move< bool > (that.value);
        break;

      case 69: // ir_value_type_array
        value.move< corevm::IRArrayType > (that.value);
        break;

      case 54: // basic_block
        value.move< corevm::IRBasicBlock > (that.value);
        break;

      case 49: // function_def
        value.move< corevm::IRClosure > (that.value);
        break;

      case 66: // ir_identifier_type
        value.move< corevm::IRIdentifierType > (that.value);
        break;

      case 56: // instruction
      case 57: // expr
        value.move< corevm::IRInstruction > (that.value);
        break;

      case 62: // label
        value.move< corevm::IRLabel > (that.value);
        break;

      case 41: // input
        value.move< corevm::IRModule > (that.value);
        break;

      case 17: // OPCODE
        value.move< corevm::IROpcode > (that.value);
        break;

      case 64: // operand
        value.move< corevm::IROperand > (that.value);
        break;

      case 52: // function_arg
        value.move< corevm::IRParameter > (that.value);
        break;

      case 46: // type_def
        value.move< corevm::IRTypeDecl > (that.value);
        break;

      case 48: // type_field
        value.move< corevm::IRTypeField > (that.value);
        break;

      case 67: // ir_value
        value.move< corevm::IRValue > (that.value);
        break;

      case 68: // ir_value_type
      case 70: // ir_value_type_string
      case 71: // ir_value_type_floating_numeric
      case 72: // ir_value_type_integer_numeric
      case 73: // ir_value_type_long_integer_numeric
      case 74: // ir_value_type_short_integer_numeric
        value.move< corevm::IRValueType > (that.value);
        break;

      case 43: // metadata_def
        value.move< corevm::ir::MetadataPair > (that.value);
        break;

      case 24: // FLOATINGNUM
        value.move< double > (that.value);
        break;

      case 23: // DECIMALINTEGER
        value.move< int64_t > (that.value);
        break;

      case 3: // TYPE_NAME_I8
      case 4: // TYPE_NAME_UI8
      case 5: // TYPE_NAME_I16
      case 6: // TYPE_NAME_UI16
      case 7: // TYPE_NAME_I32
      case 8: // TYPE_NAME_UI32
      case 9: // TYPE_NAME_I64
      case 10: // TYPE_NAME_UI64
      case 11: // TYPE_NAME_SPF
      case 12: // TYPE_NAME_DPF
      case 13: // TYPE_NAME_BOOLEAN
      case 14: // TYPE_NAME_VOID
      case 15: // TYPE_NAME_STRING
      case 16: // TYPE_NAME_OBJECT
      case 18: // ARRAY
      case 19: // DEF
      case 20: // TYPE
      case 21: // IDENTIFIER
      case 22: // STRING_LITERAL
      case 26: // COMMA
      case 27: // COLON
      case 28: // SEMICOLON
      case 29: // PERCENT
      case 30: // STAR
      case 31: // POND
      case 32: // ASSIGN
      case 33: // LPAREN
      case 34: // RPAREN
      case 35: // LBRACKET
      case 36: // RBRACKET
      case 37: // LBRACE
      case 38: // RBRACE
      case 39: // LABEL
      case 65: // identifier
        value.move< std::string > (that.value);
        break;

      case 53: // basic_block_list
        value.move< std::vector<corevm::IRBasicBlock> > (that.value);
        break;

      case 44: // function_def_list
        value.move< std::vector<corevm::IRClosure> > (that.value);
        break;

      case 55: // instruction_group
        value.move< std::vector<corevm::IRInstruction > > (that.value);
        break;

      case 60: // label_list
      case 61: // label_list_core
        value.move< std::vector<corevm::IRLabel> > (that.value);
        break;

      case 63: // operand_list
        value.move< std::vector<corevm::IROperand> > (that.value);
        break;

      case 50: // function_arg_list
      case 51: // function_arg_list_core
        value.move< std::vector<corevm::IRParameter> > (that.value);
        break;

      case 45: // type_def_list
        value.move< std::vector<corevm::IRTypeDecl> > (that.value);
        break;

      case 47: // type_field_list
        value.move< std::vector<corevm::IRTypeField> > (that.value);
        break;

      case 42: // metadata_def_list
        value.move< std::vector<corevm::ir::MetadataPair> > (that.value);
        break;

      case 58: // instruction_options
      case 59: // instruction_option_list
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  ir_parser::stack_symbol_type&
  ir_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 25: // BOOLEAN_CONSTANT
        value.copy< bool > (that.value);
        break;

      case 69: // ir_value_type_array
        value.copy< corevm::IRArrayType > (that.value);
        break;

      case 54: // basic_block
        value.copy< corevm::IRBasicBlock > (that.value);
        break;

      case 49: // function_def
        value.copy< corevm::IRClosure > (that.value);
        break;

      case 66: // ir_identifier_type
        value.copy< corevm::IRIdentifierType > (that.value);
        break;

      case 56: // instruction
      case 57: // expr
        value.copy< corevm::IRInstruction > (that.value);
        break;

      case 62: // label
        value.copy< corevm::IRLabel > (that.value);
        break;

      case 41: // input
        value.copy< corevm::IRModule > (that.value);
        break;

      case 17: // OPCODE
        value.copy< corevm::IROpcode > (that.value);
        break;

      case 64: // operand
        value.copy< corevm::IROperand > (that.value);
        break;

      case 52: // function_arg
        value.copy< corevm::IRParameter > (that.value);
        break;

      case 46: // type_def
        value.copy< corevm::IRTypeDecl > (that.value);
        break;

      case 48: // type_field
        value.copy< corevm::IRTypeField > (that.value);
        break;

      case 67: // ir_value
        value.copy< corevm::IRValue > (that.value);
        break;

      case 68: // ir_value_type
      case 70: // ir_value_type_string
      case 71: // ir_value_type_floating_numeric
      case 72: // ir_value_type_integer_numeric
      case 73: // ir_value_type_long_integer_numeric
      case 74: // ir_value_type_short_integer_numeric
        value.copy< corevm::IRValueType > (that.value);
        break;

      case 43: // metadata_def
        value.copy< corevm::ir::MetadataPair > (that.value);
        break;

      case 24: // FLOATINGNUM
        value.copy< double > (that.value);
        break;

      case 23: // DECIMALINTEGER
        value.copy< int64_t > (that.value);
        break;

      case 3: // TYPE_NAME_I8
      case 4: // TYPE_NAME_UI8
      case 5: // TYPE_NAME_I16
      case 6: // TYPE_NAME_UI16
      case 7: // TYPE_NAME_I32
      case 8: // TYPE_NAME_UI32
      case 9: // TYPE_NAME_I64
      case 10: // TYPE_NAME_UI64
      case 11: // TYPE_NAME_SPF
      case 12: // TYPE_NAME_DPF
      case 13: // TYPE_NAME_BOOLEAN
      case 14: // TYPE_NAME_VOID
      case 15: // TYPE_NAME_STRING
      case 16: // TYPE_NAME_OBJECT
      case 18: // ARRAY
      case 19: // DEF
      case 20: // TYPE
      case 21: // IDENTIFIER
      case 22: // STRING_LITERAL
      case 26: // COMMA
      case 27: // COLON
      case 28: // SEMICOLON
      case 29: // PERCENT
      case 30: // STAR
      case 31: // POND
      case 32: // ASSIGN
      case 33: // LPAREN
      case 34: // RPAREN
      case 35: // LBRACKET
      case 36: // RBRACKET
      case 37: // LBRACE
      case 38: // RBRACE
      case 39: // LABEL
      case 65: // identifier
        value.copy< std::string > (that.value);
        break;

      case 53: // basic_block_list
        value.copy< std::vector<corevm::IRBasicBlock> > (that.value);
        break;

      case 44: // function_def_list
        value.copy< std::vector<corevm::IRClosure> > (that.value);
        break;

      case 55: // instruction_group
        value.copy< std::vector<corevm::IRInstruction > > (that.value);
        break;

      case 60: // label_list
      case 61: // label_list_core
        value.copy< std::vector<corevm::IRLabel> > (that.value);
        break;

      case 63: // operand_list
        value.copy< std::vector<corevm::IROperand> > (that.value);
        break;

      case 50: // function_arg_list
      case 51: // function_arg_list_core
        value.copy< std::vector<corevm::IRParameter> > (that.value);
        break;

      case 45: // type_def_list
        value.copy< std::vector<corevm::IRTypeDecl> > (that.value);
        break;

      case 47: // type_field_list
        value.copy< std::vector<corevm::IRTypeField> > (that.value);
        break;

      case 42: // metadata_def_list
        value.copy< std::vector<corevm::ir::MetadataPair> > (that.value);
        break;

      case 58: // instruction_options
      case 59: // instruction_option_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  ir_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  ir_parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  ir_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  ir_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  ir_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  ir_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ir_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ir_parser::debug_level_type
  ir_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  ir_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline ir_parser::state_type
  ir_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  ir_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  ir_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ir_parser::parse ()
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
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 26 "src/ir/ir_parser.yy" // lalr1.cc:745
{
  // Initialize the initial location.
  if (!driver.input_file().empty())
  {
    yyla.location.begin.filename = yyla.location.end.filename = &driver.input_file();
  }
}

#line 737 "src/ir/ir_parser.tab.cc" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

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
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver, yyscanner));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
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
        switch (yyr1_[yyn])
    {
      case 25: // BOOLEAN_CONSTANT
        yylhs.value.build< bool > ();
        break;

      case 69: // ir_value_type_array
        yylhs.value.build< corevm::IRArrayType > ();
        break;

      case 54: // basic_block
        yylhs.value.build< corevm::IRBasicBlock > ();
        break;

      case 49: // function_def
        yylhs.value.build< corevm::IRClosure > ();
        break;

      case 66: // ir_identifier_type
        yylhs.value.build< corevm::IRIdentifierType > ();
        break;

      case 56: // instruction
      case 57: // expr
        yylhs.value.build< corevm::IRInstruction > ();
        break;

      case 62: // label
        yylhs.value.build< corevm::IRLabel > ();
        break;

      case 41: // input
        yylhs.value.build< corevm::IRModule > ();
        break;

      case 17: // OPCODE
        yylhs.value.build< corevm::IROpcode > ();
        break;

      case 64: // operand
        yylhs.value.build< corevm::IROperand > ();
        break;

      case 52: // function_arg
        yylhs.value.build< corevm::IRParameter > ();
        break;

      case 46: // type_def
        yylhs.value.build< corevm::IRTypeDecl > ();
        break;

      case 48: // type_field
        yylhs.value.build< corevm::IRTypeField > ();
        break;

      case 67: // ir_value
        yylhs.value.build< corevm::IRValue > ();
        break;

      case 68: // ir_value_type
      case 70: // ir_value_type_string
      case 71: // ir_value_type_floating_numeric
      case 72: // ir_value_type_integer_numeric
      case 73: // ir_value_type_long_integer_numeric
      case 74: // ir_value_type_short_integer_numeric
        yylhs.value.build< corevm::IRValueType > ();
        break;

      case 43: // metadata_def
        yylhs.value.build< corevm::ir::MetadataPair > ();
        break;

      case 24: // FLOATINGNUM
        yylhs.value.build< double > ();
        break;

      case 23: // DECIMALINTEGER
        yylhs.value.build< int64_t > ();
        break;

      case 3: // TYPE_NAME_I8
      case 4: // TYPE_NAME_UI8
      case 5: // TYPE_NAME_I16
      case 6: // TYPE_NAME_UI16
      case 7: // TYPE_NAME_I32
      case 8: // TYPE_NAME_UI32
      case 9: // TYPE_NAME_I64
      case 10: // TYPE_NAME_UI64
      case 11: // TYPE_NAME_SPF
      case 12: // TYPE_NAME_DPF
      case 13: // TYPE_NAME_BOOLEAN
      case 14: // TYPE_NAME_VOID
      case 15: // TYPE_NAME_STRING
      case 16: // TYPE_NAME_OBJECT
      case 18: // ARRAY
      case 19: // DEF
      case 20: // TYPE
      case 21: // IDENTIFIER
      case 22: // STRING_LITERAL
      case 26: // COMMA
      case 27: // COLON
      case 28: // SEMICOLON
      case 29: // PERCENT
      case 30: // STAR
      case 31: // POND
      case 32: // ASSIGN
      case 33: // LPAREN
      case 34: // RPAREN
      case 35: // LBRACKET
      case 36: // RBRACKET
      case 37: // LBRACE
      case 38: // RBRACE
      case 39: // LABEL
      case 65: // identifier
        yylhs.value.build< std::string > ();
        break;

      case 53: // basic_block_list
        yylhs.value.build< std::vector<corevm::IRBasicBlock> > ();
        break;

      case 44: // function_def_list
        yylhs.value.build< std::vector<corevm::IRClosure> > ();
        break;

      case 55: // instruction_group
        yylhs.value.build< std::vector<corevm::IRInstruction > > ();
        break;

      case 60: // label_list
      case 61: // label_list_core
        yylhs.value.build< std::vector<corevm::IRLabel> > ();
        break;

      case 63: // operand_list
        yylhs.value.build< std::vector<corevm::IROperand> > ();
        break;

      case 50: // function_arg_list
      case 51: // function_arg_list_core
        yylhs.value.build< std::vector<corevm::IRParameter> > ();
        break;

      case 45: // type_def_list
        yylhs.value.build< std::vector<corevm::IRTypeDecl> > ();
        break;

      case 47: // type_field_list
        yylhs.value.build< std::vector<corevm::IRTypeField> > ();
        break;

      case 42: // metadata_def_list
        yylhs.value.build< std::vector<corevm::ir::MetadataPair> > ();
        break;

      case 58: // instruction_options
      case 59: // instruction_option_list
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 120 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRModule > () = corevm::IRModule();
            yylhs.value.as< corevm::IRModule > ().types = std::move(yystack_[1].value.as< std::vector<corevm::IRTypeDecl> > ());
            yylhs.value.as< corevm::IRModule > ().closures = std::move(yystack_[0].value.as< std::vector<corevm::IRClosure> > ());
            corevm::ir::set_metadata(yystack_[2].value.as< std::vector<corevm::ir::MetadataPair> > (), yylhs.value.as< corevm::IRModule > ());
            driver.set_module(std::move(yylhs.value.as< corevm::IRModule > ()));
        }
#line 1011 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 131 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::ir::MetadataPair> > () = std::vector<corevm::ir::MetadataPair>();
        }
#line 1019 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 135 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::ir::MetadataPair> > () = std::move(yystack_[1].value.as< std::vector<corevm::ir::MetadataPair> > ());
            yylhs.value.as< std::vector<corevm::ir::MetadataPair> > ().push_back(yystack_[0].value.as< corevm::ir::MetadataPair > ());
        }
#line 1028 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 143 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::ir::MetadataPair > () = std::make_pair(yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ());      
        }
#line 1036 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 150 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRClosure> > () = std::vector<corevm::IRClosure>();
        }
#line 1044 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 154 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRClosure> > () = std::move(yystack_[1].value.as< std::vector<corevm::IRClosure> > ());
            yylhs.value.as< std::vector<corevm::IRClosure> > ().push_back(yystack_[0].value.as< corevm::IRClosure > ());
        }
#line 1053 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 162 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRTypeDecl> > () = std::vector<corevm::IRTypeDecl>();
        }
#line 1061 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 166 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRTypeDecl> > () = std::move(yystack_[1].value.as< std::vector<corevm::IRTypeDecl> > ());
            yylhs.value.as< std::vector<corevm::IRTypeDecl> > ().push_back(yystack_[0].value.as< corevm::IRTypeDecl > ());
        }
#line 1070 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 174 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRTypeDecl > () = corevm::IRTypeDecl();
            yylhs.value.as< corevm::IRTypeDecl > ().name = std::move(yystack_[3].value.as< std::string > ());
            yylhs.value.as< corevm::IRTypeDecl > ().fields = std::move(yystack_[1].value.as< std::vector<corevm::IRTypeField> > ());
        }
#line 1080 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 183 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRTypeField> > () = std::vector<corevm::IRTypeField>();
        }
#line 1088 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 187 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRTypeField> > () = std::move(yystack_[1].value.as< std::vector<corevm::IRTypeField> > ());
            yylhs.value.as< std::vector<corevm::IRTypeField> > ().push_back(yystack_[0].value.as< corevm::IRTypeField > ());
        }
#line 1097 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 195 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRTypeField > () = corevm::IRTypeField();
            yylhs.value.as< corevm::IRTypeField > ().type = std::move(yystack_[2].value.as< corevm::IRIdentifierType > ());
            yylhs.value.as< corevm::IRTypeField > ().identifier = std::move(yystack_[1].value.as< std::string > ());
        }
#line 1107 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 204 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRClosure > () = corevm::IRClosure();
            yylhs.value.as< corevm::IRClosure > ().rettype = yystack_[5].value.as< corevm::IRIdentifierType > ();
            yylhs.value.as< corevm::IRClosure > ().name = std::move(yystack_[4].value.as< std::string > ());
            yylhs.value.as< corevm::IRClosure > ().parameters = std::move(yystack_[3].value.as< std::vector<corevm::IRParameter> > ());
            yylhs.value.as< corevm::IRClosure > ().blocks = std::move(yystack_[1].value.as< std::vector<corevm::IRBasicBlock> > ());
        }
#line 1119 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 212 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRClosure > () = corevm::IRClosure();
            yylhs.value.as< corevm::IRClosure > ().rettype = yystack_[7].value.as< corevm::IRIdentifierType > ();
            yylhs.value.as< corevm::IRClosure > ().name = std::move(yystack_[6].value.as< std::string > ());
            yylhs.value.as< corevm::IRClosure > ().parameters = std::move(yystack_[5].value.as< std::vector<corevm::IRParameter> > ());
            yylhs.value.as< corevm::IRClosure > ().parent.set_string(yystack_[3].value.as< std::string > ());
            yylhs.value.as< corevm::IRClosure > ().blocks = std::move(yystack_[1].value.as< std::vector<corevm::IRBasicBlock> > ());
        }
#line 1132 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 224 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRParameter> > () = std::vector<corevm::IRParameter>();
        }
#line 1140 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 228 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRParameter> > () = std::move(yystack_[1].value.as< std::vector<corevm::IRParameter> > ());
        }
#line 1148 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 235 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRParameter> > () = std::vector<corevm::IRParameter>();
            yylhs.value.as< std::vector<corevm::IRParameter> > ().push_back(yystack_[0].value.as< corevm::IRParameter > ());
        }
#line 1157 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 240 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRParameter> > () = std::move(yystack_[2].value.as< std::vector<corevm::IRParameter> > ());
            yylhs.value.as< std::vector<corevm::IRParameter> > ().push_back(yystack_[0].value.as< corevm::IRParameter > ());
        }
#line 1166 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 248 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRParameter > () = corevm::IRParameter();
            yylhs.value.as< corevm::IRParameter > ().type = std::move(yystack_[1].value.as< corevm::IRIdentifierType > ());
            yylhs.value.as< corevm::IRParameter > ().identifier = std::move(yystack_[0].value.as< std::string > ());
        }
#line 1176 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 257 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRBasicBlock> > () = std::vector<corevm::IRBasicBlock>();
        }
#line 1184 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 261 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRBasicBlock> > () = std::move(yystack_[1].value.as< std::vector<corevm::IRBasicBlock> > ());
            yylhs.value.as< std::vector<corevm::IRBasicBlock> > ().push_back(yystack_[0].value.as< corevm::IRBasicBlock > ());
        }
#line 1193 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 269 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRBasicBlock > () = corevm::IRBasicBlock();
            yylhs.value.as< corevm::IRBasicBlock > ().label = std::move(yystack_[2].value.as< std::string > ());
            yylhs.value.as< corevm::IRBasicBlock > ().body = std::move(yystack_[0].value.as< std::vector<corevm::IRInstruction > > ());
        }
#line 1203 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 278 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRInstruction > > () = std::vector<corevm::IRInstruction>();
            yylhs.value.as< std::vector<corevm::IRInstruction > > ().push_back(yystack_[0].value.as< corevm::IRInstruction > ());
        }
#line 1212 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 283 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRInstruction > > () = std::move(yystack_[1].value.as< std::vector<corevm::IRInstruction > > ());
            yylhs.value.as< std::vector<corevm::IRInstruction > > ().push_back(yystack_[0].value.as< corevm::IRInstruction > ());
        }
#line 1221 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 291 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = std::move(yystack_[1].value.as< corevm::IRInstruction > ());
            yylhs.value.as< corevm::IRInstruction > ().target.set_string(yystack_[3].value.as< std::string > ());
        }
#line 1230 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 296 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = std::move(yystack_[1].value.as< corevm::IRInstruction > ());
            yylhs.value.as< corevm::IRInstruction > ().target.set_null();
        }
#line 1239 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 304 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = corevm::IRInstruction();
            yylhs.value.as< corevm::IRInstruction > ().opcode = yystack_[1].value.as< corevm::IROpcode > ();
            yylhs.value.as< corevm::IRInstruction > ().options = std::move(yystack_[0].value.as< std::vector<std::string> > ());
            yylhs.value.as< corevm::IRInstruction > ().type.set_null();
        }
#line 1250 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 311 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = corevm::IRInstruction();
            yylhs.value.as< corevm::IRInstruction > ().opcode = yystack_[2].value.as< corevm::IROpcode > ();
            yylhs.value.as< corevm::IRInstruction > ().options = std::move(yystack_[1].value.as< std::vector<std::string> > ());
            yylhs.value.as< corevm::IRInstruction > ().type.set_IRIdentifierType(yystack_[0].value.as< corevm::IRIdentifierType > ());
        }
#line 1261 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 318 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = corevm::IRInstruction();
            yylhs.value.as< corevm::IRInstruction > ().opcode = yystack_[2].value.as< corevm::IROpcode > ();
            yylhs.value.as< corevm::IRInstruction > ().options = std::move(yystack_[1].value.as< std::vector<std::string> > ());
            yylhs.value.as< corevm::IRInstruction > ().oprds = std::move(yystack_[0].value.as< std::vector<corevm::IROperand> > ());
            yylhs.value.as< corevm::IRInstruction > ().type.set_null();
        }
#line 1273 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 326 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = corevm::IRInstruction();
            yylhs.value.as< corevm::IRInstruction > ().opcode = yystack_[3].value.as< corevm::IROpcode > ();
            yylhs.value.as< corevm::IRInstruction > ().options = std::move(yystack_[2].value.as< std::vector<std::string> > ());
            yylhs.value.as< corevm::IRInstruction > ().oprds = std::move(yystack_[1].value.as< std::vector<corevm::IROperand> > ());
            yylhs.value.as< corevm::IRInstruction > ().labels.set_array(yystack_[0].value.as< std::vector<corevm::IRLabel> > ());
            yylhs.value.as< corevm::IRInstruction > ().type.set_null();
        }
#line 1286 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 335 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = corevm::IRInstruction();
            yylhs.value.as< corevm::IRInstruction > ().opcode = yystack_[3].value.as< corevm::IROpcode > ();
            yylhs.value.as< corevm::IRInstruction > ().options = std::move(yystack_[2].value.as< std::vector<std::string> > ());
            yylhs.value.as< corevm::IRInstruction > ().type.set_IRIdentifierType(yystack_[1].value.as< corevm::IRIdentifierType > ());
            yylhs.value.as< corevm::IRInstruction > ().oprds = std::move(yystack_[0].value.as< std::vector<corevm::IROperand> > ());
        }
#line 1298 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 343 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRInstruction > () = corevm::IRInstruction();
            yylhs.value.as< corevm::IRInstruction > ().opcode = yystack_[4].value.as< corevm::IROpcode > ();
            yylhs.value.as< corevm::IRInstruction > ().options = std::move(yystack_[3].value.as< std::vector<std::string> > ());
            yylhs.value.as< corevm::IRInstruction > ().type.set_IRIdentifierType(yystack_[2].value.as< corevm::IRIdentifierType > ());
            yylhs.value.as< corevm::IRInstruction > ().oprds = std::move(yystack_[1].value.as< std::vector<corevm::IROperand> > ());
            yylhs.value.as< corevm::IRInstruction > ().labels.set_array(yystack_[0].value.as< std::vector<corevm::IRLabel> > ());
        }
#line 1311 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 355 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
        }
#line 1319 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 359 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
        }
#line 1327 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 366 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
        }
#line 1336 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 371 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
        }
#line 1345 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 379 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRLabel> > () = std::move(yystack_[1].value.as< std::vector<corevm::IRLabel> > ());
        }
#line 1353 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 386 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRLabel> > () = std::vector<corevm::IRLabel>();
            yylhs.value.as< std::vector<corevm::IRLabel> > ().push_back(yystack_[0].value.as< corevm::IRLabel > ());
        }
#line 1362 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 391 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IRLabel> > () = std::move(yystack_[2].value.as< std::vector<corevm::IRLabel> > ());
            yylhs.value.as< std::vector<corevm::IRLabel> > ().push_back(yystack_[0].value.as< corevm::IRLabel > ());
        }
#line 1371 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 399 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRLabel > () = corevm::IRLabel();
            yylhs.value.as< corevm::IRLabel > ().name = std::move(yystack_[0].value.as< std::string > ());
        }
#line 1380 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 407 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IROperand> > () = std::vector<corevm::IROperand>();
            yylhs.value.as< std::vector<corevm::IROperand> > ().push_back(yystack_[0].value.as< corevm::IROperand > ());
        }
#line 1389 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 412 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::vector<corevm::IROperand> > () = std::move(yystack_[1].value.as< std::vector<corevm::IROperand> > ());
            yylhs.value.as< std::vector<corevm::IROperand> > ().push_back(yystack_[0].value.as< corevm::IROperand > ());
        }
#line 1398 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 420 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IROperand > () = corevm::IROperand();
            yylhs.value.as< corevm::IROperand > ().type = corevm::constant;
            yylhs.value.as< corevm::IROperand > ().value.set_IRValue(yystack_[0].value.as< corevm::IRValue > ());
        }
#line 1408 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 426 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IROperand > () = corevm::IROperand();
            yylhs.value.as< corevm::IROperand > ().type = corevm::ref;
            yylhs.value.as< corevm::IROperand > ().value.set_string(yystack_[0].value.as< std::string > ());
        }
#line 1418 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 435 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::string > () = std::move(yystack_[0].value.as< std::string > ());
        }
#line 1426 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 442 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRIdentifierType > () = corevm::IRIdentifierType();
            yylhs.value.as< corevm::IRIdentifierType > ().type = corevm::IdentifierType_Identifier;
            yylhs.value.as< corevm::IRIdentifierType > ().ref_type = corevm::value;
            yylhs.value.as< corevm::IRIdentifierType > ().value.set_string(yystack_[0].value.as< std::string > ());
        }
#line 1437 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 449 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRIdentifierType > () = corevm::IRIdentifierType();
            yylhs.value.as< corevm::IRIdentifierType > ().type = corevm::IdentifierType_ValueType;
            yylhs.value.as< corevm::IRIdentifierType > ().ref_type = corevm::value;
            yylhs.value.as< corevm::IRIdentifierType > ().value.set_IRValueType(yystack_[0].value.as< corevm::IRValueType > ());
        }
#line 1448 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 456 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRIdentifierType > () = corevm::IRIdentifierType();
            yylhs.value.as< corevm::IRIdentifierType > ().type = corevm::IdentifierType_Array;
            yylhs.value.as< corevm::IRIdentifierType > ().ref_type = corevm::value;
            yylhs.value.as< corevm::IRIdentifierType > ().value.set_IRArrayType(yystack_[0].value.as< corevm::IRArrayType > ());
        }
#line 1459 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 463 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRIdentifierType > () = corevm::IRIdentifierType();
            yylhs.value.as< corevm::IRIdentifierType > ().type = corevm::IdentifierType_Identifier;
            yylhs.value.as< corevm::IRIdentifierType > ().ref_type = corevm::pointer;
            yylhs.value.as< corevm::IRIdentifierType > ().value.set_string(yystack_[1].value.as< std::string > ());
        }
#line 1470 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 470 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRIdentifierType > () = corevm::IRIdentifierType();
            yylhs.value.as< corevm::IRIdentifierType > ().type = corevm::IdentifierType_ValueType;
            yylhs.value.as< corevm::IRIdentifierType > ().ref_type = corevm::pointer;
            yylhs.value.as< corevm::IRIdentifierType > ().value.set_IRValueType(yystack_[1].value.as< corevm::IRValueType > ());
        }
#line 1481 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 477 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRIdentifierType > () = corevm::IRIdentifierType();
            yylhs.value.as< corevm::IRIdentifierType > ().type = corevm::IdentifierType_Array;
            yylhs.value.as< corevm::IRIdentifierType > ().ref_type = corevm::pointer;
            yylhs.value.as< corevm::IRIdentifierType > ().value.set_IRArrayType(yystack_[1].value.as< corevm::IRArrayType > ());
        }
#line 1492 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 487 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRValue > () = corevm::IRValue();
            yylhs.value.as< corevm::IRValue > ().type = yystack_[1].value.as< corevm::IRValueType > ();
            yylhs.value.as< corevm::IRValue > ().value.set_int(yystack_[0].value.as< int64_t > ());
        }
#line 1502 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 493 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRValue > () = corevm::IRValue();
            yylhs.value.as< corevm::IRValue > ().type = yystack_[1].value.as< corevm::IRValueType > ();
            yylhs.value.as< corevm::IRValue > ().value.set_long(yystack_[0].value.as< int64_t > ());
        }
#line 1512 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 499 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRValue > () = corevm::IRValue();
            yylhs.value.as< corevm::IRValue > ().type = corevm::spf;
            yylhs.value.as< corevm::IRValue > ().value.set_float(yystack_[0].value.as< double > ());
        }
#line 1522 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 505 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRValue > () = corevm::IRValue();
            yylhs.value.as< corevm::IRValue > ().type = corevm::dpf;
            yylhs.value.as< corevm::IRValue > ().value.set_double(yystack_[0].value.as< double > ());
        }
#line 1532 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 511 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRValue > () = corevm::IRValue();
            yylhs.value.as< corevm::IRValue > ().type = yystack_[1].value.as< corevm::IRValueType > ();
            yylhs.value.as< corevm::IRValue > ().value.set_string(yystack_[0].value.as< std::string > ());
        }
#line 1542 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 517 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRValue > () = corevm::IRValue();
            yylhs.value.as< corevm::IRValue > ().type = corevm::boolean;
            yylhs.value.as< corevm::IRValue > ().value.set_bool(yystack_[0].value.as< bool > ());
        }
#line 1552 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 523 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRValue > () = corevm::IRValue();
            yylhs.value.as< corevm::IRValue > ().type = corevm::boolean;
            yylhs.value.as< corevm::IRValue > ().value.set_bool(static_cast<bool>(yystack_[0].value.as< int64_t > ()));
        }
#line 1562 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 531 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = yystack_[0].value.as< corevm::IRValueType > (); }
#line 1568 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 532 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = yystack_[0].value.as< corevm::IRValueType > (); }
#line 1574 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 62:
#line 533 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = yystack_[0].value.as< corevm::IRValueType > (); }
#line 1580 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 534 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::voidtype;   }
#line 1586 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 535 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::boolean;    }
#line 1592 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 536 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::object;     }
#line 1598 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 541 "src/ir/ir_parser.yy" // lalr1.cc:859
    {
            yylhs.value.as< corevm::IRArrayType > () = corevm::IRArrayType();
            yylhs.value.as< corevm::IRArrayType > ().len = yystack_[3].value.as< int64_t > ();
            yylhs.value.as< corevm::IRArrayType > ().type = std::move(yystack_[1].value.as< corevm::IRIdentifierType > ());
        }
#line 1608 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 67:
#line 549 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::string; }
#line 1614 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 553 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::spf; }
#line 1620 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 554 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::dpf; }
#line 1626 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 70:
#line 558 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = yystack_[0].value.as< corevm::IRValueType > (); }
#line 1632 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 559 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = yystack_[0].value.as< corevm::IRValueType > (); }
#line 1638 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 72:
#line 563 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::i64;  }
#line 1644 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 564 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::ui64; }
#line 1650 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 568 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::i8;   }
#line 1656 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 75:
#line 569 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::ui8;  }
#line 1662 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 76:
#line 570 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::i16;  }
#line 1668 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 571 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::ui16; }
#line 1674 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 572 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::i32;  }
#line 1680 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;

  case 79:
#line 573 "src/ir/ir_parser.yy" // lalr1.cc:859
    { yylhs.value.as< corevm::IRValueType > () = corevm::ui32; }
#line 1686 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
    break;


#line 1690 "src/ir/ir_parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
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
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
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
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  ir_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  ir_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char ir_parser::yypact_ninf_ = -77;

  const signed char ir_parser::yytable_ninf_ = -1;

  const short int
  ir_parser::yypact_[] =
  {
     -77,    24,     4,   -77,    18,   -77,     9,    26,    32,    52,
     -77,   -77,    35,   172,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
      38,    45,    55,    47,    48,   -77,   -77,   -77,   -77,   -77,
      -2,    51,   -77,    46,   -77,   -77,   -77,   -77,    59,    54,
      86,    10,    57,   172,   -77,    17,   -77,    60,    62,   -77,
     -77,    50,   172,   -77,   -77,    66,    -3,   -77,   -77,   -77,
      78,   -77,   -77,     1,    15,   -77,    71,    87,    15,   -77,
      81,    79,    89,   118,   -77,   -77,   -77,    70,   -77,     2,
      88,    90,    44,    53,   -77,   -77,   145,   -77,    91,    92,
      93,   107,   -77,   -77,   -77,   -77,   -77,   -77,    88,    90,
      44,    80,   -77,   -77,    91,    92,    93,    53,   -77,   -77,
     -77,   -77,   106,    16,   -77,   -77,    96,    80,   -77,   -77,
     -77
  };

  const unsigned char
  ir_parser::yydefact_[] =
  {
       3,     0,     8,     1,     0,     4,     6,     0,     0,     2,
       9,     5,     0,     0,     7,    11,    74,    75,    76,    77,
      78,    79,    72,    73,    68,    69,    64,    63,    67,    65,
       0,    47,     0,    48,    49,    62,    61,    60,    71,    70,
       0,     0,    50,     0,    51,    52,    10,    12,     0,     0,
       0,     0,     0,     0,    16,     0,    18,     0,     0,    21,
      13,     0,     0,    17,    20,     0,     0,    66,    19,    21,
       0,    14,    22,     0,     0,    15,    34,     0,    23,    24,
       0,     0,     0,    28,    46,    25,    27,     0,    36,     0,
      68,    69,    64,    30,    42,    45,    29,    44,    62,    71,
      70,     0,    37,    35,    55,    56,    59,    58,     0,     0,
       0,     0,    31,    43,     0,     0,     0,    32,    57,    54,
      53,    26,     0,     0,    39,    33,     0,     0,    38,    41,
      40
  };

  const signed char
  ir_parser::yypgoto_[] =
  {
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,    56,    69,   -77,   -77,    63,    58,   -77,   -77,
      23,   -77,    19,    65,   -76,   -28,   -13,   -77,   -77,   -77,
     -68,   -77,   -77,   -63,   -62
  };

  const signed char
  ir_parser::yydefgoto_[] =
  {
      -1,     1,     2,     5,     9,     6,    10,    40,    47,    14,
      51,    55,    56,    66,    72,    78,    79,    80,    83,    89,
     112,   123,   124,    93,    94,    95,    57,    97,    33,    34,
      35,    36,    37,    38,    39
  };

  const unsigned char
  ir_parser::yytable_[] =
  {
      32,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    98,    30,   113,    70,    31,
      99,   100,    70,   102,     3,   114,     4,    48,   114,     8,
     115,   116,    76,   115,   116,    71,    46,    58,   103,    75,
      61,   113,   127,    62,    77,     7,    81,    59,    11,   114,
      81,    63,   128,    12,   115,   116,    16,    17,    18,    19,
      20,    21,    22,    23,   108,   109,   110,   106,    28,   107,
      96,    13,    15,    41,    49,    42,    43,    44,    45,    50,
      52,    64,    77,    65,    53,    60,    67,    76,   111,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    69,    30,    74,    82,    31,    84,    86,
      88,    87,   104,   118,   105,   119,   120,   129,    68,   122,
      54,    16,    17,    18,    19,    20,    21,    22,    23,    90,
      91,    92,    27,    28,    29,   121,    30,   126,    73,    31,
     125,    85,     0,     0,     0,   101,   130,    77,    16,    17,
      18,    19,    20,    21,    22,    23,   108,   109,   110,     0,
      28,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    77,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
      30,     0,     0,    31
  };

  const signed char
  ir_parser::yycheck_[] =
  {
      13,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    83,    18,    93,    21,    21,
      83,    83,    21,    21,     0,    93,    22,    40,    96,    20,
      93,    93,    17,    96,    96,    38,    38,    27,    36,    38,
      53,   117,    26,    26,    29,    27,    74,    37,    22,   117,
      78,    34,    36,    21,   117,   117,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    23,    15,    25,
      83,    19,    37,    35,    23,    30,    21,    30,    30,    33,
      21,    21,    29,    21,    30,    28,    36,    17,    35,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    37,    18,    27,    35,    21,    21,    28,
      21,    32,    24,    22,    24,    23,    23,    21,    62,    39,
      34,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    28,    18,    31,    69,    21,
     117,    78,    -1,    -1,    -1,    87,   127,    29,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    96,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      18,    -1,    -1,    21
  };

  const unsigned char
  ir_parser::yystos_[] =
  {
       0,    41,    42,     0,    22,    43,    45,    27,    20,    44,
      46,    22,    21,    19,    49,    37,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      18,    21,    66,    68,    69,    70,    71,    72,    73,    74,
      47,    35,    30,    21,    30,    30,    38,    48,    66,    23,
      33,    50,    21,    30,    34,    51,    52,    66,    27,    37,
      28,    66,    26,    34,    21,    21,    53,    36,    52,    37,
      21,    38,    54,    53,    27,    38,    17,    29,    55,    56,
      57,    65,    35,    58,    21,    56,    28,    32,    21,    59,
      11,    12,    13,    63,    64,    65,    66,    67,    70,    73,
      74,    57,    21,    36,    24,    24,    23,    25,    11,    12,
      13,    35,    60,    64,    70,    73,    74,    63,    22,    23,
      23,    28,    39,    61,    62,    60,    31,    26,    36,    21,
      62
  };

  const unsigned char
  ir_parser::yyr1_[] =
  {
       0,    40,    41,    42,    42,    43,    44,    44,    45,    45,
      46,    47,    47,    48,    49,    49,    50,    50,    51,    51,
      52,    53,    53,    54,    55,    55,    56,    56,    57,    57,
      57,    57,    57,    57,    58,    58,    59,    59,    60,    61,
      61,    62,    63,    63,    64,    64,    65,    66,    66,    66,
      66,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      68,    68,    68,    68,    68,    68,    69,    70,    71,    71,
      72,    72,    73,    73,    74,    74,    74,    74,    74,    74
  };

  const unsigned char
  ir_parser::yyr2_[] =
  {
       0,     2,     3,     0,     2,     3,     0,     2,     0,     2,
       5,     0,     2,     3,     7,     9,     2,     3,     1,     3,
       2,     0,     2,     3,     1,     2,     4,     2,     2,     3,
       3,     4,     4,     5,     0,     3,     1,     2,     3,     1,
       3,     3,     1,     2,     1,     1,     2,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const ir_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "TYPE_NAME_I8",
  "TYPE_NAME_UI8", "TYPE_NAME_I16", "TYPE_NAME_UI16", "TYPE_NAME_I32",
  "TYPE_NAME_UI32", "TYPE_NAME_I64", "TYPE_NAME_UI64", "TYPE_NAME_SPF",
  "TYPE_NAME_DPF", "TYPE_NAME_BOOLEAN", "TYPE_NAME_VOID",
  "TYPE_NAME_STRING", "TYPE_NAME_OBJECT", "OPCODE", "ARRAY", "DEF", "TYPE",
  "IDENTIFIER", "STRING_LITERAL", "DECIMALINTEGER", "FLOATINGNUM",
  "BOOLEAN_CONSTANT", "COMMA", "COLON", "SEMICOLON", "PERCENT", "STAR",
  "POND", "ASSIGN", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE",
  "RBRACE", "LABEL", "$accept", "input", "metadata_def_list",
  "metadata_def", "function_def_list", "type_def_list", "type_def",
  "type_field_list", "type_field", "function_def", "function_arg_list",
  "function_arg_list_core", "function_arg", "basic_block_list",
  "basic_block", "instruction_group", "instruction", "expr",
  "instruction_options", "instruction_option_list", "label_list",
  "label_list_core", "label", "operand_list", "operand", "identifier",
  "ir_identifier_type", "ir_value", "ir_value_type", "ir_value_type_array",
  "ir_value_type_string", "ir_value_type_floating_numeric",
  "ir_value_type_integer_numeric", "ir_value_type_long_integer_numeric",
  "ir_value_type_short_integer_numeric", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  ir_parser::yyrline_[] =
  {
       0,   119,   119,   131,   134,   142,   150,   153,   162,   165,
     173,   183,   186,   194,   203,   211,   223,   227,   234,   239,
     247,   257,   260,   268,   277,   282,   290,   295,   303,   310,
     317,   325,   334,   342,   355,   358,   365,   370,   378,   385,
     390,   398,   406,   411,   419,   425,   434,   441,   448,   455,
     462,   469,   476,   486,   492,   498,   504,   510,   516,   522,
     531,   532,   533,   534,   535,   536,   540,   549,   553,   554,
     558,   559,   563,   564,   568,   569,   570,   571,   572,   573
  };

  // Print the state stack on the debug stream.
  void
  ir_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ir_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 2174 "src/ir/ir_parser.tab.cc" // lalr1.cc:1167
#line 576 "src/ir/ir_parser.yy" // lalr1.cc:1168


void
yy::ir_parser::error(const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define parser_class_name {ir_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
{
# include <cstdint>
# include <string>
# include <utility>
# include "format.h"
# include "format_util.h"
namespace corevm {
namespace ir {
class IRParserDriver;
} /* end namespace ir */
} /* end namespace corevm */
}
// The parsing context.
%param { corevm::ir::IRParserDriver& driver }
%param { void* yyscanner }
%locations
%define parse.error verbose
%initial-action
{
  // Initialize the initial location.
  if (!driver.input_file().empty())
  {
    @$.begin.filename = @$.end.filename = &driver.input_file();
  }
};
%code
{
# include "ir_parser_driver.h"
}
%token <std::string>      TYPE_NAME_I8
%token <std::string>      TYPE_NAME_UI8
%token <std::string>      TYPE_NAME_I16
%token <std::string>      TYPE_NAME_UI16
%token <std::string>      TYPE_NAME_I32
%token <std::string>      TYPE_NAME_UI32
%token <std::string>      TYPE_NAME_I64
%token <std::string>      TYPE_NAME_UI64
%token <std::string>      TYPE_NAME_SPF
%token <std::string>      TYPE_NAME_DPF
%token <std::string>      TYPE_NAME_BOOLEAN
%token <std::string>      TYPE_NAME_VOID
%token <std::string>      TYPE_NAME_STRING
%token <std::string>      TYPE_NAME_OBJECT

%token <corevm::IROpcode> OPCODE
%token <std::string>      ARRAY
%token <std::string>      DEF
%token <std::string>      DECLARE
%token <std::string>      TYPE
%token <std::string>      IDENTIFIER
%token <std::string>      STRING_LITERAL
%token <int64_t>          DECIMALINTEGER
%token <double>           FLOATINGNUM
%token <bool>             BOOLEAN_CONSTANT
%token <std::string>      COMMA
%token <std::string>      DOT
%token <std::string>      COLON
%token <std::string>      SEMICOLON
%token <std::string>      PERCENT
%token <std::string>      STAR
%token <std::string>      POND
%token <std::string>      ASSIGN
%token <std::string>      LPAREN
%token <std::string>      RPAREN
%token <std::string>      LBRACKET
%token <std::string>      RBRACKET
%token <std::string>      LBRACE
%token <std::string>      RBRACE
%token <std::string>      LABEL
%token END                0  "end of file"

%type <corevm::IRValueType> ir_value_type_short_integer_numeric;
%type <corevm::IRValueType> ir_value_type_long_integer_numeric;
%type <corevm::IRValueType> ir_value_type_integer_numeric;
%type <corevm::IRValueType> ir_value_type_floating_numeric;
%type <corevm::IRValueType> ir_value_type_string;
%type <corevm::IRValueType> ir_value_type;
%type <corevm::IRValue> ir_value;
%type <corevm::IRArrayType> ir_value_type_array;
%type <corevm::IRIdentifierType> ir_identifier_type;
%type <std::string> identifier;
%type <corevm::IROperand> operand;
%type <std::vector<corevm::IROperand>> operand_list;
%type <corevm::IRLabel> label;
%type <std::vector<corevm::IRLabel>> label_list_core;
%type <std::vector<corevm::IRLabel>> label_list;
%type <std::vector<std::string>> instruction_option_list;
%type <std::vector<std::string>> instruction_options;
%type <corevm::IRInstruction> expr;
%type <corevm::IRInstruction> instruction;
%type <std::vector<corevm::IRInstruction >> instruction_group;
%type <corevm::IRBasicBlock> basic_block;
%type <std::vector<corevm::IRBasicBlock>> basic_block_list;
%type <corevm::IRParameter> function_arg;
%type <std::vector<corevm::IRParameter>> function_arg_list;
%type <std::string> position_args;
%type <std::string> keyword_args;
%type <std::string> closure_parent;
%type <int64_t> function_def_option;
%type <int64_t> function_def_option_list_core;
%type <int64_t> function_def_option_list;
%type <corevm::IRClosure> function_def;
%type <std::string> intrinsic_decl_name;
%type <corevm::IRIntrinsicDecl> intrinsic_decl;
%type <corevm::IRTypeField> type_field;
%type <std::vector<corevm::IRTypeField>> type_field_list;
%type <corevm::IRTypeAttribute> type_attribute;
%type <std::vector<corevm::IRTypeAttribute>> type_attribute_list;
%type <corevm::IRTypeDecl> type_def;
%type <std::vector<corevm::ir::IRDefn>> definition_list;
%type <corevm::ir::MetadataPair> metadata_def;
%type <std::vector<corevm::ir::MetadataPair>> metadata_def_list;
%type <corevm::IRModule> input;

%debug

%%

%start input;

input
    : metadata_def_list definition_list
        {
            $$ = corevm::IRModule();
            corevm::ir::set_metadata_and_definitions($1, $2, $$);
            driver.set_module(std::move($$));
        }
    ;

metadata_def_list
    :
        {
            $$ = std::vector<corevm::ir::MetadataPair>();
        }
    |   metadata_def_list metadata_def
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    ;

metadata_def
    : STRING_LITERAL COLON STRING_LITERAL
        {
            $$ = std::make_pair($1, $3);      
        }
    ;

definition_list
    :
        {
            $$ = std::vector<corevm::ir::IRDefn>();
        }
    | definition_list type_def
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    | definition_list function_def
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    | definition_list intrinsic_decl
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    ;

type_def
    : TYPE IDENTIFIER LBRACE type_field_list RBRACE
        {
            $$ = corevm::IRTypeDecl();
            $$.name = std::move($2);
            $$.fields = std::move($4);
        }
    |
        LBRACKET type_attribute_list RBRACKET TYPE IDENTIFIER LBRACE type_field_list RBRACE
        {
            $$ = corevm::IRTypeDecl();
            $$.attributes = std::move($2);
            $$.name = std::move($5);
            $$.fields = std::move($7);
        }
    ;

type_attribute_list
    : type_attribute
        {
            $$ = std::vector<corevm::IRTypeAttribute>();
            $$.push_back($1);
        }
    | type_attribute_list COMMA type_attribute
        {
            $$ = std::move($1);
            $$.push_back($3);
        }
    ;

type_attribute
    : IDENTIFIER ASSIGN IDENTIFIER
        {
            $$ = corevm::IRTypeAttribute();
            $$.name = std::move($1);
            $$.value = std::move($3);
        }
    ;

type_field_list
    :
        {
            $$ = std::vector<corevm::IRTypeField>();
        }
    | type_field_list type_field
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    ;

type_field
    : ir_identifier_type IDENTIFIER SEMICOLON
        {
            $$ = corevm::IRTypeField();
            $$.type = std::move($1);
            $$.identifier = std::move($2);
        }
    ;

intrinsic_decl
    : DECLARE ir_identifier_type intrinsic_decl_name LPAREN RPAREN
        {
            $$ = corevm::IRIntrinsicDecl();
            $$.rettype = std::move($2);
            $$.name = std::move($3);
        }
    | DECLARE ir_identifier_type intrinsic_decl_name LPAREN function_arg_list RPAREN
        {
            $$ = corevm::IRIntrinsicDecl();
            $$.rettype = std::move($2);
            $$.name = std::move($3);
            $$.parameters = std::move($5);
        }
    ;

intrinsic_decl_name
    : IDENTIFIER
        {
            $$ = std::move($1);
        }
    | intrinsic_decl_name DOT IDENTIFIER
        {
            std::string name(std::move($1));
            name += ($2);
            name += ($3);
            $$ = std::move(name);
        }
    ;

function_def
    : DEF ir_identifier_type IDENTIFIER LPAREN RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.parent = std::move($6);
            $$.options = $7;
            $$.blocks = std::move($9);
        }
    | DEF ir_identifier_type IDENTIFIER LPAREN function_arg_list RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.parameters = std::move($5);
            $$.parent = std::move($7);
            $$.options = $8;
            $$.blocks = std::move($10);
        }
    | DEF ir_identifier_type IDENTIFIER LPAREN function_arg_list COMMA position_args RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.parameters = std::move($5);
            $$.positional_args = std::move($7);
            $$.parent = std::move($9);
            $$.options = $10;
            $$.blocks = std::move($12);
        }
    | DEF ir_identifier_type IDENTIFIER LPAREN function_arg_list COMMA keyword_args RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.parameters = std::move($5);
            $$.keyword_args = std::move($7);
            $$.parent = std::move($9);
            $$.options = $10;
            $$.blocks = std::move($12);
        }
    | DEF ir_identifier_type IDENTIFIER LPAREN position_args RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.positional_args = std::move($5);
            $$.parent = std::move($7);
            $$.options = $8;
            $$.blocks = std::move($10);
        }
    | DEF ir_identifier_type IDENTIFIER LPAREN keyword_args RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.keyword_args = std::move($5);
            $$.parent = std::move($7);
            $$.options = $8;
            $$.blocks = std::move($10);
        }
    | DEF ir_identifier_type IDENTIFIER LPAREN position_args COMMA keyword_args RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.positional_args = std::move($5);
            $$.keyword_args = std::move($7);
            $$.parent = $9;
            $$.options = $10;
            $$.blocks = std::move($12);
        }
    | DEF ir_identifier_type IDENTIFIER LPAREN function_arg_list COMMA position_args COMMA keyword_args RPAREN closure_parent function_def_option_list LBRACE basic_block_list RBRACE
        {
            $$ = corevm::IRClosure();
            $$.rettype = $2;
            $$.name = std::move($3);
            $$.parameters = std::move($5);
            $$.positional_args = std::move($7);
            $$.keyword_args = std::move($9);
            $$.parent = std::move($11);
            $$.options = $12;
            $$.blocks = std::move($14);
        }
    ;

function_def_option_list
    :
        {
            $$ = 0;
        }
    | LBRACKET function_def_option_list_core RBRACKET
        {
            $$ = $2;
        }
    ;

function_def_option_list_core
    : function_def_option
        {
            $$ = $1;
        }
    | function_def_option_list_core function_def_option
        {
            $$ = corevm::ir::add_func_defn_option($1, $2);
        }
    ;

function_def_option
    : IDENTIFIER
        {
            $$ = corevm::ir::interpret_func_defn_option($1);
        }
    ;

closure_parent
    :
        {
        }
    | COLON IDENTIFIER
        {
            $$ = std::move($2);
        }
    ;

keyword_args
    : STAR STAR IDENTIFIER
        {
            $$ = std::move($3);
        }
    ;

position_args
    : STAR IDENTIFIER
        {
            $$ = std::move($2);
        }
    ;

function_arg_list
    : function_arg
        {
            $$ = std::vector<corevm::IRParameter>();
            $$.push_back($1);
        }
    | function_arg_list COMMA function_arg
        {
            $$ = std::move($1);
            $$.push_back($3);
        }
    ;

function_arg
    : ir_identifier_type IDENTIFIER
        {
            $$ = corevm::IRParameter();
            $$.type = std::move($1);
            $$.identifier = std::move($2);
        }
    ;

basic_block_list
    :
        {
            $$ = std::vector<corevm::IRBasicBlock>();
        }
    | basic_block_list basic_block
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    ;

basic_block
    : IDENTIFIER COLON instruction_group
        {
            $$ = corevm::IRBasicBlock();
            $$.label = std::move($1);
            $$.body = std::move($3);
        }
    ;

instruction_group
    : instruction
        {
            $$ = std::vector<corevm::IRInstruction>();
            $$.push_back($1);
        }
    | instruction_group instruction
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    ;

instruction
    : identifier ASSIGN expr SEMICOLON
        {
            $$ = std::move($3);
            $$.target.set_string($1);
        }
    | expr SEMICOLON
        {
            $$ = std::move($1);
            $$.target.set_null();
        }
    ;

expr
    : OPCODE instruction_options
        {
            $$ = corevm::IRInstruction();
            $$.opcode = $1;
            $$.options = std::move($2);
            $$.type.set_null();
        }
    | OPCODE instruction_options ir_identifier_type
        {
            $$ = corevm::IRInstruction();
            $$.opcode = $1;
            $$.options = std::move($2);
            $$.type.set_IRIdentifierType($3);
        }
    | OPCODE instruction_options operand_list
        {
            $$ = corevm::IRInstruction();
            $$.opcode = $1;
            $$.options = std::move($2);
            $$.oprds = std::move($3);
            $$.type.set_null();
        }
    | OPCODE instruction_options operand_list label_list
        {
            $$ = corevm::IRInstruction();
            $$.opcode = $1;
            $$.options = std::move($2);
            $$.oprds = std::move($3);
            $$.labels.set_array($4);
            $$.type.set_null();
        }
    | OPCODE instruction_options ir_identifier_type operand_list
        {
            $$ = corevm::IRInstruction();
            $$.opcode = $1;
            $$.options = std::move($2);
            $$.type.set_IRIdentifierType($3);
            $$.oprds = std::move($4);
        }
    | OPCODE instruction_options ir_identifier_type operand_list label_list
        {
            $$ = corevm::IRInstruction();
            $$.opcode = $1;
            $$.options = std::move($2);
            $$.type.set_IRIdentifierType($3);
            $$.oprds = std::move($4);
            $$.labels.set_array($5);
        }
    | OPCODE label_list
        {
            $$ = corevm::IRInstruction();
            $$.opcode = $1;
            $$.labels.set_array($2);
        }
    ;

instruction_options
    :
        {
            $$ = std::vector<std::string>();
        }
    | LBRACKET instruction_option_list RBRACKET
        {
            $$ = std::move($2);
        }
    ;

instruction_option_list
    : IDENTIFIER
        {
            $$ = std::vector<std::string>();
            $$.push_back($1);
        }
    | instruction_option_list IDENTIFIER
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    ;

label_list
    : LBRACKET label_list_core RBRACKET
        {
            $$ = std::move($2);
        }
    ;

label_list_core
    : label
        {
            $$ = std::vector<corevm::IRLabel>();
            $$.push_back($1);
        }
    | label_list_core COMMA label
        {
            $$ = std::move($1);
            $$.push_back($3);
        }
    ;

label
    : LABEL POND IDENTIFIER
        {
            $$ = corevm::IRLabel();
            $$.name = std::move($3);
        }
    ;

operand_list
    : operand
        {
            $$ = std::vector<corevm::IROperand>();
            $$.push_back($1);
        }
    | operand_list operand
        {
            $$ = std::move($1);
            $$.push_back($2);
        }
    ;

operand
    : ir_value
        {
            $$ = corevm::IROperand();
            $$.type = corevm::constant;
            $$.value.set_IRValue($1);
        }
    | identifier
        {
            $$ = corevm::IROperand();
            $$.type = corevm::ref;
            $$.value.set_string($1);
        }
    ;

identifier
    : PERCENT IDENTIFIER
        {
            $$ = std::move($2);
        }
    ;

ir_identifier_type
    : IDENTIFIER
        {
            $$ = corevm::IRIdentifierType();
            $$.type = corevm::IdentifierType_Identifier;
            $$.ref_type = corevm::value;
            $$.value.set_string($1);
        }
    | ir_value_type
        {
            $$ = corevm::IRIdentifierType();
            $$.type = corevm::IdentifierType_ValueType;
            $$.ref_type = corevm::value;
            $$.value.set_IRValueType($1);
        }
    | ir_value_type_array
        {
            $$ = corevm::IRIdentifierType();
            $$.type = corevm::IdentifierType_Array;
            $$.ref_type = corevm::value;
            $$.value.set_IRArrayType($1);
        }
    | IDENTIFIER STAR
        {
            $$ = corevm::IRIdentifierType();
            $$.type = corevm::IdentifierType_Identifier;
            $$.ref_type = corevm::pointer;
            $$.value.set_string($1);
        }
    | ir_value_type STAR
        {
            $$ = corevm::IRIdentifierType();
            $$.type = corevm::IdentifierType_ValueType;
            $$.ref_type = corevm::pointer;
            $$.value.set_IRValueType($1);
        }
    | ir_value_type_array STAR
        {
            $$ = corevm::IRIdentifierType();
            $$.type = corevm::IdentifierType_Array;
            $$.ref_type = corevm::pointer;
            $$.value.set_IRArrayType($1);
        }
    ;

ir_value
    : ir_value_type_short_integer_numeric DECIMALINTEGER
        {
            $$ = corevm::IRValue();
            $$.type = $1;
            $$.value.set_int($2);
        }
    | ir_value_type_long_integer_numeric DECIMALINTEGER
        {
            $$ = corevm::IRValue();
            $$.type = $1;
            $$.value.set_long($2);
        }
    | TYPE_NAME_SPF FLOATINGNUM
        {
            $$ = corevm::IRValue();
            $$.type = corevm::spf;
            $$.value.set_float($2);
        }
    | TYPE_NAME_DPF FLOATINGNUM
        {
            $$ = corevm::IRValue();
            $$.type = corevm::dpf;
            $$.value.set_double($2);
        }
    | ir_value_type_string STRING_LITERAL
        {
            $$ = corevm::IRValue();
            $$.type = $1;
            $$.value.set_string($2);
        }
    | TYPE_NAME_BOOLEAN BOOLEAN_CONSTANT
        {
            $$ = corevm::IRValue();
            $$.type = corevm::boolean;
            $$.value.set_bool($2);
        }
    | TYPE_NAME_BOOLEAN DECIMALINTEGER
        {
            $$ = corevm::IRValue();
            $$.type = corevm::boolean;
            $$.value.set_bool(static_cast<bool>($2));
        }
    ;

ir_value_type
    : ir_value_type_integer_numeric             { $$ = $1; }
    | ir_value_type_floating_numeric            { $$ = $1; }
    | ir_value_type_string                      { $$ = $1; }
    | TYPE_NAME_VOID                            { $$ = corevm::voidtype;   }
    | TYPE_NAME_BOOLEAN                         { $$ = corevm::boolean;    }
    | TYPE_NAME_OBJECT                          { $$ = corevm::object;     }
    ;

ir_value_type_array
    : ARRAY LBRACKET DECIMALINTEGER STAR ir_identifier_type RBRACKET
        {
            $$ = corevm::IRArrayType();
            $$.len = $3;
            $$.type = std::move($5);
        }
    ;

ir_value_type_string
    : TYPE_NAME_STRING                          { $$ = corevm::string; }
    ;

ir_value_type_floating_numeric
    : TYPE_NAME_SPF                             { $$ = corevm::spf; }
    | TYPE_NAME_DPF                             { $$ = corevm::dpf; }
    ;

ir_value_type_integer_numeric
    : ir_value_type_short_integer_numeric       { $$ = $1; }
    | ir_value_type_long_integer_numeric        { $$ = $1; }
    ;

ir_value_type_long_integer_numeric
    : TYPE_NAME_I64                             { $$ = corevm::i64;  }
    | TYPE_NAME_UI64                            { $$ = corevm::ui64; }
    ;

ir_value_type_short_integer_numeric
    : TYPE_NAME_I8                              { $$ = corevm::i8;   }
    | TYPE_NAME_UI8                             { $$ = corevm::ui8;  }
    | TYPE_NAME_I16                             { $$ = corevm::i16;  }
    | TYPE_NAME_UI16                            { $$ = corevm::ui16; }
    | TYPE_NAME_I32                             { $$ = corevm::i32;  }
    | TYPE_NAME_UI32                            { $$ = corevm::ui32; }
    ;

%%

void
yy::ir_parser::error(const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_RIGHT    "right"
%token            KW_LEFT     "left"
%token            KW_HEADING  "heading"
%token            KW_POSITION "position"
%token            KW_UP       "up"
%token            KW_DOWN     "down"

%token            KW_COLOR    "color"
%token            KW_HOME     "home"
%token            KW_PRINT    "print"
%token            KW_REPEAT   "repeat"
%token            KW_SET      "set"

%token            KW_PROC     "proc"
%token            KW_CALL     "call"

%token            KW_SIN      "sin"
%token            KW_COS      "cos"
%token            KW_TAN      "tan"
%token            KW_SQRT     "sqrt"
%token            KW_RANDOM   "random"

%token            KW_RED      "red"
%token            KW_GREEN    "green"
%token            KW_BLUE     "blue"
%token            KW_CYAN     "cyan"
%token            KW_MAGENTA  "magenta"
%token            KW_YELLOW   "yellow"
%token            KW_BLACK    "black"
%token            KW_GRAY     "gray"
%token            KW_WHITE    "white"

%left '+' '-'
%left '*' '/'
%right '^'
%right UMINUS

%type <node> unit cmds cmd internal_functions
block expr color

%%

unit:
    cmds              { $$ = make_cmd_block($1); ret->unit = $$; }
  | /* empty */       { $$ = make_cmd_block(NULL); ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_UP                      { $$ = make_cmd_up(); }
  | KW_DOWN                    { $$ = make_cmd_down(); }
  | KW_HOME                    { $$ = make_cmd_home(); }
  | KW_FORWARD expr            { $$ = make_cmd_forward($2); }
  | KW_BACKWARD expr           { $$ = make_cmd_backward($2); }
  | KW_LEFT expr               { $$ = make_cmd_left($2); }
  | KW_RIGHT expr              { $$ = make_cmd_right($2); }
  | KW_HEADING expr            { $$ = make_cmd_heading($2); }
  | KW_POSITION expr ',' expr  { $$ = make_cmd_position($2, $4); }
  | KW_PRINT expr              { $$ = make_cmd_print($2); }
  | KW_SET NAME expr           { $$ = make_cmd_set(make_expr_name($2), $3); }
  | KW_REPEAT expr block       { $$ = make_cmd_repeat($2, $3); }
  | KW_PROC NAME block         { $$ = make_cmd_proc(make_expr_name($2), $3); }
  | KW_CALL NAME               { $$ = make_cmd_call(make_expr_name($2)); }
  | color
  | internal_functions
  | block
;

internal_functions:
    KW_SIN '(' expr ')'              { $$ = make_func_sin($3); }
  | KW_COS '(' expr ')'              { $$ = make_func_cos($3); }
  | KW_TAN '(' expr ')'              { $$ = make_func_tan($3); }
  | KW_SQRT '(' expr ')'             { $$ = make_func_sqrt($3); }
  | KW_RANDOM '(' expr ',' expr ')'  { $$ = make_func_random($3, $5); }
;

block:
    '{' cmds '}'                   { $$ = make_cmd_block($2); }
;

expr:
    expr '+' expr          { $$ = make_expr_binop('+', $1, $3); }
  | expr '-' expr          { $$ = make_expr_binop('-', $1, $3); }
  | expr '*' expr          { $$ = make_expr_binop('*', $1, $3); }
  | expr '/' expr          { $$ = make_expr_binop('/', $1, $3); }
  | expr '^' expr          { $$ = make_expr_binop('^', $1, $3); }
  | '-' expr %prec UMINUS  { $$ = make_expr_unop('-', $2); }
  | '(' expr ')'           { $$ = $2; }
  | NAME                   { $$ = make_expr_name($1); }
  | VALUE                  { $$ = make_expr_value($1); }
  | internal_functions
;

color:
    KW_COLOR expr ',' expr ',' expr  { $$ = make_color_expr($2, $4, $6); }
  | KW_COLOR KW_RED                  { $$ = make_color_keyword("red"); }
  | KW_COLOR KW_GREEN                { $$ = make_color_keyword("green"); }
  | KW_COLOR KW_BLUE                 { $$ = make_color_keyword("blue"); }
  | KW_COLOR KW_CYAN                 { $$ = make_color_keyword("cyan"); }
  | KW_COLOR KW_MAGENTA              { $$ = make_color_keyword("magenta"); }
  | KW_COLOR KW_YELLOW               { $$ = make_color_keyword("yellow"); }
  | KW_COLOR KW_BLACK                { $$ = make_color_keyword("black"); }
  | KW_COLOR KW_GRAY                 { $$ = make_color_keyword("gray"); }
  | KW_COLOR KW_WHITE                { $$ = make_color_keyword("white"); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}

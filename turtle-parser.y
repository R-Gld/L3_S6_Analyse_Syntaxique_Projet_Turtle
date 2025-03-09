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

/* Les types que peuvent prendre */
%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

/* Movement */
%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_RIGHT     "right"
%token            KW_LEFT     "left"
%token            KW_HEADING     "heading"
%token            KW_POSITION     "position"

/* Pen */
%token            KW_UP     "up"
%token            KW_DOWN     "down"

/* Others */
%token            KW_COLOR     "color"
%token            KW_HOME     "home"
%token            KW_PRINT     "print"
%token            KW_REPEAT     "repeat"
%token            KW_SET     "set"

/* functions */
%token            KW_PROC     "proc"
%token            KW_CALL     "call"

/* Intern functions */
%token            KW_SIN     "sin"
%token            KW_COS     "cos"
%token            KW_TAN     "tan"
%token            KW_SQRT    "sqrt"
%token            KW_RANDOM  "random"

/* Colors */
%token            KW_RED     "red"
%token            KW_GREEN   "green"
%token            KW_BLUE    "blue"
%token            KW_CYAN    "cyan"
%token            KW_MAGENTA "magenta"
%token            KW_YELLOW  "yellow"
%token            KW_BLACK   "black"
%token            KW_GRAY    "gray"
%token            KW_WHITE   "white"

%left '+' '-'
%left '*' '/'
%right '^'
%right UMINUS

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_UP expr             { /* Not yet implemented */ }
  | KW_DOWN expr           { /* Not yet implemented */ }
  | KW_HOME expr           { /* Not yet implemented */ }
  | KW_FORWARD expr        { $$ = make_cmd_forward($2); }
  | KW_BACKWARD expr       { $$ = make_cmd_backward($2); }
  | KW_LEFT expr           { /* Not yet implemented */ }
  | KW_RIGHT expr          { /* Not yet implemented */ }
  | KW_HEADING expr        { /* Not yet implemented */ }
  | KW_POSITION expr ',' expr       { /* Not yet implemented */ }
  | KW_COLOR expr          { /* Not yet implemented */ }
  | KW_HOME expr           { /* Not yet implemented */ }
  | KW_PRINT expr          { /* Not yet implemented */ }
  | KW_SET expr            { /* Not yet implemented */ }
;

expr:
    expr '+' expr       { $$ = make_expr_binop('+', $1, $3); }
  | expr '-' expr       { $$ = make_expr_binop('-', $1, $3); }
  | expr '*' expr       { $$ = make_expr_binop('*', $1, $3); }
  | expr '/' expr       { $$ = make_expr_binop('/', $1, $3); }
  | expr '^' expr       { $$ = make_expr_binop('^', $1, $3); }
  | '-' expr %prec UMINUS  { $$ = make_expr_unop('-', $2); }
  | '(' expr ')'        { $$ = $2; }
  | NAME                { $$ = make_expr_name($1); }
  | VALUE               { $$ = make_expr_value($1); }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}

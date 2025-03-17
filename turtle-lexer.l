%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT  [0-9]
LETTER [a-zA-Z]
ID     {LETTER}({LETTER}|{DIGIT})*

%%
{DIGIT}+"."{DIGIT}*([eE][+-]?{DIGIT}+)?     { yylval.value = strtod(yytext, NULL); if(errno == ERANGE) { exit(EXIT_FAILURE); } return VALUE; }
"."{DIGIT}+([eE][+-]?{DIGIT}+)?             { yylval.value = strtod(yytext, NULL); if(errno == ERANGE) { exit(EXIT_FAILURE); } return VALUE; }
{DIGIT}+([eE][+-]?{DIGIT}+)?                { yylval.value = strtod(yytext, NULL); if(errno == ERANGE) { exit(EXIT_FAILURE); } return VALUE; }


"forward"           { return KW_FORWARD; }
"fw"                { return KW_FORWARD; }
"backward"          { return KW_BACKWARD; }
"bw"                { return KW_BACKWARD; }
"right"             { return KW_RIGHT; }
"rt"                { return KW_RIGHT; }
"left"              { return KW_LEFT; }
"lt"                { return KW_LEFT; }
"heading"           { return KW_HEADING; }
"hd"                { return KW_HEADING; }
"position"          { return KW_POSITION; }
"pos"               { return KW_POSITION; }
"up"                { return KW_UP; }
"down"              { return KW_DOWN; }
"color"             { return KW_COLOR; }
"home"              { return KW_HOME; }
"print"             { return KW_PRINT; }
"repeat"            { return KW_REPEAT; }
"set"               { return KW_SET; }
"proc"              { return KW_PROC; }
"call"              { return KW_CALL; }

"sin"             { return KW_SIN; }
"cos"             { return KW_COS; }
"tan"             { return KW_TAN; }
"sqrt"            { return KW_SQRT; }
"random"          { return KW_RANDOM; }

"red"             { return KW_RED; }
"green"           { return KW_GREEN; }
"blue"            { return KW_BLUE; }
"cyan"            { return KW_CYAN; }
"magenta"         { return KW_MAGENTA; }
"yellow"          { return KW_YELLOW; }
"black"           { return KW_BLACK; }
"gray"            { return KW_GRAY; }
"white"           { return KW_WHITE; }

"{"   { return '{'; }
"}"   { return '}'; }
"("   { return '('; }
")"   { return ')'; }
","   { return ','; }

"-"   { return '-'; }
"+"   { return '+'; }
"*"   { return '*'; }
"/"   { return '/'; }
"^"   { return '^'; }


"#".*             { /* Ignore the comment */ }

{ID}              { yylval.name = strdup(yytext); return NAME; }

[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%

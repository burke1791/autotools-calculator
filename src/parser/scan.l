
%option noyywrap nounput noinput

%option reentrant bison-bridge

%option header-file="scan.lex.h"

%{

#include "gram.h"

#define YY_EXIT_FAILURE ((void)yyscanner, EXIT_FAILURE)

/* XOPEN for strdup */
#define _XOPEN_SOURCE 600
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int yyerror(const char* msg);

%}

/* float exponent */
EXP   ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"|" |
"(" |
")"   { return yytext[0]; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?    { yylval->d = atof(yytext); return NUMBER; }

\n      { return EOL; }

"//".*
[ \t]   { /* ignore whitespace */ }

.       { yyerror("Mystery character"); }

 
%%
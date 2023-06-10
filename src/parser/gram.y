
%define api.pure true
%define parse.error verbose

%define api.prefix {calc}

%code top {

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bison versions 3.7.5 and above provide the YYNOMEM
    macro to allow our actions to signal the unlikely
    event that they couldn't allocate memory. Thanks
    to the Bison team for adding this feature at my
    request. :) YYNOMEM causes yyparse() to return 2.

    The following conditional define allows us to use
    the functionality in earlier versions too. */

#ifndef YYNOMEM
#define YYNOMEM goto yyexhaustedlab
#endif

#include "include/ast.h"

}

%union {
  double d;
  struct Node* t;
}

%parse-param { struct Node** t }
%param { void* scanner }

%code {
  int calcerror(void* foo, const char* msg, const void* s);
  int calclex(void* lval, const void* s);
}

%token <d> NUMBER
%token EOL

%type <t> exp factor term calclist

%destructor { free_node($$); } <t>

%%

calclist: /* nothing */
  | calclist exp EOL {
      *t = $$ = $2;
      return 0;
    }
  | calclist EOL {
      printf("> ");
    }
  ;

exp: factor
  | exp '+' factor  { $$ = new_ast(N_PLUS, $1, $3); }
  | exp '-' factor  { $$ = new_ast(N_MINUS, $1, $3); }
  ;

factor: term
  | factor '*' term   { $$ = new_ast(N_TIMES, $1, $3); }
  | factor '/' term   { $$ = new_ast(N_DIV, $1, $3); }
  ;

term: NUMBER    { $$ = new_num($1); }
  | '|' term    { $$ = new_ast(N_ABS, $2, NULL); }
  | '(' exp ')' { $$ = $2; }
  | '-' term    { $$ = new_ast(N_NEG, $2, NULL); }
  ;

%%

int calcerror(void* yylval, const char* msg, const void* s) {
  (void)yylval;
  (void)s;
  return fprintf(stderr, "%s\n", msg);
}
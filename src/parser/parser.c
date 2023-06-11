#include <stdio.h>
#include <stdlib.h>

#include "gram.h"
#include "scan.lex.h"
#include "ast.h"
#include "parser.h"

AST* parse_equation(char* eqn) {
  int i;
  struct Node* t;
  yyscan_t scanner;
  YY_BUFFER_STATE buf;

  if ((i = yylex_init(&scanner)) != 0) exit(i);

  buf = yy_scan_string(eqn, scanner);
  yy_switch_to_buffer(buf, scanner);

  int e = yyparse(&t, scanner);

  if (e != 0) {
    printf("parse error\n");
  }

  yy_delete_buffer(buf, scanner);
  yylex_destroy(scanner);

  return (AST*)t;
}
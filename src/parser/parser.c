#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE CALCSTYPE

#include "calc.tab.h"
#include "calc.lex.h"
#include "ast.h"

AST* parse_equation(char* eqn) {
  int i;
  struct Node* t;
  yyscan_t scanner;
  YY_BUFFER_STATE buf;

  if ((i = calclex_init(&scanner)) != 0) exit(i);

  buf = calc_scan_string(eqn, scanner);
  calc_switch_to_buffer(buf, scanner);

  int e = calcparse(&t, scanner);

  if (e == 0) {
    printf("parse success\n");
  }

  calc_delete_buffer(buf, scanner);
  calclex_destroy(scanner);

  return (AST*)t;
}
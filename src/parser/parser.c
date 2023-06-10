#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE CALCSTYPE

#include "calc.tab.h"
#include "calc.lex.h"
#include "ast.h"

int parse_equation(AST* t, char* eqn) {
  int i;
  calcscan_t scanner;
  CALC_BUFFER_STATE buf;

  if ((i = calclex_init(&scanner)) != 0) exit(i);

  buf = calc_scan_string(eqn, scanner);
  calc_switch_to_buffer(buf, scanner);

  int e = calcparse(&t, scanner);

  if (e == 0) {
    printf("parse success");
  }

  calc_delete_buffer(buf, scanner);
  calclex_destroy(scanner);

  return EXIT_SUCCESS;
}
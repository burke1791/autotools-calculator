#include <stdio.h>

#include "parser.h"

int main() {
  char* eqn = "33 + 36\n";

  AST* t = parse_equation(eqn);

  if (t == NULL) {
    printf("idk what went wrong...\n");
  }

  printf("do the evaluation here\n");

  free_node((Node*)t);

  return 0;
}
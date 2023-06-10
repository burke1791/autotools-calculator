
#include "parser.h"

int main() {
  AST* t;
  char* eqn = "33 + 36";

  if (parse_equation(t, eqn) != 0) {
    printf("idk what went wrong...\n");
  }

  return 0;
}
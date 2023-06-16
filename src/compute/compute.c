#include <stdio.h>

#include "compute/compute.h"
#include "parser/ast.h"

double compute(Node* t) {
  double v;  // calculated value of this subtree

  switch (t->type) {
    case N_CONST:
      v = ((Num*)t)->val;
      break;
    case N_PLUS:
      v = compute(((AST*)t)->l) + compute(((AST*)t)->r);
      break;
    case N_MINUS:
      v = compute(((AST*)t)->l) - compute(((AST*)t)->r);
      break;
    case N_TIMES:
      v = compute(((AST*)t)->l) * compute(((AST*)t)->r);
      break;
    case N_DIV:
      v = compute(((AST*)t)->l) / compute(((AST*)t)->r);
      break;
    case N_ABS:
      v = compute(((AST*)t)->l);
      if (v < 0) v = -v;
      break;
    case N_NEG:
      v = -compute(((AST*)t)->l);
      break;
    default:
      printf("Internal error: bad node %c\n", t->type);
  }

  return v;
}
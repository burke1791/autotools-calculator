#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "parser/ast.h"

Node* new_ast(NodeType type, Node* l, Node* r) {
  AST* a = malloc(sizeof(AST));

  if (!a) {
    exit(EXIT_FAILURE);
  }

  a->type = type;
  a->l = l;
  a->r = r;

  return (Node*)a;
}

Node* new_num(double d) {
  Num* n = malloc(sizeof(Num));

  if (!n) {
    exit(EXIT_FAILURE);
  }

  n->type = N_CONST;
  n->val = d;

  return (Node*)n;
}

void free_node(Node* n) {
  switch (n->type) {
    case N_AST:
      free_node(((AST*)n)->l);
      free_node(((AST*)n)->r);
      free(n);
      break;

    case N_PLUS:
    case N_MINUS:
    case N_TIMES:
    case N_DIV:
      free_node(((AST*)n)->r);
      /**
       * Using a clever switch/case trick here. Since there's no break,
       * it will continue executing code (even if downstream cases don't match)
       * until the end of the closure or it hits a downstream break.
      */
    
    case N_ABS:
    case N_NEG:
      free_node(((AST*)n)->l);
    
    case N_CONST:
      free(n);
      break;
    
    default:
      printf("Internal error: free bad node %d\n", n->type);
  }
}

#ifndef AST_H
#define AST_H

typedef enum NodeType {
  N_AST,
  N_CONST,
  N_PLUS,
  N_MINUS,
  N_TIMES,
  N_DIV,
  N_ABS,
  N_NEG
} NodeType;

typedef struct Node {
  NodeType type;
} Node;

// nodes in the abstract syntax tree
typedef struct AST {
  NodeType type;
  Node* l;
  Node* r;
} AST;

typedef struct Num {
  NodeType type;
  double val;
} Num;

// build as AST
Node* new_ast(NodeType type, Node* l, Node* r);
Node* new_num(double d);

// delete and free a Node
void free_node(Node* t);

#endif /* AST_H */
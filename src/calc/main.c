#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "reader/buffer.h"
#include "parser/ast.h"
#include "parser/parser.h"
#include "compute/compute.h"

void print_prompt() {
  printf("autocalc > ");
}

int main() {
  printf("Too stupid to do mental math, eh?\n");
  InputBuffer* buf = new_input_buffer();

  double res;

  while (true) {
    print_prompt();
    read_input(buf);

    if (strncmp(buf->buf, "exit", 4) == 0) {
      printf("Hope you learned something...\n");
      break;
    }

    AST* t = parse_equation(buf->buf);

    if (t == NULL) {
      printf("idk what went wrong...\n");
    }

    res = compute((Node*)t);

    printf("   = %f\n", res);

    free_node((Node*)t);
  }

  close_input_buffer(buf);

  return 0;
}
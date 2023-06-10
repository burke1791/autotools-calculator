#include <stdio.h>
#include <stdbool.h>

#include "buffer.h"

void print_prompt() {
  printf("autocalc > ");
}

int main() {
  printf("Too stupid to do mental math, eh?\n");
  InputBuffer* buf = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(buf);

    printf("Eqn: %s\n", buf->buf);
    printf("This is where we would do the calculation\n");
  }
}
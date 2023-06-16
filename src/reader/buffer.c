#include <stdlib.h>
#include <stdio.h>

#include "reader/buffer.h"
#include "mmgr/mempool.h"

InputBuffer* new_input_buffer() {
  InputBuffer* buf = pool_alloc(sizeof(InputBuffer));
  buf->buf = NULL;
  buf->bufLen = 0;
  buf->inputLen = 0;

  return buf;
}

void read_input(InputBuffer* buf) {
  ssize_t bytes_read = getline(&(buf->buf), &(buf->bufLen), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  // buf->inputLen = bytes_read - 1;
  // buf->buf[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* buf) {
  if (buf->buf != NULL) {
    // this buffer is not allocated in our mempool, so we free like this
    free(buf->buf);
  }
  pool_free(buf);
}
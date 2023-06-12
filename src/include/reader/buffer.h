#ifndef BUFFER_H
#define BUFFER_H

#include <sys/types.h>

typedef struct {
  char* buf;
  size_t bufLen;
  ssize_t inputLen;
} InputBuffer;

InputBuffer* new_input_buffer();
void read_input(InputBuffer* buf);
void close_input_buffer(InputBuffer* buf);

#endif /* BUFFER_H */
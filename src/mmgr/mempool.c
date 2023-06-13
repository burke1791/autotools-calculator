#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mmgr/mempool.h"

extern MemPool* p;

MemPool* pool_create(int size) {
  MemPool* pool = malloc(sizeof(MemPool));

  pool->size = size;
  pool->used = 0;
  pool->available = size - sizeof(MemPool);
  pool->head = NULL;

  return pool;
}

static void* free_mem_chunk(MemChunk* c) {
  void* nextChunk = c->nextChunk;
  if (c != NULL && c->ptr != NULL) {
    free(c->ptr);
    free(c);
  } else if (c != NULL) {
    free(c);
  }

  return nextChunk;
}

void pool_destroy(MemPool* pool) {
  MemChunk* chunk = pool->head;

  while (chunk != NULL) {
    chunk = free_mem_chunk(chunk);
  }

  free(pool);
}

static void* pool_append(MemPool* pool, int size) {
  MemChunk* mc = malloc(sizeof(MemChunk));
  mc->size = size;
  mc->nextChunk = NULL;
  mc->ptr = malloc(size);
  memset(mc->ptr, 0, size);

  if (pool->head == NULL) {
    pool->head = mc;
  } else {
    MemChunk* chunk = pool->head;

    while (chunk->nextChunk != NULL) {
      chunk = chunk->nextChunk;
    }

    chunk->nextChunk = mc;
    mc->prevChunk = chunk;
  }

  pool->available -= (size + sizeof(MemChunk));
  pool->used += (size + sizeof(MemChunk));

  return mc->ptr;
}

/**
 * Allocates and zeros memory
*/
void* pool_alloc(int size) {
  int spaceRequired = size + sizeof(MemChunk);

  if (p->available < spaceRequired) {
    printf("Not enough memory available in the MemPool\n");
    return NULL;
  }

  return pool_append(p, size);
}

static void pool_list_remove(MemPool* pool, MemChunk* prevChunk, MemChunk* c) {
  pool->used -= (c->size + sizeof(MemChunk));
  pool->available += (c->size + sizeof(MemChunk));

  MemChunk* nextChunk = free_mem_chunk(c);

  // reconnect the linked list
  if (prevChunk != NULL) {
    prevChunk->nextChunk = nextChunk;
  }

  if (nextChunk != NULL) {
    nextChunk->prevChunk = prevChunk;
  }

  if (prevChunk == NULL && nextChunk == NULL) {
    pool->head = NULL;
  }
}

void pool_free(void* ptr) {
  MemChunk* prevChunk = NULL;
  MemChunk* mc = p->head;

  while (mc->ptr != ptr && mc != NULL) {
    prevChunk = mc;
    mc = mc->nextChunk;
  }

  if (mc != NULL) {
    pool_list_remove(p, prevChunk, mc); 
  }
}

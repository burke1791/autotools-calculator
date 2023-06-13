#ifndef MEMPOOL_H
#define MEMPOOL_H

#define MIN_MEMPOOL_SIZE 40960 // 40kb

typedef struct MemChunk {
  void* ptr;
  int size;
  void* prevChunk;
  void* nextChunk;
} MemChunk;

typedef struct MemPool {
  int size;             /* number of bytes this MemPool is allowed to consume */
  int used;             /* number of bytes in use by the MemPool */
  int available;        /* number of bytes available for new allocations */
  MemChunk* head;       /* head node of the linked list of MemChunks */
} MemPool;

MemPool* pool_create(int size);
void pool_destroy(MemPool* pool);
void* pool_alloc(int size);
void pool_free(void* ptr);

#endif /* MEMPOOL_H */
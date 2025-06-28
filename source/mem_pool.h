#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct MemBlockHeader {
    size_t size;
    int free;
    struct MemBlockHeader *next;
} MemBlockHeader;

typedef struct {
    uint8_t *pool;
    size_t pool_size;
    MemBlockHeader *first;
} MemPool;

void mempool_init(MemPool *mp, void *buffer, size_t pool_size);
void *mempool_alloc(MemPool *mp, size_t size);
void *mempool_realloc(MemPool *mp, void *ptr, size_t new_size);
void mempool_free(MemPool *mp, void *ptr);
size_t mempool_bytes_used(MemPool *mp);
size_t mempool_bytes_total(MemPool *mp);
#include "mem_pool.h"
#include <string.h>

#define ALIGN4(x) (((x) + 3) & ~3)

void mempool_init(MemPool *mp, void *buffer, size_t pool_size) {
    mp->pool = (uint8_t *)buffer;
    mp->pool_size = pool_size;
    mp->first = (MemBlockHeader *)buffer;
    mp->first->size = pool_size - sizeof(MemBlockHeader);
    mp->first->free = 1;
    mp->first->next = NULL;
}

void *mempool_alloc(MemPool *mp, size_t size) {
    size = ALIGN4(size);
    MemBlockHeader *curr = mp->first;
    while (curr) {
        if (curr->free && curr->size >= size) {
            // Split block if large enough
            if (curr->size >= size + sizeof(MemBlockHeader) + 4) {
                MemBlockHeader *new_block = (MemBlockHeader *)((uint8_t *)curr + sizeof(MemBlockHeader) + size);
                new_block->size = curr->size - size - sizeof(MemBlockHeader);
                new_block->free = 1;
                new_block->next = curr->next;
                curr->next = new_block;
                curr->size = size;
            }
            curr->free = 0;
            return (void *)(curr + 1);
        }
        curr = curr->next;
    }
    return NULL; // Out of memory
}

void *mempool_realloc(MemPool *mp, void *ptr, size_t new_size) {
    if (!ptr) return mempool_alloc(mp, new_size); // realloc(NULL, size) == malloc(size)
    if (new_size == 0) {
        mempool_free(mp, ptr);
        return NULL;
    }

    MemBlockHeader *block = ((MemBlockHeader *)ptr) - 1;
    new_size = ALIGN4(new_size);

    // If shrinking, optionally split the block
    if (block->size >= new_size) {
        if (block->size >= new_size + sizeof(MemBlockHeader) + 4) {
            // Split as in alloc
            MemBlockHeader *new_block = (MemBlockHeader *)((uint8_t *)block + sizeof(MemBlockHeader) + new_size);
            new_block->size = block->size - new_size - sizeof(MemBlockHeader);
            new_block->free = 1;
            new_block->next = block->next;
            block->next = new_block;
            block->size = new_size;
        }
        return ptr;
    }

    // Try to expand into next block if it's free and large enough
    if (block->next && block->next->free &&
        block->size + sizeof(MemBlockHeader) + block->next->size >= new_size) {
        // Merge with next block
        block->size += sizeof(MemBlockHeader) + block->next->size;
        block->next = block->next->next;
        // Now try to split if still too large
        if (block->size >= new_size + sizeof(MemBlockHeader) + 4) {
            MemBlockHeader *new_block = (MemBlockHeader *)((uint8_t *)block + sizeof(MemBlockHeader) + new_size);
            new_block->size = block->size - new_size - sizeof(MemBlockHeader);
            new_block->free = 1;
            new_block->next = block->next;
            block->next = new_block;
            block->size = new_size;
        }
        return ptr;
    }

    // Otherwise, allocate a new block, copy, and free old
    void *new_ptr = mempool_alloc(mp, new_size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size < new_size ? block->size : new_size);
        mempool_free(mp, ptr);
    }
    return new_ptr;
}

void mempool_free(MemPool *mp, void *ptr) {
    if (!ptr) return;
    MemBlockHeader *block = ((MemBlockHeader *)ptr) - 1;
    block->free = 1;

    // Coalesce adjacent free blocks
    MemBlockHeader *curr = mp->first;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += sizeof(MemBlockHeader) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

size_t mempool_bytes_used(MemPool *mp) {
    size_t used = 0;
    MemBlockHeader *curr = mp->first;
    while (curr) {
        if (!curr->free) used += curr->size;
        curr = curr->next;
    }
    return used;
}

size_t mempool_bytes_total(MemPool *mp) {
    return mp->pool_size;
}
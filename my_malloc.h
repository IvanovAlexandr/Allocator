//
// Created by alexandr on 03.10.16.
//

#ifndef LAB1_MY_MALLOC_H
#define LAB1_MY_MALLOC_H



#include <stdint-gcc.h>
/** Header structure for linear buffer. */
typedef struct _Buffer {

    uint8_t *mem;       /*!< Pointer to buffer memory. */
    uint32_t totalSize; /*!< Total size in bytes. */
} Buffer;

typedef  struct _HeaderBlock {
    uint8_t high_header;
    uint8_t low_header;


} HeaderBlock;

void print_all_mem();
void init_malloc(uint32_t totalSize);
void *mem_alloc(uint8_t size);
void *mem_realloc(void *addr, uint8_t size);
void mem_free(void *addr);


#endif //LAB1_MY_MALLOC_H

//
// Created by alexandr on 03.10.16.
//


#include <cstdio>
#include <iostream>
#include "unistd.h"
#include "my_malloc.h"
/** Header structure for linear buffer. */

Buffer buf;


void print_all_mem() {
    uint8_t *addr = buf.mem;
    for (int i = 1; i <= buf.totalSize; i++) {
        std::cout << (int)*addr << "  ";
        addr++;
        if (i % 16 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}


void init_malloc(uint32_t totalSize) {
    void* mem = malloc(totalSize);
    buf = {(uint8_t*) mem, totalSize};
    uint8_t *addr = buf.mem;
    for (int i = 0; i < buf.totalSize; i = i + 4) {
        *(addr+1) = 0b00000001;
        addr += 4;
    }
}


void* mem_alloc(uint8_t size) {
    if (size > 508) {
        return NULL;
    }

    size += 2;
    if (size % 4 != 0) {
        size += 4 - (size % 4);
    }

    uint8_t *addr = buf.mem;
    uint8_t high_header;
    uint8_t *mem_addr = NULL;
    uint32_t prev_size = 0;
    uint32_t current_size = 0;
    int i = 0;

    while (i < buf.totalSize)
    {
        high_header = (uint8_t) (*addr & 0b10000000);
        uint8_t low_header = *(addr+1);
        low_header = (uint8_t) (low_header & 0b01111111);

        if (high_header == 128) {
            prev_size = low_header;
            current_size = 0;
            mem_addr = NULL;
        } else {
            if (current_size == 0)
                mem_addr = addr;

            current_size +=(low_header * 4);
            if (current_size >= size) {
                break;
            }
        }
        addr += (low_header * 4);
        i+=(low_header * 4);
    }
    if (mem_addr != NULL) {
        HeaderBlock block;
        block.high_header =  0b10000000;
        block.high_header += prev_size;
        block.low_header = (uint8_t) ((size / 4));
        *mem_addr = block.high_header;
        mem_addr++;
        *mem_addr = block.low_header;
        mem_addr++;
    }
    return mem_addr;
}


void mem_free(void *addr) {
    uint8_t *ptr = (uint8_t *) addr;
    uint8_t high_header = *(ptr-2);
    high_header = (uint8_t) (high_header & 0b01111111);
    *(ptr-2) = high_header;
}


void *mem_realloc(void *addr, uint8_t size){
    if (size > 508) {
        return NULL;
    }

    uint8_t *ptr = (uint8_t *) addr;

    uint8_t current_size = (uint8_t) (*(ptr-2) & 0b01111111);
    if (current_size > size) {
        uint8_t *new_addr = (uint8_t *) mem_alloc(size);
        if (new_addr != NULL) {
            for (int i = 0; i < size; i++) {
                *(new_addr + i) = *(ptr + i);
            }
            *(ptr - 2) = (uint8_t) (*(ptr-2) & 0b01111111);;
        }
        else {
            *(ptr-2) = (uint8_t) (*(ptr - 2) - current_size + size);;
            return  ptr;
        }
        return new_addr;
    } else {
        *(ptr - 2) = (uint8_t) (*(ptr-2) & 0b01111111);
        uint8_t *new_addr = (uint8_t *) mem_alloc(size);
        if (new_addr != NULL) {
            for (int i = 0; i < current_size; i++) {
                *(new_addr + i) = *(ptr + i);
            }
        }
        else {
            *(ptr - 2) = (uint8_t) (*(ptr-2) | 0b10000000);
            return  NULL;
        }
        return new_addr;
    }
}
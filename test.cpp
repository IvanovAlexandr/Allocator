/*
    @file test.cpp
    @brief Test for memory allocator
    @author Alexandr Ivanov (alexandr.ivanov.1995@gmail.com)
*/

#include <iostream>
#include "my_malloc.h"

#define SIZE  128


int main() {

    init_malloc(SIZE);
    //print_all_mem();
    std::cout << "Hello, World!" << std::endl;

    //print_mem();
    char* ptr = (char *) mem_alloc(14);

    //print_mem();
    print_all_mem();
    char* ptr2 = (char *) mem_alloc(33);
    print_all_mem();
    char* ptr3 = (char *) mem_alloc(2);
    print_all_mem();
    mem_free(ptr2);
    print_all_mem();
    char* ptr4 = (char *) mem_alloc(4);
    print_all_mem();
    char* ptr5 = (char *) mem_alloc(4);
    print_all_mem();

    char* ptr6 = (char *) mem_alloc(8);

    *ptr6 = 100;
    *(ptr6+1) = (char) 232;
    *(ptr6+2) = 'C';

    print_all_mem();
    mem_free(ptr4);
    mem_free(ptr5);
    print_all_mem();
    char* ptr7 = (char *) mem_alloc(8);
    print_all_mem();
    char* ptr8 = (char *) mem_alloc(2);
    print_all_mem();
    mem_free(ptr8);
    print_all_mem();
    mem_realloc(ptr6, 2);
    print_all_mem();
    return 0;
}
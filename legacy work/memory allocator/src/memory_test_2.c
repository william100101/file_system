#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"

int main(int argc, char*argv[]) {

    //init allocator
    int r = allocator_init(500);
    if (r == -1) {
        printf("allocate init failed\n");
        exit(1);
    }

    //trying alloc
    void *i = allocate(10);  // size of an int is 4 bytes


    void *j = allocate(20);  // size of an int is 4 bytes

    void *k = allocate(30);  // size of an int is 4 bytes


    printf("%p\n", i);

    deallocate(i);
}
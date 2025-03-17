#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "dlist.h"

struct allocator{
    struct dlist *allocatedList;
    struct dlist *freeList;
};

int allocator_init(size_t size); 

void *allocate (size_t size, int algorithm); 

int deallocate(void *ptr); 

void *first_fit(size_t size);

void *best_fit(size_t size);

void *worst_fit(size_t size);

/*
This function computes average fragementationby taking the largest free memory block and dividing it by total free memory
*/
double average_frag();

#endif
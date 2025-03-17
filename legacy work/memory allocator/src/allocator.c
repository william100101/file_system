#include "allocator.h"
#include "dlist.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

//globals
struct allocator *memory;

int allocator_init(size_t size){ //M IS SIZE AT INIT
    memory = malloc(sizeof(struct allocator));
    
    memory->allocatedList = dlist_create();
    memory->freeList = dlist_create();

    void *ptr = malloc(size);// arbitrary
    dlist_add_front(memory->freeList, ptr, size); // no data at this point

    return 1;
}


void *allocate (size_t size, int algorithm){ //should return a void pointer which can be used later for deallocate

    void *ret_ptr;

    if(algorithm == 0){
        ret_ptr = first_fit(size);
    }
    else if(algorithm == 1){
        ret_ptr = best_fit(size);
    }
    else if(algorithm == 2){
        ret_ptr = worst_fit(size);
    }
    else{
        printf("invalid input\n");
    }

    

    return ret_ptr;
}

void *first_fit(size_t size){
  
    char *str;
    void *ret_ptr;

    for (str = dlist_iter_begin(memory->freeList); str != NULL;
        str = (char *) dlist_iter_next(memory->freeList))	{ 
        
        
        //printf("[");
		//printf((memory->freeList)->iter->data);
		//printf(", %ld", *(memory->freeList)->iter->memory);
		//printf("]--");
        
        
        if(*(memory->freeList)->iter->memory >= size){
            //adjust allocated
            ret_ptr = malloc(size);
            
            dlist_add_front(memory->allocatedList, ret_ptr, size);

            //adjust free
            *((memory->freeList)->iter->memory) = *((memory->freeList)->iter->memory)- size;


            printf("%p\n", ret_ptr);
            return ret_ptr;
        }
        
    }
}


int deallocate(void *ptr){ //working
  
    printf("%p\n", ptr);

    size_t size = dlist_find_memory(memory->allocatedList, ptr); //working

    dlist_add_front(memory->freeList, ptr, size);

    dlist_find_remove((memory->allocatedList), ptr);

    return 1;

}



void *best_fit(size_t size){
  
  
    char *str;
    void *ret_ptr;

    void *current_min_node;
    size_t current_min_memory = 999;


    for (str = dlist_iter_begin(memory->freeList); str != NULL;
        str = (char *) dlist_iter_next(memory->freeList))	{ 
        
        
        //printf("[");
		//printf((memory->freeList)->iter->data);
		//printf(", %ld", *(memory->freeList)->iter->memory);
		//printf("]--");
        
        
        if((*(memory->freeList)->iter->memory >= size) && *(memory->freeList)->iter->memory <= current_min_memory){
            current_min_node = (memory->freeList)->iter->data;
            current_min_memory = *(memory->freeList)->iter->memory;
        }
        
    }
    
    ret_ptr = malloc(size);
            
    dlist_add_front(memory->allocatedList, ret_ptr, size);

    //adjust free
    dlist_find_memory_reduce(memory->freeList, current_min_node, size); //CHECK THIS


    return ret_ptr;

}

void *worst_fit(size_t size){
    
    char *str;
    void *ret_ptr;

    void *current_max_node;
    size_t current_max_memory = 0;


    for (str = dlist_iter_begin(memory->freeList); str != NULL;
        str = (char *) dlist_iter_next(memory->freeList))	{ 
        
        
        //printf("[");
		//printf((memory->freeList)->iter->data);
		//printf(", %ld", *(memory->freeList)->iter->memory);
		//printf("]--");
        
        
        if((*(memory->freeList)->iter->memory >= size) && *(memory->freeList)->iter->memory >= current_max_memory){
            current_max_node = (memory->freeList)->iter->data;
            current_max_memory = *(memory->freeList)->iter->memory;
        }
        
    }
    
    ret_ptr = malloc(size);
            
    dlist_add_front(memory->allocatedList, ret_ptr, size);

    //adjust free
    dlist_find_memory_reduce(memory->freeList, current_max_node, size); //CHECK THIS

    return ret_ptr;

}

double average_frag(){
    int total_mem;
    int max_free = 0;

    double average_frag;

    char *str;

    for (str = dlist_iter_begin(memory->freeList); str != NULL;
        str = (char *) dlist_iter_next(memory->freeList))	{ 
        
        //getting total free mem
        total_mem = total_mem + (*(memory->freeList)->iter->memory);

        //getting max
        if(*(memory->freeList)->iter->memory >= max_free){

            max_free = *(memory->freeList)->iter->memory;
        }
    }

    printf("%d", total_mem);
    

    average_frag = ((total_mem-max_free)/total_mem) * 100;

    return average_frag;
}
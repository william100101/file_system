/*
 * Copyright (c) 2012 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>

#include "dnode.h"
#include "dlist.h"

struct dlist * //no change
dlist_create() {
	return calloc(1, sizeof(struct dlist));
}

void 
dlist_destroy(struct dlist *l) {
	struct dnode *p = l->front;

	do {
		l->front = l->front->next;
		free(p->data);

		// new
		//free(p->memory);
		
		free(p);
		p = l->front;
	} while (l->front != NULL);

	l->front = l->back = NULL;
	l->counter = 0;
}


void //no change
dlist_obliterate(struct dlist *l) {
	dlist_destroy(l);
	free(l);
}

void 
dlist_add_front(struct dlist *l, void *ptr, size_t memory) {
	struct dnode *n = dnode_create();
	
	n->data = ptr;
	
	//new
	n->memory = malloc(memory);
	*(n->memory) = memory;

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->next = l->front;
		l->front->prev = n;
		l->front = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
#endif /* DEBUG */
}

void 
dlist_add_back(struct dlist *l, void *ptr, size_t memory) {
	struct dnode *n = dnode_create();
	n->data = ptr;

	//new
	n->memory = &memory;

	if (0 == l->counter) {
		l->front = l->back = n;	
		l->counter = 1;
	} else {
		n->prev = l->back;
		l->back->next = n;
		l->back = n;
		(l->counter)++;
	}

#ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
#endif /* DEBUG */
}

void * //no change
dlist_remove_front(struct dlist *l) {
	struct dnode *n = l->front;
	void* ptr = n->data;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->front = l->front->next;
		l->front->prev = NULL;
	}

	(l->counter)--;
	free(n);
	return ptr;
}

void * //no change
dlist_remove_back(struct dlist *l) {
	struct dnode *n = l->back;
	void *ptr = n->data;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->back = l->back->prev;
		l->back->next = NULL;
	}

	(l->counter)--;
	free(n);
	return ptr;
}

void *
dlist_find_remove(struct dlist *l, void *ptr) { //add size removal
	struct dnode *n = l->front;
	void *ret_ptr = NULL;

	while ((n != NULL) && (n->data != ptr)) {
	  n = n->next;
	}

	if (n != NULL) {
	  if (l->front == n) {
	    return dlist_remove_front(l);
	  } else if (l->back == n) {
	    return dlist_remove_back(l);
	  } else {
	    if (1 == l->counter) {
	      l->front = l->back = NULL;
	    } else {
	      n->prev->next = n->next;
	      n->next->prev = n->prev;
	    }
	    (l->counter)--;
	  }
	  
	  ret_ptr = n->data;
	  free(n);
	}
	
	return ret_ptr;
}

uint32_t //no change
dlist_num_elems(struct dlist *l) {
	return l->counter;
}

void * //no change
dlist_iter_begin(struct dlist *l) {
	void *ret_val = NULL;

	l->iter = l->front;
	if (l->iter != NULL) {
		ret_val = l->iter->data; 
	}

	return ret_val;
}

void *
dlist_iter_next(struct dlist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->next;
		if (l->iter != NULL) {
			ret_val = l->iter->data;
		}
	}

	return ret_val;
}

bool 
dlist_iter_has_next(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->next != NULL);
	}

#ifdef DEBUG
	if (ret_val) {
		printf("dlist_has_next: current is %s\n", (char *) l->iter->data);
		printf("dlist_has_next: returning %d\n\n", ret_val);
	}
#endif /* DEBUG */

	return ret_val;
}


void *
dlist_iter_end(struct dlist *l) {
	void *ret_val = NULL;

	l->iter = l->back;
	if (l->iter != NULL) {
		ret_val = l->iter->data;
	}

	return ret_val;
}

void *
dlist_iter_prev(struct dlist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->prev;
		if (l->iter != NULL) {
			ret_val = l->iter->data;
		}
	}

	return ret_val;
}

bool 
dlist_iter_has_prev(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->prev != NULL);
	}

	return ret_val;
}

void
traverse_forward(struct dlist *l) {
  char *str;
  printf("forward traversal\n");
  for (str = dlist_iter_begin(l); str != NULL;
       str = (char *) dlist_iter_next(l))	{ 
    printf("string = %s\n", str);
  }
}

void
traverse_backward(struct dlist *l) {
  char *str;
  printf("backward traversal\n");
  for (str = dlist_iter_end(l); str != NULL;
       str = (char *) dlist_iter_prev(l))	{ 
    printf("string = %s\n", str);
  }
}

void
dlist_print(struct dlist *l){
	printf("dlist: -");
	char *str;

  for (str = dlist_iter_begin(l); str != NULL;
       str = (char *) dlist_iter_next(l))	{ 
		printf("[");
		printf(l->iter->data);
		printf(", %zu", *l->iter->memory);
		printf("]--");
  }

	printf("-");
}

//NEW
size_t dlist_find_memory(struct dlist *l, void *ptr){

	char *str;
	size_t size;

  	for (str = dlist_iter_begin(l); str != NULL;
       	str = (char *) dlist_iter_next(l))	{ 
		
		if(l->iter->data == ptr){
			size = *(l->iter->memory);
			return size;
		}

  	}

	return -1;
}


//NEW
void dlist_find_memory_reduce(struct dlist *l, void *ptr, size_t size){

	char *str;

  	for (str = dlist_iter_begin(l); str != NULL;
       	str = (char *) dlist_iter_next(l))	{ 
		
		if(l->iter->data == ptr){
			*(l->iter->memory) = *(l->iter->memory) - size;
		}

  	}

	return -1;
}
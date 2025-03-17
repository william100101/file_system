/*
 * Test some basic memory allocatino functions.
 * CSCI 315
 * For lab checks.
 */
#include <stdio.h>
#include <stdlib.h>

#include "allocator.h"

#define N 10   // number of trials

int main(int argc, char*argv[]) {
  
  int algorithm = atoi(argv[1]);
  int seed = atoi(argv[2]);
  int requests = atoi(argv[3]);

  int r = 0;
  void *p = NULL;

  int all = allocator_init(10240);
  if (all == -1) {
    printf("allocate init failed\n");
    exit(1);
  }

  srandom(seed);

  while(r < requests){

    int s = random() % (1001 - 100) + 100;
    p = allocate(s, algorithm);

    deallocate(p);

    p = NULL;
    r += 1;
  }

  double fragmentation = average_frag();
  printf("%f\n", fragmentation);

  return 0;
}

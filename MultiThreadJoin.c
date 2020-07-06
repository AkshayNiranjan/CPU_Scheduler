#include <stdio.h>
#include <stdlib.h>
#include "my_pthread.h"

#define EXTRA_THREADS 6

void thread_run(){
  int x = 0;
  for(x = 0; x < 500000; x++){
    printf("Thread %d Running\n", my_pthread_self());
  }
  printf("Thread %d Finished", my_pthread_self());
  my_pthread_exit();
}


int main(){
  int x;

  my_pthread_t threads[EXTRA_THREADS];

  for(x = 0; x < EXTRA_THREADS; x++){
    my_pthread_create(&threads[x], (void*) thread_run, (void*) NULL);
  }

  for(x = 0; x < 9; x++){
    my_pthread_join(threads[x]);
  }

  printf("Main Thread Resuming\n");

  printf("Main Ehread Exitting\n");
}

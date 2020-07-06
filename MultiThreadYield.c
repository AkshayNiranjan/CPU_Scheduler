#include <stdio.h>
#include <stdlib.h>
#include "my_pthread.h"

#define EXTRA_THREADS 6

void thread_run(){
  int x;
  for(x = 0; x < 20; x++){
    printf("Thread %d Running\n", my_pthread_self());
    my_pthread_yield();
  }
  printf("Thread %d Finished\n", my_pthread_self());
  my_pthread_exit();
}


int main(){
  int x,y;

  my_pthread_t threads[EXTRA_THREADS];

  for(x = 0; x < EXTRA_THREADS; x++){
    my_pthread_create(&threads[x], (void*) thread_run, (void*) NULL);
  }

  for(y = 0; y < 21; y++){
    printf("Main Thread Running\n");
    my_pthread_yield();
  }

  printf("Main Thread Resuming\n");

  printf("Main Thread Exitting\n");

}

#include <stdio.h>
#include <stdlib.h>
#include "my_pthread.h"

#define EXTRA_THREADS 3

void thread_run(){
  while(1){
    printf("Thread %d Running\n", my_pthread_self());
  }
}

int main(){
  int x;

  my_pthread_t threads[EXTRA_THREADS];

  for(x = 0; x < EXTRA_THREADS; x++){
    my_pthread_create(&threads[x], (void*)thread_run, (void*)NULL);
  }

  while(1){
    printf("Main Thread Running\n");
  }

}

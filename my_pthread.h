#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <ucontext.h>

#define STACKSIZE 32768
#define TIME_QUANTUM_MS 500000 // Time quantum in microseconds

/* Thread ID */
typedef uint my_pthread_t;

/* Thread Status Enum */
typedef enum threadStatus {
	RUNNABLE,   // Thread can be run
  SLEEP,      // Thread is currently asleep
	FINISHED    // Thread has finished execution
} status_t;

/*  Thread Contol Block */
typedef struct threadControlBlock{
  my_pthread_t tid;   // Thread ID
  status_t status;    // Thread Status
  ucontext_t context; // Ucontext
  struct threadControlBlock* next;
} my_pthread_tcb;

struct tCB{
	struct threadControlBlock* slept;
	struct threadControlBlock* slept_on;
  struct tCB* next;
};

/* Function Declarations */
void my_pthread_create(my_pthread_t *thread, void*(*function)(void*), void *arg);

my_pthread_t my_pthread_self();

void my_pthread_yield();

void my_pthread_exit();

void my_pthread_join(my_pthread_t thread);

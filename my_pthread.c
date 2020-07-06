#include "my_pthread.h"

/* Scheduler State */
my_pthread_t TID=0;
//circly linked list
struct threadControlBlock* r_tail=NULL;
//circly linked list to contain the threadControlBlock
struct tCB* s_tail=NULL;
//node for thread currently running
struct threadControlBlock* execute=NULL;



/* Scheduler Function
 * Pick the next runnable thread and swap contexts to start executing
 */
typedef enum scheduler_status{
  OFF,
  ON
}sched;

sched s=OFF;

void executeToReady(){
  if(r_tail!=NULL){
    execute->next=r_tail->next;
    r_tail->next=execute;
    r_tail=execute;
    execute=NULL;
  }
  else{
    execute->next=execute;
    r_tail=execute;
    execute=NULL;
  }
}


void readyToExecute(){
  if(r_tail!=NULL){
    execute=r_tail->next;
    if(r_tail->next==r_tail){
      r_tail=NULL;
    }
    else{
      r_tail->next=r_tail->next->next;
    }
  }
}

void schedule(int signum){
  if(signum==SIGPROF){
    if(execute!=NULL) {
      if(execute->status==RUNNABLE){
        //swap context first
        //swap execute and r_tail->next
	executeToReady();
        readyToExecute();
        swapcontext(&r_tail->context, &execute->context);
      }
      else{
        if(execute->status==FINISHED){
          //check sleep
          if(s_tail!=NULL){
            struct tCB* temp=s_tail->next;
            struct tCB* before=s_tail;
            while(temp!=s_tail && temp->slept_on!=execute){
              before=temp;
              temp=temp->next;
            }
            if(temp->slept_on==execute){
              temp->slept->status=RUNNABLE;
              if(before==temp){
                if(s_tail==temp){

                }
                free(s_tail);

              }
              else{

              }
            }
          }
	  
          struct threadControlBlock* temp = execute;
          execute = NULL;
          readyToExecute();
          swapcontext(&temp->context, &execute->context);
          //swap context first
          //swap execute and r_tail->next
        }
      }
    }

  }
  else{
    printf("%d\n",signum);
    printf("Error: Akshay Fucked Up Our Code\n");
  }
}



void addToReady(my_pthread_tcb * node) {
  if( r_tail == NULL) {
    r_tail = node;
    r_tail -> next = r_tail;
  } else {
    node->next = r_tail -> next;
    r_tail -> next = node;
    r_tail = node; 
  }
}

/* Create a new TCB for a new thread execution context and add it to the queue
 * of runnable threads. If this is the first time a thread is created, also
 * create a TCB for the main thread as well as initalize any scheduler state.
 */
void my_pthread_create(my_pthread_t *thread, void*(*function)(void*), void *arg){
  my_pthread_tcb * newtcb = (my_pthread_tcb *) malloc(sizeof(my_pthread_tcb));
  newtcb->tid = ++TID;
  *thread = TID;
  newtcb->status = RUNNABLE;
  if(!getcontext(&newtcb->context)) {
    printf("Get New Context Successful\n");
  } else {
    printf("Get New Context Failed\n");
  }
  newtcb->context.uc_link = 0; 
  newtcb->context.uc_stack.ss_sp=malloc(STACKSIZE);
  newtcb->context.uc_stack.ss_size=STACKSIZE;
  newtcb->context.uc_stack.ss_flags=0;
  addToReady(newtcb);
  makecontext(&newtcb->context,(void *)function, 0);
  printf("New Thread Created: TID = %d\n", newtcb->tid);  


  if(s==OFF){
    s=ON;

    struct itimerval it_val;
    signal(SIGPROF, schedule);
    
    it_val.it_value.tv_sec = 0;
    it_val.it_value.tv_usec = 500000;
    it_val.it_interval = it_val.it_value;
    if (setitimer(ITIMER_PROF, &it_val, NULL) == -1) {
      printf("Error Calling Settimer\n");
      exit(0);
    } else {
      printf("Set timer\n");
    }

    execute = (my_pthread_tcb *) malloc(sizeof(my_pthread_tcb));
    execute->tid = 0;
    execute->status = RUNNABLE;
    if(!getcontext(&execute->context)) {
      printf("Create Main Context Successful\n");
    } else {
      printf("Create Main Context Failed\n");
    }
    execute->context.uc_link = 0; 
    execute->context.uc_stack.ss_sp=malloc(STACKSIZE);
    execute->context.uc_stack.ss_size=STACKSIZE;
    execute->context.uc_stack.ss_flags=0;
    printf("Main Thread Created: TID = %d\n", execute->tid);
  }
  
}







/* Give up the CPU and allow the next thread to run.
 */
void my_pthread_yield(){

  schedule(SIGPROF);
}

/* The calling thread will not continue until the thread with tid thread
 * has finished executing.
 * needs to be changed, he said it was a one line check after identifying node and calling schedular??
 */
void my_pthread_join(my_pthread_t thread){
  //replace my_pthread_tcb with whatever the head of the linked list is
  /*
  struct threadControlBlock* temp = &my_pthread_tcb;
  if(temp==NULL){
    return;
  }
  if(temp->tid==thread){
    while(temp->status!=FINISHED){}
    my_pthread_tcb=my_pthread_tcb->next;
    return;
  }
  while(temp->next!=NULL && temp->tid!=thread){
    temp=temp->next;
  }
  if(temp->next!=NULL){
    while(temp->next->status!=FINISHED){}
    temp->next=temp->next->next;
  }
  */
}


/* Returns the thread id of the currently running thread
 */
my_pthread_t my_pthread_self(){

  // Implement Here //

  return execute->tid;  // temporary return, replace this

}

/* Thread exits, setting the state to finished and allowing the next thread
 * to run.
 */
void my_pthread_exit(){

  // Implement Here //
  execute->status = FINISHED;
  schedule(SIGPROF);
  //just set status to finished and call schedule(SIGALRM)
  //the scheduler will take care of it.
}

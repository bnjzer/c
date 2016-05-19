#include<stdio.h>
#include<stdlib.h>
#include "pthread.h"
#include <sys/types.h>
#include <unistd.h>

#define pthread_attr_default NULL

void print_message(void *ptr){
  char *msg;
  msg = (char *) ptr;
  printf("pthread %ld (PID %d). Message: %s\n", pthread_self(), getpid(), msg);
}

int i;

void sum(){
  i += 10;
  printf("thread: i is %d\n", i);
  i += 20;
  printf("thread: i is %d\n", i);
}

int main(int argc, char **argv){
  pthread_t thread;
   i=0; 

  if(pthread_create(&thread, pthread_attr_default, (void*) sum, NULL) == -1)
    perror("Problem while creating thread\n");

  i += 1000;
  printf("processus: i is %d\n", i);
  i += 2000;
  printf("processus: i is %d\n", i);

  pthread_join(thread, NULL);

  /*pthread_t thread1, thread2;; 
  char *msg1 = "ooonnneeee";
  char *msg2 = "tttwwwooo";
  int iret1, iret2;

  iret1 = pthread_create(&thread1, pthread_attr_default, print_message, (void*) msg1);   
  iret2 = pthread_create(&thread2, pthread_attr_default, print_message, (void*) msg2);   
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Thread 1 returns %d\n", iret1);
  printf("Thread 2 returns %d\n", iret2);*/

  return 0;
}

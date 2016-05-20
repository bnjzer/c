#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>

#define pthread_attr_default NULL

int i;

void somme(){
  i += 10;
  printf("son: i is %d (PID: %d)\n", i, getpid());
  i += 20;
  printf("son: i is %d (PID: %d)\n", i, getpid());
}

int main(int argc, char **argv){
  int pid;
  i=0; 
  pid = fork();

  if(pid == 0){
    somme();
  }else{
    i += 1000;
    printf("father: i is %d (PID: %d)\n", i, getpid());
    i += 2000;
    printf("father: i is %d (PID: %d)\n", i, getpid());
    wait(NULL);
  }

  return 0;
}

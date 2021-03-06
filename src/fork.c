#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void){
  pid_t pid = fork();

  int exitStatus;
  int status;

  switch(pid){
    case -1:
      printf("An error occured while fork()\n");
      exitStatus = 1;
      break;
    case 0:
      printf("I'm the son, my PID is %d and my father PID is %d\n", getpid(), getppid());
      exitStatus = EXIT_SUCCESS;
      break;
    default:
      printf("I'm the father, my PID is %d and the one of my son is %d\n", getpid(), pid);
      waitpid(-1, &status, 0);
      printf("The son has returned with status %d\n", status);
      exitStatus = EXIT_SUCCESS;
  }

  return exitStatus;
}

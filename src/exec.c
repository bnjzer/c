#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(void){
  int exitStatus;
  int status;

  int i,j;

  printf("Donnez la valeur de i : ");
  scanf("%d", &i);
  printf("Donnez la valeur de j : ");
  scanf("%d", &j);

  pid_t pid = fork();

  switch(pid){
    case -1:
      printf("An error occured while fork()\n");
      exitStatus = 1;
      break;
    case 0:
      printf("I'm the son, my PID is %d and my father PID is %d\n", getpid(), getppid());
      char conv1[10], conv2[10];
      sprintf(conv1, "%d", i);
      sprintf(conv2, "%d", j);
      execl("./bin/calculer", "Calcul", conv1, conv2, NULL);
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

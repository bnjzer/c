/* a zombie is a process that ended its execution and is waiting for its father to take it into account */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char **argv){
  pid_t child_pid = fork();

  if(child_pid  == 0){
    printf("I'm the son. Finished\n");
  } else {
    printf("We're in parent, waiting for 1 minute...\n");
    sleep(60);
  }
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  int p[2], status;
  pid_t ret;
  char chaine[7];

  pipe(p);
  ret = fork();

  if(ret == 0){
    // Le fils écrit dans le tube

    close(p[0]); // pas de lecture

    write(p[1], "Bonjour", 7);
    close(p[1]);
    exit(0);
  } else {
    // Le père lit le tube

    close(p[1]); // pas d'écriture dans le tube
   
    read(p[0], chaine, 7);
    close(p[0]);
    printf("Message received: %s\n", chaine);
    wait(&status);
  }

  return 0;
}

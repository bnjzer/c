#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  mode_t mode;
  int tub;

  mode = S_IRUSR | S_IWUSR;

  // création du utbe nommé
  mkfifo("fictub", mode);

  // ouverture tube
  tub = open("fictub", O_WRONLY);

  printf("tube opened\n");

  // écriture dans le tube
  write(tub, "0123456789", 10);
  
  printf("written\n");

  // fermeture tube
  close(tub);

  return 0;
}

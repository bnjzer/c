#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
  char zone[10];
  int tub;

  // ouverture tube
  tub = open("fictub", O_RDONLY);

  printf("tube opened\n");

  // lecture dans tube
  read(tub, zone, 10);
  zone[10]=0;
  printf("lu dans le tube : %s\n", zone);

  // fermeture tube
  close(tub);

  return 0;
}

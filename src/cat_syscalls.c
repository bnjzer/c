#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include <unistd.h>

#define BUFFSIZE 100

int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(1);
  }

  int fd;
  if((fd = open(argv[1], O_RDONLY)) == -1){
    fprintf(stderr, "Error while opening %s\n", argv[1]);
    exit(1);
  }

  char buf[BUFFSIZE];
  int n;

  while((n = read(fd, buf, BUFFSIZE)) > 0)
    if(write(STDOUT_FILENO, buf, n) != n){
      fprintf(stderr, "Error while displaying file %s\n", argv[1]);
      exit(1);
    }

  return 0;
}

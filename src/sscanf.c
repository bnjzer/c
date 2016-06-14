#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
  if(argc != 3){
    printf("Error, required 2 args\n");
    return 1;
  }

  int i,j;
  sscanf(argv[1], "%d", &i);
  sscanf(argv[2], "%d", &j);
  printf("sum is %d\n", i+j);
  return 0;
}

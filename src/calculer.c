#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
  if(argc != 3){
    printf("Error, required 2 args\n");
    return 1;
  }

  int i,j;
  i = atoi(argv[1]);
  j = atoi(argv[2]);
  printf("sum is %d\n", i+j);
  return 0;
}

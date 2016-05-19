#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libgetline2.h"

#define MAXLINE 100

int main(int argc, char *argv[]){
  char line[MAXLINE];
  int c, except = 0, number = 0, found = 0;
  long lineno=0;
  
  while(--argc > 0 && (*++argv)[0] == '-'){
    while((c = *++argv[0])){
      switch(c){
        case 'x':
          except = 1;
          break;
        case 'n':
          number = 1;
          break;
        default:
          printf("illegal option: %c\n", c);
          argc = 0;
          found = -1;
          break;
      }
    }
  }

  if(argc != 1)
    printf("usage...\n");
  else{
    while(getline2(line, MAXLINE) > 0){
      lineno++;
      if((strstr(line, *argv) != NULL) != except){
        if(number)
          printf("%ld: ", lineno);
        printf("%s\n", line);
        found++;
      }
    }
  }
  return found;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "libgetline2.h"

#define MAXLINE 100

int main(int argc, char *argv[]){
  int tail = 0;
  int nbLines = 0;

  if(argc != 1 && argc != 3){
    printf("usage\n");
    return 1;
  }

  if(argc == 3 && **++argv == '-' && *++*argv == 'n'){
    ++argv;        
    while(isdigit(**argv)){
      tail = tail * 10 + **argv - '0';
      ++(*argv);
    }
  }

  if(!tail) tail = 10;

  printf("tail : %d\n", tail);

  char lines[tail*MAXLINE];
  char *linesptr[tail];

  int i;
  for(i=0;i<tail;i++){
    linesptr[i] = lines + i*MAXLINE;
  }

  i=0;
  while(getline2(linesptr[i++], MAXLINE) > 0){
    if(i==tail) i=0;
    nbLines++;
  }
  
  int min = nbLines > tail ? tail : nbLines;
  
  printf("min : %d\n", min);
int j;
  for(j=i-1; j<min; j++){
      printf("%s\n",linesptr[j]);
  }
  for(j=0; j<i-1; j++){
      printf("%s\n",linesptr[j]);
  }

  return 0;
}

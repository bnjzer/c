#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char **argv){
  int lower = 1;
  int c;

  if(!(argc == 2 && (strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "-l") == 0))){
    printf("usage: %s <mode>\n  mode : -u : uppercase\n         -l : lowercase\n", argv[0]);
    return 1;
  }

  if(!strcmp(argv[1], "-u"))
    lower = 0;

  while((c = getchar()) != EOF)
    if(lower)
      putchar(tolower(c));
    else
      putchar(toupper(c));

  return 0;
}

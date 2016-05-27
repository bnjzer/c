#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include "libgetch.h"

#define MAXWORD 100

int getword(char *word){
  int lim = MAXWORD;
  int c;
  char *w = word;

  while(isspace(c = getch()))
    ;

  if(c != EOF){
    *w++ = c;
  }

  if(!isalpha(c)) { // hiiii
    *w = '\0';
    return c;
  }

  for( ; --lim > 0; w++){
    if(!isalnum(*w = getch())){
      ungetch(*w);
      break;
    }
  }

  *w = '\0';
  return word[0];
}

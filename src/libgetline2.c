#include<stdio.h>

int getline2(char *s, int lim){
  int c,i;

  for(i=0; i<lim-1 && (c=getchar()) != EOF && c!= '\n'; i++){
    *(s+i)=c;
  }

  if(c == '\n'){
    *(s+i)='\0';
    ++i;
  }

  return i;
}

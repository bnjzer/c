#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "libgetch.h"

#define MAXWORD 100

struct key {
  char* word;
  int count;
} keytab[] = {
  {"char", 0},
  {"define", 0},
  {"else", 0},
  {"if", 0},
  {"include", 0},
  {"int", 0},
  {"for", 0},
  {"return", 0},
  {"size_t", 0},
  {"struct", 0},
  {"while", 0}
};

#define NKEYS (sizeof keytab/sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);

int main(int argc, char **argv){

  int n;
  char word[MAXWORD];

  while(getword(word, MAXWORD) != EOF){
    if(isalpha(word[0]))
      if((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
    if(strcmp(word, "\n"))
      printf("saut de ligne\n");
  }
  
  for(n=0; n < NKEYS; n++)
    if(keytab[n].count > 0)
      printf("%s: %d \n", keytab[n].word, keytab[n].count);
  
  size_t sizeInt = sizeof(int); 
  size_t sizeChar = sizeof(char);
  printf("size of int : %ld\n", sizeInt);
  printf("size of char : %ld\n", sizeChar);

  return 0;
}

int binsearch(char *word, struct key tab[], int n){
  int cond;
  int low, high, mid;

  low = 0;
  high = n-1;

  while(low <= high){
    mid = (low + high) / 2;
    if((cond = strcmp(word, tab[mid].word)) < 0){
      high = mid - 1;
    } else if(cond > 0){
      low = mid + 1;
    } else {
      return mid;
    }
  }

  return -1;
}

int getword(char *word, int lim){
  int c;
  char *w = word;

  while(isspace(c = getch()))
    ;
  
  if(c != EOF){
    *w++ = c;
  }

  if(!isalpha(c)) {
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

// TODO: properly handle _, string constants, comments, preprocessor lines

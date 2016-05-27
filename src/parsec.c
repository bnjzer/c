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

int nbPreprocess = 0;
int nbOneLineComments = 0;
int nbSeveralLineComments = 0;
int nbStringConstants = 0;

// hmm

#define NKEYS (sizeof keytab/sizeof keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int); /* blabla */

/**** this 
 * is 
 * the  
 * main *******/

int main(int argc, char **argv){

  int n;
  char word[MAXWORD];

  word[0] = '\n';

  while(getword(word, MAXWORD) != EOF){
    if(isalpha(word[0])){
      if((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
    } 
  }

  for(n=0; n < NKEYS; n++)
    if(keytab[n].count > 0)
      printf("%s: %d \n", keytab[n].word, keytab[n].count);
  printf("preprocessing: %d\n", nbPreprocess);
  printf("comments one line: %d\n", nbOneLineComments);
  printf("comments several line: %d\n", nbSeveralLineComments);
  printf("string constants: %d\n", nbStringConstants);

  size_t sizeInt = sizeof(int);  // just to test _
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

// skip spaces, returns the first symbol, and if first symbol is letter returns all following letters/numbers
int getword(char *word, int lim){
  int c;
  char *w = word;

  while(isblank(c = getch()))
    ;

  if(*w == '\n'){
    if(c == '#'){
      while((c = getch()) != '\n')
        ;
      ungetch(c);
      nbPreprocess++;
      return word[0];
    }
  }

  if(c == '/'){
    if((c=getch()) == '/'){
      while((c = getch()) != '\n')
        ;
      nbOneLineComments++;
      return word[0];
    } else if(c == '*'){
      int commentGoing = 1;
      while(commentGoing){
        while((c=getch()) != '*')
          ;
        if((c=getch()) == '/') {
          nbSeveralLineComments++;
          return word[0];
        } else
          ungetch(c);
      }
    }
  }

  if(c == '"'){
    while((c=getch()) != '"')
      ;
    nbStringConstants++;
    return word[0];
  }

  if(c != EOF){
    *w++ = c;
  }

  if(!isalpha(c)) { // hiiii
    *w = '\0';
    return c;
  }

  for( ; --lim > 0; w++){
    if(!(isalnum(*w = getch()) || *w == '_')){
      ungetch(*w);
      break;
    }
  }

  *w = '\0';
  return word[0];
}

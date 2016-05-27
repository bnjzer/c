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
struct key *binsearch(char *, struct key *, int); /* blabla */

/**** this 
 * is 
 * the  
 * main *******/

int main(int argc, char **argv){

  char word[MAXWORD];
  struct key *p;

  word[0] = '\n';

  while(getword(word, MAXWORD) != EOF){
    if(isalpha(word[0])){
      if((p = binsearch(word, keytab, NKEYS)) != NULL)
        p->count++;
    } 
  }

  for(p=keytab; p < keytab + NKEYS; p++)
    if(p->count > 0)
      printf("%s: %d \n", p->word, p->count);
  printf("preprocessing: %d\n", nbPreprocess);
  printf("comments one line: %d\n", nbOneLineComments);
  printf("comments several line: %d\n", nbSeveralLineComments);
  printf("string constants: %d\n", nbStringConstants);

  size_t keytabElt = sizeof(keytab[0]);
  printf("size of keytab element : %ld\n", keytabElt);

  return 0;
}

struct key * binsearch(char *word, struct key *tab, int n){
  int cond;
  struct key *low, *high, *mid;

  low = &tab[0];
  high = &tab[n];

  while(low < high){
    mid = low + (high - low) / 2;
    if((cond = strcmp(word, mid->word)) < 0){
      high = mid;
    } else if(cond > 0){
      low = mid + 1;
    } else {
      return mid;
    }
  }

  return NULL;
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

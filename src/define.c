#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgetword.h"

#define MAXWORD 100

#define HASHSIZE 101

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};
static struct nlist *hashtab[HASHSIZE];

#define RETURN 0
#define DEFINE "define"

char *strdup2(char *);
unsigned hash(char *s);
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
void undef(char *name);
void printHashTable(struct nlist **, int size);

int main(int argc, char **argv){
  //install("foo", "hi");
  //install("bar", "ha");
  //install("arb", "ah");
  //install("arb", "ih");
  //install("rba", "ah");
  //undef("arb");
  //undef("bar");
  //printf("\n");
  //printHashTable(hashtab, HASHSIZE);

  char word[MAXWORD];
  char name[MAXWORD];
  char defn[MAXWORD];

  while(getword(word) != EOF)
    if(strcmp(word,"#") == 0){
      if((getword(word) != EOF) && strcmp(word,DEFINE) == 0)
        if(getword(word) != EOF){
          strcpy(name, word);
          if(getword(word) != EOF){
            strcpy(defn, word);
            while(getword(word) != '\n'){
              strcat(defn, word);
            }
            install(name, defn);
          }
        }
    } else {
      struct nlist *p = (struct nlist *) malloc(sizeof(struct nlist));
      if((p = lookup(word)) != NULL)
        printf("%s", p->defn);
      else
        printf("%s", word);
    }

  return RETURN;
}

unsigned hash(char *s){
  unsigned hashval;

  for(hashval=0; *s != '\0'; s++)
    //hashval += *s + 31 * hashval;
    hashval += *s;

  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s){
  struct nlist *p;

  for(p = hashtab[hash(s)]; p != NULL; p = p->next)
    if(strcmp(p->name,s) == 0)
      return p;

  return NULL;
}

struct nlist *install(char *name, char *defn){
  struct nlist *p;
  unsigned hashval;

  if((p = lookup(name)) == NULL){ // not found
    p = (struct nlist *) malloc(sizeof(*p));
    if(p == NULL || (p->name = strdup2(name)) == NULL)
      return NULL;
    hashval = hash(name);
    p->next = hashtab[hashval];
    hashtab[hashval] = p;
  } else
    free((void *) p->defn);
  if((p->defn = strdup2(defn)) == NULL)
    return NULL;
  return p;
}

void undef(char *name){
  int h = hash(name);
  struct nlist *lastElem = NULL, *elem = hashtab[h];
  while(elem != NULL){
    if(strcmp(elem->name, name) == 0){
      if(lastElem == NULL) {
        hashtab[h] = elem->next;
      } else {
        lastElem->next = elem->next;
      }

      free(elem->name);
      free(elem->defn);
      free(elem);

      break;
    } else {
      lastElem = elem;
      elem = elem->next;
    }
  }
}

char *strdup2(char *s){
  char *cpy;
  cpy = (char *) malloc(strlen(s)+1); // returns NULL if no space left
  if(cpy != NULL)
    strcpy(cpy, s);
  return cpy;
}

void printHashTable(struct nlist ** elems, int size){
  int i;

  for(i=0; i<size; i++){
    struct nlist *elem = elems[i];
    elem = hashtab[i];
    while(elem != NULL){
      printf("%d: %s -> %s\n", i, elem->name, elem->defn);
      elem = elem->next;
    }
  }
}

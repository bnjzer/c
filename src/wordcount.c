#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include "libgetword.h"

#define MAXWORD 100

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *talloc(void);
char *strdup2(char *);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

int main(int argc, char **argv){
  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while(getword(word) != EOF){
    if(isalpha(word[0]))
      root = addtree(root, word);
  }
  treeprint(root);

  return 0;
}

struct tnode *addtree(struct tnode *p, char *w){
  int cond;

  if(p == NULL){ // it's a new word
    p = talloc(); //get addres for new node
    p->word = strdup2(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if((cond = strcmp(w, p->word)) < 0)
      p->left = addtree(p->left, w);
  else if(cond > 0)
      p->right = addtree(p->right, w);
  else
    p->count++;

  return p;
}

char *strdup2(char *s){
  char *cpy;
  cpy = (char *) malloc(strlen(s)+1); // returns NULL if no space left
  if(cpy != NULL)
    strcpy(cpy, s);
  return cpy;
}

struct tnode *talloc(void){
  return (struct tnode *) malloc(sizeof(struct tnode));
}

void treeprint(struct tnode *p){
  if(p != NULL){
    treeprint(p->left);
    printf("%s %d\n", p->word, p->count);
    treeprint(p->right);
  }
}

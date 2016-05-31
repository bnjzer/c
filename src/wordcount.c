#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include "libgetword.h"

#define MAXWORD 100
#define MAXOCCURENCE 150

struct tnode {
  char *word;
  int count;
  int lines[MAXOCCURENCE];
  int indLastoccurence;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *talloc(void);
char *strdup2(char *);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);

struct tnode *sortTree(struct tnode *, struct tnode *);
struct tnode *addNode(struct tnode *sortedTree, struct tnode *nodeToAdd);

int main(int argc, char **argv){
  struct tnode *root;
  char word[MAXWORD];
  int nLine = 1;

  root = NULL;
  while(getword(word) != EOF){
    if(*word == '\n')
      nLine++;
    if(isalpha(word[0]))
      root = addtree(root, word, nLine);
  }
  printf("before sort: \n\n");
  treeprint(root);
  
  struct tnode *sortedTree = sortTree(root, NULL);
  printf("\nafter sort: \n\n");
  treeprint(sortedTree);

  return 0;
}

struct tnode *addtree(struct tnode *p, char *w, int nline){
  int cond;

  if(p == NULL){ // it's a new word
    p = talloc(); //get addres for new node
    p->word = strdup2(w);
    p->count = 1;
    p->left = p->right = NULL;
    p->lines[0] = nline;
    p->indLastoccurence = 0;
  } else if((cond = strcmp(w, p->word)) < 0)
    p->left = addtree(p->left, w, nline);
  else if(cond > 0)
    p->right = addtree(p->right, w,nline);
  else {
    p->count++;
    if(p->indLastoccurence == MAXOCCURENCE-1)
      printf("Max occurences reached for word %s\n", p->word);
    else
      if(p->lines[p->indLastoccurence] != nline)
        p->lines[++p->indLastoccurence] = nline;
  }

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
    printf("%s %d: %d", p->word, p->count, p->lines[0]);
    int i;
    for(i=1; i<=p->indLastoccurence; i++)
      printf(", %d", p->lines[i]);
    printf("\n");
    treeprint(p->right);
  }
}

struct tnode *sortTree(struct tnode *root, struct tnode *sortedTree){
  if(root != NULL){
    sortedTree = addNode(sortedTree, root);
    sortTree(root->left, sortedTree);
    sortTree(root->right, sortedTree);
  }
  return sortedTree;
}

struct tnode *addNode(struct tnode *sortedTree, struct tnode *nodeToAdd){
  if(sortedTree == NULL){
    sortedTree = talloc();
    sortedTree->word = malloc(strlen(nodeToAdd->word)+1);
    strcpy(sortedTree->word, nodeToAdd->word);
    sortedTree->count = nodeToAdd->count;
    int i;
    for(i=0; i <= nodeToAdd->indLastoccurence; i++)
      sortedTree->lines[i] = nodeToAdd->lines[i];
    sortedTree->indLastoccurence = nodeToAdd->indLastoccurence;
    sortedTree->left = sortedTree->right = NULL;
    return sortedTree;
  } else if(nodeToAdd->count <= sortedTree->count)
    sortedTree->left = addNode(sortedTree->left, nodeToAdd);
  else
    sortedTree->right = addNode(sortedTree->right, nodeToAdd);
  return sortedTree;
}


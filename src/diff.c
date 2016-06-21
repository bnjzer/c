#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 100

int main(int argc, char **argv){
  char *progName = argv[0];

  if(argc != 3){
    fprintf(stderr, "usage: %s <file1> <file2>\n", progName);
    exit(1);
  }

  char line1[MAXLINE], line2[MAXLINE];
  char *filename1 = argv[1], *filename2 = argv[2];
  FILE *fd1, *fd2;
  
  if((fd1 = fopen(filename1, "r")) == NULL){
    fprintf(stderr, "%s: can't open %s\n", progName, filename1);
    exit(1);
  }

  if((fd2 = fopen(filename2, "r")) == NULL){
    fprintf(stderr, "%s: can't open %s\n", progName, filename2);
    exit(1);
  }

  while(fgets(line1, MAXLINE, fd1) != NULL && fgets(line2, MAXLINE, fd2) != NULL)
    if(strcmp(line1, line2)){
      printf("Files differ at :\n%s : %s\n%s : %s\n", filename1, line1, filename2, line2);
      exit(1);
    }

  exit(0);
}

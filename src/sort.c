#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "libgetline2.h"

#define MAXLINES 100
#define MAXLEN 1000

char *linesptr[MAXLINES];

int readlines(char *lineptr[], char lines[], int maxlines);
void writelines(char *lineptr[], int nlines, char reversed);

void qsort2(void *linesptr[], int left, int right, int (*comp)(const char *, const char *));
int numcmp(const char *, const char *);

int main(int argc, char *argv[]){
  char numeric = 0;
  char reverse = 0;
  char caseInsensitive = 0;

  int nlines;
  char lines[MAXLINES*MAXLEN];
  int arg = 1;

  while(arg < argc){
    if(strcmp(argv[arg], "-n") == 0){
      numeric = 1;
    } else if(strcmp(argv[arg], "-r") == 0){
      reverse = 1;
    } else if(strcmp(argv[arg], "-f") == 0){
      caseInsensitive = 1;
    }
    arg++;
  }

  if((nlines = readlines(linesptr, lines, MAXLINES)) >= 0){
    qsort2((void **) linesptr, 0, nlines-1, (numeric ? numcmp : caseInsensitive ? strcasecmp : strcmp));
    writelines(linesptr, nlines, reverse);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

int readlines(char *lineptr[], char lines[], int maxlines){
  int len, totalLength, nlines;

  nlines = 0;
  totalLength=0;
  while((len=getline2(lines, MAXLEN)) > 0){
    if (nlines >= MAXLINES){
      return -1;
    } else {
      totalLength += len;
      lineptr[nlines++] = lines;
      lines+=totalLength;
    }
  }
  return nlines;
}

void swap (void *v[], int i, int j);

void qsort2(void *linesptr[], int left, int right, int (*comp)(const char *, const char *)){
  int i,indPivot;

  if(left >= right)
    return;

  indPivot=left;

  for(i=indPivot+1; i<=right; i++){
    if((*comp)(linesptr[i], linesptr[indPivot]) < 0){
      swap(linesptr, indPivot, i);
    }
    qsort2(linesptr,left,indPivot-1, comp);
    qsort2(linesptr, indPivot+1,right, comp);
  }
}

void swap (void *v[], int i, int j){
  void *temp;

  temp=v[i];
  v[i]=v[j];
  v[j]=temp;
}

int numcmp(const char *s1, const char *s2){
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);

  if(v1<v2){
    return -1;
  }else if(v2>v1){
    return 1;
  } else {
    return 0;
  }
}

void writelines(char *lineptr[], int nlines, char reversed){
  int i;

  if(reversed){
    lineptr+=nlines-1;
    for(i=0; i<nlines; i++){
      printf("%s\n", *lineptr--);
    }
  }else{
    for(i=0; i<nlines; i++){
      printf("%s\n", *lineptr++);
    }
  }
}

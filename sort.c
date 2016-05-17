#include<stdio.h>
#include<string.h>

#define MAXLINES 500
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char lines[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main(){
  int nlines;
  char lines[MAXLINES*MAXLEN];

  if((nlines = readlines(lineptr,lines, MAXLINES)) >= 0){
    printf("%d lines read\n",nlines);
    qsort(lineptr,0,nlines-1);
    writelines(lineptr,nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

int getline2(char*, int);

int readlines(char *lineptr[], char lines[], int maxlines){
  int len, totalLength, nlines;
  char *p;

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

void writelines(char *lineptr[], int nlines){
  int i;
  printf("\n");

  for(i=0; i<nlines; i++){
    printf("%s\n", *lineptr++);
  }
}

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

void swap (char *v[], int i, int j);

void qsort(char *v[], int left, int right){
  int i,indPivot;

  if(left >= right)
    return;
  
  indPivot=left;

  for(i=indPivot+1; i<=right; i++){
    if(strcmp(v[i], v[indPivot]) < 0){
      swap(v, indPivot, i);
    }
    qsort(v,left,indPivot-1);
    qsort(v, indPivot+1,right);
  }
}

void swap (char *v[], int i, int j){
  char *temp;

  temp=v[i];
  v[i]=v[j];
  v[j]=temp;
}

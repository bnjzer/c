#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
  FILE *fp;
  void filecopy(FILE *, FILE *);
  char *progName = argv[0];

  if(argc == 1)
    filecopy(stdin, stdout);
  else
    while(--argc > 0)
      if((fp = fopen(*++argv, "r")) == NULL){
        fprintf(stderr, "%s: can't open %s\n", progName, *argv);
        exit(1);
      } else {
        filecopy(fp, stdout);
        fclose(fp);
      }
  if(ferror(stdout)){
    fprintf(stderr, "%s: error writing stdout\n", progName);
    exit(2);
  }
  exit(0);
}

void filecopy(FILE *ifp, FILE *ofp){
  int c;

  while((c = getc(ifp)) != EOF)
    putc(c, ofp);
}

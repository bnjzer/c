#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buf

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype; // type of last token
char token[MAXTOKEN]; // last token string
char name[MAXTOKEN]; // identifier name
char datatype[MAXTOKEN]; // char, int, etc.
char out[1000]; // output string

int main(){
  int undcl=1;

  if(undcl){
    int type;
    char temp[MAXTOKEN];

    while(gettoken() != EOF){ // x () * [] * () char
      strcpy(out, token);
      while((type = gettoken()) != '\n')
        if(type == PARENS || type == BRACKETS)
          strcat(out, token);
        else if(type == '*'){
          sprintf(temp, "(*%s)", out);
          strcpy(out, temp);
        } else if(type == NAME){ // it must end with the type
          sprintf(temp, "%s %s", token, out);
          strcpy(out, temp);
        } else 
          printf("invalid input at %s\n", token);
      printf("%s\n", out);
    }
  } else{ // char (*(*x())[])()
    int c;

    while(gettoken() != EOF){
      strcpy(datatype, token); // 1st token on the line is the datatype
      out[0] = '\0';
      dcl(); // parse rest of the line
      if(tokentype != '\n')
        printf("syntax error : %c\n", tokentype);
      printf("%s : %s %s\n", name, out, datatype);
    }
  }

  return 0;
}

int gettoken(void){ // token: name, pair of parenthesis, pair of brackets with possible number, any single caracter
  char *p = token;
  int c, getch(void);
  void ungetch(int);

  while((c = getch()) == ' ' || c == '\t')
    ;

  if(c == '('){
    if((c=getch()) == ')'){
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if(c == '['){
    for(*p++=c; (*p++ = getch()) != ']'; )
      ;
    *p = '\0';
    return tokentype = BRACKETS;
  } else if(isalpha(c)){
    for(*p++ = c; isalnum(c = getch()); )
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

int getch(void){
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
  if(bufp >= BUFSIZE){
    printf("ungetch: too many characters in buffer\n");
  } else {
    buf[bufp++] = c;
  }
}

void dcl(void){
  int ns;

  for(ns = 0; gettoken() == '*'; ) // count the number of *'s
    ns++;
  dirdcl();
  while(ns-- > 0)
    strcat(out, " pointer to ");
}

void dirdcl(void){
  int type;

  if(tokentype == '(') { // (dcl)
    dcl();
    if(tokentype != ')')
      printf("error: missing )\n");
  } else if(tokentype == NAME)
    strcpy(name, token);
  else
    printf("error: expected name or (dcl)\n");

  while((type = gettoken()) == PARENS || type == BRACKETS)
    if(type == PARENS)
      strcat(out, " function returning ");
    else {
      strcat(out, " array ");
      strcat(out, token);
      strcat(out, " of ");
    }
}

/*
 * 1) add arguments type in function
 * 3) error recovery : exemple [a]
 * 4) modify undcl to not add redundant parentheses
 */

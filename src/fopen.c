#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

//#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20

#define FLAG_READ {1, 0, 0, 0, 0}
#define FLAG_WRITE {0, 1, 0, 0, 0}

typedef struct {
  unsigned int readable : 1;
  unsigned int writable : 1;
  unsigned int unbuffered : 1;
  unsigned int eof : 1;
  unsigned int error : 1;
} FLAGS;

typedef struct _iobuf {
  int cnt; // characters left
  char *ptr; // next character position
  char *base; // location of buffer
  FLAGS flags;
  int fd; // flag descriptor
} FILE;

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE _iob[OPEN_MAX] = {
  {0, (char *) 0, (char *) 0, FLAG_READ, 0}, // stdin
  {0, (char *) 0, (char *) 0, FLAG_WRITE, 1}, // stdin
  {0, (char *) 0, (char *) 0, {0, 0, 1, 1, 0}, 2}, // stderr
};

int _fillbuff(FILE*);
int _flushbuf(int, FILE*);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? \
    (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar() getc(stdin)
#define putchar(c) putc(stdout, c)

#define PERMS 0644

/* open files and returns file pointer */
FILE *fopen(char *name, char *mode){
  int fd;
  FILE *fp;

  if (*mode != 'r' && *mode != 'a' && *mode != 'r')
    return NULL;

  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if (fp->flags.readable ||  fp->flags.writable)
      break;

  if (fp >= _iob + OPEN_MAX)
    return NULL;

  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a'){
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);

  if(fd == -1)
    return NULL;

  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flags = (*mode == 'r') ? (FLAGS) FLAG_READ : (FLAGS) FLAG_WRITE;

  return fp;
}

/* allocate and fill input buffer */
int _fillbuf(FILE *fp){
  int bufsize;

  if (!fp->flags.readable || fp->flags.eof || fp->flags.error)
    return EOF;

  bufsize = fp->flags.unbuffered ? 1 : BUFSIZE;

  if(fp->base == NULL) // no buffer yet
    if((fp->base = (char*) malloc(bufsize)) == NULL)
      return EOF; // can't allocate memory

  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);

  if (--fp->cnt < 0){
    if (fp->cnt == -1)
      fp->flags.eof = 1;
    else
      fp->flags.error = 1;

    fp->cnt=0;
    return EOF;
  }

  return (unsigned char) *fp->ptr++;
}

int main(int argc, char **argv){
  FILE *f;
  f = fopen("/tmp/toto", "r");
  if (f == NULL)
    printf("An error occured while opening file\n");
  else
    _fillbuf(f);

  return 0;
}

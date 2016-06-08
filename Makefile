GCC=gcc
AR=ar rcs
CFLAGS=-Wall -g

SRCDIR=src
INCLUDEDIR=inc
LIBDIR=lib
BINDIR=bin

all: $(BINDIR)/args $(BINDIR)/calculer $(BINDIR)/calendar $(BINDIR)/dcl $(BINDIR)/exec $(BINDIR)/find $(BINDIR)/fork $(BINDIR)/parsec $(BINDIR)/pcalendar $(BINDIR)/procs $(BINDIR)/sort $(BINDIR)/tail $(BINDIR)/threads $(BINDIR)/zombie $(BINDIR)/ordo $(BINDIR)/files $(BINDIR)/dir $(BINDIR)/ipc $(BINDIR)/ipc2ways $(BINDIR)/namedpipe1 $(BINDIR)/namedpipe2 $(BINDIR)/wordcount $(BINDIR)/define

# binaries

$(BINDIR)/define: $(SRCDIR)/define.c $(LIBDIR)/libgetword.a 
	$(GCC) $(CFLAGS) -o $@ $^ -I $(INCLUDEDIR)

$(BINDIR)/wordcount: $(SRCDIR)/wordcount.c $(LIBDIR)/libgetword.a 
	$(GCC) $(CFLAGS) -o $@ $^ -I $(INCLUDEDIR)

$(BINDIR)/parsec: $(SRCDIR)/parsec.c $(LIBDIR)/libgetch.a 
	$(GCC) $(CFLAGS) -o $@ $^ -I $(INCLUDEDIR)

$(BINDIR)/dcl: $(SRCDIR)/dcl.c $(LIBDIR)/libgetch.a
	$(GCC) $(CFLAGS) -o $@ $^ -I $(INCLUDEDIR)

$(BINDIR)/sort: $(SRCDIR)/sort.c $(LIBDIR)/libgetline2.a
	$(GCC) $(CFLAGS) -o $@ $^ -I $(INCLUDEDIR)

$(BINDIR)/find: $(SRCDIR)/find.c $(LIBDIR)/libgetline2.a
	$(GCC) $(CFLAGS) -o $@ $^ -I $(INCLUDEDIR)

$(BINDIR)/tail: $(SRCDIR)/tail.c $(LIBDIR)/libgetline2.a
	$(GCC) $(CFLAGS) -o $@ $^ -I $(INCLUDEDIR)

$(BINDIR)/threads: $(SRCDIR)/threads.c
	$(GCC) $(CFLAGS) -o $@ $^ -lpthread -I /usr/include

$(BINDIR)/ipc2ways: $(SRCDIR)/ipc2ways.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/namedpipe2: $(SRCDIR)/namedpipe2.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/namedpipe1: $(SRCDIR)/namedpipe1.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/ipc: $(SRCDIR)/ipc.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/dir: $(SRCDIR)/dir.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/ordo: $(SRCDIR)/ordo.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/procs: $(SRCDIR)/procs.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/zombie: $(SRCDIR)/zombie.c
	$(GCC) $(CFLAGS) -o $@ $^ 

$(BINDIR)/files: $(SRCDIR)/files.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/args: $(SRCDIR)/args.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/calendar: $(SRCDIR)/calendar.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/pcalendar: $(SRCDIR)/pcalendar.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/fork: $(SRCDIR)/fork.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/exec: $(SRCDIR)/exec.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/calculer: $(SRCDIR)/calculer.c
	$(GCC) $(CFLAGS) -o $@ $^

# libraries

$(LIBDIR)/libgetword.a: $(SRCDIR)/libgetword.c $(LIBDIR)/libgetch.a
	$(GCC) $(CFLAGS) -c $< -o $(SRCDIR)/libgetword.o -I $(INCLUDEDIR)
	$(AR) $@ $(SRCDIR)/libgetword.o $(SRCDIR)/libgetch.o 

$(LIBDIR)/libgetch.a: $(SRCDIR)/libgetch.c
	$(GCC) $(CFLAGS) -c $^ -o $(SRCDIR)/libgetch.o
	$(AR) $@ $(SRCDIR)/libgetch.o

$(LIBDIR)/libgetline2.a: $(SRCDIR)/libgetline2.c
	$(GCC) $(CFLAGS) -c $^ -o $(SRCDIR)/libgetline2.o
	$(AR) $@ $(SRCDIR)/libgetline2.o

clean:
	rm -f $(BINDIR)/*
	rm -f $(LIBDIR)/*
	rm -f $(SRCDIR)/*.o

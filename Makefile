GCC=gcc
AR=ar rcs
CFLAGS=-Wall -pedantic

SRCDIR=src
INCLUDEDIR=inc
LIBDIR=lib
BINDIR=bin

# binaries

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

$(BINDIR)/args: $(SRCDIR)/args.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/calendar: $(SRCDIR)/calendar.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/pcalendar: $(SRCDIR)/pcalendar.c
	$(GCC) $(CFLAGS) -o $@ $^

$(BINDIR)/fork: $(SRCDIR)/fork.c
	$(GCC) $(CFLAGS) -o $@ $^

# libraries

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

CTAGS= ctags -x >tags
CFLAGS= -O
LDFLAGS= -s
CC=gcc
SRCS=.c
OBJS=.o
HDRS=.h
SRCDIR=./src/
BINDIR=./bin/
all:    foom

$(SRCS):
	$(CC) $(CFLAGS) -c $*.c

# To make an executable

foom: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

# where are functions/procedures?
tags: $(SRCS)
	$(CTAGS) $(SRCS)

# what have I done wrong?
lint: $(SRCS)
	lint $(CFLAGS) $(SRCS)

# what are the source dependencies
depend: $(SRCS)
	$(DEPEND) $(SRCS)

# clean out the dross
clean:
	-rm foom *~ *.o *.bak core tags shar

# DO NOT DELETE THIS LINE -- make depend depends on it.
foom.o: /usr/include/stdio.h

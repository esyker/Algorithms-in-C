CC=gcc
CFLAGS= -Wall -ansi -O3
SOURCES= main.c utils.c puzzle.c  tree.c hash.c
OBJECTS= main.o utils.o puzzle.o tree.o hash.o

zeruns:$(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)


puzzle.o: puzzle.h

utils.o: utils.h

tree.o: tree.h

hash.o:hash.c

clean::
	rm -f *.o core a.out zeruns *~

depend::
	makedepend $(SOURCES)


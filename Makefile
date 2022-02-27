CC=gcc
CFLAGS=-I.
DEPS = mymalloc.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mymalloc: mymalloc.o memgrind.o 
	$(CC) -o mymalloc mymalloc.o memgrind.o 
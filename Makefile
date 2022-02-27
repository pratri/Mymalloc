CC=gcc
CFLAGS=-I.
DEPS = mymalloc.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

memgrind: mymalloc.o memgrind.o 
	$(CC) -o memgrind mymalloc.o memgrind.o 

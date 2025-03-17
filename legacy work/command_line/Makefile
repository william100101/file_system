CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

OBJS = wrapper.o
EXECS = ishell

all: $(EXECS)


ishell:
	gcc -pthread $(CFLAGS) wrapper.o ishell.c -o ishell

wrapper.o: wrapper.c
	$(CC) -c $(CFLAGS) wrapper.c -o wrapper.o

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS)

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

COMMON_OBJS = minixfs.o

all: minls minget

minls: minls.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o minls minls.o $(COMMON_OBJS)

minget: minget.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o minget minget.o $(COMMON_OBJS)

minls.o: minls.c minixfs.h
	$(CC) $(CFLAGS) -c minls.c

minget.o: minget.c minixfs.h
	$(CC) $(CFLAGS) -c minget.c

minixfs.o: minixfs.c minixfs.h
	$(CC) $(CFLAGS) -c minixfs.c

clean:
	rm -f *.o minls minget
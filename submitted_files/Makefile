CC=cc
CFLAGS=-g
LFLAGS=-pthread

all: dining selectionSort.o selectionSortTest

dining: dining.c dining.h
	$(CC) $(CFLAGS) dining.c -o dining $(LFLAGS)

selectionSort.o: selectionSort.c
	$(CC) $(CFLAGS) -c selectionSort.c -o selectionSort.o

selectionSortTest: selectionSort.o
	$(CC) $(CFLAGS) selectionSortTest.c -o selectionSortTest selectionSort.o $(LFLAGS)

clean:
	rm -f *.o selectionSortTest dining

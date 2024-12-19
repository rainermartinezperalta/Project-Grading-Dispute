CC=cc
CFLAGS=-g
LFLAGS=-pthread

all: dining selectionSort.o selectionSortTest

dining : dining.c dining.h
	$(CC) $(CFLAGS) -o dining dining.c $(LFLAGS)

selectionSort.o : selectionSort.c
	$(CC) $(CFLAGS) -c selectionSort.c -o selectionSort.o

selectionSortTest: selectionSort.o
	$(CC) $(CFLAGS) -o selectionSortTest selectionSortTest.c selectionSort.o $(LFLAGS)

clean:
	rm -rf *.o selectionSortTest dining

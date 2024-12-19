#include "selectionSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void* sortThread(void* args) {
   TArg* targ = args;
   Segment* me = targ->seg;
   Share*  shr = targ->shr;
   me->won  = 1;
   int best = MAXINT, myGen = 0;
   while (me->from < me->to) {
     /*
       TODO: Implement this function as follows.
        * Set the generation for the thread as the barrier gen and find the min element of the segment array.
        * Compare the min value to the value stored in the "best" field of the shared data structure shr. If the min found is smaller, update the best and winner fields of the shared structure. Do not forget to grab the lock before checking and updating values.
        * Increment the number of threads reported and wait till all threads have entered the barrier.
        * If this thread is the last to enter, add the best value to the output array and swap the min element with the first elements of the winning segment. Reset the other fields of the shared structure and update the generation. Broadcast to wake up all threads. Note that if the winning segment has no more values left, the thread should exit and the number of threads expected in the barrier would be one less than before.
        * Finally, unlock the mutex for the shared object.
      */
   }
   return NULL;
}

MTArray* initArray(int* numbers, int n)  {   /* To initialize the array */
  MTArray* array = malloc(sizeof(MTArray));
  array->numbers = numbers;
  array->size = n;
  return array;
}

void printArray(MTArray* array) {           /* To print the array */
  for (int i = 0; i < array->size; i++)
    printf("%d ", array->numbers[i]);    
  printf("\n");
}

void checkArray(MTArray* a) {            /* To check if the array contains n elements and all elements are sorted */ 
   int ok =  1;
   for (int i = 0; ok && i < a->size - 1; i++)
      ok = ok && a->numbers[i] <= a->numbers[i+1];
   if (!ok) {
      printf("Not sorted....\n");
      exit(1);
   }
}

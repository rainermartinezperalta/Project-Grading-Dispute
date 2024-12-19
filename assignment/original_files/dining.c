/* Dining groups of philosophers on small and big dining tables. */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "dining.h"

/* THIS FUNCTION IS NOT CALLED. IT ONLY SHOWS THE STEPS A GROUP TAKES FOR DINING AND IS PROVIDED AS A GUIDANCE FOR YOU TO IMPLEMENT small_group_dining and big_group_dining FUNCTIONS */ 
void dining_process(group_t * grp)
{
    /* Try to get a table for the group. 

       maitain counters in mutex protected section 

       for small groups, keep the table size to be used 
       with this group in a local variable, e.g., table_size
       
       lock the mutex
       while (! predicate) {
            PRINT_WAITING_MSG(grp) 
            pthread_cond_wait(...);
       }
       PRINT_SEATED_MSG(grp, table_size);
       unlock the mutex

    */

    DINING(grp);  // dining

    /* Leaving
       
       lock the mutex
       maintain counters and signal properly
       PRINT_LEAVING_MSG(grp, table_size);
       unlock the mutex

    */
}

/* Handle the dining process for small groups. Read the dining_process() function above and the comments below for steps to take. */ 
void small_group_dining(group_t * grp) 
{
    restaurant_t * restt = grp->restaurant;
 
    int table_size;     /* this variable keeps track of table size used by this group */

    /* TODO:
        * A small group dines at a small table. A small group may dine at a big table if big tables are available and no big groups are waiting.
        * Otherwise, a group must wait till a small table becomes available.
        * Remember to update the values of the shared variables based on the table assignment both before and after a group has completed dining.
        * Note: you must print the appropriate messages on stdout based on the state of the group.
            * If the group is about to enter the wait state, call the PRINT_WAITING_MSG.
            * If the group gets a table, call the PRINT_SEATED_MSG macro.
            * If the group empties a table, call the PRINT_LEAVING_MSG macro.
        
        * The sequence of steps to be taken for this implementation is given in the dining_process function above.
     */

    return;
}

/* Handle the dining process for big groups. Read the dining_process() function above and the comments below for steps to take. */ 
void big_group_dining(group_t * grp) 
{
    restaurant_t * restt = grp->restaurant;

    /* TODO:
        * A big group can only dine at a big table. 
        * If all big tables are taken, a group must wait till a big table becomes available.
        * Remember to update the values of the shared variables based on the table assignment both before and after a group has completed dining.
        * Note: you must print the appropriate messages on stdout based on the state of the group.
            * If the group is about to enter the wait state, call the PRINT_WAITING_MSG.
            * If the group gets a table, call the PRINT_SEATED_MSG macro.
            * If the group empties a table, call the PRINT_LEAVING_MSG macro.
        
        * The sequence of steps to be taken for this implementation is given in the dining_process function above.
    */

    return;
}

/* Thread function for each group. Each group dines for n_meals times. Call functions to handle the actual dining process. */
void * thread_grp(void *arg_orig)
{
    group_t *grp = arg_orig;

    /* Randomize the seed as a function of group id to set a different wait time for threads */
    unsigned short g_random_buffer[3]; // buffer for random numbers
    if (grp->seed) {
        int actual_seed = (grp->seed << 10) + grp->id; 
        RANDOM_INIT(actual_seed);
    } else {
        int actual_seed = 3100 * grp->id + 12345;
        RANDOM_INIT(actual_seed);
    }

    /* Each group has n_meals number of meals */
    for (int i = 0; i < grp->n_meals; i ++) {
        
        if (grp->seed) {   /* a group waits for random amount of time */
            WAITING();
        }
        grp->time_to_dine = RANDOM_INT();           /* Set a random time needed to dine for each group */

        PRINT_ARRIVING_MSG(grp);

        /* Call functions to handle dining process for the groups */
        if (grp->sz == SIZE_SMALL)
            small_group_dining(grp);
        else 
            big_group_dining(grp);
    }

    return NULL;
}


int main(int argc, char *argv[]) 
{
    if(argc < 6) {
        printf("The correct usage is: ./dining num_small_groups num_big_groups n_small_tables n_big_tables n_meals. \n");
        exit(-1);
    }

    int n_small_groups = atoi(argv[1]);         /* Number of small groups */
    int n_big_groups = atoi(argv[2]);           /* Number of big groups */
    int n_small_tables = atoi(argv[3]);         /* Number of small tables */
    int n_big_tables = atoi(argv[4]);           /* Number of big tables */ 
    int n_meals = atoi(argv[5]);                /* Number of meals a group will have */
    int seed = 3100;

    printf("Options: -g%d -G%d -t%d -T%d -m%d\n", 
            n_small_groups, n_big_groups, n_small_tables, n_big_tables, n_meals);

    /* Declare and initialize an instance of the restaurant structure */
    restaurant_t restt = {0};                    
    restt.n_big_tables = n_big_tables;
    restt.n_small_tables = n_small_tables;
    pthread_mutex_init(&restt.mutex, NULL);
    pthread_cond_init(&restt.cond_small, NULL);
    pthread_cond_init(&restt.cond_big, NULL);

    /* Create threads such that each group is represented by a single thread */
    int nbT = n_big_groups + n_small_groups;      // number of threads to create
    pthread_t tid[nbT];
    group_t grps[nbT];

    /* Initialize the group information for each thread */
    for (int i = 0; i < nbT; i++) {
        grps[i] = (group_t){i, SIZE_SMALL, n_meals, seed, 0, &restt};
        if (i >= n_small_groups) {      
            grps[i].sz = SIZE_BIG;
        }
        pthread_create(&tid[i], NULL, thread_grp, &grps[i]);
    }

    /* Join the threads and destroy mutexes and condition variables */
    for(int i = 0; i < nbT; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&restt.mutex);
    pthread_cond_destroy(&restt.cond_small);
    pthread_cond_destroy(&restt.cond_big);

    return 0;
}

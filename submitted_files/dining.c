#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "dining.h"

// Handles small groups trying to dine
void small_group_dining(group_t *grp) {
    restaurant_t *restt = grp->restaurant; // Get the restaurant details
    int table_size; // To keep track of which table is used

    pthread_mutex_lock(&restt->mutex); // Lock to ensure thread safety

    // Wait until a small or big table is free
    while ((restt->n_small_taken >= restt->n_small_tables) &&
           ((restt->n_big_taken >= restt->n_big_tables) || restt->n_big_waiting > 0)) {
        restt->n_small_waiting++; // Count this group as waiting
        PRINT_WAITING_MSG(grp);  // Show that the group is waiting
        pthread_cond_wait(&restt->cond_small, &restt->mutex); // Wait for a table
        restt->n_small_waiting--; // No longer waiting
    }

    // Use a small table if available, otherwise use a big table
    if (restt->n_small_taken < restt->n_small_tables) {
        table_size = SIZE_SMALL; // Mark as using a small table
        restt->n_small_taken++; // Increase count of small tables in use
    } else {
        table_size = SIZE_BIG; // Mark as using a big table
        restt->n_big_taken++; // Increase count of big tables in use
    }

    PRINT_SEATED_MSG(grp, table_size); // Show that the group is seated
    pthread_mutex_unlock(&restt->mutex); // Unlock after changes

    DINING(grp); // Simulate dining

    pthread_mutex_lock(&restt->mutex); // Lock again to update table counts
    if (table_size == SIZE_SMALL) {
        restt->n_small_taken--; // Free up a small table
        pthread_cond_signal(&restt->cond_small); // Notify waiting small groups
    } else {
        restt->n_big_taken--; // Free up a big table
        if (restt->n_big_waiting > 0)
            pthread_cond_signal(&restt->cond_big); // Notify waiting big groups
        else
            pthread_cond_signal(&restt->cond_small); // Notify waiting small groups
    }
    PRINT_LEAVING_MSG(grp, table_size); // Show that the group is leaving
    pthread_mutex_unlock(&restt->mutex); // Unlock after changes
}

// Handles big groups trying to dine
void big_group_dining(group_t *grp) {
    restaurant_t *restt = grp->restaurant; // Get the restaurant details

    pthread_mutex_lock(&restt->mutex); // Lock to ensure thread safety

    // Wait until a big table is free
    while (restt->n_big_taken >= restt->n_big_tables) {
        restt->n_big_waiting++; // Count this group as waiting
        PRINT_WAITING_MSG(grp); // Show that the group is waiting
        pthread_cond_wait(&restt->cond_big, &restt->mutex); // Wait for a table
        restt->n_big_waiting--; // No longer waiting
    }

    restt->n_big_taken++; // Take a big table
    PRINT_SEATED_MSG(grp, SIZE_BIG); // Show that the group is seated
    pthread_mutex_unlock(&restt->mutex); // Unlock after changes

    DINING(grp); // Simulate dining

    pthread_mutex_lock(&restt->mutex); // Lock again to update table counts
    restt->n_big_taken--; // Free up a big table
    if (restt->n_big_waiting > 0)
        pthread_cond_signal(&restt->cond_big); // Notify waiting big groups
    else
        pthread_cond_signal(&restt->cond_small); // Notify waiting small groups
    PRINT_LEAVING_MSG(grp, SIZE_BIG); // Show that the group is leaving
    pthread_mutex_unlock(&restt->mutex); // Unlock after changes
}

// This function runs for each group in a separate thread
void *thread_grp(void *arg_orig) {
    group_t *grp = arg_orig; // Get the group details

    for (int i = 0; i < grp->n_meals; i++) { // Repeat for the number of meals
        PRINT_ARRIVING_MSG(grp); // Show that the group is arriving
        if (grp->sz == SIZE_SMALL)
            small_group_dining(grp); // Handle dining for small groups
        else
            big_group_dining(grp); // Handle dining for big groups
    }

    return NULL; // End the thread
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Usage: ./dining num_small_groups num_big_groups n_small_tables n_big_tables n_meals\n");
        return 1; // Exit if arguments are incorrect
    }

    int n_small_groups = atoi(argv[1]);
    int n_big_groups = atoi(argv[2]);
    int n_small_tables = atoi(argv[3]);
    int n_big_tables = atoi(argv[4]);
    int n_meals = atoi(argv[5]);

    restaurant_t restt = {0}; // Initialize the restaurant
    restt.n_small_tables = n_small_tables;
    restt.n_big_tables = n_big_tables;
    pthread_mutex_init(&restt.mutex, NULL);
    pthread_cond_init(&restt.cond_small, NULL);
    pthread_cond_init(&restt.cond_big, NULL);

    int total_groups = n_small_groups + n_big_groups;
    pthread_t threads[total_groups]; // Array of threads
    group_t groups[total_groups];   // Array of group details

    // Create threads for each group
    for (int i = 0; i < total_groups; i++) {
        groups[i] = (group_t){i, (i < n_small_groups) ? SIZE_SMALL : SIZE_BIG, n_meals, 0, 0, &restt};
        pthread_create(&threads[i], NULL, thread_grp, &groups[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < total_groups; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&restt.mutex);
    pthread_cond_destroy(&restt.cond_small);
    pthread_cond_destroy(&restt.cond_big);

    return 0;
}

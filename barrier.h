#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

pthread_mutex_t barrier_lock;
pthread_mutex_t counter_lock;
int subscriber_count = NUM_THREADS;
int wait_counter = 0;

/*
 * Initializes the barrier
*/
void barrier_init() {
    pthread_mutex_init(&barrier_lock, NULL);
    pthread_mutex_init(&counter_lock, NULL);
    pthread_mutex_lock(&barrier_lock);
    pthread_mutex_unlock(&counter_lock);
}

/*
 * All subscribers to the barrier will wait until all threads reach this point before proceeding
*/
void barrier_wait() {
    pthread_mutex_lock(&counter_lock);
    wait_counter++;
    if (wait_counter != subscriber_count) pthread_mutex_unlock(&counter_lock);
    else pthread_mutex_unlock(&barrier_lock);
    pthread_mutex_lock(&barrier_lock);
    wait_counter--;
    if (wait_counter != 0) pthread_mutex_unlock(&barrier_lock);
    else pthread_mutex_unlock(&counter_lock);   
}


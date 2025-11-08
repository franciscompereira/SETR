#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define NUM_INCREMENTS 1000000

int counter = 0;

void* increment(void* arg) {
	(void) arg;
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        counter++;
    }
    return NULL;
}  

int main(void) {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Final counter value (no mutex): %d\n", counter);
    
    
    return 0;
}

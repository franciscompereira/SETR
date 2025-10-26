#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // for sleep()

// Thread function
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    printf("Thread %d starting\n", thread_id);
    sleep(2 + thread_id);  // wait for a few seconds (different per thread)
    printf("Thread %d finishing\n", thread_id);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {1, 2};
    int rc;

    printf("Main thread: creating two threads named 1 and 2\n");

    // Create two threads
    for (int i = 0; i < 2; i++) {
        rc = pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
        if (rc) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            exit(-1);
        }
    }

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread: all threads finished, exiting now\n");
    pthread_exit(NULL);
}

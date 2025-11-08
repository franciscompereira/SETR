#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>     // For uint16_t
#include <semaphore.h>  // For sem_t
#include <string.h>     // For strerror()
#define BUFFER_SIZE 10 // Now we can use all 10 slots!

struct SharedRingBuffer {
   
    int head;
    int tail;
    uint16_t buffer[BUFFER_SIZE];
};

struct SharedRingBuffer g_ring_buffer; // Our shared buffer
pthread_mutex_t g_mutex; // <<< NEW: The lock for the buffer
sem_t g_sem_full;  // (Same as before) Counts full slots
sem_t g_sem_empty; // <<< NEW: Counts empty slots


void* producer_function(void* arg) {
    printf("[Producer] Thread started. Will send 1-20.\n");

    for (uint16_t i = 1; i <= 20; i++) {
        sem_wait(&g_sem_empty);
        pthread_mutex_lock(&g_mutex);

        g_ring_buffer.buffer[g_ring_buffer.head] = i;
        printf("[Producer] Wrote: %u (at index %d)\n", i, g_ring_buffer.head);
        g_ring_buffer.head = (g_ring_buffer.head + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&g_mutex);

        sem_post(&g_sem_full);
    }

    printf("[Producer] Finished. Exiting.\n");
    return NULL;
}

void* consumer_function(void* arg) {
    printf("[Consumer] Thread started. Will consume 20 items.\n");

    for (int i = 1; i <= 20; i++) {
        uint16_t value;
        sem_wait(&g_sem_full);
        pthread_mutex_lock(&g_mutex);

        value = g_ring_buffer.buffer[g_ring_buffer.tail];
        printf("[Consumer] Read: %u (from index %d)\n", value, g_ring_buffer.tail);
        g_ring_buffer.tail = (g_ring_buffer.tail + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&g_mutex);


        sem_post(&g_sem_empty);

        if (i % 4 == 0) {
            printf("[Consumer] *** Long sleep (10s) ***\n");
            sleep(10);
        } else {
            printf("[Consumer] Short sleep (1s)\n");
            sleep(1);
        }
    }

    printf("[Consumer] Finished. Exiting.\n");
    return NULL;
}

int main() {
    pthread_t producer_tid, consumer_tid;
    int ret;

    g_ring_buffer.head = 0;
    g_ring_buffer.tail = 0;


    if (pthread_mutex_init(&g_mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(1);
    }

    if (sem_init(&g_sem_full, 0, 0) == -1) {
        perror("sem_init(full)");
        exit(1);
    }
    

    if (sem_init(&g_sem_empty, 0, BUFFER_SIZE) == -1) {
        perror("sem_init(empty)");
        exit(1);
    }



    ret = pthread_create(&producer_tid, NULL, producer_function, NULL);
    if (ret != 0) {
        fprintf(stderr, "Error creating producer: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_create(&consumer_tid, NULL, consumer_function, NULL);
    if (ret != 0) {
        fprintf(stderr, "Error creating consumer: %s\n", strerror(ret));
        exit(1);
    }

    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    sem_destroy(&g_sem_full);
    sem_destroy(&g_sem_empty);
    pthread_mutex_destroy(&g_mutex);

    printf("[Main] All threads finished. Exiting.\n");
    return 0;
}

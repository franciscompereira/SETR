#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>     // For uint16_t
#include <semaphore.h>  // For sem_t
#include <string.h>     // For strerror()
#define BUFFER_SIZE 25

struct SharedRingBuffer {
    int head; // The "WHERE" for the producer
    int tail; // The "WHERE" for the consumer
    uint16_t buffer[BUFFER_SIZE];
};

struct SharedRingBuffer g_ring_buffer; // Our shared "whiteboard"
pthread_mutex_t g_mutex; // The "lock" for the whiteboard
sem_t g_sem_full;  // The "counter" for full slots
sem_t g_sem_empty; // The "counter" for empty slots

void* producer_function(void* arg) {
    for (uint16_t i = 1; i <= 20; i++) {
                
        sem_wait(&g_sem_empty); // This makes the producer sleep if the buffer is full.

        pthread_mutex_lock(&g_mutex); // "IS IT SAFE?" (Lock the buffer)

        g_ring_buffer.buffer[g_ring_buffer.head] = i;     // "WHERE?" (Use 'head' to find the write spot)

        printf("[Producer] Wrote: %u (at index %d)\n", i, g_ring_buffer.head); // write line
         
        g_ring_buffer.head = (g_ring_buffer.head + 1) % BUFFER_SIZE; // WHERE update

        pthread_mutex_unlock(&g_mutex);  // "IS IT SAFE?" (Unlock the buffer)

        sem_post(&g_sem_full);    // "SIGNAL" (Tell the consumer an item is ready)
    }
    return NULL;
}

void* consumer_function(void* arg) {
    for (int i = 1; i <= 20; i++) {
        uint16_t value;

        sem_wait(&g_sem_full);         // This makes the consumer sleep if the buffer is empty.

        pthread_mutex_lock(&g_mutex);   // "IS IT SAFE?" (Lock the buffer)

        value = g_ring_buffer.buffer[g_ring_buffer.tail]; // "WHERE?" (Use 'tail' to find the read spot)
        printf("[Consumer] Read: %u (from index %d)\n", value, g_ring_buffer.tail);
        
        g_ring_buffer.tail = (g_ring_buffer.tail + 1) % BUFFER_SIZE;    // Update the "WHERE"

        pthread_mutex_unlock(&g_mutex); // "IS IT SAFE?" (Unlock the buffer)

        sem_post(&g_sem_empty); // SIGNAL" (Tell the producer a slot is free)

        if (i % 4 == 0){
            sleep(10); // atrasar consumer prepositadamente
        } else {
            sleep(1);
        }
    }
    return NULL;
}

int main() {
    pthread_t producer_tid, consumer_tid;
    int ret;

    g_ring_buffer.head = 0;
    g_ring_buffer.tail = 0;

    pthread_mutex_init(&g_mutex, NULL);

    sem_init(&g_sem_full, 0, 0);          // 0 items are full
    sem_init(&g_sem_empty, 0, BUFFER_SIZE); // 10 slots are empty

    ret = pthread_create(&producer_tid, NULL, producer_function, NULL);
    if(ret != 0){ 
        fprintf(stderr, "Error: %s\n", strerror(ret)); exit(1);
    }
    
    ret = pthread_create(&consumer_tid, NULL, consumer_function, NULL);
    if(ret != 0){
        fprintf(stderr, "Error: %s\n", strerror(ret)); exit(1);
    }

    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    // Clean up
    sem_destroy(&g_sem_full);
    sem_destroy(&g_sem_empty);
    pthread_mutex_destroy(&g_mutex);

    printf("[Main] All threads finished. Exiting.\n");
    return 0;
}
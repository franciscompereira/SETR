#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>   
#include <stdint.h>  
#define BUFFER_SIZE 10

struct SharedRingBuffer ring_buffer;
sem_t semi;

struct SharedRingBuffer {
    volatile int head;
    volatile int tail;
    uint16_t buffer[BUFFER_SIZE];
};

void* producer_function (void* arg){
      for(u_int16_t i = 1; i < 20; i++){
        while ((ring_buffer.head + 1) % BUFFER_SIZE == ring_buffer.tail) {}
        ring_buffer.buffer[ring_buffer.head] = i; // "escrever" o numero
        printf("[Producer] Wrote: %u (at index %d)\n", i, ring_buffer.head);

        ring_buffer.head = (ring_buffer.head + 1) % BUFFER_SIZE;  //move head to the next spot 
        sem_post(&semi);
      }

    fprintf("Producer has finished \n");
    return NULL;   // never reached
}

void* consumer_function (void* arg){

     for (int i = 1; i <= 20; i++) {
        sem_wait(&semi);

        uint16_t value = ring_buffer.buffer[ring_buffer.tail];
        printf("[Consumer] Read: %u (from index %d)\n", value, ring_buffer.tail);

        ring_buffer.tail = (ring_buffer.tail + 1) % BUFFER_SIZE;

        if (i % 4 == 0) {
            printf("[Consumer] *** Long sleep (10s) ***\n");
            sleep(10);
        } else {
            printf("[Consumer] Short sleep (1s)\n");
            sleep(1);
        }
    }

    printf("[Consumer] Finished. Exiting.\n");    

    pthread_exit(NULL);  // never reached
}

int main (){
    int ret;
    pthread_t pt1, pt2;
    ring_buffer.head = 0;
    ring_buffer.tail = 0;

    if (sem_init(&semi, 0, 0) == -1){
        perror("sem_init");
        exit(1);
    }

    printf("Creating both threads \n");

    ret = pthread_create(&pt1,NULL,producer_function,NULL);
    if (ret != 0){
        printf(stderr,"Error creating consumer: %s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_create(&pt2,NULL,consumer_function,NULL);
    if (ret != 0){
        printf(stderr,"Error creating consumer: %s\n", strerror(ret));
        exit(1);
    }

    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);

    sem_destroy(&semi);

    printf("Main thread: all threads finished, exiting\n");

    return 0;
}
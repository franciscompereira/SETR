#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define BUFFER_SIZE 10

volatile int counter = 0;    
sem_t semi;

void* producer_function (void* arg){
    while(1){
        counter++;
         if (sem_post(&semi) == -1) {
            perror("sem_post");
        }
        sleep(1);
    }
    return NULL;   // never reached
}

void* consumer_function (void* arg){
    while (1) {

        if (sem_wait(&semi) == -1) {
            perror("sem_wait");
        }
        printf("Counter updated: %d\n", counter);

    }

    pthread_exit(NULL);  // never reached
}

int main (){
    int ret;
    pthread_t pt1, pt2;

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
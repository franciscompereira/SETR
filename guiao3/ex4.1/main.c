#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

volatile int counter = 0;

void* producer_function (void* arg){
    while(1){
        counter++;
        sleep(1);
    }
    return NULL;   // never reached
}

void* consumer_function (void* arg){
    int last_value = -1;
    while (1) {
        int temp = counter;
        if(last_value != temp)
            printf("Counter updated: %d\n", temp);
        last_value = temp;
    usleep(800000);
    }

    pthread_exit(NULL);  // never reached
}

int main (){

    pthread_t pt1, pt2;

    printf("Creating both threads \n");

    pthread_create(&pt1,NULL,producer_function,NULL);
    pthread_create(&pt2,NULL,consumer_function,NULL);

    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);

    printf("Main thread: all threads finished, exiting\n");

    return 0;
}
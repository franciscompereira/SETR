#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>  // para sleep()
#include <signal.h>  // para sig_atomic

// Define number of updates (compile-time constant)
#define NUM_UPDATES 10

// Shared variables
volatile int counter = 0;
volatile sig_atomic_t updated_flag = 0;

// Thread 1: updates the counter   cuidado está diferente do stor
void* update_thread(void* arg) {
    while(1){
        counter++;
        updated_flag = true;

        if(counter > NUM_UPDATES){
            pthread_exit(NULL);
        }
    sleep(1);
    }
    /*
        for (int i = 0; i < NUM_UPDATES; i++) {
        sleep(1); // wait 1 second
        counter++;
        updated_flag = 1; // signal that counter changed
    }

    pthread_exit(NULL);
    */

}

// Thread 2: prints counter whenever it changes
void* print_thread(void* arg) {
    int last_printed = 0;

    while (last_printed < NUM_UPDATES) {
        if (updated_flag) {
            printf("Counter updated: %d\n", counter);
            updated_flag = 0;       // reset flag
            last_printed = counter; // track last printed value
        } else {
            usleep(100000); // sleep 0.1s to avoid busy waiting
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    printf("Main thread: creating updater and printer threads\n");

    pthread_create(&t1, NULL, update_thread, NULL);
    pthread_create(&t2, NULL, print_thread, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main thread: all threads finished, exiting\n");
    return 0;
}

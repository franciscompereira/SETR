#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

// Signal handler
void handler(int sig, siginfo_t *info, void *context) {
    void (context);
    printf("received signal ...", pthread_self(), sig, info->si_pid);
}

// worker thread

void *worker(void* arg) {
    int id;

    id = *(int*)arg;
    printf("Worker started waiting", id, pthread_self());
    pause();
    printf("worker exited", id, pthread_self());
    return NULL;
}


int main() {

    /*
    pthread_t t1, t2;

    printf("Main thread: creating two threads\n");

    // Create threads
    pthread_create(&t1, NULL, thread_function, NULL);
    pthread_create(&t2, NULL, thread_function, NULL);

    // Give them time to start and block on pause()
    sleep(1);

    // Send signals
    printf("Main thread: sending SIGUSR1 to thread 1\n");
    pthread_kill(t1, SIGUSR1);

    sleep(1);

    printf("Main thread: sending SIGUSR1 to thread 2\n");
    pthread_kill(t2, SIGUSR1);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main thread: both threads finished, exiting now\n");
    return 0;
    */
}

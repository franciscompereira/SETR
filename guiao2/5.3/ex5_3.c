#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>     // For sleep(), pause()
#include <string.h>     // For memset(), strerror()

/**
 * @brief This is the signal handler.
 * It's run by whichever thread receives the signal.
 * We use the advanced sa_sigaction handler to get more info.
 */
void handler(int sig, siginfo_t *info, void *context) {
    // (void)context; // Supress "unused variable" warning
    
    // pthread_self() gets the ID of the thread *currently running this code*
    pthread_t thread_id = pthread_self();
    
    // info->si_pid gets the PID of the process that *sent* the signal
    pid_t sender_pid = info->si_pid;

    printf("  [Thread %lu] Received signal %d from PID %d\n", 
           (unsigned long)thread_id, sig, sender_pid);
    
    // No need to flush stdout here, as the thread will exit,
    // which flushes its buffers.
}

/**
 * @brief This is the worker thread's main function.
 * It just waits to be told to exit.
 */
void *worker(void* arg) {
    int id = *(int*)arg;
    pthread_t thread_id = pthread_self();

    printf("[Worker %d] Starting (Thread ID: %lu). Waiting for signal...\n", 
           id, (unsigned long)thread_id);
    
    // pause() puts the thread to sleep until *any* signal is received.
    // When the signal arrives, the 'handler' runs, and then
    // pause() returns.
    pause();

    printf("[Worker %d] Signal received. Exiting.\n", id);
    return NULL;
}


int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    int ret;
    struct sigaction sa;

    // --- 1. Set up the Signal Handler ---
    // This setup is shared by the whole process, including
    // the threads we are about to create.

    memset(&sa, 0, sizeof(sa));     // Zero out the struct
    sa.sa_sigaction = handler;      // Use the advanced 3-argument handler
    sa.sa_flags = SA_SIGINFO;       // We MUST set this flag to use sa_sigaction
    sigemptyset(&sa.sa_mask);       // Don't block other signals during handling

    // Register this handler for the SIGUSR1 signal
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("[Main] Main thread PID: %d\n", getpid());
    printf("[Main] Creating two threads...\n");

    // --- 2. Create Threads ---
    ret = pthread_create(&t1, NULL, worker, &id1);
    if (ret != 0) {
        fprintf(stderr, "Error creating thread 1: %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    ret = pthread_create(&t2, NULL, worker, &id2);
    if (ret != 0) {
        fprintf(stderr, "Error creating thread 2: %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    // Give the threads a moment to start up and call pause()
    // This helps prevent a "race condition"
    sleep(1); 

    // --- 3. Send Signals ---
    printf("[Main] Sending SIGUSR1 to thread 1 (ID: %lu)\n", (unsigned long)t1);
    ret = pthread_kill(t1, SIGUSR1); // Send signal *only* to thread t1
    if (ret != 0) {
        fprintf(stderr, "Error sending signal to thread 1: %s\n", strerror(ret));
    }

    sleep(1); // Wait one second

    printf("[Main] Sending SIGUSR1 to thread 2 (ID: %lu)\n", (unsigned long)t2);
    ret = pthread_kill(t2, SIGUSR1); // Send signal *only* to thread t2
    if (ret != 0) {
        fprintf(stderr, "Error sending signal to thread 2: %s\n", strerror(ret));
    }
    
    // --- 4. Wait for Threads to Finish ---
    pthread_join(t1, NULL); // Wait for thread 1 to exit
    pthread_join(t2, NULL); // Wait for thread 2 to exit

    printf("[Main] Both threads have finished. Exiting.\n");
    return 0;
}
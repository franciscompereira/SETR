#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t signal_count = 0;

void child_handler(int sig) {
    if (sig == SIGUSR1) {
        signal_count++; // Increment the global counter
        printf("  [CHILD] Received SIGUSR1. Count is now: %d\n", (int)signal_count);
        fflush(stdout); // Force printf to show immediately
    }
}

int main(void){

    pid_t pid;

    pid = fork(); // create a new process

    if (pid < 0){
        perror("fork");
        return 1;
    }


    else if (pid == 0){
        //child process
        printf("Hello from the child process! My PID is %d, my parent is %d\n", getpid(), getppid());
        // Set up the sigaction struct
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = child_handler; // Set our custom handler
        sigemptyset(&sa.sa_mask);

        // Register the handler ONLY for SIGUSR1
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("sigaction SIGUSR1");
            exit(1);
        }

        // Wait until we have received all 10 signals
        while (signal_count < 10) {
            pause(); // Go to sleep and wait for a signal
        }

        printf("  [CHILD] Received 10 signals. Exiting.\n");
        exit(0); // Child terminates successfully    
    } 


    else if (pid > 0){
        //parent process
        printf("Hello from the parent process! My PID is %d, i created child PID %d\n", getpid(), pid);

        for (int i = 0; i < 10; i++){
        kill(pid,SIGUSR1);
        printf("SIGUSR1 message number: %d\n", i+1);
        sleep(1);
        }
        wait(NULL); // wait for the child to finish

    }

    return 0;
}

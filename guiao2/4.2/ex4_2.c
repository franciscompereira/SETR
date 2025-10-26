#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// volatile implica que nao guardemos as 2 variaveis na memoria do CPU dado que vão estar a ser alteradas regularmente
volatile sig_atomic_t is_paused = 0;
volatile sig_atomic_t counter = 0;

void handler (int sig){
    switch(sig){
        case SIGINT:
            printf("Caught signal: SIGINT \n");
            counter = 0;       // Reset the counter
            is_paused = 0;     // Ensure it's not paused
            break;
        case SIGHUP:
            printf("Caught signal: SIGHUP \n");
            is_paused = 1;     // Set the pause flag
            break;
        case SIGUSR1:
            printf("Caught signal: SIGUSR1 \n");
            break;
        case SIGCONT:
            printf("Received SIGCONT (Continue)\n");
            is_paused = 0;
            break;
        default:
            printf("Caught signal: %d\n",sig);    
    }
    fflush(stdout);
}

int main(void){

    struct sigaction sa;  // sa é signal action

    memset(&sa,0,sizeof(sa));

    sa.sa_handler = handler;

    sigemptyset(&sa.sa_mask);

    // Register Handlers in case of signal failure

    if(sigaction(SIGINT , &sa , NULL) ==-1 ){
        perror("Sigaction SIGINT");
        exit(1);
    }

    if(sigaction(SIGHUP, &sa, NULL) == -1){
        perror("sigaction SIGHUP");
        exit(1);
    }

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction SIGUSR1");
        exit(1);
    }
    if (sigaction(SIGCONT, &sa, NULL) == -1) {
        perror("sigaction SIGCONT");
        exit(1);
    }

    printf("Process PID: %d\n", getpid());    // a propria shell cria um child process
    printf("Parent Process PID: %d\n", getppid());
    printf("send me signals with: kill -SIGINT");

    while(1){                                       //loop inf a receber signals
         if (!is_paused) {
            printf("Timer: %d\n", counter);
            counter++;
        }
        sleep(1);
    }

    return 0;
}
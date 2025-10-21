#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler (int sig){

    switch(sig){
        case SIGINT:
            printf("Caught signal: SIGINT \n");
            break;
        case SIGHUP:
            printf("Caught signal: SIGHUP \n");
            break;
        case SIGUSR1:
            printf("Caught signal: SIGUSR1 \n");
            break;
        default:
            printf("Caught signal: %d\n",sig);    
    }
    fflush(stdout);
}

int main(void){
    struct sigaction sa;

    memset(&sa,0,sizeof(sa));

    sa.sa_handler = handler;

    sigemptyset(&sa.sa_mask);

    //Register Handlers
    
    if(sigaction(SIGINT , &sa , NULL) ==-1 ){
        perror("Sigaction SIGINT");
        exit(1);
    }

    //if()

    if(sigaction(SIGHUP, &sa, NULL) == -1){
        perror("sigaction SIGHUP");
        exit(1);
    }

    printf("Process PID: %d\n", getpid());
    printf("send me signals with: kill -SIGINT");

    while(1){
        pause();
    }

    return 0;
}

//kill -KILL PID number

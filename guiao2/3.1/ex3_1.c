#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void){

    pid_t pid;

    printf("Before fork, My PID is %d\n", getpid()); //processo pai

    pid = fork(); // create a new process

    if (pid < 0){

        perror("fork");
        return 1;
    }

    else if (pid == 0){
        //child process
        printf("Hello from the child process! My PID is %d, my parent is %d\n", getpid(), getppid());
    }
    else {
        //parent process
        printf("Hello from the parent process! My PID is %d, i created child PID %d\n", getpid(), pid);
    }

}
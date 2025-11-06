#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // For exit(), EXIT_FAILURE
#include <errno.h>  // For errno
#include <string.h> // For strerror()

int main(int argc, char *argv[]){

   const char *path_fifo;
    int fd;
    int num;

    if (argc != 2){
        fprintf(stderr, "Usage: %s <fifo_path>\n", argv[0]);
        exit(1);
    }

    // config da pipe

    path_fifo = argv[1];

    if (mkfifo(path_fifo,0666) == -1){
        if (errno != EEXIST) {
            fprintf(stderr, "[Producer] Could not create FIFO: %s\n", strerror(errno));
            exit(1);
        }
    printf("[Producer] FIFO already exists. Connecting...\n");
    } else{
        printf("[Producer] Created new FIFO: %s \n", path_fifo);
    }

    // entrada e uso da pipe

    fd = open(path_fifo, O_RDONLY);
    if(fd == -1){
        perror("[Consumer] Failed to open FIFO");
        exit(1);
    }
    printf("[Consumer] connected! Enter numbers (Ctrl+D to quit): \n");

    while(read(fd,&num,sizeof(num)) == sizeof(num)){
        printf("[Consumer] Received: %d\n", num);
    }

    printf("[Consumer] Producer disconnected. Closing pipe.\n");
    close(fd);
    return 0;
}
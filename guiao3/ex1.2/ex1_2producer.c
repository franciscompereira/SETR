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

    fd = open(path_fifo, O_WRONLY);
    if (fd == -1) {
        perror("[Producer] Failed to open FIFO");
        exit(1);
    } else{
        printf("[Producer] Consumer connected! Enter numbers (Ctrl+D to quit):\n");
    }

    while (scanf("%d", &num) == 1){
        printf("[Producer] Sending: %d\n", num);
        if (write(fd, &num, sizeof(num)) == -1) {
            perror("[Producer] Write error");
            break;
        }
    }

    printf("[Producer] Done. Closing pipe.\n");
    close(fd);
    unlink(path_fifo); // Producer is in charge of deleting the pipe
    return 0;

    return 0;
}
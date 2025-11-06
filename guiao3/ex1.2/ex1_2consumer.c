#define window_size 5
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
    ssize_t bytes_read;
    int buffer[window_size] = {0}; // Initialize our window to all zeros
    int index = 0;                 // Current position in the buffer
    int count = 0;                 // How many numbers we've read so far
    double sum = 0.0;              // Current sum of the buffer (use double for floats)

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
    printf("[Consumer] FIFO already exists. Connecting...\n");
    } else{
        printf("[Consumer] Created new FIFO: %s \n", path_fifo);
    }

    // entrada e uso da pipe

    fd = open(path_fifo, O_RDONLY);
    if(fd == -1){
        perror("[Consumer] Failed to open FIFO");
        exit(1);
    }
    printf("[Consumer] connected! Enter numbers (Ctrl+D to quit): \n");

    while ((bytes_read = read(fd, &num, sizeof(num))) > 0){

        printf("[Consumer] Received: %d\n", num);
        sum -= buffer[index];
        sum += num;
        buffer[index] = num;
        index = (index + 1) % window_size;
        if (count < window_size) {
            count++;
            printf("[Consumer] ... buffering data (%d/%d)\n", count, window_size);
        } else {
            double average = sum / window_size;
            printf("[Consumer] MOVING AVERAGE: %.2f\n", average);
        }
    }
    
    if (bytes_read == 0) {
        printf("[Consumer] Producer disconnected (EOF). Exiting.\n");
    } else {
        // This will run if read() fails
        perror("[Consumer] read error");
    }
    close(fd);
    return 0;
}
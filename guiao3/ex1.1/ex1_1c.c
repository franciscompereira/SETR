#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // For exit(), EXIT_FAILURE
#include <errno.h>  // For errno
#include <string.h> // For strerror()


// Comments from original code:
//int mkfifo("numberPipe",0066);     cria uma pipe
//int fd = open(const char *pathname, int flags); abre a pipe para ler ou para escrever
//RDONLY
//WRONLY
//write(fd, "Hello", 5)
//int d = read(int fd, void *buf, size_t count);

int main(int argc, char *argv[])
{
    const char *path_fifo;
    int fd;
    int num;
    ssize_t bytes_read;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fifo_path>\n", argv[0]);
        exit(EXIT_FAILURE); // Exit on incorrect usage
    }

    path_fifo = argv[1];
    printf("[Consumer] Using FIFO path: %s\n", path_fifo);

    printf("[Consumer] Opening FIFO for reading (will block until producer opens)...\n");
    fd = open(path_fifo, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }
    printf("[Consumer] FIFO opened. Waiting for data...\n");

    while ((bytes_read = read(fd, &num, sizeof(num))) == sizeof(num))
    {
        printf("[Consumer] Received number: %d\n", num);
    }

    if (bytes_read == 0) {
        printf("[Consumer] Producer closed the pipe (EOF).\n");
    } else if (bytes_read == -1) {
        perror("read failed");
    } else {
        // This case handles partial reads, which might indicate an issue
        fprintf(stderr, "[Consumer] Received incomplete data (%zd bytes) before EOF/error.\n", bytes_read);
    }

    printf("[Consumer] Closing FIFO.\n");
    if (close(fd) == -1) {
        perror("close failed");
    }

    printf("[Consumer] Exiting.\n");
    return 0; // Return 0 for success
}

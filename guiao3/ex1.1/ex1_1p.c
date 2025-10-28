#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // For exit(), EXIT_FAILURE
#include <errno.h>  // For errno
#include <string.h> // For strerror()

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

    // Check argument count
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fifo_path>\n", argv[0]);
        exit(EXIT_FAILURE); // Exit on incorrect usage
    }

    path_fifo = argv[1];
    printf("[Producer] Using FIFO path: %s\n", path_fifo);

    // Create the FIFO
    printf("[Producer] Attempting to create FIFO...\n");
    if (mkfifo(path_fifo, 0666) == -1) {
        // EEXIST means it already exists, which is okay.
        if (errno != EEXIST) {
            perror("mkfifo failed");
            exit(EXIT_FAILURE);
        }
        printf("[Producer] FIFO already exists, reusing.\n");
    } else {
        printf("[Producer] FIFO created successfully.\n");
    }

    // Open the FIFO for writing
    printf("[Producer] Opening FIFO for writing (will block until consumer opens)...\n");
    fd = open(path_fifo, O_WRONLY);
    if (fd == -1) {
        perror("open failed");
        // Don't unlink if open failed, consumer might need it or already have it open
        exit(EXIT_FAILURE);
    }
    printf("[Producer] FIFO opened. Enter integers (non-integer or Ctrl+D to quit):\n");

    // Read loop
    while (scanf("%d", &num) == 1) // verifica que foi lido com sucesso
    {
        printf("[Producer] Writing number: %d\n", num);
        ssize_t bytes_written = write(fd, &num, sizeof(num));
        if (bytes_written == -1) {
            perror("write failed");
            break; // Stop if write fails
        } else if (bytes_written < sizeof(num)) {
            fprintf(stderr, "[Producer] Warning: Incomplete write occurred.\n");
        }
    }

    // Cleanup
    printf("[Producer] End of input detected. Closing FIFO.\n");
    if (close(fd) == -1) {
        perror("close failed");
        // Continue to unlink even if close fails
    }

    printf("[Producer] Removing FIFO '%s'.\n", path_fifo);
    if (unlink(path_fifo) == -1) {
         perror("unlink failed");
         // Exit with error if unlink fails? Or just report? For now, report.
    }

    printf("[Producer] Exiting.\n");
    return 0; // Return 0 for success
}

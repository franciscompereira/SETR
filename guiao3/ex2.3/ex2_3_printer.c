#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>   
#include <stdint.h>     
#define BUFFER_SIZE 10

const char *SHM_NAME = "/my_ring_buffer";

struct SharedRingBuffer {
    volatile int head;
    volatile int tail;
    uint16_t buffer[BUFFER_SIZE];
};

int main() {
    int shm_fd;
    struct SharedRingBuffer *shared_data; // This will be our pointer to the shared memory
    uint16_t value;

    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open (is the producer running?)");
        exit(1);
    }

    shared_data = (struct SharedRingBuffer *)mmap(
        0, 
        sizeof(struct SharedRingBuffer), 
        PROT_READ | PROT_WRITE, 
        MAP_SHARED, 
        shm_fd, 
        0
    );

    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("[Consumer] Mapped. Waiting for items...\n");

    for (int i = 1; i <= 20; i++) {

        while (shared_data->head == shared_data->tail) {
        }

        value = shared_data->buffer[shared_data->tail];
        printf("[Consumer] Read: %u (from index %d)\n", value, shared_data->tail);

        shared_data->tail = (shared_data->tail + 1) % BUFFER_SIZE;

        if (i % 4 == 0) {
            printf("[Consumer] *** Long sleep (10s) ***\n");
            sleep(10);
        } else {
            printf("[Consumer] Short sleep (1s)\n");
            sleep(1);
        }
    }

    printf("[Consumer] Finished 20 items. Cleaning up and exiting.\n");
    
    munmap(shared_data, sizeof(struct SharedRingBuffer));
    close(shm_fd);

    return 0;
}
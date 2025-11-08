#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>   // For mmap, shm_open, etc.
#include <sys/stat.h>   // For ftruncate
#include <stdint.h>     // For uint16_t
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
 
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, sizeof(struct SharedRingBuffer)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    shared_data = (struct SharedRingBuffer *)mmap(0, sizeof(struct SharedRingBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("[Producer] Mapped. Initializing buffer...\n");

    shared_data->head = 0;
    shared_data->tail = 0;

    for (uint16_t i = 1; i <= 20; i++) {
        while ((shared_data->head + 1) % BUFFER_SIZE == shared_data->tail) {}
        shared_data->buffer[shared_data->head] = i;
        printf("[Producer] Wrote: %u (at index %d)\n", i, shared_data->head);
        shared_data->head = (shared_data->head + 1) % BUFFER_SIZE;
    }

    printf("[Producer] Finished. Cleaning up and exiting.\n");
    
    munmap(shared_data, sizeof(struct SharedRingBuffer));
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return 0;
}
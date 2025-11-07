#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> 

const char *SHM_NAME = "/my_shm_counter";  // tem barra no ínicio devido a especificação do Kernel
const size_t SHM_SIZE = sizeof(int);       // como apenas vamos guardar 1 valor de int de cada vez apenas precisamos do tamanho de 1 inteiro (4 bytes)

int main(){

    int shm_fd;
    int *shared_counter_ptr;

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666); // criar shared memmory, com nome, flag e mode
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    int size = ftruncate(shm_fd, SHM_SIZE);
    if ( size == -1) {                                   // definir tamanho shared memmory
        perror("ftruncate");
        exit(1);
    }

   
    shared_counter_ptr = (int *)mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);  // 0 em mmap diz que não queremos saber qual é o endereço
    if (shared_counter_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("[Writer] Mapped. Starting counter... (Press Ctrl+C to stop)\n");

    *shared_counter_ptr = 0;
    while (1) {
        *shared_counter_ptr = *shared_counter_ptr + 1;
        printf("[Writer] Incremented to: %d\n", *shared_counter_ptr);
        sleep(1);
    }

    return 0;
}
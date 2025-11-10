#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char* argv[]){

    const char* path_fifo;
    int fd;
    int num;

    if(argc != 2){
        //fprintf(stderr, "Usage: %s <fifo_path>\n", argv[0]);        
        exit(1);
    }

    path_fifo = argv[1];  // pipeline name
    printf("[Producer] Using FIFO path: %s\n", path_fifo);
    if(mkfifo(path_fifo, 0666) == -1){
        if(errno != EEXIST){
            perror("FIFO Generation Error");
            exit(EXIT_FAILURE);
        }
        // in case the path already exists
        printf("[Producer] path already exists \n");
    }else {
        printf("FIFO created successfully \n");
    }

    fd = open(path_fifo,O_WRONLY);
    if (fd == -1){
        perror("[Producer] Error writing");
        exit(EXIT_FAILURE);
    }

    printf("[Producer] FIFO opened. Enter integers: \n");

    while(scanf("%d", &num) == 1){
        printf("producer sending num: %d \n", num);
        if(write(fd,&num, sizeof(int)) == -1){
                perror ("Producer writing error");
                break;
        }
    }
    
    printf("[Producer] Done Writing, now closing FIFO \n");
    close(fd);
    unlink(path_fifo);

    return 0;
}
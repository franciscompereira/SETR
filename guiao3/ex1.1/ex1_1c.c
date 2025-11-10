#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char* argv[]){
    char* path_fifo;
    int fd;
    int num;

    if(argc != 2){
        fprintf(stderr,"Number of arguments incorrect: %s", argv[0]);
        exit(EXIT_FAILURE);
    }

    path_fifo = argv[1];
    printf("[Consumer] is using the pipe: %s \n",path_fifo);

    if(mkfifo(path_fifo,0666) == -1){
        if(errno != EEXIST){
            perror("error creating pipeline");
            exit(EXIT_FAILURE);
        }
        printf("[Consumer] Path already exists \n");
    }else{
        printf("FIFO created successfully");
    }

    fd = open(path_fifo,O_RDONLY);
    if(fd == -1){
        perror("[Consumer] error opening");
        exit(EXIT_FAILURE);
    }

    printf("[Consumer] FIFO opened \n");

    while(read(fd,&num,sizeof(int))){
    printf("[Consumer] Received: %d\n", num);
    }


    printf("[Consumer] Done Writing, now closing FIFO \n");
    close(fd);
    unlink(path_fifo);

    return 0;
}
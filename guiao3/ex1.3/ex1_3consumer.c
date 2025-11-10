#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define window_size 5


int main(int argc, char* argv[]){
    char* path_fifo;
    int fd;
    int num;
    int buffer[window_size] = {0};
    int index;
    int count = 0;
    double average = 0.0;
    double sum = 0.0;

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

        sum = sum - buffer[index]; // ir retirando ultimos numero
        sum += num;                // acrescentar ultimo numero na sma
        buffer[index] = num;       // acrescentar ultimo nmero no buffer
        index = (index +1) % window_size;  //reposicionar index

        if (count < window_size) {
            count++;
            //printf("[Consumer] ... buffering data (%d/%d)\n", count, window_size);
        } else {
            // Buffer is full, so we can now print the average
            double average = sum / window_size;
            printf("[Consumer] MOVING AVERAGE: %.2f\n", average); // Use %.2f for a double
            if(average < 80){
                printf("Too cold! \n");
            }else if(average >= 80 && average <= 95){
                printf("Fine! \n");
            }else if(average > 95){
                printf("Too hot! \n");
            }
        }
    }


    printf("[Consumer] Done Writing, now closing FIFO \n");
    close(fd);
    // unlink(path_fifo);

    return 0;
}
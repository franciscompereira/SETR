#include <stdlib.h>
#include <stdio.h>



int main(int argc, char *argv){   //argc é sempre pelo menos 1, dado que o comando em si já ocupa 1 posição
    
    char command[50];
    int ret = 0;

    if(argc < 2){
        return 1;
    }

    snprintf(command,sizeof(command), "wc -w -m \"%s\"", argv[1]);

    ret = system(command);

    if(ret == -1){
        perror("System");
        return -1;
    }

    return 0;
}
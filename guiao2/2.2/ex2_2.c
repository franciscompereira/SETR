#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    char command[50];
    int ret = 0;

    if(argc != 2){
        // printf("Error! Number of input files incorrect");
        return 1;
    }

    execlp("wc", "wc", "-w", "-m", argv[1], NULL);  // segundo "wc" é arg[0] null define o fim da lista 

    perror("execlp");            // faz com que vejamos isto na consola -> system: No such file or directory

    return 0;
}

// para testar o código basta fazer o seguinte:
// 1º -> echo "Hello world this is a test" > test.txt
// 2º -> cat test.txt
// 3º -> ./count test.txt, count é o nome do teste colocado antes para correr o código em gcc

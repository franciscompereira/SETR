#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){   // argc é sempre pelo menos 1, dado que o comando em si já ocupa 1 posição
    
    char command[50];               // armazena o shell que vamos executar
    int ret = 0;                    // veriável de retorno

    if(argc < 2){
        return 1;                   // argc = 2 pois ao compilar teremos de ler pelo menos program name + text_filename
    }

    snprintf(command,sizeof(command), "wc -w -m \"%s\"", argv[1]); // -w -> word e -m -> chars, ver mais em man wc
                                                                   // \"%s\" -> placeholder for the filename.

    ret = system(command);           // syscall retorna 0 se tiver sucesso e -1 caso não tenha sucesso

    if(ret == -1){
        perror("System");            // faz com que vejamos isto na consola -> system: No such file or directory
        return -1;                   // return -1 means error
    }

    return 0;
}

// para testar o código basta fazer o seguinte:
// 1º -> echo "Hello world this is a test" > test.txt
// 2º -> cat test.txt
// 3º -> ./count test.txt, count é o nome do teste colocado antes para correr o código em gcc


// o que acontece no fim de contas é 

// na verdade ./count myfile.txt é basicamente wc -w -m "myfile.txt"

// o system corre comandos externos a partir de código
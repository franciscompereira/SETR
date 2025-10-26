#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char foldername[100];
    int n;

    if (argc != 3){     
        return 1;              // são obrigatorios 3 argumentos: programa + string + number
    }

    n = atoi(argv[2]);         // passar segundo argumento de string para inteiro
    if(n < 1 || n > 99){
        return 1;              // garantir numero de directories entre 1 e 99
    }

    for (int i = 0; i <= n; i++){
        snprintf(foldername, sizeof(foldername), "%s%d", argv[1], i);

        printf("Creating folder: %s\n", foldername);

        execlp("mkdir", "mkdir", foldername, NULL);  // so corre uma vez
        

        //perror("execlpfailed");  // apenas chega aqui caso dê erro
        //return 1;
    }

    return 0;
}
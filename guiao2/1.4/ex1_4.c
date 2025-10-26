#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char command[100];
    int n;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <name> <n>\n", argv[0]);         //garantir que tenho 3 argumentos a compilar
        return 1;
    }

    n = atoi(argv[2]);
    if (n < 1 || n > 99) {
        fprintf(stderr, "Error: n must be between 1 and 99.\n");   // garantir que  valor está entre 1 e 99 
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        snprintf(command, sizeof(command), "rmdir \"%s%d\"", argv[1], i);           // escreve na consola de rmdir de quantas pasta houver

        printf("Removing folder: %s%d\n", argv[1], i);

        if (system(command) == -1) {
            perror("system");                                                       // caso dê erro return 1 para acabar
            return 1;
        }
    }

    return 0;
}

// para testar o código basta fazer o seguinte:
// 1º -> echo "Hello world this is a test" > test.txt
// 2º -> cat test.txt
// 3º -> ./count test.txt num_pretendido, count é o nome do teste colocado antes para correr o código em gccS
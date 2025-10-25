#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    char command[100];
    int n;                      //number of files that will be created

    if (argc != 3) {            // Check if user provided both arguments
        fprintf(stderr, "Usage: %s <name> <n>\n", argv[0]);
        return 1;
    }

    // Convert second argument (string) to integer
    n = atoi(argv[2]);
    if (n < 1 || n > 99) {
        fprintf(stderr, "Error: n must be between 1 and 99.\n"); //print formatado
        return 1;
    }

    // Loop to create n folders
    for (int i = 1; i <= n; i++) {
        snprintf(command, sizeof(command), "rmdir %s%d", argv[1], i);

        // Execute mkdir command
        if (system(command) == -1) {
            perror("system");
            return 1;
        }

        printf("Deleted folder: %s%d\n", argv[1], i);
    }

    return 0;
}

// para testar o código basta fazer o seguinte:
// 1º -> echo "Hello world this is a test" > test.txt
// 2º -> cat test.txt
// 3º -> ./count test.txt num_pretendido, count é o nome do teste colocado antes para correr o código em gccS
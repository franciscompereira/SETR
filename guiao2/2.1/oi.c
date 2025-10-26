#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    printf("Executing 'ps aux' using exec only...\n");


    execlp("ps", "ps", "aux", NULL);                    // l -> list, p -> path, o l é conveniente porque podemos passar o arg em lista e o p é conveniente porque basta escrever o comando 
                                                        // que pretendemos sem dar detalhes quanto ao path

    return 0;
}
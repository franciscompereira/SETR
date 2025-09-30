#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex2_1.h"

                    //main apenas para testar 2.2

void swap(int **a, int **b);

int main(void) {
    int x = 5, y = 10;
    int *px = &x;
    int *py = &y;

    printf("Antes do swap: x = %d, y = %d\n", *px, *py);

    swap(&px, &py);  // passa o endereço dos ponteiros

    printf("Depois do swap: x = %d, y = %d\n", *px, *py);

    return 0;
}
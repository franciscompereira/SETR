#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex2_1.h"
#include "ex2_2.h"

int main(void){
    srand(time(NULL));

                // definição variáveis de teste
    int N = 10;
    int M = 50;
    double average;
    int max;
    int min;

    int arr[N];     // definir array

    dyn_array_stats(arr,N,M,&average,&max,&min);

    printf("Array 2.1: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nAverage: %.2f, Max: %d, Min: %d\n", average, max, min);

    swap(&arr[0],&arr[3]);

    printf("Array 2.2: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
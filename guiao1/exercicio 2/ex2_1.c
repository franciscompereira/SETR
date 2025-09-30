#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex2_2.h"

void dyn_array_stats(int *arr, int N, int M, double *average, int*max, int *min);

void dyn_array_stats(int *arr, int N, int M, double *average, int*max, int *min){
    int sum = 0;
    *max = 0;
    *min = M + 1;

    for (int i = 0; i < N; i++){
        arr[i] = (rand() % M) + 1;  // atribuir nums aleatorios para o intervalo [ 1; M]
        sum += arr[i];              // sum vai conter a soma de todos os valores do array
        if (arr[i] > *max){
            *max = arr[i];         // define o valor mais alto até agora como maximo
        }

        if (arr[i] < *min){
            *min = arr[i];         // define o valor mais baixo até agora como minimo
        }                           // duvida aqui?
    }

    *average = (double) sum / N;

}
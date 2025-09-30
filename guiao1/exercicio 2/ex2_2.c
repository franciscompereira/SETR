#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex2_1.h"

void swap(int *a, int *b) {
    int *temp = *a;
    *a = *b;
    *b = temp;
}

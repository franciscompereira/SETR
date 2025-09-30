#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex2_3.h"

int main(void){
    char str[] = "OpenAI";
    printf("Original: %s\n", str);

    reverse_string(str);

    printf("Invertida: %s\n", str);
    return 0;
}


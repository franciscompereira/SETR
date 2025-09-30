#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex2_3.h"

void reverse_string (char *str){
    char *start = str;             // ponteiro início string
    char *end = str;               // ponteiro fim string

    // 1️⃣ - Avança 'end' até ao último carácter
    while (*end != '\0') {
        end++;
    }
    end--; // recua 1 porque agora está no '\0'

    // 2️⃣ - Troca caracteres até se encontrarem a meio
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;

        start++; // avança do início
        end--;   // recua do fim
    }
}





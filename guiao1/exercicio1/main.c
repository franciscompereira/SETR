#include <stdio.h>
#include "configData.h"

extern uint16_t maxConnections;

int main(void) {
// Initialize maxConnections to 0
    configInit();
    printf("maxConnections initialzed, value is %d\n");

    maxConnections = 25;
    printf("Updated maxConnections");

    //incompleto
}
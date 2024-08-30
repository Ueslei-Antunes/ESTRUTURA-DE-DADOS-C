#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

int main() {
    char palavra1[] = "mamam";
    char palavra2[] = "hello";

    if (palindroma(palavra1)) {
        printf("'%s' e uma palavra palindroma.\n", palavra1);
    } else {
        printf("'%s' nao e uma palavra palindroma.\n", palavra1);
    }

    if (palindroma(palavra2)) {
        printf("'%s' e uma palavra palindroma.\n", palavra2);
    } else {
        printf("'%s' nao e uma palavra palindroma.\n", palavra2);
    }

    return 0;
}
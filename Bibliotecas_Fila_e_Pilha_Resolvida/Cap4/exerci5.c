#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

int main() {
    pDPilha pilha1 = criarPilha();
    pDPilha pilha2 = criarPilha();

    int a = 1, b = 2, c = 3;
    int d = 3, e = 1, f = 2;

    empilharInfo(pilha1, &a);
    empilharInfo(pilha1, &b);
    empilharInfo(pilha1, &c);

    empilharInfo(pilha2, &d);
    empilharInfo(pilha2, &e);
    empilharInfo(pilha2, &f);

    if (iguais(pilha1, pilha2, compararInteiros)) {
        printf("As pilhas sao iguais.\n");
    } else {
        printf("As pilhas nao sao iguais.\n");
    }
    return 0;
}
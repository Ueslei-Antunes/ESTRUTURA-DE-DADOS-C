#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

int main() {
    pDPilha pilhaOriginal = criarPilha();
    int a = 1, b = 2, c = 3;

    // Empilhar elementos na pilha original
    empilharInfo(pilhaOriginal, &a);
    empilharInfo(pilhaOriginal, &b);
    empilharInfo(pilhaOriginal, &c);

    // Copiar a pilha
    pDPilha pilhaCopia = copia(pilhaOriginal, alocarInteiro);

    // Exibir elementos da pilha original
    printf("Pilha original: ");
    while (!pilhaVazia(pilhaOriginal)) {
        printf("%d ", *(int*)desempilharInfo(pilhaOriginal));
    }
    printf("\n");

    // Exibir elementos da pilha copiada
    printf("Pilha copiada: ");
    while (!pilhaVazia(pilhaCopia)) {
        printf("%d ", *(int*)desempilharInfo(pilhaCopia));
    }
    printf("\n");

    // Limpeza de memória
    free(pilhaOriginal);
    free(pilhaCopia);

    return 0;
}
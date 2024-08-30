#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

int main() {
    pDFila fila = criarFila();

    // Enfileira alguns números
    int* x = malloc(sizeof(int));
    int* y = malloc(sizeof(int));
    *x = 1;
    *y = 2;

    enfileirarInfo(fila, x);
    enfileirarInfo(fila, y);

    // Imprime a fila antes da trocaw
    printf("Fila antes da troca: ");
    pDFila tempFila = criarFila(); // Fila temporária para impressão
    while (!filaVazia(fila)) {
        int* elemento = desenfileirarInfo(fila);
        printf("%d ", *elemento);
        enfileirarInfo(tempFila, elemento);
    }
    printf("\n");

    // Restaura a fila original a partir da fila temporária
    while (!filaVazia(tempFila)) {
        enfileirarInfo(fila, desenfileirarInfo(tempFila));
    }

    // Troca os elementos 1 e 2
    troca(fila, 1, 2);

    // Imprime a fila após a troca
    printf("Fila apos troca: ");
    while (!filaVazia(fila)) {
        int* elemento = desenfileirarInfo(fila);
        printf("%d ", *elemento);
        free(elemento);  // Libera a memória após o uso
    }
    printf("\n");

    destruirFila(tempFila); // Destroi a fila temporária

    return 0;
}

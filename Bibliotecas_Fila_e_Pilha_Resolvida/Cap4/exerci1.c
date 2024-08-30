#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fila.h"

int main() {
    pDFila fila = criarFila(); // Cria uma fila vazia

    // Aloca e insere alguns elementos na fila
    enfileirarInfo(fila, strdup("A"));
    enfileirarInfo(fila, strdup("B"));
    enfileirarInfo(fila, strdup("C"));
    enfileirarInfo(fila, strdup("D"));
    enfileirarInfo(fila, strdup("E"));

    // Cria uma cópia da fila original para impressão sem esvaziar a fila original
    pDFila filaCopia = criarFila();
    pDFila tempFila = criarFila(); // Fila temporária para manutenção da fila original

    // Copia elementos da fila original para a filaCopia e a tempFila
    while (!filaVazia(fila)) {
        void* elem = desenfileirarInfo(fila);
        enfileirarInfo(filaCopia, elem);
        enfileirarInfo(tempFila, elem);
    }

    // Restaura a fila original a partir da tempFila
    while (!filaVazia(tempFila)) {
        enfileirarInfo(fila, desenfileirarInfo(tempFila));
    }

    // Imprime a fila original
    printf("Fila original: ");
    while (!filaVazia(filaCopia)) {
        printf("%s ", (char*)desenfileirarInfo(filaCopia));
    }
    printf("\n");

    // Inverte a fila original
    fila = inverteFila(fila);

    // Imprime a fila invertida
    printf("Fila invertida: ");
    while (!filaVazia(fila)) {
        printf("%s ", (char*)desenfileirarInfo(fila));
    }
    printf("\n");

    // Destroi as filas
    destruirFila(fila);
    destruirFila(filaCopia);
    destruirFila(tempFila);

    return 0;
}
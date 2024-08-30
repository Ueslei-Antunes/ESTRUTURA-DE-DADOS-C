#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fila.h"

int main() {
    pDFila filaOriginal = criarFila();
    enfileirarInfo(filaOriginal, strdup("A"));
    enfileirarInfo(filaOriginal, strdup("B"));
    enfileirarInfo(filaOriginal, strdup("C"));

    pDFila filaCopiada = copiaF(filaOriginal, alocaString);

    // Imprimir as filas para verificar a cópia
    printf("Fila original: ");
    while (!filaVazia(filaOriginal)) {
        printf("%s ", (char*)desenfileirarInfo(filaOriginal));
    }
    printf("\n");

    printf("Fila copiada: ");
    while (!filaVazia(filaCopiada)) {
        printf("%s ", (char*)desenfileirarInfo(filaCopiada));
    }
    printf("\n");

    // Destroi as filas
    destruirFila(filaOriginal);
    destruirFila(filaCopiada);

    return 0;
}

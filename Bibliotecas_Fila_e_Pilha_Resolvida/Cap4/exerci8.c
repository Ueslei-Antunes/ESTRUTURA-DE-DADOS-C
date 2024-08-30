#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

// Função para remover um elemento específico da pilha
int removePorInfo(pDPilha pilha, void* info, FuncaoComparacao fc) {
    pDPilha pilhaAux = criarPilha(); // Cria uma pilha auxiliar
    int removido = 0;  // Flag para indicar se o elemento foi removido

    // Enquanto a pilha original não estiver vazia
    while (!pilhaVazia(pilha)) {
        void* elemento = desempilharInfo(pilha); // Desempilha o topo da pilha original

        // Se o elemento atual é o que queremos remover
        if (fc(elemento, info) == 0) {
            removido = 1;  // Sinaliza que o elemento foi encontrado e removido
            // Não empilha na pilha auxiliar, efetivamente removendo-o
            // Lembre-se de liberar a memória se necessário
        } else {
            empilharInfo(pilhaAux, elemento);  // Empilha o elemento na pilha auxiliar
        }
    }

    // Reempilha os elementos da pilha auxiliar de volta na pilha original
    while (!pilhaVazia(pilhaAux)) {
        empilharInfo(pilha, desempilharInfo(pilhaAux));
    }

    // Libera a memória da pilha auxiliar
    free(pilhaAux);

    return removido;  // Retorna 1 se o elemento foi removido, 0 caso contrário
}
// Função de comparação para inteiros
int compararinteiros(void* a, void* b) {
    return (*(int*)a == *(int*)b) ? 0 : 1;
}

int main() {
    pDPilha pilha = criarPilha();
    int a = 1, b = 2, c = 3, d = 4;

    // Empilhar elementos na pilha
    empilharInfo(pilha, &a);
    empilharInfo(pilha, &b);
    empilharInfo(pilha, &c);
    empilharInfo(pilha, &d);

    // Exibir a pilha antes da remoção
    printf("Pilha antes da remocao: ");
    pDPilha pilhaAux = criarPilha();
    while (!pilhaVazia(pilha)) {
        int* elem = desempilharInfo(pilha);
        printf("%d ", *elem);
        empilharInfo(pilhaAux, elem);  // Reempilha na auxiliar para restaurar a original
    }
    while (!pilhaVazia(pilhaAux)) {
        empilharInfo(pilha, desempilharInfo(pilhaAux));
    }
    printf("\n");

    // Remover o elemento com valor 3
    int elementoRemover = 3;
    if (removePorInfo(pilha, &elementoRemover, compararinteiros)) {
        printf("Elemento %d removido.\n", elementoRemover);
    } else {
        printf("Elemento %d nao encontrado.\n", elementoRemover);
    }

    // Exibir a pilha após a remoção
    printf("Pilha apos a remocao: ");
    while (!pilhaVazia(pilha)) {
        int* elem = desempilharInfo(pilha);
        printf("%d ", *elem);
        empilharInfo(pilhaAux, elem);  // Reempilha na auxiliar para restaurar a original
    }
    while (!pilhaVazia(pilhaAux)) {
        empilharInfo(pilha, desempilharInfo(pilhaAux));
    }
    printf("\n");

    // Limpeza de memória
    free(pilha);
    free(pilhaAux);

    return 0;
}

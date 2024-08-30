#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

// Função recursiva para limpar a pilha
void limpaPilha(pDPilha pilha, FuncaoLiberacao fl) {
    if (!pilhaVazia(pilha)) {
        // Remove o elemento do topo da pilha
        void* elemento = desempilharInfo(pilha);
        
        // Chama recursivamente para limpar o restante da pilha
        limpaPilha(pilha, fl);
        
        // Libera a memória do elemento removido usando a função de liberação
        fl(elemento);
    }
}

// Função de liberação para inteiros
void liberarInteiro(void* elemento) {
    free(elemento);
}

int main() {
    pDPilha pilha = criarPilha();
    int *a = malloc(sizeof(int)), *b = malloc(sizeof(int)), *c = malloc(sizeof(int));

    // Inicializando valores
    *a = 1; *b = 2; *c = 3;

    // Empilhar elementos
    empilharInfo(pilha, a);
    empilharInfo(pilha, b);
    empilharInfo(pilha, c);

    // Limpar a pilha usando a função limpaPilha
    limpaPilha(pilha, liberarInteiro);

    // A pilha deve estar vazia agora, então podemos liberá-la
    free(pilha);

    return 0;
}

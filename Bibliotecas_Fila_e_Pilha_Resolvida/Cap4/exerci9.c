#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

// Função para destruir uma pilha (libera memória)
void destruirPilha(pDPilha pilha) {
    while (!pilhaVazia(pilha)) {
        free(desempilharInfo(pilha));
    }
    free(pilha);
}

// Função de comparação para inteiros
int compararinteiro(void* a, void* b) {
    return (*(int*)a == *(int*)b) ? 0 : 1;
}

// Função para encontrar a interseção de duas pilhas
pDPilha interseccao(pDPilha pilha1, pDPilha pilha2, FuncaoComparacao fc) {
    pDPilha pilhaResultado = criarPilha();  // Pilha para armazenar o resultado da interseção
    pDPilha pilhaAux1 = criarPilha();       // Pilha auxiliar para manipulação da pilha1
    pDPilha pilhaAux2 = criarPilha();       // Pilha auxiliar para manipulação da pilha2

    if (!pilhaResultado || !pilhaAux1 || !pilhaAux2) {
        // Verifica se todas as pilhas foram criadas corretamente
        fprintf(stderr, "Erro ao criar pilhas auxiliares ou de resultado.\n");
        exit(EXIT_FAILURE);
    }

    // Criar cópias das pilhas originais para não modificá-las diretamente
    pDPilha copiaPilha1 = copia(pilha1, alocarInteiro);
    pDPilha copiaPilha2 = copia(pilha2, alocarInteiro);

    if (!copiaPilha1 || !copiaPilha2) {
        fprintf(stderr, "Erro ao criar cópias das pilhas originais.\n");
        exit(EXIT_FAILURE);
    }

    // Percorre a primeira pilha
    while (!pilhaVazia(copiaPilha1)) {
        void* elemento1 = desempilharInfo(copiaPilha1);
        int encontrado = 0;

        // Verifica se o elemento está presente na segunda pilha
        while (!pilhaVazia(copiaPilha2)) {
            void* elemento2 = desempilharInfo(copiaPilha2);
            if (fc(elemento1, elemento2) == 0) {
                encontrado = 1; // Elemento comum encontrado
                break; // Sai do loop ao encontrar o primeiro elemento comum
            }
            empilharInfo(pilhaAux2, elemento2);  // Empilha de volta na pilha auxiliar
        }

        // Se o elemento é comum, empilha na pilha de resultado
        if (encontrado) {
            empilharInfo(pilhaResultado, alocarInteiro(elemento1)); // Usa a função de alocação para criar uma nova cópia do elemento
        }

        // Restaura a segunda pilha
        while (!pilhaVazia(pilhaAux2)) {
            empilharInfo(copiaPilha2, desempilharInfo(pilhaAux2));
        }

        // Empilha o elemento da primeira pilha de volta na pilha auxiliar
        empilharInfo(pilhaAux1, elemento1);
    }

    // Restaura a primeira pilha
    while (!pilhaVazia(pilhaAux1)) {
        empilharInfo(copiaPilha1, desempilharInfo(pilhaAux1));
    }

    // Libera a memória das pilhas auxiliares e cópias
    destruirPilha(pilhaAux1);
    destruirPilha(pilhaAux2);
    destruirPilha(copiaPilha1);
    destruirPilha(copiaPilha2);

    return pilhaResultado;  // Retorna a nova pilha com a interseção
}

int main() {
    pDPilha pilha1 = criarPilha();
    pDPilha pilha2 = criarPilha();
    int *a = malloc(sizeof(int)), *b = malloc(sizeof(int)), *c = malloc(sizeof(int)), 
        *d = malloc(sizeof(int)), *e = malloc(sizeof(int)), *f = malloc(sizeof(int));

    // Inicializando valores
    *a = 1; *b = 2; *c = 3; *d = 4; *e = 5; *f = 3;

    // Empilhar elementos nas pilhas
    empilharInfo(pilha1, a);
    empilharInfo(pilha1, b);
    empilharInfo(pilha1, c);

    empilharInfo(pilha2, d);
    empilharInfo(pilha2, e);
    empilharInfo(pilha2, f);

    // Calcular a interseção das pilhas
    pDPilha resultado = interseccao(pilha1, pilha2, compararinteiro);

    // Exibir a pilha de interseção
    printf("Pilha de intersecao: ");
    while (!pilhaVazia(resultado)) {
        int* elem = desempilharInfo(resultado);
        printf("%d ", *elem);
        free(elem);  // Libera memória do elemento removido
    }
    printf("\n");

    // Limpeza de memória
    destruirPilha(pilha1);
    destruirPilha(pilha2);
    destruirPilha(resultado);

    return 0;
}
#ifndef PILHA_H
#define PILHA_H

#include "TAD_Pilha.h"

#include "ListaLinear/Lista.h"

#include "OperacoesPilha/0_structs.h"

#include "OperacoesPilha/1_criarPilha.h"

#include "OperacoesPilha/2_empilharInfo.h"

#include "OperacoesPilha/3_desempilharInfo.h"

#include "OperacoesPilha/4_pilhaVazia.h"

#endif

/*---------------------------------------------------*/
/*EXERCICIO 5*/
// Função para verificar se duas pilhas são iguais
int compararInteiros(void* a, void* b) {
    return (*(int*)a - *(int*)b);
}

// Função para verificar se duas pilhas são iguais independentemente da ordem
int iguais(pDPilha pilha1, pDPilha pilha2, FuncaoComparacao fc) {
    pDPilha auxPilha1 = criarPilha(); // Pilha auxiliar para pilha1
    pDPilha auxPilha2 = criarPilha(); // Pilha auxiliar para pilha2

    int iguais = 1; // Flag para verificar se as pilhas são iguais

    // Verifica se ambas as pilhas têm o mesmo número de elementos
    while (!pilhaVazia(pilha1)) {
        void* elemento1 = desempilharInfo(pilha1);
        empilharInfo(auxPilha1, elemento1);
    }
    while (!pilhaVazia(pilha2)) {
        void* elemento2 = desempilharInfo(pilha2);
        empilharInfo(auxPilha2, elemento2);
    }

    // Se o tamanho das pilhas for diferente, não são iguais
    if (pilhaVazia(auxPilha1) != pilhaVazia(auxPilha2)) {
        iguais = 0;
    } else {
        // Array de contagem de elementos
        int contagem[100] = {0}; // Para simplificação, assumindo no máximo 100 elementos
        void* elementos[100]; // Array para armazenar elementos da pilha

        // Contar elementos na primeira pilha
        int count = 0;
        while (!pilhaVazia(auxPilha1)) {
            void* elemento1 = desempilharInfo(auxPilha1);
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (fc(elementos[i], elemento1) == 0) {
                    contagem[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                elementos[count] = elemento1;
                contagem[count] = 1;
                count++;
            }
            empilharInfo(pilha1, elemento1); // Reempilhar na pilha original
        }

        // Verificar elementos na segunda pilha
        while (!pilhaVazia(auxPilha2)) {
            void* elemento2 = desempilharInfo(auxPilha2);
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (fc(elementos[i], elemento2) == 0 && contagem[i] > 0) {
                    contagem[i]--;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                iguais = 0;
                break;
            }
            empilharInfo(pilha2, elemento2); // Reempilhar na pilha original
        }
    }

    // Limpeza das pilhas auxiliares
    while (!pilhaVazia(auxPilha1)) {
        free(desempilharInfo(auxPilha1));
    }
    free(auxPilha1);

    while (!pilhaVazia(auxPilha2)) {
        free(desempilharInfo(auxPilha2));
    }
    free(auxPilha2);

    return iguais;
}


/*---------------------------------------------------*/
/*EXERCICIO 6*/
// Função para copiar uma pilha
pDPilha copia(pDPilha pilha, FuncaoAlocacao fa) {
    pDPilha pilhaCopia = criarPilha();  // Cria uma nova pilha para a cópia
    pDPilha pilhaAux = criarPilha();    // Pilha auxiliar para inverter a ordem

    // Transferir todos os elementos para a pilha auxiliar
    while (!pilhaVazia(pilha)) {
        void* elemento = desempilharInfo(pilha);
        empilharInfo(pilhaAux, elemento);
    }

    // Transferir os elementos de volta para a pilha original e para a pilha de cópia
    while (!pilhaVazia(pilhaAux)) {
        void* elemento = desempilharInfo(pilhaAux);
        void* elementoCopia = fa(elemento);  // Aloca um novo elemento usando a função de alocação
        empilharInfo(pilha, elemento);       // Reempilha o elemento na pilha original
        empilharInfo(pilhaCopia, elementoCopia);  // Empilha o elemento copiado na nova pilha
    }

    // Destruir a pilha auxiliar
    free(pilhaAux);

    return pilhaCopia;  // Retorna a nova pilha copiada
}

// Função de alocação para inteiros
void* alocarInteiro(void* elemento) {
    int* novoElemento = malloc(sizeof(int));
    if (novoElemento) {
        *novoElemento = *(int*)elemento;
    }
    return novoElemento;
}

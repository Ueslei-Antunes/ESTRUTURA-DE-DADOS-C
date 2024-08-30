#ifndef FILA_H
#define FILA_H
#include <string.h>
#include "TAD_Fila.h"

#include "Pilha.h"

#include "ListaLinear/Lista.h"

#include "OperacoesFila/0_structs.h"

#include "OperacoesFila/1_criarFila.h"

#include "OperacoesFila/2_enfileirarInfo.h"

#include "OperacoesFila/3_desenfileirarInfo.h"

#include "OperacoesFila/4_filaVazia.h"

#endif // FILA_H

/*EXERCICIO 1*/
pDFila inverteFila(pDFila fila) {
    pDPilha pilha = criarPilha(); // Cria uma pilha vazia
    while (!filaVazia(fila)) {
        // Retira o elemento da frente da fila e coloca na pilha
        empilharInfo(pilha, desenfileirarInfo(fila));
    }
    while (!pilhaVazia(pilha)) {
        // Retira o elemento do topo da pilha e coloca na fila
        enfileirarInfo(fila, desempilharInfo(pilha));
    }
    // Não há uma função para destruir a pilha no TAD_Pilha,
    // então não é necessário chamar uma função para destruir a pilha
    return fila;
}

void destruirFila(pDFila fila) {
    while (!filaVazia(fila)) {
        free(desenfileirarInfo(fila));
    }
    free(fila);
}

/*---------------------------------------------------*/
//EXERCICIO 2
// Tipo da função de alocação que recebe um ponteiro para o elemento e retorna um ponteiro para o elemento copiado
typedef void* (*FuncaoAlocacao)(void*);

pDFila copiaF(pDFila fila, FuncaoAlocacao fa) {
    // Cria uma nova fila para a cópia
    pDFila novaFila = criarFila();
    pDFila tempFila = criarFila(); // Fila temporária para manter a ordem original

    // Copia os elementos da fila original para novaFila e tempFila
    while (!filaVazia(fila)) {
        void* elemento = desenfileirarInfo(fila); // Remove o elemento da fila original
        void* copiaElemento = fa(elemento); // Cria uma cópia do elemento usando a função de alocação

        // Enfileira o elemento copiado na nova fila e o elemento original na fila temporária
        enfileirarInfo(novaFila, copiaElemento);
        enfileirarInfo(tempFila, elemento);
    }

    // Restaura a fila original a partir da fila temporária
    while (!filaVazia(tempFila)) {
        enfileirarInfo(fila, desenfileirarInfo(tempFila));
    }

    // Destrói a fila temporária
    destruirFila(tempFila);

    // Retorna a nova fila copiada
    return novaFila;
}

// Função de alocação para duplicar uma string
void* alocaString(void* elemento) {
    return strdup((char*)elemento); // Duplica a string e retorna o ponteiro para a cópia
}
/*----------------------------------------------------------*/
//EXERCICIO 3
void troca(pDFila fila, int a, int b) {
    // Fila temporária para armazenamento de elementos
    pDFila tempFila = criarFila();
    void* elementoA = NULL;
    void* elementoB = NULL;
    int encontradoA = 0;
    int encontradoB = 0;
    
    // Percorre a fila original para encontrar os elementos a e b
    while (!filaVazia(fila)) {
        void* elemento = desenfileirarInfo(fila);

        if (*(int*)elemento == a && !encontradoA) {
            // Encontra o elemento 'a' e armazena ele em elementoA
            elementoA = elemento;
            encontradoA = 1;
            enfileirarInfo(tempFila, NULL);  // Espaço reservado para 'b'
        } else if (*(int*)elemento == b && !encontradoB) {
            // Encontra o elemento 'b' e armazena ele em elementoB
            elementoB = elemento;
            encontradoB = 1;
            enfileirarInfo(tempFila, NULL);  // Espaço reservado para 'a'
        } else {
            // Enfileira outros elementos na fila temporária
            enfileirarInfo(tempFila, elemento);
        }
    }

    // Verifica se ambos elementos foram encontrados
    if (encontradoA && encontradoB) {
        // Restaurar os elementos na fila original com os elementos trocados
        while (!filaVazia(tempFila)) {
            void* elemento = desenfileirarInfo(tempFila);

            if (elemento == NULL) {
                // Substitui pelo elemento trocado
                if (encontradoA) {
                    enfileirarInfo(fila, elementoB); // Troca o 'a' por 'b'
                    encontradoA = 0; // Marca que o 'a' foi trocado
                } else {
                    enfileirarInfo(fila, elementoA); // Troca o 'b' por 'a'
                }
            } else {
                // Enfileira os elementos que não foram trocados
                enfileirarInfo(fila, elemento);
            }
        }
    } else {
        // Se não encontrou ambos, apenas restaura a fila original
        while (!filaVazia(tempFila)) {
            enfileirarInfo(fila, desenfileirarInfo(tempFila));
        }
    }

    // Destroi a fila temporária
    destruirFila(tempFila);
}
/*----------------------------------------------------------------------*/
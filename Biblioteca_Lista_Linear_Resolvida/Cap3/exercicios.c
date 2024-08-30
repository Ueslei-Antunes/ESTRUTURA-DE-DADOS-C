#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"


// Função para incluir informação no início da lista
void incluirInfoNoInicio(pDLista lista, void *info) {
    pNoh novoNoh = (pNoh) malloc(sizeof(Noh));
    novoNoh->info = info;
    novoNoh->prox = lista->primeiro;
    lista->primeiro = novoNoh;
    if (lista->ultimo == NULL) {
        lista->ultimo = novoNoh;
    }
    lista->tamanho++;
}
// Função para incluir informação em uma posição específica da lista
void incluirInfoNaPosicao(pDLista lista, void *info, int posicao) {
    if (posicao < 0 || posicao > lista->tamanho) {
        printf("Posição inválida\n");
        return;
    }
    if (posicao == 0) {
        incluirInfoNoInicio(lista, info);
        return;
    }
    pNoh novoNoh = (pNoh) malloc(sizeof(Noh));
    novoNoh->info = info;
    pNoh atual = lista->primeiro;
    for (int i = 0; i < posicao - 1; i++) {
        atual = atual->prox;
    }
    novoNoh->prox = atual->prox;
    atual->prox = novoNoh;
    if (novoNoh->prox == NULL) {
        lista->ultimo = novoNoh;
    }
    lista->tamanho++;
}
//Função para imprimir a lista
void imprimirListaSimples(pDLista lista) {
    pNoh atual = lista->primeiro;
    while (atual != NULL) {
        printf("%s ", (char *)atual->info); 
        atual = atual->prox;
    }
    printf("\n");
}
//Função para excluir um dado
void excluirInfoComLiberacao(pDLista lista, void *info, FuncaoLiberacao liberar) {
    pNoh atual = lista->primeiro;
    pNoh anterior = NULL;
    while (atual != NULL) {
        if (atual->info == info) {
            if (anterior == NULL) {
                lista->primeiro = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            liberar(atual->info);
            free(atual);
            lista->tamanho--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}
//Função para incluir um dado no final da lista
void incluirInfoNoFim(pDLista lista, void *info) {
    pNoh novoNoh = (pNoh) malloc(sizeof(Noh));
    novoNoh->info = info;
    novoNoh->prox = NULL;

    if (lista->ultimo == NULL) {
        lista->primeiro = novoNoh;
        lista->ultimo = novoNoh;
    } else {
        lista->ultimo->prox = novoNoh;
        lista->ultimo = novoNoh;
    }

    lista->tamanho++;
}
//Função para dividir as listas
pDLista dividirListaPorValor(pDLista lista, void *valorDivisao) {
    pDLista listaNova = criarLista(); 
    pNoh atual = lista->primeiro;
    pNoh anterior = NULL;

    while (atual != NULL) {
        if (atual->info == valorDivisao) {
            listaNova->primeiro = atual->prox;
            listaNova->ultimo = lista->ultimo;
            lista->ultimo = anterior;
            lista->tamanho = lista->tamanho - (listaNova->tamanho = lista->tamanho - (atual->prox == NULL ? 1 : 0));
            atual->prox = NULL; // adicionado essa linha para separar as listas
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }

    return listaNova;
}
//Função para unir lista 1 e lista 2
pDLista unirListas(pDLista lista1, pDLista lista2, FuncaoComparacao fc) {
    pDLista listaUnida = criarLista();
    pNoh atual1 = lista1->primeiro;
    pNoh atual2 = lista2->primeiro;

    // Adiciona todos os elementos da lista1 na listaUnida
    while (atual1 != NULL) {
        incluirInfoNoFim(listaUnida, atual1->info);
        atual1 = atual1->prox;
    }

    // Adiciona os elementos da lista2 na listaUnida e evitando repetições
    while (atual2 != NULL) {
        if (!fc(atual2->info, listaUnida)) {
            incluirInfoNoFim(listaUnida, atual2->info);
        }
        atual2 = atual2->prox;
    }

    return listaUnida;
}
//Função de Interseção
pDLista intersecaoListas(pDLista lista1, pDLista lista2, FuncaoComparacao fc) {
    pDLista listaIntersecao = criarLista();
    pNoh atual1 = lista1->primeiro;

    while (atual1 != NULL) {
        pNoh atual2 = lista2->primeiro;
        while (atual2 != NULL) {
            if (fc(atual1->info, atual2->info)) {
                incluirInfoNoFim(listaIntersecao, atual1->info);
                break;
            }
            atual2 = atual2->prox;
        }
        atual1 = atual1->prox;
        atual2 = lista2->primeiro; // reinicia a busca na lista2
    }
    return listaIntersecao;
}
//Função de Disjunção
int disjuncaoListas(pDLista lista1, pDLista lista2, FuncaoComparacao fc) {
    pNoh atual1 = lista1->primeiro;

    while (atual1 != NULL) {
        pNoh atual2 = lista2->primeiro;
        while (atual2 != NULL) {
            if (fc(atual1->info, atual2->info)) {
                return 0; // foi encontrado um elemento comum, não são disjuntas
            }
            atual2 = atual2->prox;
        }
        atual1 = atual1->prox;
    }

    return 1; // não foi encontrado nenhum elemento comum, são disjuntas
}
//Função contida
int contida(pDLista lista1, pDLista lista2, FuncaoComparacao fc) {
    pNoh atual1 = lista1->primeiro;

    while (atual1 != NULL) {
        int encontrado = 0;
        pNoh atual2 = lista2->primeiro;
        while (atual2 != NULL) {
            if (fc(atual1->info, atual2->info)) {
                encontrado = 1;
                break;
            }
            atual2 = atual2->prox;
        }
        if (!encontrado) {
            return 0; // não foi encontrado um elemento da lista1 na lista2
        }
        atual1 = atual1->prox;
    }

    return 1; // foi encontrado todos os elementos da lista1 na lista2
}
//Função para criar lista invertida
void criarlistaInvertida(pDLista lista) {
    pNoh atual = lista->primeiro;
    pNoh anterior = NULL;
    pNoh proximo = NULL;

    while (atual != NULL) {
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }

    lista->primeiro = anterior;
    lista->ultimo = lista->primeiro;
    while (lista->ultimo->prox != NULL) {
        lista->ultimo = lista->ultimo->prox;
    }
}
//2° versão do inverter lista sem inverter a lista
pDLista inverterLista(pDLista lista) {
    pDLista listaInvertida = criarLista();
    pNoh atual = lista->primeiro;

    while (atual != NULL) {
        pNoh proximo = atual->prox;
        incluirInfoNoInicio(listaInvertida, atual->info);
        atual = proximo;
    }

    return listaInvertida;
}

void imprimirListaRecursiva(pDLista lista, FuncaoImpressao fi) {
    if (lista == NULL || lista->primeiro == NULL) {
        return;
    }

    imprimirListaRecursivaAux(lista->primeiro, fi);
}

void imprimirListaRecursivaAux(pNoh noh, FuncaoImpressao fi) {
    if (noh == NULL) {
        return;
    }
    fi(noh->info); 
    imprimirListaRecursivaAux(noh->prox, fi);
}

/* ------------------------------------------------------------------ */

void liberarString(void *info) {
    free((char *)info);
}
int compararStrings(void *info1, void *info2) {
    char *str1 = (char *)info1;
    char *str2 = (char *)info2;
    return strcmp(str1, str2) == 0;
}
void imprimirString(void *info) {
    printf("%s ", (char *)info);
}


int main() {
    pDLista lista1 = criarLista();
    pDLista lista2 = criarLista();

    // Adicione elementos nas listas
    incluirInfoNoInicio(lista1, strdup("valor 2"));
    incluirInfoNoInicio(lista1, strdup("valor 1"));
    incluirInfoNoInicio(lista2, strdup("valor 3"));
    incluirInfoNoInicio(lista2, strdup("valor 4"));

    printf("\nLista 1\n");
    imprimirListaSimples(lista1);
    printf("\nLista 2\n");
    imprimirListaSimples(lista2);

    pDLista listaUnida = unirListas(lista1, lista2, compararStrings);

    printf("\nLista Unida\n");
    imprimirListaSimples(listaUnida);

    pDLista listaIntersecao = intersecaoListas(lista1, lista2,compararStrings);

    printf("\nLista Intersecao\n");
    imprimirListaSimples(listaIntersecao);

    int disjuncao = disjuncaoListas(lista1, lista2, compararStrings);
    printf("\nDisjuncao Listas: %d\n", disjuncao);

    int contida1 = contida(lista1, lista2, compararStrings);
    printf("\nContida: %d\n", contida1);

    printf("\n---------------------------------------------\n");

    printf("\nLista Original\n");
    imprimirListaSimples(lista1);
    criarlistaInvertida(lista1);
    printf("\nLista Invertida\n");
    imprimirListaSimples(lista1);


    pDLista listaInvertida = inverterLista(lista1);
    printf("\nLista Invertida.2\n");
    imprimirListaSimples(listaInvertida);

    printf("\nLista Recursiva\n");
    imprimirListaRecursiva(lista1, imprimirString);

    return 0;
}
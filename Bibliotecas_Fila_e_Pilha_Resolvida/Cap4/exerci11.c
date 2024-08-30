#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pilha.h"

// Função auxiliar para converter um caractere de número para um inteiro
int charParaInt(char c) {
    return c - '0';
}

// Função para avaliar uma expressão aritmética prefixada
int avalia(char expr[]) {
    int i, resultado;
    pDPilha operandos = criarPilha();  // Pilha para armazenar operandos

    // Percorre a expressão de trás para frente
    for (i = strlen(expr) - 1; i >= 0; i--) {
        // Ignorar espaços em branco
        if (expr[i] == ' ') {
            continue;
        }
        // Se o caractere é um dígito, empilhá-lo como um operando
        else if (isdigit(expr[i])) {
            int* operando = malloc(sizeof(int));
            *operando = charParaInt(expr[i]);
            empilharInfo(operandos, operando);
        }
        // Se o caractere é um operador, realizar a operação
        else {
            // Desempilhar os dois operandos
            int* operando1 = desempilharInfo(operandos);
            int* operando2 = desempilharInfo(operandos);
            int* resultadoOperacao = malloc(sizeof(int));

            // Realizar a operação de acordo com o operador
            switch (expr[i]) {
                case '+':
                    *resultadoOperacao = *operando1 + *operando2;
                    break;
                case '-':
                    *resultadoOperacao = *operando1 - *operando2;
                    break;
                case '*':
                    *resultadoOperacao = *operando1 * *operando2;
                    break;
                case '/':
                    *resultadoOperacao = *operando1 / *operando2;
                    break;
                default:
                    printf("Operador desconhecido: %c\n", expr[i]);
                    exit(EXIT_FAILURE);
            }

            // Empilhar o resultado de volta na pilha de operandos
            empilharInfo(operandos, resultadoOperacao);

            // Liberar a memória dos operandos
            free(operando1);
            free(operando2);
        }
    }

    // O resultado final é o único elemento restante na pilha
    resultado = *(int*)desempilharInfo(operandos);

    // Liberar a memória da pilha e do resultado
    free(operandos);

    return resultado;
}

int main() {
    char expr[] = "* 2 + 3 5";
    int resultado = avalia(expr);
    printf("Resultado da expressao '%s': %d\n", expr, resultado);
    return 0;
}

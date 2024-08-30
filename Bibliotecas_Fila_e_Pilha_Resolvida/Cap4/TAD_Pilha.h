#ifndef PILHA_TAD_H
#define PILHA_TAD_H
/*------------------------------------------*/
/* tipos de dados                           */
/*------------------------------------------*/
/* descritor da pilha */
typedef struct dPilha  DPilha;
typedef DPilha*        pDPilha;

/* Definição de tipo para a função de liberação */
typedef void (*FuncaoLiberacao)(void*);

/*------------------------------------------*/
/* operacoes                                */
/*------------------------------------------*/
pDPilha  criarPilha     ();
void     empilharInfo   (pDPilha, void *);
void*    desempilharInfo(pDPilha);
int      pilhaVazia     (pDPilha);
void     liberarInteiro (void*);

#endif


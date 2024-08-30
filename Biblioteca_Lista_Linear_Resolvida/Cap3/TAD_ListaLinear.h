#ifndef LISTA_TAD_H
#define LISTA__TAD_H
/*------------------------------------------*/
/* tipos de dados                           */
/*------------------------------------------*/
typedef struct noh  Noh;
typedef Noh*        pNoh;

/* descritor da lista */
typedef struct dLista  DLista;
typedef DLista*        pDLista;

/* 3 tipos que representam ponteiros para fun��o */
typedef int   (*FuncaoComparacao)(void *, void *);
typedef void  (*FuncaoImpressao) (void *);
typedef void* (*FuncaoAlocacao)  (void *);
typedef void  (*FuncaoLiberacao)(void *);

/*------------------------------------------*/
/* operacoes                                */
/*------------------------------------------*/
pDLista  criarLista    ();
void     incluirInfo   (pDLista, void *);
void     incluirInfoNoInicio(pDLista, void *);
void incluirInfoNoFim(pDLista lista, void *info);
void     incluirInfoNaPosicao(pDLista, void *, int);
int      excluirInfo   (pDLista, void *, FuncaoComparacao);
void excluirInfoComLiberacao(pDLista, void *, FuncaoLiberacao);
int      contemInfo    (pDLista, void *, FuncaoComparacao);
void imprimirListaSimples(pDLista lista);
pDLista unirListas(pDLista lista1, pDLista lista2, FuncaoComparacao fc);
pDLista inverterLista(pDLista lista);
void     destruirLista (pDLista);
pDLista  duplicarLista (pDLista, FuncaoAlocacao);
/* o parametro int estabelece a posicao da lista onde a divisao deve acontecer */
pDLista dividirListaPorValor(pDLista lista, void *valorDivisao);
void*    buscarNohInfo (pDLista, void*, FuncaoComparacao);

#endif

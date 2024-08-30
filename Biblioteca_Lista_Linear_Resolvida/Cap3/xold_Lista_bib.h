#ifndef LISTA_BIB_H
#define LISTA__BIB_H

typedef struct noh  Noh;
typedef Noh*        pNoh;

typedef struct dLista  DLista;
typedef DLista*        pDLista;

typedef int   (*FuncaoComparacao)(void *, void *);
typedef void  (*FuncaoImpressao) (void *);
typedef void* (*FuncaoAlocacao)  (void *);

#endif /* LISTA_TAD_H */

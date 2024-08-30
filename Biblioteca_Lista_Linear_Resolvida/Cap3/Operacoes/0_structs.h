#ifndef STRUCTS_H
#define STRUCTS_H

/* ------------------------------- */
struct noh{
   void       *info;
   struct noh *prox;
};
/* ------------------------------- */
struct dLista{
    int         quantidade;
    int         tamanho;
    struct noh *primeiro;
    struct noh *ultimo;
    
};

#endif

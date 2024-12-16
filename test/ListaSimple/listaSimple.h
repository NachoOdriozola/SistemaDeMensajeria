#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <stdlib.h>

typedef struct s_nodo
{
    void *dato;
    unsigned tam;
    struct s_nodo *sig;
} t_nodo;
typedef t_nodo *t_lista;

void crearLista (t_lista *pl);

#endif // LISTASIMPLE_H_INCLUDED

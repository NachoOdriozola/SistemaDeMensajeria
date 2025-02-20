#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

///MISMO NODO UTILIZADO PARA LISTA SIMPLE Y LISTA CIRCULAR

typedef struct r_nodo
{
    void *dato;
    unsigned tam;
    struct r_nodo *sig;
} s_nodo;

#endif // NODO_H_INCLUDED

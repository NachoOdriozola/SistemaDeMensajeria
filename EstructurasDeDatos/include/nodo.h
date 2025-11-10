/**
 * \file   nodo.h
 * \brief  Define la estructura base de un nodo.
 */



#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED



typedef struct r_nodo
{
    void *dato;
    unsigned tam;
    struct r_nodo *sig;
} s_nodo;



#endif // NODO_H_INCLUDED

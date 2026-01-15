/**
 * \file   nodo.h
 * \brief  Define la estructura base de un nodo.
 */



#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED


/** \struct t_nodo
 * \brief Define la estructura base de un nodo. Utiliza el s_nodo como recursivo.
 */
typedef struct s_nodo
{
    void *dato;
    unsigned tam;
    struct s_nodo *sig;
} t_nodo;


#endif // NODO_H_INCLUDED

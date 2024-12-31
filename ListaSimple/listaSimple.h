#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include <stdlib.h>
#include <string.h>


#define OK 0
#define SIN_MEMORIA -1

#define MINIMO(X, Y)    ((X > Y) ? (X) : (Y))


typedef struct r_nodo
{
    void *dato;
    unsigned tam;
    struct r_nodo *sig;
} s_nodo;
typedef s_nodo *s_lista;

void crearLista (s_lista *pl);
int insertarAlInicioLista (s_lista *pl, const void *dato, unsigned tamDato);
void eliminarNodoConAccion (s_lista *pl, void *dato, unsigned tamDato, void accion (void *dato));
void vaciarListaConAccion (s_lista *pl, void accion (void *dato));


#endif // LISTASIMPLE_H_INCLUDED

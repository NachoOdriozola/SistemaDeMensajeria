#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED


#include <stdlib.h>
#include <string.h>


#define OK 0
#define SIN_MEMORIA -1


typedef struct r_nodo
{
    void *dato;
    unsigned tam;
    struct r_nodo *sig;
} s_nodo;

typedef s_nodo *s_listaCircular;

void crearListaCircular (s_listaCircular *pl);
int insertarSegundoCircular (s_listaCircular *pl, const void *dato, unsigned tamDato);
void mapListaCircular (s_listaCircular *pl, void accion (void *dato));
void mapListaCircularConComplemento (s_listaCircular *pl, void *complemento, void accion (void *dato, void *complemento));
void mapListaCircularConDobleComplemento (s_listaCircular *pl, void *primerComplemento, void *segundoComplemento, void accion (void *dato, void *primerComplemento, void *segundoComplemento));
void vaciarListaCircularConAccion (s_listaCircular *pl, void accion (void *dato));

#endif // LISTACIRCULAR_H_INCLUDED

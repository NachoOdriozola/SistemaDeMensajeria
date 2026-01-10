/**
 * \file   listaSimple.h
 * \brief  Contiene las funciones primitivas de lista simple.
 */


#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED


/* ============================
   INCLUDES
   ============================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nodo.h"
#include "../../Constantes/constantes.h"


/* ============================
   DEFINES
   ============================ */


#define MINIMO(X, Y)    ((X > Y) ? (X) : (Y))

typedef t_nodo *t_listaSimple;


/* ============================
   FUNCIONES
   ============================ */


void crearListaSimple (t_listaSimple *pl);
int insertarAlInicioListaSimple (t_listaSimple *pl, const void *dato, unsigned tamDato);
void vincularNodoAListaSimple (t_listaSimple *pl, t_nodo *nodoAVincular);
void mapListaSimple (t_listaSimple *pl, void accion (void *dato));
void mapListaSimpleConComplemento (t_listaSimple *pl, void *complemento, void accion (void *dato, void *complemento));
int buscarClaveUnicaEnListaSimple (t_listaSimple *pl, const void *key, void *dato, unsigned tamDato, int cmp (const void *a, const void *b));
t_nodo* desvincularNodoDeListaSimple (t_nodo **nodo);
void eliminarNodoConAccionListaSimple (t_listaSimple *pl, void *dato, unsigned tamDato, void accion (void *dato));
void vaciarListaSimpleConAccion (t_listaSimple *pl, void accion (void *dato));


#endif // LISTASIMPLE_H_INCLUDED












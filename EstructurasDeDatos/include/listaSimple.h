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

typedef s_nodo *s_listaSimple;


/* ============================
   FUNCIONES
   ============================ */


void crearListaSimple (s_listaSimple *pl);
int insertarAlInicioListaSimple (s_listaSimple *pl, const void *dato, unsigned tamDato);
void vincularNodoAListaSimple (s_listaSimple *pl, s_nodo *nodoAVincular);
void mapListaSimple (s_listaSimple *pl, void accion (void *dato));
void mapListaSimpleConComplemento (s_listaSimple *pl, void *complemento, void accion (void *dato, void *complemento));
int buscarClaveUnicaEnListaSimple (s_listaSimple *pl, const void *key, void *dato, unsigned tamDato, int cmp (const void *a, const void *b));
s_nodo* desvincularNodoDeListaSimple (s_nodo **nodo);
void eliminarNodoConAccionListaSimple (s_listaSimple *pl, void *dato, unsigned tamDato, void accion (void *dato));
void vaciarListaSimpleConAccion (s_listaSimple *pl, void accion (void *dato));


#endif // LISTASIMPLE_H_INCLUDED












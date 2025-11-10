/**
 * \file   listaSimple.h
 * \brief  Contiene las funciones primitivas de lista circular.
 */


#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED


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


typedef s_nodo *s_listaCircular;


/* ============================
   FUNCIONES
   ============================ */


void crearListaCircular (s_listaCircular *pl);
int insertarSegundoCircular (s_listaCircular *pl, const void *dato, unsigned tamDato);
void mapListaCircular (s_listaCircular *pl, void accion (void *dato));
void mapListaCircularConComplemento (s_listaCircular *pl, void *complemento, void accion (void *dato, void *complemento));
void vaciarListaCircularConAccion (s_listaCircular *pl, void accion (void *dato));


#endif // LISTACIRCULAR_H_INCLUDED

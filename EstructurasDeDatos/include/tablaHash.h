/**
 * \file   tablaHash.h
 * \brief  Contiene las funciones primitivas de tabla hash.
 */


#ifndef TABLAHASH_H_INCLUDED
#define TABLAHASH_H_INCLUDED


/* ============================
   INCLUDES
   ============================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../Constantes/constantes.h"
#include "listaSimple.h"


/* ============================
   ESTRUCTURAS
   ============================ */


typedef struct
{
    s_listaSimple *buckets;
    unsigned short int cantBuckets;
} s_tablaHash;


/* ============================
   FUNCIONES
   ============================ */


int crearTablaHash (s_tablaHash *tablaHash, unsigned short int cantBuckets);
bool insertarEnTablaHash (s_tablaHash *tablaHash, const void *clave, unsigned short int funcionHash (const void*), const void *dato, unsigned tamDato);
void vincularNodoATablaHash (s_tablaHash *tablaHash, const void *clave, unsigned short int funcionHash (const void*), s_nodo *nodoAVincular);
bool buscarClaveEnTablaHash (s_tablaHash *tablaHash, const void *clave, unsigned short int funcionHash (const void*), void *dato, unsigned tamDato, int cmp (const void*, const void*));
void mapTablaHash (s_tablaHash *tablaHash, void accion (void*));
void eliminarTablaHashConAccion (s_tablaHash *tablaHash, void accion (void*));


#endif // TABLAHASH_H_INCLUDED

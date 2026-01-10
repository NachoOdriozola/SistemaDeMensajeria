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
    t_listaSimple *buckets;
    unsigned short int cantBuckets;
} t_tablaHash;


/* ============================
   FUNCIONES
   ============================ */


int crearTablaHash (t_tablaHash *tablaHash, int cantBuckets);
bool insertarEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), const void *dato, unsigned tamDato);
void vincularNodoATablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), t_nodo *nodoAVincular);
bool buscarClaveEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), void *returnDato, unsigned tamDato, int cmp (const void*, const void*));
void mapTablaHash (t_tablaHash *tablaHash, void accion (void*));
void eliminarTablaHashConAccion (t_tablaHash *tablaHash, void accion (void*));


#endif // TABLAHASH_H_INCLUDED

/**
 * \file   tabla_hash.h
 * \brief  Contiene las funciones primitivas de tabla hash.
 */


#ifndef TABLA_HASH_H_INCLUDED
#define TABLA_HASH_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "constantes.h"

#include "logs.h"

#include "lista_doble.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct TablaHash
 * \brief Define la estructura base de la tabla hash.
 */
typedef struct
{
   ListaDoble *buckets;
   unsigned short int cantBuckets;
} TablaHash;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Crear la tabla hash con la cantidad de buckets enviados por parametros.
 *
 * Asigna memoria dinamica para la cantidad de buckets solicitados.
 * Crea las listas simples.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param cantBuckets Cantidad de buckets a crear.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
CodigoRetorno tabla_hash_crear (TablaHash *tablaHash, unsigned short int cantBuckets);

/** \brief Insertar dato en la tabla hash.
 *
 * Calcula el indice del bucket al que pertenece la clave y guarda el dato en la lista simple.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param clave Puntero a la clave a la que se le aplicara la funcion hash para obtener el indice del bucket.
 * \param hash funcion hash que se le aplicara a la clave.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
CodigoRetorno tabla_hash_insertar (TablaHash *tablaHash, const void *clave, int hash (const void*), const void *dato, size_t tamDato);

/** \brief Busca una clave unica en la lista simple que pertenece al bucket de la clave.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param clave Puntero a la clave a la que se le aplicara la funcion hash para obtener el indice del bucket.
 * \param hash funcion hash que se le aplicara a la clave.
 * \param returnDato Puntero donde se guardara el dato del nodo encontrado por la clave.
 * \param tamDato tamanio en bytes del dato a guardar.
 * \param cmp Funcion de comparacion que se debe realizar para encontrar el nodo con la clave.
 *
 * \return 1 si encontro la clave, 0 en caso contrario.
 *
 */
bool tabla_hash_buscar_elemento_con_clave (TablaHash *tablaHash, const void *clave, int hash (const void*), void **returnDato, int cmp (const void *a, const void *b));

/** \brief Funcion map sobre la tabla hash.
 *
 * Itera sobre cada lista simple encontrada en cada bucket.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param accion Funcion de accion a realizar sobre la tabla hash.
 *
 */
void tabla_hash_map (TablaHash *tablaHash, void accion (void *dato));

CodigoRetorno tabla_hash_map_con_contexto_y_error (TablaHash *tablaHash, CodigoRetorno accion (void *dato, void *contexto), void *contexto);

void tabla_hash_filter_con_accion (TablaHash *tablaHash, bool filtro (const void *dato), void accion (void *dato));

void tabla_hash_mostrar (TablaHash *tablaHash, void mostrar (void *dato));

/** \brief Elimina la tabla hash, realizando una accion sobre los datos previamente.
 *
 * Itera sobre cada lista simple encontrada en cada bucket.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param accion Funcion de accion a realizar sobre los datos de los nodos antes de eliminarlos.
 *
 */
void tabla_hash_eliminar_con_accion (TablaHash *tablaHash, void accion (void *dato));


#endif // TABLA_HASH_H_INCLUDED




























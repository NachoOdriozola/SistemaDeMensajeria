/**
 * \file   tablaHash.h
 * \brief  Contiene las funciones primitivas de tabla hash.
 */


#ifndef TABLAHASH_H_INCLUDED
#define TABLAHASH_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../listaSimple/include/listaSimple.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_tablaHash
 * \brief Define la estructura base de la tabla hash.
 */
typedef struct
{
    t_listaSimple *buckets;
    unsigned short int cantBuckets;
} t_tablaHash;


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
int crearTablaHash (t_tablaHash *tablaHash, int cantBuckets);

/** \brief Insertar dato en la tabla hash.
 *
 * Calcula el indice del bucket al que pertenece la clave y guarda el dato en la lista simple.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param clave Puntero a la clave a la que se le aplicara la funcion hash para obtener el indice del bucket.
 * \param funcionHash funcion hash que se le aplicara a la clave.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
int insertarEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), const void *dato, unsigned tamDato);

/** \brief Vincula un nodo ya creado a la lista simple que pertenece al bucket de la clave.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param clave Puntero a la clave a la que se le aplicara la funcion hash para obtener el indice del bucket.
 * \param funcionHash funcion hash que se le aplicara a la clave.
 * \param nodoAVincular Puntero al nodo a vincular.
 *
 */
void vincularNodoATablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), t_nodo *nodoAVincular);

/** \brief Busca una clave unica en la lista simple que pertenece al bucket de la clave.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param clave Puntero a la clave a la que se le aplicara la funcion hash para obtener el indice del bucket.
 * \param funcionHash funcion hash que se le aplicara a la clave.
 * \param returnDato Puntero donde se guardara el dato del nodo encontrado por la clave.
 * \param tamDato tamanio en bytes del dato a guardar.
 * \param cmp Funcion de comparacion que se debe realizar para encontrar el nodo con la clave.
 *
 * \return 1 si encontro la clave, 0 en caso contrario.
 *
 */
int buscarClaveUnicaEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), void *returnDato, unsigned tamDato, int cmp (const void*, const void*));

/** \brief Funcion map sobre la tabla hash.
 *
 * Itera sobre cada lista simple encontrada en cada bucket.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param accion Funcion de accion a realizar sobre la tabla hash.
 *
 */
void mapTablaHash (t_tablaHash *tablaHash, void accion (void*));

/** \brief Elimina la tabla hash, realizando una accion sobre los datos previamente.
 *
 * Itera sobre cada lista simple encontrada en cada bucket.
 *
 * \param tablaHash Direccion de la tabla hash.
 * \param accion Funcion de accion a realizar sobre los datos de los nodos antes de eliminarlos.
 *
 */
void eliminarTablaHashConAccion (t_tablaHash *tablaHash, void accion (void*));


#endif // TABLAHASH_H_INCLUDED





























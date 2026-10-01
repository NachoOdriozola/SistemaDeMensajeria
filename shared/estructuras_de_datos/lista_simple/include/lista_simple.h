/**
 * \file   lista_simple.h
 * \brief  Contiene las funciones primitivas de lista simplemente enlazada.
 */


#ifndef LISTA_SIMPLE_H_INCLUDED
#define LISTA_SIMPLE_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/** \struct NodoListaSimple
 * \brief Define la estructura base de un nodo de una lista doblemente enlazada. Utiliza el s_nodoListaSimple como recursivo.
 */
typedef struct s_nodoListaSimple
{
    void *dato;
    unsigned tam;
    struct s_nodoListaSimple *sig;
} NodoListaSimple;

typedef NodoListaSimple *ListaSimple;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */



/** \brief Crear la lista simple apuntandola a NULL.
 *
 * \param pl Direccion de la lista simple.
 *
 */
void lista_simple_crear (ListaSimple *pl);

/** \brief Insertar al inicio de la lista simple.
 *
 * Crea un nuevo nodo y le asigna espacio en el dato del tamanio del dato con memoria dinamica, le copia el dato al nodo y lo ubica al inicio de la lista simple.
 *
 * \param pl Direccion de la lista simple.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
int lista_simple_insertar_al_inicio (ListaSimple *pl, const void *dato, unsigned tamDato);

/** \brief Funcion map sobre la lista simple.
 *
 * \param pl Direccion de la lista simple.
 * \param accion Funcion de accion a realizar sobre la lista simple.
 *
 */
void lista_simple_map (ListaSimple *pl, void accion (void *dato));

/** \brief Funcion map utilizando un complemento sobre la lista simple.
 *
 * \param pl Direccion de la lista simple.
 * \param complemento Puntero al complemento a utilizar en la funcion de accion.
 * \param accion Funcion de accion a realizar sobre la lista simple utilizando el complemento.
 *
 */
void lista_simple_map_con_complemento (ListaSimple *pl, void *complemento, void accion (void *dato, void *complemento));

/** \brief Buscar una clave unica en la lista simple.
 *
 * Devolver en returnDato el dato si es encontrado por su clave en la lista simple.
 * Verifica devolver en returnDato el tamanio minimo entre el argumento enviado y el tamanio almacenado en el nodo.
 * returnDato puede ser NULL si no se necesita almacenar el dato buscado.
 *
 * \param pl Direccion de la lista simple.
 * \param key Puntero a la clave a buscar.
 * \param returnDato Puntero donde se guardara el dato del nodo encontrado por la clave.
 * \param tamDato tamanio en bytes del dato a guardar.
 * \param cmp Funcion de comparacion que se debe realizar para encontrar el nodo con la clave.
 *
 * \return 1 si encontro la clave, 0 en caso contrario.
 *
 */
int lista_simple_buscar_clave_unica (ListaSimple *pl, const void *key, void *returnDato, unsigned tamDato, int cmp (const void *a, const void *b));

/** \brief Eliminar el nodo, apuntado por la lista simple.
 *
 * Verifica que returnDato sea distinto de NULL, sino no copiara el dato.
 *
 * \param pl Direccion de la lista simple.
 * \param returnDato Puntero donde se guardara el dato antes de eliminarse.
 * \param tamDato tamanio en bytes del dato.
 *
 */
void lista_simple_eliminar_nodo (ListaSimple *pl, void *returnDato, unsigned tamDato);

/** \brief Eliminar el nodo, realizando una accion sobre el dato previamente, apuntado por la lista simple.
 *
 * Verifica que returnDato sea distinto de NULL, sino no copiara el dato.
 *
 * \param pl Direccion de la lista simple.
 * \param returnDato Puntero donde se guardara el dato antes de eliminarse.
 * \param tamDato tamanio en bytes del dato.
 * \param accion Funcion de accion a realizar sobre el dato del nodo antes de eliminarlo.
 *
 */
void lista_simple_eliminar_nodo_con_accion (ListaSimple *pl, void *returnDato, unsigned tamDato, void accion (void *dato));

/** \brief Vaciar la lista simple.
 *
 * Libera la memoria dinamica creada para el dato y para el nodo.
 *
 * \param pl Direccion de la lista simple.
 *
 */
void lista_simple_vaciar (ListaSimple *pl);

/** \brief Vaciar la lista simple, realizando una accion sobre los datos previamente.
 *
 * Libera la memoria dinamica creada para el dato y para el nodo.
 *
 * \param pl Direccion de la lista simple.
 * \param accion Funcion de accion a realizar sobre los datos de los nodos antes de eliminarlos.
 *
 */
void lista_simple_vaciar_con_accion (ListaSimple *pl, void accion (void *dato));


#endif // LISTA_SIMPLE_H_INCLUDED




































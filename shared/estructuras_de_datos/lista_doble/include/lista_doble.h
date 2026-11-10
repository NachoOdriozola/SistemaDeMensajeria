/**
 * \file   lista_doble.h
 * \brief  Contiene las funciones primitivas de lista doblemente enlazada. la abstraccion de esta lista siempre apunta al inicio de la misma. admite duplicados
 */


#ifndef LISTA_DOBLE_H_INCLUDED
#define LISTA_DOBLE_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "constantes.h"

#include "logs.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct NodoListaDoble
 * \brief Define la estructura base de un nodo de una lista doblemente enlazada. Utiliza el s_nodoListaDoble como recursivo.
 */
typedef struct s_NodoListaDoble
{
   void *dato;
   size_t tam;
   struct s_NodoListaDoble *sig;
   struct s_NodoListaDoble *ant;
} NodoListaDoble;

typedef NodoListaDoble *ListaDoble;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Crear la lista doble apuntandola a NULL.
 *
 * \param listaDoble Direccion de la lista doble.
 *
 */
void lista_doble_crear (ListaDoble *listaDoble);

/** \brief Insertar al inicio de la lista doble.
 *
 * Crea un nuevo nodo y le asigna espacio en el dato del tamanio del dato con memoria dinamica, le copia el dato al nodo y lo ubica al inicio de la lista doble.
 *
 * \param listaDoble Direccion de la lista doble.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
CodigoRetorno lista_doble_insertar_al_inicio (ListaDoble *listaDoble, const void *dato, size_t tamDato);

/** \brief Funcion map sobre la lista doble.
 *
 * \param listaDoble Direccion de la lista doble.
 * \param accion Funcion de accion a realizar sobre la lista doble.
 *
 */
void lista_doble_map (ListaDoble *listaDoble, void accion (void *dato));

/** \brief Funcion map con un complemento sobre la lista doble.
 *
 * \param listaDoble Direccion de la lista doble.
 * \param accion Funcion de accion a realizar sobre la lista doble.
 * \param complemento Complemento que se utilizara en la funcion de accion.
 *
 */
void lista_doble_map_con_contexto (ListaDoble *listaDoble, void accion (void *dato, void *contexto), void *contexto);

CodigoRetorno lista_doble_map_con_contexto_y_error (ListaDoble *listaDoble, CodigoRetorno accion (void *dato, void *contexto), void *contexto);

void lista_doble_filter_con_accion (ListaDoble *listaDoble, bool filtro (const void *dato), void accion (void *dato));

/** \brief Buscar una clave unica en la lista doble.
 *
 * Devolver en returnDato el dato si es encontrado por su clave en la lista doble.
 * Retorna en returnDato el tamanio minimo entre el argumento enviado y el tamanio almacenado en el nodo.
 * returnDato puede ser NULL si no se necesita almacenar el dato buscado.
 *
 * \param listaDoble Direccion de la lista doble.
 * \param key Puntero a la clave a buscar.
 * \param returnDato Puntero donde se guardara el dato del nodo encontrado por la clave.
 * \param tamDato tamanio en bytes del dato a guardar.
 * \param cmp Funcion de comparacion que se debe realizar para encontrar el nodo con la clave.
 *
 * \return 1 si encontro la clave, 0 en caso contrario.
 *
 */
bool lista_doble_buscar_elemento_con_clave (ListaDoble *listaDoble, const void *key, void **returnDato, int cmp (const void *a, const void *b));

bool lista_doble_eliminar_elemento_con_clave (ListaDoble *listaDoble, const void *key, void *returnDato, size_t tamDato, int cmp (const void *a, const void *b));
bool lista_doble_eliminar_elemento_con_clave_y_accion (ListaDoble *listaDoble, const void *key, void *returnDato, size_t tamDato, int cmp (const void *a, const void *b), void accion (void *dato));

/** \brief Vaciar la lista doble, realizando una accion sobre los datos previamente.
 *
 * Libera la memoria dinamica creada para el dato y para el nodo.
 *
 * \param listaDoble Direccion de la lista doble.
 * \param accion Funcion de accion a realizar sobre los datos de los nodos antes de eliminarlos.
 *
 */
void lista_doble_vaciar_con_accion (ListaDoble *listaDoble, void accion (void *dato));


#endif // LISTA_DOBLE_H_INCLUDED
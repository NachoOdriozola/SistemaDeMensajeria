/**
 * \file   cola.h
 * \brief  Contiene las funciones primitivas de cola.
 */


#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED


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


/** \struct NodoCola
 * \brief Define la estructura base de un nodo de una cola. Utiliza el s_nodoCola como recursivo.
 */
typedef struct s_NodoCola
{
   void *dato;
   size_t tam;
   struct s_NodoCola *sig;
} NodoCola;

typedef struct
{
    NodoCola *pri;
    NodoCola *ult;
} Cola;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Crear la cola apuntandola a NULL;
 *
 * \param cola Direccion de la cola.
 *
 */
void cola_crear (Cola *cola);

/** \brief Insertar a la cola.
 *
 * Crea un nuevo nodo y le asigna espacio en el dato del tamanio del dato con memoria dinamica, le copia el dato al nodo y lo ubica en la cola.
 *
 * \param cola Direccion de la cola.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
CodigoRetorno cola_insertar (Cola *cola, const void *dato, size_t tamDato);

/** \brief cola_sacar el primer elemento de la cola.
 *
 * Elimina el nodo desacolado con su dato almacenado.
 *
 * \param cola Direccion de la cola.
 * \param returnDato Puntero donde se retorna el dato que contenia el nodo.
 * \param tamDato tamanio en bytes del dato.
 *
 */
void cola_sacar (Cola *cola, void *returnDato, size_t tamDato);

/** \brief Verificar si la cola no esta vacia.
 *
 * \param cola Direccion de la cola.
 *
 * \return True si la cola no esta vacia, False en caso contrario.
 * 
 */
bool cola_no_esta_vacia (Cola *cola);

/** \brief Vaciar la cola. Asegura que la cola apunte a NULL.
 *
 * \param cola Direccion de la cola.
 *
 */
void cola_vaciar (Cola *cola);


#endif // COLA_H_INCLUDED
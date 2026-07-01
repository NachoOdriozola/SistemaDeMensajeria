/**
 * \file   utiles.h
 * \brief  Contiene funciones utiles que trabajan con las estructuras del servidor.
 */



#ifndef UTILES_H_INCLUDED
#define UTILES_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Calcular el indice del bucket de la tabla hash segun el ID del cliente y la cantidad de buckets de la tabla hash.
 *
 * \param clave Puntero al ID del cliente.
 * 
 * \return Indice del bucket correspondiente al ID del cliente.
 *
 */
int funcionHash (const void *clave);

/** \brief Comparar el ID de un cliente con una clave ID.
 *
 * \param cliente Puntero a la estructura del cliente a comparar.
 * \param clave Puntero al ID int con el que se comparara.
 * 
 * \return Diferencia entre el ID del cliente y la clave ID.
 *
 */
int cmpIdCliente (const void *a, const void *b);

/** \brief Mostrar el ID de un cliente en consola. Agrega salto de linea.
 *
 * \param cliente Puntero al cliente cuyo ID se desea mostrar.
 *
 */
void mostrarCliente (void *cliente);

/** \brief Liberar los recursos asociados a un cliente.
 *
 * \param cliente Puntero al cliente cuyos recursos seran liberados.
 *
 */
void liberarCliente (void *cliente);



#endif // UTILES_H_INCLUDED
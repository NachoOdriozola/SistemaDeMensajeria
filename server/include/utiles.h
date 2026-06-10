/**
 * \file   utiles.h
 * \brief  g
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
   DEFINES
   ============================================================================================================================================ */



/**
 * \def MAX_BUFFER_CONSULTA_SQLITE
 * \brief Tamanio maximo del buffer para almacenar consultas SQLite.
 */
#define MAX_BUFFER_CONSULTA_SQLITE 128



/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */



int funcionHash (const void *clave);
int cmpIdCliente (const void *a, const void *b);
void mostrarCliente (void *cliente);
void liberarCliente (void *cliente);



#endif // UTILES_H_INCLUDED
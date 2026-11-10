/**
 * \file   cliente.h
 * \brief  
 */


#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sockets.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


#define CONECTADO 1
#define DESCONECTADO 0


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \struct Cliente
 * \brief  Representa un cliente.
 */
typedef struct
{
   Socket socket;     /**< Socket del cliente. */
   int id;                   /**< Identificador correspondiente del usuario. */
   bool estado;
} Cliente;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void cliente_inicializar (Cliente *cliente, Socket socket);
void cliente_asignar_id (Cliente *cliente, int idCliente);
int cliente_obtener_id (const Cliente *cliente);
void cliente_marcar_desconectado (Cliente *cliente);
bool cliente_esta_conectado (const Cliente *cliente);
void cliente_mostrar (const Cliente *cliente);
void cliente_liberar (Cliente *cliente);


#endif // CLIENTE_H_INCLUDED
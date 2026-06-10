/**
 * \file   estructuras.h
 * \brief  Define las estructuras principales de la aplicacion.
 */



#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */



#include <winsock2.h>
#include <ws2tcpip.h>
#include <sqlite3.h>

#include "../../shared/estructurasDeDatos/listaSimple/include/listaSimple.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"



/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */



/**
 * \def CANT_BUCKETS_TABLA_HASH
 * \brief Cantidad de buckets que tiene la tabla hash de clientes autenticados.
 */
#define CANT_BUCKETS_TABLA_HASH 1000



/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */

   

/**
 * \struct t_cliente
 * \brief  Representa un cliente.
 */
typedef struct
{
    SOCKET sock; /**< Socket del cliente. */
    int id;      /**< Identificador correspondiente del usuario. */
} t_cliente;

/**
 * \struct t_contextoServidor
 * \brief  Contexto (estados y recursos) global del servidor.
 */
typedef struct
{
    bool estadoWinsock;                              /**< Estado de Winsock API */
    SOCKET sock;                                     /**< Socket del servidor. */
    sqlite3 *baseDeDatos;                            /**< Puntero a la base de datos. */
    t_listaSimple listaSimpleClientesNoAutenticados; /**< Lista simple de clientes conectados pero no autenticados. */
    t_tablaHash tablaHashClientes;                   /**< Tabla hash de clientes conectados y autenticados. */
} t_contextoServidor;



#endif // ESTRUCTURAS_H_INCLUDED


















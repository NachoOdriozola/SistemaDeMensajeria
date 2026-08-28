/**
 * \file   estructuras.h
 * \brief  Define las estructuras principales de la aplicacion.
 */


#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <sqlite3.h>

#include "cola.h"
#include "listaSimple.h"
#include "listaDoble.h"
#include "tablaHash.h"
#include "sockets.h"

#include "baseDeDatos/baseDeDatos.h"


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
 * \struct t_solicitudCliente
 * \brief  Almacena un cliente con la solicitud que envio para ser procesada.
 */
typedef struct
{
   t_nodoListaDoble *clienteAProcesar;               /**< Direccion del nodo del cliente que envio la solicitud a procesar. */
   char solicitud [MAX_BUFFER_SOLICITUD];       /**< Cadena que contiene la solicitud enviada por el cliente. */
} t_solicitudCliente;

/**
 * \struct t_cliente
 * \brief  Representa un cliente.
 */
typedef struct
{
    t_socket sock;    /**< Socket del cliente. */
    int id;                /**< Identificador correspondiente del usuario. */
} t_cliente;

/**
 * \struct t_respuestaCliente
 * \brief  Almacena los datos de una respuesta para ser enviada a su respectivo cliente.
 */
typedef struct
{
   t_cliente *clienteAResponder;
   char *datosAEnviar;
   int tamDatosAEnviar;
} t_respuestaCliente;

/**
 * \struct t_contextoServidor
 * \brief  Contexto (estados y recursos) global del servidor.
 */
typedef struct
{
   t_socket sock;                                           /**< Socket del servidor. */
   sqlite3 *baseDeDatos;                              /**< Puntero a la base de datos. */
   t_sentenciasSqlite sentenciasSqlite;         /**< Cache de sentencias de consultas de base de datos. */
   t_listaDoble clientesNoAutenticados;      /**< Lista doble que contiene a los clientes conectados pero no autenticados. */
   t_tablaHash clientes;                                /**< Tabla hash que contiene a los clientes conectados y autenticados. */
   t_cola solicitudes;                                     /**< Cola que almacena las solicitudes enviadas por los clientes. */
   t_listaSimple respuestasPendientes;        /**< Lista que almacena las respuestas que no se pudieron enviar en el momento para que puedan ser enviadas luego. */
} t_contextoServidor;


#endif // ESTRUCTURAS_H_INCLUDED


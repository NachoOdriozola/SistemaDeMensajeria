/**
 * \file   estructuras.h
 * \brief  Define las estructuras principales de la aplicacion.
 */


#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


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
 * \struct Cliente
 * \brief  Representa un cliente.
 */
typedef struct
{
   Socket sock;    /**< Socket del cliente. */
   int id;                /**< Identificador correspondiente del usuario. */
} Cliente;

/**
 * \struct SolicitudCliente
 * \brief  Almacena un cliente con la solicitud que envio para ser procesada.
 */
typedef struct
{
   NodoListaDoble *clienteAProcesar;               /**< Direccion del nodo del cliente que envio la solicitud a procesar. */
   char solicitud [MAX_BUFFER_SOLICITUD];       /**< Cadena que contiene la solicitud enviada por el cliente. */
} SolicitudCliente;

/**
 * \struct RespuestaCliente
 * \brief  Almacena los datos de una respuesta para ser enviada a su respectivo cliente.
 */
typedef struct
{
   Cliente *clienteAResponder;
   char *datosAEnviar;
   int tamDatosAEnviar;
} RespuestaCliente;


/**
 * \struct ContextoServidor
 * \brief  Contexto (EstadoSolicituds y recursos) global del servidor.
 */
typedef struct
{
   Socket sock;                                           /**< Socket del servidor. */
   sqlite3 *bd;                                            /**< Puntero a la base de datos. */
   SentenciasSqlite sentenciasSqlite;         /**< Cache de sentencias de consultas de base de datos. */
   ListaDoble clientesNoAutenticados;      /**< Lista doble que contiene a los clientes conectados pero no autenticados. */
   TablaHash clientes;                                /**< Tabla hash que contiene a los clientes conectados y autenticados. */
   Cola solicitudes;                                     /**< Cola que almacena las solicitudes enviadas por los clientes. */
   ListaSimple respuestasPendientes;        /**< Lista que almacena las respuestas que no se pudieron enviar en el momento para que puedan ser enviadas luego. */
} ContextoServidor;


#endif // ESTRUCTURAS_H_INCLUDED


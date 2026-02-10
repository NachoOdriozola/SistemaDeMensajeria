/**
 * \file   estructuras.h
 * \brief  Define las estructuras principales de la aplicacion.
 */



#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <winsock2.h>
#include <ws2tcpip.h>
#include <sqlite3.h>

#include "../../Constantes/constantes.h"
#include "../../EstructurasDeDatos/include/listaSimple.h"
#include "../../EstructurasDeDatos/include/tablaHash.h"



/* ============================
   ESTRUCTURAS
   ============================ */



/**
 * \struct t_buffersComunicacion
 * \brief  Contiene los buffers necesarios para establecer la comunicacion entre el cliente y el servidor.
 */
typedef struct
{
    char solicitud [MAX_BUFFER_SOLICITUD];              /**< Buffer que almacena una solicitud un clientes. */
    char respuesta [MAX_BUFFER_RESPUESTA];              /**< Buffer que almacena una respuestas del servidor para enviar al cliente. */
} t_buffersComunicacion;

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
 * \struct t_servidor
 * \brief  Estructura base del servidor.
 */
typedef struct
{
    SOCKET sock;                                     /**< Socket del servidor. */
    sqlite3 *baseDeDatos;                            /**< Puntero a la base de datos. */
    t_listaSimple listaSimpleClientesNoAutenticados; /**< Lista simple de clientes conectados pero no autenticados. */
    t_tablaHash tablaHashClientes;                   /**< Tabla hash de clientes conectados y autenticados. */
} t_servidor;



#endif // ESTRUCTURAS_H_INCLUDED


















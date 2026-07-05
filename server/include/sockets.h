/**
 * \file   sockets.h
 * \brief  Interfaz comun que contiene las funciones de los sockets independientemente del SO.
 */


#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED


#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <ws2tcpip.h>
    typedef SOCKET t_socket;
    #define SOCKET_INVALIDO INVALID_SOCKET
    #define ERROR_SOCKET SOCKET_ERROR
#else
    typedef int t_socket;
    #define SOCKET_INVALIDO (-1)
    #define ERROR_SOCKET (-1)
#endif


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar el uso de sockets y crear el socket del servidor.
 *
 * \param sock Puntero al socket del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 *
 */
t_codigoRetorno socket_inicializarServidor (t_socket *sock);

/** \brief Configurar el socket del servidor.
 *
 * Establecer que el socket escuche cualquier direccion IP en el puerto asignado. Ademas, lo establece como modo no bloqueante.
 * 
 * \param sock Puntero al socket del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_CONFIGURACION en caso de fallas al inicializar recursos.
 *
 */
t_codigoRetorno socket_configurarServidor (t_socket *sock);

/** \brief Aceptar nuevos clientes que se quieren conectar con el servidor.
 *
 * \param sockServidor Socket del servidor.
 *
 * \return Resultado del socket aceptado del nuevo cliente.
 *
 */
t_socket socket_aceptarNuevoCliente (t_socket sockServidor);

/** \brief Establecer el socket como modo no bloqueante.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_establecerModoNoBloqueante (t_socket *sock);

/** \brief Enviar al socket recibido un buffer.
 *
 * \param sock Puntero al socket a procesar.
 * \param buffer Cadena que contiene el buffer a enviar.
 *
 * \return Resultado del envio.
 * 
 */
int socket_enviar (t_socket sock, const char *buffer);

/** \brief Recibir un buffer del socket.
 *
 * \param sock Puntero al socket a procesar.
 * \param returnBuffer Cadena que contiene recibe el buffer.
 *
 * \return Resultado del recibo.
 * 
 */
int socket_recibir (t_socket sock, char *returnBuffer);

/** \brief Preguntar si el socket perdio la conexion.
 *
 * \param sock Socket a procesar.
 * \param bytesRecibidos Bytes recibidos al intentar recibir datos del socket.
 *
 * \return 1 si el socket perdio la conexion, 0 en caso contrario.
 * 
 */
bool socket_perdioConexion (t_socket sock, int bytesRecibidos);

/** \brief Cerrar el socket.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_cerrar (t_socket *sock);

/** \brief Finalizar el uso de sockets.
 *
 */
void socket_finalizar ();


#endif // SOCKETS_H_INCLUDED
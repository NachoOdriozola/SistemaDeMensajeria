/**
 * \file   sockets.h
 * \brief  Interfaz comun que contiene las funciones de los sockets independientemente del SO.
 */


#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED


#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <mstcpip.h>
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

#include "../../constantes/include/constantes.h"
#include "../../protocolos/include/protocolos.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar el uso de sockets. Inicializa Winsock API.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 * 
 */
t_codigoRetorno socket_inicializar ();

/** \brief Crear un socket.
 *
 * \param sock Puntero al socket a crear.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 *
 */
t_codigoRetorno socket_crear (t_socket *sock);

/** \brief Conectar el socket del servidor. Establecer que el socket escuche cualquier direccion IP en el puerto asignado.
 * 
 * \param sock Puntero al socket del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_CONFIGURACION en caso de fallas al configurar recursos.
 *
 */
t_codigoRetorno socket_conectarServidor (t_socket *sock);

/** \brief Conectar el socket del cliente. Establecer que el socket se conecte a la IP establecida.
 * 
 * \param sock Puntero al socket del cliente.
 *
 * \return EXITO si se inicializo correctamente, ERROR_CONFIGURACION en caso de fallas al configurar recursos.
 *
 */
t_codigoRetorno socket_conectarCliente (t_socket *sock);

/** \brief Establecer el socket como modo bloqueante.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_establecerModoBloqueante (t_socket *sock);

/** \brief Establecer el socket como modo no bloqueante.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_establecerModoNoBloqueante (t_socket *sock);

/** \brief Establecer timeout al socket.
 *
 * \param sock Puntero al socket a procesar.
 * \param tiempo Tiempo en milisegundos para que ocurra el timeout.
 *
 */
void socket_establecerTimeout (t_socket *sock, DWORD tiempo);

/** \brief Crear y establecer keepalive al socket. Se envian sondas cada 60s y 5s de intervalo.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
t_codigoRetorno socket_establecerKeepAlive (t_socket *sock);

/** \brief Aceptar nuevos clientes que se quieren conectar con el servidor.
 *
 * \param sockServidor Socket del servidor.
 *
 * \return Resultado del socket aceptado del nuevo cliente.
 *
 */
t_socket socket_aceptarNuevoCliente (t_socket sockServidor);

/** \brief Enviar al socket un buffer.
 *
 * \param sock Socket que realiza el envio
 * \param buffer Cadena que contiene el buffer a enviar.
 *
 * \return Resultado en bytes del envio.
 * 
 */
int socket_enviar (t_socket sock, const char *buffer);

/** \brief Recibir un buffer del socket.
 *
 * \param sock Socket que realiza el recibo.
 * \param returnBuffer Cadena que contiene recibe el buffer.
 *
 * \return Resultado en bytes del recibo.
 * 
 */
int socket_recibir (t_socket sock, char *returnBuffer);

/** \brief Preguntar si el socket perdio la conexion.
 *
 * \param sock Socket a procesar.
 * \param bytesRecibidos Bytes recibidos al intentar recibir datos del socket (recv()).
 *
 * \return true si el socket perdio la conexion, false en caso contrario.
 * 
 */
bool socket_perdioConexion (t_socket sock, int bytesRecibidos);

/** \brief Cerrar el socket. Verifica que sea un socket valido. Si es un socket valido, asegura que su contenido sea SOCKET_INVALIDO al finalizar.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_cerrar (t_socket *sock);

/** \brief Finalizar el uso de sockets. Libera Winsock API. Verifica que Winsock API haya sido inicializada.
 *
 */
void socket_finalizar ();


#endif // SOCKETS_H_INCLUDED
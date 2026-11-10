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
    typedef SOCKET Socket;
    #define SOCKET_INVALIDO INVALID_SOCKET
    #define ERROR_SOCKET SOCKET_ERROR
#else
    typedef int Socket;
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

#include "constantes.h"

#include "logs.h"

#include "frame.h"


/* ============================================================================================================================================
   CONEXION
   ============================================================================================================================================ */


/**
 * \def PUERTO
 * \brief Puerto en el que se comunicaran los sockets.
 */
#define PUERTO 8070


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \struct ResultadoEnvio
 * \brief Informa el resultado del envio de datos.
 */
typedef enum
{
   ENVIO_EXITO,
   ENVIO_NO_REALIZADO,
   ENVIO_BLOQUEADO,
   ENVIO_ERROR_CONEXION
} ResultadoEnvio;

/**
 * \struct ResultadoRecepcion
 * \brief Informa el resultado de la recepcion de datos.
 */
typedef enum
{
   RECEPCION_RECIBIO_DATOS,
   RECEPCION_NO_RECIBIO_DATOS,
   RECEPCION_NO_REALIZADA,
   RECEPCION_CERRADA_ORDENADA,
   RECEPCION_ERROR_CONEXION
} ResultadoRecepcion;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar el uso de sockets. Inicializa Winsock API.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 * 
 */
CodigoRetorno socket_inicializar ();

/** \brief Crear un socket.
 *
 * \param sock Puntero al socket a crear.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 *
 */
CodigoRetorno socket_crear (Socket *sock);

/** \brief Conectar el socket del servidor. Establecer que el socket escuche cualquier direccion IP en el puerto asignado.
 * 
 * \param sock Puntero al socket del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_CONFIGURACION en caso de fallas al configurar recursos.
 *
 */
CodigoRetorno socket_conectar_servidor (Socket *sock);

/** \brief Conectar el socket del cliente. Establecer que el socket se conecte a la IP establecida.
 * 
 * \param sock Puntero al socket del cliente.
 *
 * \return EXITO si se inicializo correctamente, ERROR_CONFIGURACION en caso de fallas al configurar recursos.
 *
 */
CodigoRetorno socket_conectar_cliente (Socket *sock);

bool socket_es_valido (Socket sock);

/** \brief Establecer el socket como modo bloqueante.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_establecer_modo_bloqueante (Socket *sock);

/** \brief Establecer el socket como modo no bloqueante.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_establecer_modo_no_bloqueante (Socket *sock);

/** \brief Establecer timeout al socket.
 *
 * \param sock Puntero al socket a procesar.
 * \param tiempo Tiempo en milisegundos para que ocurra el timeout.
 *
 */
void socket_establecer_timeout (Socket *sock, DWORD tiempo);

/** \brief Crear y establecer keepalive al socket. Se envian sondas cada 60s y 5s de intervalo.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
CodigoRetorno socket_establecer_keep_alive (Socket *sock);

/** \brief Aceptar nuevos clientes que se quieren conectar con el servidor.
 *
 * \param sockServidor Socket del servidor.
 *
 * \return Resultado del socket aceptado del nuevo cliente.
 *
 */
Socket socket_aceptar_nuevo_cliente (Socket socketServidor);

/** \brief Enviar al socket un buffer. Iterar hasta enviar todos los datos.
 * 
 * \param sock Socket que realiza el envio
 * \param buffer Cadena que contiene el buffer a enviar.
 * \param tamBuffer Tamanio del buffer.
 *
 * \return ENVIO_COMPLETO si pudo enviar todos los datos correctamente, ENVIO_BUFFER_LLENO si el buffer del socket se encuentra agotado y no se pueden cargar mas datos, ENVIO_ERROR_CONEXION en caso de error de conexion.
 * 
 */
ResultadoEnvio socket_enviar (Socket sock, const char *buffer, size_t tam);

/** \brief Recibir un buffer del socket. Iterar hasta recibir todos los datos.
 *
 * Primero recibe el header, y luego recibe la cadena con la cantidad de bytes asigandos en el header.
 * 
 * \param sock Socket que realiza el recibo.
 * \param returnBuffer Cadena que retorna el contenido del buffer.
 *
 * \return RECEPCION_RECIBIO_DATOS en caso de haber recibido datos, RECEPCION_NO_RECIBIO_DATOS en caso contrario, y RECEPCION_ERROR_CONEXION en caso de error de conexion.
 * 
 */
ResultadoRecepcion socket_recibir (Socket sock, char *returnBuffer, size_t tamBuffer);

/** \brief Cerrar el socket. Verifica que sea un socket valido. Si es un socket valido, asegura que su contenido sea SOCKET_INVALIDO al finalizar.
 *
 * \param sock Puntero al socket a procesar.
 *
 */
void socket_cerrar (Socket *sock);

/** \brief Finalizar el uso de sockets. Libera Winsock API. Verifica que Winsock API haya sido inicializada.
 *
 */
void socket_finalizar ();


#endif // SOCKETS_H_INCLUDED
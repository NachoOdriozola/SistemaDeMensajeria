/**
 * \file   comunicacion.h
 * \brief  Contiene funciones para realizar la comunicacion entre el cliente y el servidor.
 */


#ifndef COMUNICACION_H_INCLUDED
#define COMUNICACION_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */

   
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/constantes/include/constantes.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def RECIBIO_RESPUESTA
 * \brief Codigo de retorno para indicar que se recibio una respuesta del servidor.
 */
#define RECIBIO_RESPUESTA 1

/**
 * \def NO_RECIBIO_RESPUESTA
 * \brief Codigo de retorno para indicar que no se recibio una respuesta del servidor.
 */
#define NO_RECIBIO_RESPUESTA 0


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \enum t_buffersComunicacion
 * \brief Almacena la solicitud y la respuesta del servidor. Se utiliza para no consumir mucha memoria debido a que no se necesitaran en simultaneo.
 */
typedef union
{
   char solicitud [MAX_BUFFER_SOLICITUD];
   char respuesta [MAX_BUFFER_RESPUESTA];
} t_buffersComunicacion;


/**
 * \enum t_respuestaAutenticacion
 * \brief Contiene los datos de la respuesta recibida por el servidor a la solicitud de autenticacion enviada.
 */
typedef struct
{
   char estado;
   int idUsuario;
} t_respuestaAutenticacion;

/**
 * \enum t_respuestaRegistro
 * \brief Contiene los datos de la respuesta recibida por el servidor a la solicitud de respuesta enviada.
 */
typedef struct
{
   char estado;
   int idUsuario;
} t_respuestaRegistro;

/**
 * \enum t_respuestaAutenticacion
 * \brief Contiene los datos de la respuesta recibida por el servidor a la solicitud de seleccion de chat enviada.
 */
typedef struct
{
   char estado;
   int idUsuarioChatSeleccionado;
} t_respuestaSeleccionChat;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Recibir una respuesta del servidor a traves del socket.
 *
 * Intentar leer datos disponibles en el socket especificado.
 * Si se recibe una respuesta, asegura terminar el bufferRespuesta con caracter nulo para que sea una cadena valida.
 * No bloquea el socket.
 *
 * \param sock Socket del usuario desde el cual se recibe la respuesta.
 * \param bufferRespuesta Buffer donde se almacenara la respuesta recibida.
 *
 * \return RECIBIO_RESPUESTA en caso de que haya recibido respuesta, NO_RECIBIO_RESPUESTA en caso contrario.
 *
 */
bool recibioRespuesta (SOCKET sock, char *bufferRespuesta);

/** \brief Enviar una solicitud al servidor y esperar a recibir su respuesta.
 *
 * Enviar una solicitud y recibir una respuesta que se almacenara en buffersComunicacion. Todo el proceso se comunica mediante el socket especificado.
 * Asegura terminar el buffer con caracter nulo para que sea una cadena valida.
 * Cambia temporalmente el modo del socket a bloqueante para asegurar que el envio y la recepcion se completen antes de continuar. Una vez realizado el proceso, se desbloquea.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param buffersComunicacion Buffers donde se recibe la solicitud y se almacena la respuesta.
 *
 */
void enviarSolicitudYRecibirRespuesta (SOCKET sock, t_buffersComunicacion *buffersComunicacion);

/** \brief Enviar solicitud para autenticar usuario.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_AUTENTICACION|nombre de usuario|contrasenia del usuario
 * 
 * Envia la solicitud y espera la respuesta para saber su estado antes de continuar. Se comunican a traves del socket especificado.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param nombreUsuario Cadena que contiene el nombre que escribio el usuario.
 * \param contrasenia Cadena que contiene la contrasenia que escribio el usuario.
 *
 * \return t_respuestaAutenticacion que contiene los datos de la respuesta recibida por el servidor.
 */
t_respuestaAutenticacion enviarSolicitudAutenticacion (SOCKET sock, const char *nombreUsuario, const char *contrasenia);

/** \brief Enviar solicitud para registrar usuario.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_REGISTRO|nombre de usuario|contrasenia del usuario|correo electronico del usuario
 * 
 * Envia la solicitud y espera la respuesta para saber su estado antes de continuar. Se comunican a traves del socket especificado.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param nombreUsuario Cadena que contiene el nombre que escribio el usuario.
 * \param contrasenia Cadena que contiene la contrasenia que escribio el usuario.
 * \param correoElectronico Cadena que contiene el correo electronico que escribio el usuario.
 *
 * \return t_respuestaRegistro que contiene los datos de la respuesta recibida por el servidor.
 */
t_respuestaRegistro enviarSolicitudRegistro (SOCKET sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico);

/** \brief Enviar solicitud para enviar un mensaje a otro usuario.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_MENSAJE|ID del emisor|ID del receptor|texto
 * 
 * Envia la solicitud y espera la respuesta para saber su estado antes de continuar. Se comunican a traves del socket especificado.
 * Verifica que el ID del receptor sea un ID valido y que no sea el mismo que el ID del usuario.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param idUsuario ID del usuario que envia la solicitud y el mensaje.
 * \param idReceptor ID del usuario que recibe el mensaje.
 * \param mensaje Cadena que contiene el texto del mensaje.
 *
 * \return char que contiene el estado de la respuesta recibida por el servidor.
 *
 */
char enviarSolicitudEnvioMensaje (SOCKET sock, int idUsuario, int idReceptor, const char* mensaje);

/** \brief Enviar solicitud para seleccionar un chat con un usuario para comunicarse.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_SELECCIONAR_CHAT|nombre del contacto
 * 
 * Envia la solicitud y espera la respuesta para saber su estado antes de continuar. Se comunican a traves del socket especificado.
 * Verifica si el nombre de usuario del chat seleccionado no es el propio nombre de usuario.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param nombreUsuario Nombre del propio usuario que envia la solicitud.
 * \param nombreUsuarioChatSeleccionado Nombre del usuario que se desea seleccionar el chat.
 *
 * \return t_respuestaSeleccionChat que contiene los datos de la respuesta recibida por el servidor.
 *
 */
t_respuestaSeleccionChat enviarSolicitudSeleccionChat (SOCKET sock, const char *nombreUsuarioChatSeleccionado);


#endif // COMUNICACION_H_INCLUDED
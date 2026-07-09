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
#include <stdbool.h>

#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/constantes/include/constantes.h"
#include "../../shared/sockets/include/sockets.h"


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


/** \brief Crear el socket y configurarlo como cliente para conectarse al servidor. Ademas, le establece un timeout.
 *
 * Si falla la conexion con el servidor, elimina el socket creado.
 * 
 * \param returnSock Puntero al socket del cliente donde se retornara el socket creado y conectado al servidor.
 *
 * \return SOLICITUD_EXITO en caso de poder crear el socket y conectarlo con el servidor correctamente, SOLICITUD_ERROR_CONEXION en caso contrario.
 *
 */
t_estadoSolicitud intentarConectarConServidor (t_socket *returnSock);

/** \brief Recibir una respuesta del servidor a traves del socket.
 *
 * Intentar leer datos disponibles en el socket especificado.
 * Si se recibe una respuesta, asegura terminar el bufferRespuesta con caracter nulo para que sea una cadena valida.
 *
 * \param sock Socket del usuario desde el cual se recibe la respuesta.
 * \param bufferRespuesta Buffer donde se almacenara la respuesta recibida.
 *
 * \return true en caso de que haya recibido respuesta, false en caso contrario.
 *
 */
bool recibioRespuesta (t_socket sock, char *bufferRespuesta);

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
t_respuestaAutenticacion enviarSolicitudAutenticacion (t_socket sock, const char *nombreUsuario, const char *contrasenia);

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
t_respuestaRegistro enviarSolicitudRegistro (t_socket sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico);

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
char enviarSolicitudEnvioMensaje (t_socket sock, int idUsuario, int idReceptor, const char* mensaje);

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
t_respuestaSeleccionChat enviarSolicitudSeleccionChat (t_socket sock, const char *nombreUsuarioChatSeleccionado);


#endif // COMUNICACION_H_INCLUDED
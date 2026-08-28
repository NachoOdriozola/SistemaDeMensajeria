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

#include "protocolos.h"
#include "constantes.h"
#include "sockets.h"

#include "logica/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Crear el socket y configurarlo como cliente para conectarse al servidor. Ademas, le establece un timeout y lo configura como modo no bloqueante.
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
 * \return RECEPCION_RECIBIO_DATOS en caso de recibir datos correctamente, RECEPCION_NO_RECIBIO_DATOS en caso de no recibirlos considerando el socket no bloqueante, y RECEPCION_ERROR_CONEXION 
 * si el socket perdio la conexion.
 *
 */
t_resultadoRecepcion recibirRespuesta (t_socket sock, char *bufferRespuesta);

/** \brief Enviar solicitud para autenticar usuario.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura t_datosEnvioSolicitudAutenticacion.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param nombreUsuario Cadena que contiene el nombre que escribio el usuario.
 * \param contrasenia Cadena que contiene la contrasenia que escribio el usuario.
 */
void enviarSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia);

/** \brief Enviar solicitud para registrar usuario.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura t_datosEnvioSolicitudRegistro.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param nombreUsuario Cadena que contiene el nombre que escribio el usuario.
 * \param contrasenia Cadena que contiene la contrasenia que escribio el usuario.
 * \param correoElectronico Cadena que contiene el correo electronico que escribio el usuario.
 */
void enviarSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico);

/** \brief Enviar solicitud para enviar un mensaje a otro usuario.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura t_datosEnvioSolicitudEnvioMensaje.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param idUsuario ID del usuario que envia la solicitud y el mensaje.
 * \param idReceptor ID del usuario que recibe el mensaje.
 * \param mensaje Cadena que contiene el texto del mensaje.
 *
 */
void enviarSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, int idUsuario, int idReceptor, const char* mensaje);

/** \brief Enviar solicitud para seleccionar un chat con un usuario para comunicarse.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura t_datosEnvioSolicitudSeleccionChat.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param nombreUsuario Nombre del propio usuario que envia la solicitud.
 * \param nombreUsuarioChatSeleccionado Nombre del usuario que se desea seleccionar el chat.
 *
 */
void enviarSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuarioChatSeleccionado);


#endif // COMUNICACION_H_INCLUDED
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
   FUNCIONES DE INFRAESTRUCTURA
   ============================================================================================================================================ */


/** \brief Inicializar la comunicacion configurando los recursos necesarios para su utilizacion.
 * 
 * Invocar una unica vez al inicio del programa, antes de realizar cualquier otro proceso de comunicacion.
 * 
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 *
 */
void comunicacion_inicializar (ContextoAplicacion *contextoAplicacion);

/** \brief Crear el socket y configurarlo como cliente para conectarse al servidor. Ademas, le establece un timeout y lo configura como modo no bloqueante.
 *
 * Si falla la conexion con el servidor, elimina el socket creado.
 * 
 * \param returnSock Puntero al socket del cliente donde se retornara el socket creado y conectado al servidor.
 *
 * \return SOLICITUD_EXITO en caso de poder crear el socket y conectarlo con el servidor correctamente, SOLICITUD_ERROR_CONEXION en caso contrario.
 *
 */
EstadoSolicitud comunicacion_intentar_conectar_con_servidor (Socket *returnSock);


/* ============================================================================================================================================
   FUNCIONES DE RECEPCION Y ENVIO DE SOLICITUDES
   ============================================================================================================================================ */


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
ResultadoRecepcion comunicacion_recibir_respuesta (Socket sock, char *bufferRespuesta);

/** \brief Enviar solicitud para autenticar usuario.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura SolicitudAutenticacion.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param nombreUsuario Cadena que contiene el nombre que escribio el usuario.
 * \param contrasenia Cadena que contiene la contrasenia que escribio el usuario.
 */
void comunicacion_enviar_solicitud_autenticacion (ContextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia);

/** \brief Enviar solicitud para registrar usuario.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura SolicitudRegistro.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param nombreUsuario Cadena que contiene el nombre que escribio el usuario.
 * \param contrasenia Cadena que contiene la contrasenia que escribio el usuario.
 * \param correoElectronico Cadena que contiene el correo electronico que escribio el usuario.
 */
void comunicacion_enviar_solicitud_registro (ContextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico);

/** \brief Enviar solicitud para enviar un mensaje a otro usuario.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura SolicitudEnvioMensaje.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param idUsuario ID del usuario que envia la solicitud y el mensaje.
 * \param idReceptor ID del usuario que recibe el mensaje.
 * \param mensaje Cadena que contiene el texto del mensaje.
 *
 */
void comunicacion_enviar_solicitud_envio_mensaje (ContextoAplicacion *contextoAplicacion, int idUsuario, int idReceptor, const char* mensaje);

/** \brief Enviar solicitud para seleccionar un chat con un usuario para comunicarse.
 *
 * Envia los datos del usuario necesarios para realizar la solicitud con la estructura SolicitudSeleccionChat.
 * Se comunican a traves del socket del contexto de la aplicacion.
 * Se espera que los datos enviados para la solicitud YA sean validados por las restricciones del dominio previamente debido a que no se validan antes de enviar.
 * No realiza el envio de la solicitud si ya hay una solicitud en curso.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param nombreUsuario Nombre del propio usuario que envia la solicitud.
 * \param nombreUsuarioChatSeleccionado Nombre del usuario que se desea seleccionar el chat.
 *
 */
void comunicacion_enviar_solicitud_seleccion_chat (ContextoAplicacion *contextoAplicacion, const char *nombreUsuarioChatSeleccionado);


/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */


/** \brief Preguntar si hay una solicitud en curso en el momento en el que se invoca la funcion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 *
 * \return True si hay una solicitud en curso, False en caso contrario.
 * 
 */
bool comunicacion_hay_solicitud_en_curso (const ContextoAplicacion *contextoAplicacion);

/** \brief Finalizar el proceso de solicitud en curso. 
 * 
 * Invocar siempre que se reciba la respuesta de la solicitud enviada para dar por finalizada la comunicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * 
 */
void comunicacion_finalizar_solicitud_en_curso (ContextoAplicacion *contextoAplicacion);

/** \brief Finalizar la comunicacion con el servidor del socket asignado.
 *
 * \param sock Socket del usuario donde se finalizara la comunicacion.
 * 
 */
void comunicacion_finalizar (Socket *sock);


/* ============================================================================================================================================
   FUNCIONES DE EXTRACCION DE DATOS
   ============================================================================================================================================ */


/** \brief Obtener el tipo de respuesta segun el contenido del header.
 *
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 *
 * \return Tipo de respuesta recibido.
 * 
 */
TipoRespuesta comunicacion_obtener_tipo_respuesta (const char *respuesta);


/** \brief Extraer los datos crudos del buffer que contiene la respuesta recibida por el servidor a datos procesados contenidos en una estructura.
 *
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * \param returnRespuestaAutenticacion Puntero a la estructura que contiene los datos de respuesta de la solicitud de autenticacion donde seran retornados.
 * 
 */
void comunicacion_extraer_respuesta_autenticacion (const char *respuesta, RespuestaAutenticacion *returnRespuestaAutenticacion);

/** \brief Extraer los datos crudos del buffer que contiene la respuesta recibida por el servidor a datos procesados contenidos en una estructura.
 *
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * \param returnRespuestaRegistro Puntero a la estructura que contiene los datos de respuesta de la solicitud de registro donde seran retornados.
 * 
 */
void comunicacion_extraer_respuesta_registro (const char *respuesta, RespuestaRegistro *returnRespuestaRegistro);

/** \brief Extraer los datos crudos del buffer que contiene la respuesta recibida por el servidor a datos procesados contenidos en una estructura.
 *
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * \param returnRespuestaSeleccionChat Puntero a la estructura que contiene los datos de respuesta de la solicitud de seleccion de chat donde seran retornados.
 * 
 */
void comunicacion_extraer_respuesta_seleccion_chat (const char *respuesta, RespuestaSeleccionChat *returnRespuestaSeleccionChat);

/** \brief Extraer los datos crudos del buffer que contiene la respuesta recibida por el servidor a datos procesados contenidos en una estructura.
 *
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * \param returnRespuestaEnvioMensaje Puntero a la estructura que contiene los datos de respuesta de la solicitud de envio de mensaje donde seran retornados.
 * 
 */
void comunicacion_extraer_respuesta_envio_mensaje (const char *respuesta, RespuestaEnvioMensaje *returnRespuestaEnvioMensaje);

/** \brief Extraer los datos crudos del buffer que contiene la respuesta recibida por el servidor a datos procesados contenidos en una estructura.
 *
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * \param RespuestaRecepcionMensaje Puntero a la estructura que contiene los datos de respuesta de la solicitud de envio de mensaje donde seran retornados.
 * 
 */
void comunicacion_extraer_respuesta_recepcion_mensaje (const char *respuesta, RespuestaRecepcionMensaje *returnRespuestaRecepcionMensaje);


#endif // COMUNICACION_H_INCLUDED
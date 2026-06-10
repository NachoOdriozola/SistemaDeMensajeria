/**
 * \file   comunicacion.h
 * \brief  C
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



typedef struct
{
   char estado;
   int idUsuario;
} t_respuestaAutenticacion;

typedef struct
{
   char estado;
   int idUsuario;
} t_respuestaRegistro;

typedef struct
{
   char estado;
   int idUsuario;
} t_respuestaSeleccionContacto;



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
 * \param tamMaxBufferRespuesta Tamanio maximo del buffer que recibe la respuesta.
 *
 * \return RECIBIO_RESPUESTA en caso de que haya recibido respuesta, NO_RECIBIO_RESPUESTA en caso contrario.
 *
 */
bool recibirRespuesta (SOCKET sock, char *bufferRespuesta, unsigned int tamMaxBufferRespuesta);

/** \brief Enviar una solicitud al servidor y esperar a recibir su respuesta.
 *
 * Envia una solicitud almacenada en el bufferSolicitud y recibe una respuesta que se almacenara en el bufferRespuesa. Todo el proceso se comunica mediante el socket especificado.
 * Asegura terminar el bufferRespuesta con caracter nulo para que sea una cadena valida.
 * Cambiar temporalmente el modo del socket a bloqueante para asegurar que el envio y la recepcion se completen antes de continuar. Una vez realizado el proceso, se desbloquea.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param bufferSolicitud Buffer que contiene la solicitud a enviar.
 * \param bufferRespuesta Buffer donde se almacenara la respuesta recibida.
 * \param tamMaxBufferRespuesta Tamanio maximo del buffer que recibe la respuesta.
 *
 */
void enviarSolicitudYRecibirRespuesta (SOCKET sock, t_buffersComunicacion *buffersComunicacion);

/** \brief Intentar solicitud para autenticar el usuario.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_AUTENTICACION|nombre de usuario|contrasenia del usuario
 * Envia la solicitud y espera la respuesta para saber su estado.
 * Si el estado de la respuesta es RESPUESTA_EXITO, guarda el ID del usuario.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return Char del estado de respuesta del servidor de tipo t_estadoRespuesta.
 */
t_respuestaAutenticacion enviarSolicitudAutenticar (SOCKET sock, const char *nombreUsuario, const char *contrasenia);

/** \brief Intentar solicitud para registrar el usuario.
 *
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_REGISTRO|nombre de usuario|contrasenia del usuario|correo electronico del usuario
 * Envia la solicitud y espera la respuesta para saber su estado.
 * Si el estado de la respuesta es RESPUESTA_EXITO, guarda el ID del usuario.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 *
 * \return Char del estado de respuesta del servidor de tipo t_estadoRespuesta.
 */
t_respuestaRegistro enviarSolicitudRegistrar (SOCKET sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico);

/** \brief Intentar solicitud para enviar un mensaje a otro usuario.
 *
 * Si no se tiene seleccionado un contacto para comunicarse (ID del receptor invalido), retorna.
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_MENSAJE|ID del emisor|ID del receptor|texto
 * Envia la solicitud y espera la respuesta para saber su estado.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param idReceptor ID del contacto seleccionado para comunicarse.
 *
 * \return Char del estado de respuesta del servidor de tipo t_estadoRespuesta.
 *
 */
char enviarSolicitudMensaje (SOCKET sock, int idUsuario, int idReceptor, const char* mensaje);

/** \brief Intentar solicitud para seleccionar un contacto para comunicarse.
 *
 * Verifica si el nombre del contacto seleccionado no es el propio nombre de usuario, en tal caso retorna.
 * Genera una cadena de solicitud valida compuesta de la siguiente manera:
 * SOLICITUD_SELECCIONAR_CONTACTO|nombre del contacto
 * Envia la solicitud y espera la respuesta para saber su estado.
 * Si el estado de la respuesta es RESPUESTA_EXITO, guarda el ID del usuario receptor.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return Char del estado de respuesta del servidor de tipo t_estadoRespuesta.
 *
 */
t_respuestaSeleccionContacto enviarSolicitudSeleccionarContacto (SOCKET sock, const char *nombreUsuario, const char *nombreContacto);



#endif // COMUNICACION_H_INCLUDED
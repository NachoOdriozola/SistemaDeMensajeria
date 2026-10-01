/**
 * \file   controladores.h
 * \brief  Contiene funciones que hacen de puente entre la logica y la interfaz grafica.
 */


#ifndef INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
#define INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "lista_doble.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/recursos.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \enum EstadoIntentoSeleccionChat
 * \brief Enumeracion de posibles resultados al intentar seleccionar un chat con un usuario.
 */
typedef enum
{
   INTENTO_SELECCION_CHAT_SOLICITUD_ENVIADA,
   INTENTO_SELECCION_CHAT_DATOS_INVALIDOS
} EstadoIntentoSeleccionChat;

/** \enum ValidacionSeleccionChat
 * \brief Enumeracion de los posibles resultados de la validacion de los datos del nombre del usuario del chat seleccionado.
 */
typedef enum
{
   INTENTO_SELECCION_CHAT_DATOS_VALIDOS,
   INTENTO_SELECCION_CHAT_NOMBRE_VACIO,
   INTENTO_SELECCION_CHAT_NOMBRE_INVALIDO,
   INTENTO_SELECCION_CHAT_SELECCIONO_CHAT_PROPIO,
   INTENTO_SELECCION_CHAT_CHAT_YA_SELECCIONADO
} ValidacionSeleccionChat;

/** \struct ResultadoIntentoSeleccionChat
 * \brief Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de los datos del nombre del usuario del chat seleccionado.
 */
typedef struct
{
   EstadoIntentoSeleccionChat estado;
   ValidacionSeleccionChat validacion;
} ResultadoIntentoSeleccionChat;

/**
 * \struct RespuestaSeleccionChatUi
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de seleccion de chat. No contiene el header, solo el payload.
 */
typedef struct
{
   char estado;
   int idUsuarioChatSeleccionado;
} RespuestaSeleccionChatUi;



/** \enum EstadoIntentoEnvioMensaje
 * \brief Enumeracion de posibles resultados al intentar enviar un mensaje.
 */
typedef enum
{
   INTENTO_ENVIO_MENSAJE_SOLICITUD_ENVIADA,
   INTENTO_ENVIO_MENSAJE_DATOS_INVALIDOS
} EstadoIntentoEnvioMensaje;

/** \enum ValidacionEnvioMensaje
 * \brief Enumeracion de los posibles resultados de la validacion de datos al enviar un mensaje.
 */
typedef enum
{
   INTENTO_ENVIO_MENSAJE_DATOS_VALIDOS,
   INTENTO_ENVIO_MENSAJE_MENSAJE_VACIO,
   INTENTO_ENVIO_MENSAJE_SON_TODOS_ESPACIOS,
   INTENTO_ENVIO_MENSAJE_EMISOR_RECEPTOR_INVALIDOS,
   INTENTO_ENVIO_MENSAJE_EMISOR_ES_RECEPTOR
} ValidacionEnvioMensaje;

/** \struct ResultadoIntentoEnvioMensaje
 * \brief Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de datos al enviar un mensaje.
 */
typedef struct
{
   EstadoIntentoEnvioMensaje estado;
   ValidacionEnvioMensaje validacion;
} ResultadoIntentoEnvioMensaje;

/**
 * \struct RespuestaEnvioMensajeUi
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de envio de mensaje. No contiene el header, solo el payload.
 */
typedef struct
{
   char estado;
} RespuestaEnvioMensajeUi;



/**
 * \struct RespuestaRecepcionMensajeUi
 * \brief Datos que debe saber la UI de la respuesta de la recepcion de mensaje. No contiene el header, solo el payload.
 */
typedef struct
{
   int idEmisor;
   char texto [MAX_MENSAJE];
} RespuestaRecepcionMensajeUi;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Preguntar si el mensaje es un comando.
 *
 * \param mensaje Cadena que contiene el mensaje.
 *
 * \return True si el mensaje es un comando, False en caso contrario.
 * 
 */
bool _ui_contactos_es_comando (const char *mensaje);

/** \brief Enviar solicitud de seleccion de chat.
 *
 * Verificar que los datos de seleccion de chat sean validos.
 * En caso de que lo sean, envia la solicitud de seleccion de chat.
 * 
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el EstadoSolicitud de los mensajes.
 * \param uiContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de los datos del nombre del usuario del chat seleccionado.
 * Tipo INTENTO_SELECCION_CHAT_DATOS_INVALIDOS en caso de que los datos del nombre del usuario del chat seleccionado sea invalido. Es el unico caso que modifica el valor de la validacion de los datos del usuario.
 * Tipo INTENTO_SELECCION_CHAT_SOLICITUD_ENVIADA en caso de enviar la solicitud correctamente.
 * 
 */
ResultadoIntentoSeleccionChat _ui_contactos_intentar_seleccion_chat (ContextoAplicacion *contextoAplicacion, const UiContactos *uiContactos);

/** \brief Enviar una solicitud de envio de mensaje.
 * 
 * Verificar que los datos de envio de mensaje sean validos.
 * En caso de que lo sean, envia la solicitud de envio de mensaje.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el EstadoSolicitud de los mensajes.
 * \param uiContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de datos al enviar un mensaje.
 * Tipo INTENTO_ENVIO_MENSAJE_DATOS_INVALIDOS en caso de que los datos del envio del mensaje sean invalidos. Es el unico caso que modifica el valor de la validacion de los datos del usuario.
 * Tipo INTENTO_ENVIO_MENSAJE_SOLICITUD_ENVIADA en caso de enviar la solicitud correctamente.
 * 
 */
ResultadoIntentoEnvioMensaje _ui_contactos_intentar_envio_mensaje (ContextoAplicacion *contextoAplicacion, const UiContactos *uiContactos);


/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
RespuestaEnvioMensajeUi _ui_contactos_procesar_respuesta_envio_mensaje (ContextoAplicacion *contextoAplicacion, const char *respuesta);

/** \brief Extrae los datos de la respuesta, realiza un log y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
RespuestaRecepcionMensajeUi _ui_contactos_procesar_respuesta_recepcion_mensaje (ContextoAplicacion *contextoAplicacion, const char *respuesta);

/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
RespuestaSeleccionChatUi _ui_contactos_procesar_respuesta_seleccion_chat (ContextoAplicacion *contextoAplicacion, const char *respuesta);


/** \brief Realizar el procedimiento en caso de error de conexion con el servidor.
 * 
 * Resetear la interfaz de contactos, finalizar la comunicacion y seleccionar la interfaz de autenticacion para utilizar.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el EstadoSolicitud de los mensajes.
 * \param uiContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void _ui_contactos_manejar_error_conexion (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos);


/** \brief Preparar la interfaz logicamente para establecer un nuevo chat con un contacto seleccionado.
 *
 * \param uiContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 * \param respuestaSeleccionChatUi Puntero a la estructura que contiene los datos que debe saber la UI de la respuesta de la solicitud de seleccion de chat. No contiene el header, solo el payload.
 *
 */
void _ui_contactos_setear_nuevo_chat_seleccionado (UiContactos *uiContactos, const RespuestaSeleccionChatUi *respuestaSeleccionChatUi);


/** \brief Crear la lista doble de mensajes que contiene los mensajes sfText*.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el EstadoSolicitud de los mensajes.
 *
 */
void _ui_contactos_lista_mensajes_crear (ContextoMensajes *contextoMensajes);

/** \brief Insertar un nuevo mensaje a la lista doble de mensajes.
 *
 * Crea el mensaje sfText*, lo configura, le establece el texto del mensaje con saltos de linea, desplaza hacia arriba a todos los mensajes que hay en la lista de mensajes
 * para hacer espacio para el nuevo mensaje entrante, le establece su posicion y lo inserta a la lista de mensajes.
 * En caso de que sea el primer mensaje insertado a la lista, almacena su referencia en el contexto de mensajes.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el EstadoSolicitud de los mensajes.
 * \param mensaje Cadena que contiene el mensaje. Si bien la estructura contextoMensajes contiene la cadena del mensaje que escribe el usuario, este parametro es necesario para mensajes recibidos por otros usuarios.
 * \param origenMensaje Origen de quien envio mensaje.
 * \param fuentes Puntero a la estructura que contiene las fuentes de los textos graficos de la interfaz de contactos.
 * 
 * \return EXITO en caso de que todo se ejecuto correctamente, ERROR_SIN_MEMORIA en caso de que no se pueda crear el mensaje.
 *
 */
CodigoRetorno _ui_contactos_lista_mensajes_insertar (ContextoMensajes *contextoMensajes, const char *mensaje, OrigenMensaje origenMensaje, const UiContactosFuentes *fuentes);

/** \brief Vaciar la lista doble de mensajes, liberando los sfText* creados.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el EstadoSolicitud de los mensajes.
 *
 */
void _ui_contactos_lista_mensajes_vaciar (ContextoMensajes *contextoMensajes);


#endif // INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
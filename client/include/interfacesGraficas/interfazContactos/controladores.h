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

#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "listaDoble.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/recursos.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \enum _t_tipoResultado_intentarSeleccionarChat
 * \brief Enumeracion de posibles resultados al intentar seleccionar un chat con un usuario.
 */
typedef enum
{
   INTENTARSELECCIONARCHAT_RESULTADO_EXITO,
   INTENTARSELECCIONARCHAT_RESULTADO_DATOS_INVALIDOS
} _t_tipoResultado_intentarSeleccionarChat;

/** \enum _t_resultado_validacionDatosSeleccionChat
 * \brief Enumeracion de los posibles resultados de la validacion de los datos del nombre del usuario del chat seleccionado.
 */
typedef enum
{
   INTENTARSELECCIONARCHAT_RESULTADODATOS_EXITO,
   INTENTARSELECCIONARCHAT_RESULTADODATOS_NOMBREVACIO,
   INTENTARSELECCIONARCHAT_RESULTADODATOS_NOMBREINVALIDO,
   INTENTARSELECCIONARCHAT_RESULTADODATOS_SELECCIONPROPIOCHAT,
   INTENTARSELECCIONARCHAT_RESULTADODATOS_CHATYASELECCIONADO
} _t_resultado_validacionDatosSeleccionChat;

/** \struct _t_resultado_intentarSeleccionarChat
 * \brief Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de los datos del nombre del usuario del chat seleccionado.
 */
typedef struct
{
   _t_tipoResultado_intentarSeleccionarChat tipo;
   _t_resultado_validacionDatosSeleccionChat validacion;
} _t_resultado_intentarSeleccionarChat;


/** \enum _t_tipoResultado_intentarEnviarMensaje
 * \brief Enumeracion de posibles resultados al intentar enviar un mensaje.
 */
typedef enum
{
   INTENTARENVIARMENSAJE_RESULTADO_EXITO,
   INTENTARENVIARMENSAJE_RESULTADO_DATOS_INVALIDOS
} _t_tipoResultado_intentarEnviarMensaje;

/** \enum _t_resultado_validacionDatosEnvioMensaje
 * \brief Enumeracion de los posibles resultados de la validacion de datos al enviar un mensaje.
 */
typedef enum
{
   INTENTARENVIARMENSAJE_RESULTADODATOS_EXITO,
   INTENTARENVIARMENSAJE_RESULTADODATOS_MENSAJEVACIO,
   INTENTARENVIARMENSAJE_RESULTADODATOS_SONTODOSESPACIOS,
   INTENTARENVIARMENSAJE_RESULTADODATOS_EMISORYRECEPTORINVALIDOS,
   INTENTARENVIARMENSAJE_RESULTADODATOS_EMISORESELRECEPTOR
} _t_resultado_validacionDatosEnvioMensaje;

/** \struct _t_resultado_intentarEnviarMensaje
 * \brief Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de datos al enviar un mensaje.
 */
typedef struct
{
   _t_tipoResultado_intentarEnviarMensaje tipo;
   _t_resultado_validacionDatosEnvioMensaje validacion;
} _t_resultado_intentarEnviarMensaje;


/**
 * \struct _t_datosUI_respuesta_solicitudEnvioMensaje
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de envio de mensaje. No contiene el header, solo el payload.
 */
typedef struct
{
   char estadoSolicitud;
} _t_datosUI_respuesta_solicitudEnvioMensaje;

/**
 * \struct _t_datosUI_respuesta_recepcionMensaje
 * \brief Datos que debe saber la UI de la respuesta de la recepcion de mensaje. No contiene el header, solo el payload.
 */
typedef struct
{
   int idEmisor;
   char texto [MAX_MENSAJE];
} _t_datosUI_respuesta_recepcionMensaje;

/**
 * \struct _t_datosUI_respuesta_solicitudSeleccionChat
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de seleccion de chat. No contiene el header, solo el payload.
 */
typedef struct
{
   char estadoSolicitud;
   int idUsuarioDelChatSeleccionado;
} _t_datosUI_respuesta_solicitudSeleccionChat;


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
bool _interfazContactos_esUnComando (const char *mensaje);

/** \brief Enviar solicitud de seleccion de chat.
 *
 * Verificar que los datos de seleccion de chat sean validos.
 * En caso de que lo sean, envia la solicitud de seleccion de chat.
 * 
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de los datos del nombre del usuario del chat seleccionado.
 * Tipo INTENTARSELECCIONARCHAT_RESULTADO_DATOS_INVALIDOS en caso de que los datos del nombre del usuario del chat seleccionado sea invalido. Es el unico caso que modifica el valor de la validacion de los datos del usuario.
 * Tipo INTENTARSELECCIONARCHAT_RESULTADO_EXITO en caso de enviar la solicitud correctamente.
 * 
 */
_t_resultado_intentarSeleccionarChat _interfazContactos_intentar_seleccionarChat (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos);

/** \brief Enviar una solicitud de envio de mensaje.
 * 
 * Verificar que los datos de envio de mensaje sean validos.
 * En caso de que lo sean, envia la solicitud de envio de mensaje.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return Estructura que contiene el tipo de resultado de la operacion y el tipo de resultado de la validacion de datos al enviar un mensaje.
 * Tipo INTENTARENVIARMENSAJE_RESULTADO_DATOS_INVALIDOS en caso de que los datos del envio del mensaje sean invalidos. Es el unico caso que modifica el valor de la validacion de los datos del usuario.
 * Tipo INTENTARENVIARMENSAJE_RESULTADO_EXITO en caso de enviar la solicitud correctamente.
 * 
 */
_t_resultado_intentarEnviarMensaje _interfazContactos_intentar_enviarMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos);


/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
_t_datosUI_respuesta_solicitudEnvioMensaje _interfazContactos_solicitudEnvioMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta);

/** \brief Extrae los datos de la respuesta, realiza un log y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
_t_datosUI_respuesta_recepcionMensaje _interfazContactos_recepcionMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta);

/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
_t_datosUI_respuesta_solicitudSeleccionChat _interfazContactos_solicitudSeleccionChat_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta);


/** \brief Realizar el procedimiento en caso de error de conexion con el servidor.
 * 
 * Resetear la interfaz de contactos, finalizar la comunicacion y seleccionar la interfaz de autenticacion para utilizar.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void _interfazContactos_manejarError_conexion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


/** \brief Preparar la interfaz logicamente para establecer un nuevo chat con un contacto seleccionado.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 * \param datosUI_respuesta_solicitudSeleccionChat Puntero a la estructura que contiene los datos que debe saber la UI de la respuesta de la solicitud de seleccion de chat. No contiene el header, solo el payload.
 *
 */
void _interfazContactos_setearNuevoChatSeleccionado (t_interfazContactos *interfazContactos, const _t_datosUI_respuesta_solicitudSeleccionChat *datosUI_respuesta_solicitudSeleccionChat);


/** \brief Crear la lista doble de mensajes que contiene los mensajes sfText*.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 *
 */
void _interfazContactos_listaMensajes_crear (t_contextoMensajes *contextoMensajes);

/** \brief Insertar un nuevo mensaje a la lista doble de mensajes.
 *
 * Crea el mensaje sfText*, lo configura, le establece el texto del mensaje con saltos de linea, desplaza hacia arriba a todos los mensajes que hay en la lista de mensajes
 * para hacer espacio para el nuevo mensaje entrante, le establece su posicion y lo inserta a la lista de mensajes.
 * En caso de que sea el primer mensaje insertado a la lista, almacena su referencia en el contexto de mensajes.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param mensaje Cadena que contiene el mensaje. Si bien la estructura contextoMensajes contiene la cadena del mensaje que escribe el usuario, este parametro es necesario para mensajes recibidos por otros usuarios.
 * \param origenMensaje Origen de quien envio mensaje.
 * \param fuentes Puntero a la estructura que contiene las fuentes de los textos graficos de la interfaz de contactos.
 * 
 * \return EXITO en caso de que todo se ejecuto correctamente, ERROR_SIN_MEMORIA en caso de que no se pueda crear el mensaje.
 *
 */
t_codigoRetorno _interfazContactos_listaMensajes_insertarMensaje (t_contextoMensajes *contextoMensajes, const char *mensaje, t_origenMensaje origenMensaje, const t_interfazContactosFuentes *fuentes);

/** \brief Vaciar la lista doble de mensajes, liberando los sfText* creados.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 *
 */
void _interfazContactos_listaMensajes_vaciar (t_contextoMensajes *contextoMensajes);


#endif // INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
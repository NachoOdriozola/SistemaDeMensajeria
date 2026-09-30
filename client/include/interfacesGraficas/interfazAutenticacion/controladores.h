/**
 * \file   controladores.h
 * \brief  Contiene funciones que hacen de puente entre la logica y la interfaz grafica.
 */


#ifndef INTERFAZAUTENTICACION_CONTROLADORES_H_INCLUDED
#define INTERFAZAUTENTICACION_CONTROLADORES_H_INCLUDED


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

#include "constantes.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \enum ResultadoIntentoAutenticacion
 * \brief Enumeracion de posibles resultados al intentar autenticar.
 */
typedef enum
{
   INTENTO_AUTENTICACION_SOLICITUD_ENVIADA,
   INTENTO_AUTENTICACION_CREDENCIALES_INVALIDAS,
   INTENTO_AUTENTICACION_ERROR_CONEXION
} ResultadoIntentoAutenticacion;

/**
 * \struct RespuestaAutenticacionUi
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de autenticacion. No contiene el header, solo el payload.
 */
typedef struct
{
   char estado;
   int idUsuario;
} RespuestaAutenticacionUi;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */

   
/** \brief Intentar autenticar el usuario.
 * 
 * Verifica que los datos del usuario sean validos para no realizar solicitudes innecesarias.
 * Intenta conectarse con el servidor. En caso de que la conexion falle, se maneja el error de conexion.
 * En caso de que todas las condiciones se cumplan con exito, se envia la solicitud de autenticacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param uiAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 * \return INTENTO_AUTENTICACION_CREDENCIALES_INVALIDAS en caso de que los datos del usuario sean invalidos. INTENTO_AUTENTICACION_ERROR_CONEXION en caso de no poder conectarse con el servidor.
 * INTENTO_AUTENTICACION_SOLICITUD_ENVIADA en caso de enviar la solicitud correctamente.
 * 
 */
ResultadoIntentoAutenticacion _ui_autenticacion_intentar_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);


/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
RespuestaAutenticacionUi _ui_autenticacion_procesar_respuesta_autenticacion (ContextoAplicacion *contextoAplicacion, const char *respuesta);


/** \brief Manejar que sucede en caso de error de conexion con el servidor. Finaliza la comunicacion y muestra que hubo un error de conexion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 *
 */
void _ui_autenticacion_manejar_error_conexion (ContextoAplicacion *contextoAplicacion);


/** \brief Seleccionar la interfaz de contactos. Almacenar en el contexto de la aplicacion los datos del id y nombre del usuario.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param uiAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 * \param respuestaAutenticacionUi Puntero a los datos que debe saber la UI de la respuesta de la solicitud de autenticacion. No contiene el header, solo el payload.
 *
 */
void _ui_autenticacion_cambiar_a_ui_contactos (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, const RespuestaAutenticacionUi *respuestaAutenticacionUi);

/** \brief Cambiar de la interfaz de autenticacion a la interfaz de registro.
 * 
 * Resetear la interfaz de autenticacion y configurar los recursos comunes para que se adapten a la interfaz de registro. 
 * Ademas, selecciona la interfaz desde el contexto de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param uiAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void _ui_autenticacion_cambiar_a_ui_registro (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);


#endif // INTERFAZAUTENTICACION_CONTROLADORES_H_INCLUDED
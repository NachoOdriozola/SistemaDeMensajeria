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


/** \enum _t_resultado_intentarAutenticar
 * \brief Enumeracion de posibles resultados al intentar autenticar.
 */
typedef enum
{
   INTENTARAUTENTICAR_RESULTADO_EXITO,
   INTENTARAUTENTICAR_RESULTADO_CREDENCIALES_INVALIDAS,
   INTENTARAUTENTICAR_RESULTADO_ERROR_CONEXION
} _t_resultado_intentarAutenticar;


/**
 * \struct _t_datosUI_respuesta_solicitudAutenticacion
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de autenticacion. No contiene el header, solo el payload.
 */
typedef struct
{
   char estadoSolicitud;
   int idUsuario;
} _t_datosUI_respuesta_solicitudAutenticacion;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */

   
/** \brief Intentar autenticar el usuario.
 * 
 * Verifica que los datos del usuario sean validos para no realizar solicitudes innecesarias.
 * Intenta conectarse con el servidor. En caso de que la conexion falle, se maneja el error de conexion.
 * En caso de que todas las condiciones se cumplan con exito, se envia la solicitud de autenticacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 * \return INTENTARAUTENTICAR_RESULTADO_CREDENCIALES_INVALIDAS en caso de que los datos del usuario sean invalidos. INTENTARAUTENTICAR_RESULTADO_ERROR_CONEXION en caso de no poder conectarse con el servidor.
 * INTENTARAUTENTICAR_RESULTADO_EXITO en caso de enviar la solicitud correctamente.
 * 
 */
_t_resultado_intentarAutenticar _interfazAutenticacion_intentar_autenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);


/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
_t_datosUI_respuesta_solicitudAutenticacion _interfazAutenticacion_solicitudAutenticacion_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta);


/** \brief Manejar que sucede en caso de error de conexion con el servidor. Finaliza la comunicacion y muestra que hubo un error de conexion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 *
 */
void _interfazAutenticacion_manejarError_conexion (t_contextoAplicacion *contextoAplicacion);


/** \brief Seleccionar la interfaz de contactos. Almacenar en el contexto de la aplicacion los datos del id y nombre del usuario.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 * \param datosUI_respuesta_solicitudAutenticacion Puntero a los datos que debe saber la UI de la respuesta de la solicitud de autenticacion. No contiene el header, solo el payload.
 *
 */
void _interfazAutenticacion_cambiarAInterfaz_contactos (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const _t_datosUI_respuesta_solicitudAutenticacion *datosUI_respuesta_solicitudAutenticacion);

/** \brief Cambiar de la interfaz de autenticacion a la interfaz de registro.
 * 
 * Resetear la interfaz de autenticacion y configurar los recursos comunes para que se adapten a la interfaz de registro. 
 * Ademas, selecciona la interfaz desde el contexto de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void _interfazAutenticacion_cambiarAInterfaz_registro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);


#endif // INTERFAZAUTENTICACION_CONTROLADORES_H_INCLUDED
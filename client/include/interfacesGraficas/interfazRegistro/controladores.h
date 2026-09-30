/**
 * \file   controladores.h
 * \brief  Contiene funciones que hacen de puente entre la logica y la interfaz grafica.
 */


#ifndef INTERFAZREGISTRO_CONTROLADORES_H_INCLUDED
#define INTERFAZREGISTRO_CONTROLADORES_H_INCLUDED


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
#include "interfacesGraficas/interfazRegistro/estructuras.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \enum EstadoIntentoRegistro
 * \brief Enumeracion de posibles resultados al intentar registrar.
 */
typedef enum
{
   INTENTO_REGISTRO_SOLICITUD_ENVIADA,
   INTENTO_REGISTRO_CREDENCIALES_INVALIDAS,
   INTENTO_REGISTRO_ERROR_CONEXION
} EstadoIntentoRegistro;

/** \struct ValidacionRegistro
 * \brief Resultados de la validacion de los datos del usuario.
 */
typedef struct
{
   bool nombreValido;
   bool contraseniaValida;
   bool correoValido;
} ValidacionRegistro;

/** \struct ResultadoIntentoRegistro
 * \brief Estructura que contiene el tipo de resultado de la operacion y la validacion de los datos del usuario.
 */
typedef struct
{
   EstadoIntentoRegistro estado;
   ValidacionRegistro validacion;
} ResultadoIntentoRegistro;

/**
 * \struct RespuestaRegistroUi
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de registro. No contiene el header, solo el payload.
 */
typedef struct
{
   char estado;
   int idUsuario;
} RespuestaRegistroUi;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Intentar registrar el usuario.
 * 
 * Verifica que los datos del usuario sean validos para no realizar solicitudes innecesarias. En caso de que no lo sean, se muestra el error de que las credenciales son invalidas.
 * Intenta conectarse con el servidor. En caso de que la conexion falle, se maneja el error de conexion.
 * En caso de que todas las condiciones se cumplan con exito, se envia la solicitud de registro.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 * \return Estructura que contiene el tipo de resultado de la operacion y la validacion de los datos del usuario.
 * Tipo INTENTO_REGISTRO_CREDENCIALES_INVALIDAS en caso de que los datos del usuario sean invalidos.  Es el unico caso que modifica los valores de la validacion de los datos del usuario.
 * Tipo INTENTO_REGISTRO_ERROR_CONEXION en caso de no poder conectarse con el servidor.  
 * Tipo INTENTO_REGISTRO_SOLICITUD_ENVIADA en caso de enviar la solicitud correctamente.
 * 
 */
ResultadoIntentoRegistro _ui_registro_intentar_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);


/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
RespuestaRegistroUi _ui_registro_procesar_respuesta_registro (ContextoAplicacion *contextoAplicacion, const char *respuesta);


/** \brief Manejar que sucede en caso de error de conexion con el servidor. Finaliza la comunicacion y muestra que hubo un error de conexion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 *
 */
void _ui_registro_manejar_error_conexion (ContextoAplicacion *contextoAplicacion);


/** \brief Seleccionar la interfaz de contactos. Almacenar en el contexto de la aplicacion los datos del id y nombre del usuario.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 * \param respuestaRegistroUi Puntero a los datos que debe saber la UI de la respuesta de la solicitud de registro. No contiene el header, solo el payload.
 *
 */
void _ui_registro_cambiar_a_ui_contactos (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, const RespuestaRegistroUi *respuestaRegistroUi);

/** \brief Cambiar de la interfaz de registro a la interfaz de autenticacion.
 * 
 * Verifica que no haya una solicitud en curso.
 * Resetear la interfaz de registro y configurar los recursos comunes para que se adapten a la interfaz de autenticacion. 
 * Ademas, selecciona la interfaz desde el contexto de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void _ui_registro_cambiar_a_ui_autenticacion (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);


#endif // INTERFAZREGISTRO_CONTROLADORES_H_INCLUDED
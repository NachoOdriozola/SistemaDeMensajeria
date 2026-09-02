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

#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "constantes.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazRegistro/estructuras.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \enum _t_tipoResultado_intentarRegistrar
 * \brief Enumeracion de posibles resultados al intentar registrar.
 */
typedef enum
{
   INTENTARREGISTRAR_RESULTADO_EXITO,
   INTENTARREGISTRAR_RESULTADO_CREDENCIALES_INVALIDAS,
   INTENTARREGISTRAR_RESULTADO_ERROR_CONEXION
} _t_tipoResultado_intentarRegistrar;

/** \struct _t_resultado_validacionDatosRegistro
 * \brief Resultados de la validacion de los datos del usuario.
 */
typedef struct
{
   bool nombreValido;
   bool contraseniaValida;
   bool correoValido;
} _t_resultado_validacionDatosRegistro;

/** \struct _t_resultado_intentarRegistrar
 * \brief Estructura que contiene el tipo de resultado de la operacion y la validacion de los datos del usuario.
 */
typedef struct
{
   _t_tipoResultado_intentarRegistrar tipo;
   _t_resultado_validacionDatosRegistro validacion;
} _t_resultado_intentarRegistrar;


/**
 * \struct _t_datosUI_respuesta_solicitudRegistro
 * \brief Datos que debe saber la UI de la respuesta de la solicitud de registro. No contiene el header, solo el payload.
 */
typedef struct
{
   char estadoSolicitud;
   int idUsuario;
} _t_datosUI_respuesta_solicitudRegistro;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Intentar registrar el usuario.
 * 
 * Verifica que los datos del usuario sean validos para no realizar solicitudes innecesarias. En caso de que no lo sean, se muestra el error de que las credenciales son invalidas.
 * Intenta conectarse con el servidor. En caso de que la conexion falle, se maneja el error de conexion.
 * En caso de que todas las condiciones se cumplan con exito, se envia la solicitud de registro.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 * \return Estructura que contiene el tipo de resultado de la operacion y la validacion de los datos del usuario.
 * Tipo INTENTARREGISTRAR_RESULTADO_CREDENCIALES_INVALIDAS en caso de que los datos del usuario sean invalidos.  Es el unico caso que modifica los valores de la validacion de los datos del usuario.
 * Tipo INTENTARREGISTRAR_RESULTADO_ERROR_CONEXION en caso de no poder conectarse con el servidor.  
 * Tipo INTENTARREGISTRAR_RESULTADO_EXITO en caso de enviar la solicitud correctamente.
 * 
 */
_t_resultado_intentarRegistrar _interfazRegsitro_intentar_registrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);


/** \brief Extrae los datos de la respuesta, realiza un log, da por finalizada la solicitud en curso y procesa los datos para que los pueda utilizar la UI para operar.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param respuesta Buffer que contiene la respuesta recibida por el servidor.
 * 
 * \return Estructura que contiene los datos de la respuesta que necesita la UI para operar.
 *
 */
_t_datosUI_respuesta_solicitudRegistro _interfazRegistro_solicitudRegistro_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta);


/** \brief Manejar que sucede en caso de error de conexion con el servidor. Finaliza la comunicacion y muestra que hubo un error de conexion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 *
 */
void _interfazRegistro_manejarError_conexion (t_contextoAplicacion *contextoAplicacion);


/** \brief Seleccionar la interfaz de contactos. Almacenar en el contexto de la aplicacion los datos del id y nombre del usuario.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 * \param datosUI_respuesta_solicitudRegistro Puntero a los datos que debe saber la UI de la respuesta de la solicitud de registro. No contiene el header, solo el payload.
 *
 */
void _interfazRegistro_cambiarAInterfaz_contactos (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const _t_datosUI_respuesta_solicitudRegistro *datosUI_respuesta_solicitudRegistro);

/** \brief Cambiar de la interfaz de registro a la interfaz de autenticacion.
 * 
 * Verifica que no haya una solicitud en curso.
 * Resetear la interfaz de registro y configurar los recursos comunes para que se adapten a la interfaz de autenticacion. 
 * Ademas, selecciona la interfaz desde el contexto de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void _interfazRegistro_cambiarAInterfaz_autenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);


#endif // INTERFAZREGISTRO_CONTROLADORES_H_INCLUDED
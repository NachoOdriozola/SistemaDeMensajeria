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
 */
void _interfazRegsitro_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

/** \brief Manejar que sucede en caso de error de conexion con el servidor. Cierra el socket del cliente y muestra que hubo un error de conexion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void _interfazRegistro_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

/** \brief Seleccionar la interfaz de contactos. Almacenar en el contexto de la aplicacion los datos del id y nombre del usuario.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 * \param datosRespuestaSolicitudRegistro Puntero a los datos de la respuesta de la solicitud de registro.
 *
 */
void _interfazRegistro_accederAContactos (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, t_datosRespuestaSolicitudRegistro *datosRespuestaSolicitudRegistro);

/** \brief Resetear la interfaz de registro y configurar los recursos comunes para que se adapten a la interfaz de autenticacion. ademas, selecciona la interfaz desde el contexto de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void _interfazRegistro_cambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);


#endif // INTERFAZREGISTRO_CONTROLADORES_H_INCLUDED
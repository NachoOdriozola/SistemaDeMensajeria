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

#include "external/csfml/include/SFML/System.h"
#include "external/csfml/include/SFML/Window.h"
#include "external/csfml/include/SFML/Graphics.h"

#include "shared/constantes/include/constantes.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Intentar autenticar el usuario.
 * 
 * Verifica que los datos del usuario sean validos para no realizar solicitudes innecesarias. En caso de que no lo sean, se muestra el error de que las credenciales son invalidas.
 * Intenta conectarse con el servidor. En caso de que la conexion falle, se maneja el error de conexion.
 * En caso de que todas las condiciones se cumplan con exito, se envia la solicitud de autenticacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void _interfazAutenticacion_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

/** \brief Manejar que sucede en caso de error de conexion con el servidor. Cierra el socket del cliente y muestra que hubo un error de conexion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void _interfazAutenticacion_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

/** \brief Seleccionar la interfaz de contactos. Almacenar en el contexto de la aplicacion los datos del id y nombre del usuario.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 * \param datosRespuestaSolicitudAutenticacion Puntero a los datos de la respuesta de la solicitud de autenticacion.
 *
 */
void _interfazAutenticacion_accederAContactos (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, t_datosRespuestaSolicitudAutenticacion *datosRespuestaSolicitudAutenticacion);

/** \brief Resetear la interfaz de autenticacion y configurar los recursos comunes para que se adapten a la interfaz de registro. ademas, selecciona la interfaz desde el contexto de la aplicacion.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void _interfazAutenticacion_cambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);


#endif // INTERFAZAUTENTICACION_CONTROLADORES_H_INCLUDED
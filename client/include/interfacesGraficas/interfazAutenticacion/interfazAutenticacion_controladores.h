/**
 * \file   interfazAutenticacion_controladores.h
 * \brief  Contiene funciones controladoras.
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

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/constantes/include/constantes.h"
#include "../../estructuras.h"
#include "../../utiles.h"
#include "../../comunicacion.h"

#include "../recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfazAutenticacion_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Resetear la interfaz de autenticacion.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_resetear (sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion);

void _interfazAutenticacion_deshabilitarFocos (t_interfazAutenticacion *interfazAutenticacion);


/*
 * Establecer el foco en escribir nombre y posiciona el punto de insercion.
*/
bool _interfazAutenticacion_manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion);

/*
 * Establecer el foco en escribir contrasenia y posiciona el punto de insercion.
*/
bool _interfazAutenticacion_manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion);

/*
 * Verificar que los datos de autenticacion del usuario sean validos.
 * Intentar conectar con el servidor creando el socket del cliente, configurandolo y conectandolo al servidor.
 * Enviar la solicitud de autenticacion y procesar la respuesta segun su estado.
 * En caso de una respuesta exitosa, almacena el ID, el nombre de usuario y el socket creado conectado con el servidor en el contexto de la aplicacion, y selecciona la interfaz de contactos.
*/
bool _interfazAutenticacion_manejarClickIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

/*
 * Omite los eventos pendientes de la interfaz de autenticacion, desactiva los recursos de la interfaz de autenticacion, activa los recursos de la interfaz de registro, y selecciona la interfaz de registro.
 * Retorna EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
*/
bool _interfazAutenticacion_manejarClickCambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);


/*
 * Si se encuentra el foco en escribir nombre, verifica que el caracter ingresado es valido.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene el nombre y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazAutenticacion_manejarEscribirNombre (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar);

/*
 * Si se encuentra el foco en escribir contrasenia, verifica que el caracter ingresado es valido.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene la contrasenia y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazAutenticacion_manejarEscribirContrasenia (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar);


/*
 * Verificar que los datos de autenticacion del usuario sean validos.
 * Intentar conectar con el servidor creando el socket del cliente, configurandolo y conectandolo al servidor.
 * Enviar la solicitud de autenticacion y procesar la respuesta segun su estado.
 * En caso de una respuesta exitosa, almacena el ID, el nombre de usuario y el socket creado conectado con el servidor en el contexto de la aplicacion, y selecciona la interfaz de contactos.
*/
bool _interfazAutenticacion_manejarEnterIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);


/*
 * Si se encuentra el foco en escribir nombre, intenta pegar el texto desde el portapapeles al nombre.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene el nombre y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazAutenticacion_manejarPegarTextoDesdePortapapelesAEscribirNombre (t_interfazAutenticacion *interfazAutenticacion);

/*
 * Si se encuentra el foco en escribir contrasenia, intenta pegar el texto desde el portapapeles a la contrasenia.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene la contrasenia y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazAutenticacion_manejarPegarTextoDesdePortapapelesAEscribirContrasenia (t_interfazAutenticacion *interfazAutenticacion);


#endif // INTERFAZAUTENTICACION_CONTROLADORES_H_INCLUDED
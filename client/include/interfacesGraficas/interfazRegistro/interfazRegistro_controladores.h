/**
 * \file   interfazRegistro_controladores.h
 * \brief  Contiene funciones controladoras.
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

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/constantes/include/constantes.h"
#include "../../estructuras.h"
#include "../../utiles.h"
#include "../../comunicacion.h"

#include "../recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfazRegistro_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazRegistro_deshabilitarFocos (t_interfazRegistro *interfazRegistro);

/*
 * Establecer el foco en escribir nombre y posiciona el punto de insercion.
*/
bool _interfazRegistro_manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);

/*
 * Establecer el foco en escribir contrasenia y posiciona el punto de insercion.
*/
bool _interfazRegistro_manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);

/*
 * Establecer el foco en escribir correo electronico y posiciona el punto de insercion.
*/
bool _interfazRegistro_manejarClickEscribirCorreo (const sfRenderWindow *renderizado, t_interfazRegistro *interfazRegistro);

/*
 * Verificar que la habilitacion de posibilidad de ingreso se encuentre habilitada.
 * Envia la solicitud de registro y procesa la respuesta segun su estado.
 * En caso de una respuesta exitosa, almacena el ID y el nombre de usuario en el contexto de la aplicacion, y selecciona la interfaz de contactos.
*/
bool _interfazRegistro_manejarClickIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

/*
 * Omite los eventos pendientes de la interfaz de registro, desactiva los recursos de la interfaz de registro, activa los recursos de la interfaz de autenticacion, y selecciona la interfaz de autenticacion.
 * Retorna EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
*/
bool _interfazRegistro_manejarClickCambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);


/*
 * Si se encuentra el foco en escribir nombre, verifica que el caracter ingresado es valido.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene el nombre y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazRegistro_manejarEscribirNombre (t_interfazRegistro *interfazRegistro, sfEvent eventoChar);

/*
 * Si se encuentra el foco en escribir contrasenia, verifica que el caracter ingresado es valido.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene la contrasenia y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazRegistro_manejarEscribirContrasenia (t_interfazRegistro *interfazRegistro, sfEvent eventoChar);

/*
 * Si se encuentra el foco en escribir correo electronico, verifica que el caracter ingresado es valido.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene el correo electronico y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazRegistro_manejarEscribirCorreo (t_interfazRegistro *interfazRegistro, sfEvent eventoChar);


/*
 * Verificar que la habilitacion de posibilidad de ingreso se encuentre habilitada.
 * Envia la solicitud de registro y procesa la respuesta segun su estado.
 * En caso de una respuesta exitosa, almacena el ID y el nombre de usuario en el contexto de la aplicacion, y selecciona la interfaz de contactos.
*/
bool _interfazRegistro_manejarEnterIntentarRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);


/*
 * Si se encuentra el foco en escribir nombre, intenta pegar el texto desde el portapapeles al nombre.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene el nombre y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirNombre (t_interfazRegistro *interfazRegistro);

/*
 * Si se encuentra el foco en escribir contrasenia, intenta pegar el texto desde el portapapeles a la contrasenia.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene la contrasenia y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirContrasenia (t_interfazRegistro *interfazRegistro);

/*
 * Si se encuentra el foco en escribir correo electronico, intenta pegar el texto desde el portapapeles al correo electronico.
 * En caso de exito, verifica si habilita la posibilidad de ingreso al usuario, lo agrega a la cadena que contiene el correo electronico y posiciona el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
*/
bool _interfazRegistro_manejarPegarTextoDesdePortapapelesAEscribirCorreo (t_interfazRegistro *interfazRegistro);


#endif // INTERFAZREGISTRO_CONTROLADORES_H_INCLUDED
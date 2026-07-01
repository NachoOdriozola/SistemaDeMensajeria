/**
 * \file   interfazContactos_controladores.h
 * \brief  Contiene funciones controladoras.
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

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../estructuras.h"
#include "../../comunicacion.h"
#include "../../utiles.h"

#include "../recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"
#include "interfazContactos_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazContactos_deshabilitarFocos (t_interfazContactos *interfazContactos);


/*
 * Verifica que no sea un mensaje vacio.
 * Contempla los casos de envio de un comando para seleccion de un chat y para el envio de un mensaje.
 * En caso de seleccion de chat: verifica que sea un comando valido, envia la solicitud, y si esta es respondida con exito, setea el nuevo chat logicamente y graficamente.
 * En caso de envio de un mensaje: envia la solicitud, y si esta es respondida con exito, inserta el mensaje en la lista de mensajes para mostrar.
*/
bool _interfazContactos_manejarClickEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

/*
 * Omite los eventos pendientes de la interfaz de contactos, desactiva los recursos de la interfaz de contactos, activa los recursos de la interfaz de salas, y selecciona la interfaz de salas.
 * Retorna EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
*/
bool _interfazContactos_manejarClickCambiarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


/*
 * Verifica que no sea un mensaje vacio.
 * Contempla los casos de envio de un comando para seleccion de un chat y para el envio de un mensaje.
 * En caso de seleccion de chat: verifica que sea un comando valido, envia la solicitud, y si esta es respondida con exito, setea el nuevo chat logicamente y graficamente.
 * En caso de envio de un mensaje: envia la solicitud, y si esta es respondida con exito, inserta el mensaje en la lista de mensajes para mostrar.
*/
bool _interfazContactos_manejarEnterEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


#endif // INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
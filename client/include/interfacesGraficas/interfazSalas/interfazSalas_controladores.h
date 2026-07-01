/**
 * \file   interfazSalas_controladores.h
 * \brief  Contiene funciones controladoras.
 */


#ifndef INTERFAZSALAS_CONTROLADORES_H_INCLUDED
#define INTERFAZSALAS_CONTROLADORES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../estructuras.h"
#include "../../utiles.h"

#include "../recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"
#include "interfazSalas_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazSalas_deshabilitarFocos (t_interfazSalas *interfazSalas);

/*
 * Omite los eventos pendientes de la interfaz de salas, desactiva los recursos de la interfaz de salas, activa los recursos de la interfaz de contactos, y selecciona la interfaz de contactos.
 * Retorna EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
*/
bool _interfazSalas_manejarClickCambiarAInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfazSalas *interfazSalas);


#endif // INTERFAZSALAS_CONTROLADORES_H_INCLUDED
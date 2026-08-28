/**
 * \file   actualizar.h
 * \brief  Contiene funciones de actualizacion. Captura y maneja los eventos no generados por el usuario directamente.
 */


#ifndef INTERFAZCONTACTOS_ACTUALIZAR_H_INCLUDED
#define INTERFAZCONTACTOS_ACTUALIZAR_H_INCLUDED


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
#include "protocolos.h"

#include "logica/estructuras.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */

   
void _interfazContactos_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


#endif // INTERFAZCONTACTOS_ACTUALIZAR_H_INCLUDED
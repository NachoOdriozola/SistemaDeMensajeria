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

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"
#include "protocolos.h"

#include "logica/estructuras.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */

   
void _ui_contactos_actualizar (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos);


#endif // INTERFAZCONTACTOS_ACTUALIZAR_H_INCLUDED
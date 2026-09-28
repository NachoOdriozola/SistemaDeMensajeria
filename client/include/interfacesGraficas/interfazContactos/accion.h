/**
 * \file   accion.h
 * \brief  Contiene funciones de accion. Captura y maneja los eventos generados por el usuario directamente.
 */


#ifndef INTERFAZCONTACTOS_ACCION_H_INCLUDED
#define INTERFAZCONTACTOS_ACCION_H_INCLUDED


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

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazContactos_accion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


#endif // INTERFAZCONTACTOS_ACCION_H_INCLUDED
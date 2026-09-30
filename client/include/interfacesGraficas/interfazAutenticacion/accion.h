/**
 * \file   accion.h
 * \brief  Contiene funciones de accion. Captura y maneja los eventos generados por el usuario directamente.
 */


#ifndef INTERFAZAUTENTICACION_ACCION_H_INCLUDED
#define INTERFAZAUTENTICACION_ACCION_H_INCLUDED


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

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"
#include "interfacesGraficas/interfazAutenticacion/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _ui_autenticacion_accionar (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);


#endif // INTERFAZAUTENTICACION_ACCION_H_INCLUDED
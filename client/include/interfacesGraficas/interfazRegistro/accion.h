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

#include "external/csfml/include/SFML/System.h"
#include "external/csfml/include/SFML/Window.h"
#include "external/csfml/include/SFML/Graphics.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazRegistro/estructuras.h"
#include "interfacesGraficas/interfazRegistro/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazRegistro_accion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);


#endif // INTERFAZAUTENTICACION_ACCION_H_INCLUDED
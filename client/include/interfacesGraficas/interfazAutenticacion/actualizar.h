/**
 * \file   actualizar.h
 * \brief  Contiene funciones de actualizacion. Captura y maneja los eventos no generados por el usuario directamente.
 */


#ifndef INTERFAZAUTENTICACION_ACTUALIZACIONES_H_INCLUDED
#define INTERFAZAUTENTICACION_ACTUALIZACIONES_H_INCLUDED


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
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"
#include "interfacesGraficas/interfazAutenticacion/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazAutenticacion_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);


#endif // INTERFAZAUTENTICACION_ACTUALIZACIONES_H_INCLUDED
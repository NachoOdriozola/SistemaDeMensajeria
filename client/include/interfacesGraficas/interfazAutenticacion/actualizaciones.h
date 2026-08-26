/**
 * \file   actualizaciones.h
 * \brief  Contiene funciones de actualizaciones.
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

#include "shared/constantes/include/constantes.h"
#include "shared/protocolos/include/protocolos.h"

#include "logica/estructuras.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"
#include "interfacesGraficas/interfazAutenticacion/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * Procesar las diferentes posibles respuestas que se recibio del servidor.
*/
void _interfazAutenticacion_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta, t_resultadoRecepcion resultadoRecepcion);


#endif // INTERFAZAUTENTICACION_ACTUALIZACIONES_H_INCLUDED
/**
 * \file   interfazRegistro_actualizaciones.h
 * \brief  Contiene funciones de actualizaciones.
 */


#ifndef INTERFAZREGISTRO_ACTUALIZACIONES_H_INCLUDED
#define INTERFAZREGISTRO_ACTUALIZACIONES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */

   
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../../../shared/constantes/include/constantes.h"
#include "../../../../shared/protocolos/include/protocolos.h"

#include "../../estructuras.h"
#include "../../comunicacion.h"

#include "../recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfazRegistro_estructuras.h"
#include "interfazRegistro_controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * Procesar las diferentes posibles respuestas que se recibio del servidor.
*/
void _interfazRegistro_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta, t_resultadoRecepcion resultadoRecepcion);


#endif // INTERFAZREGISTRO_ACTUALIZACIONES_H_INCLUDED
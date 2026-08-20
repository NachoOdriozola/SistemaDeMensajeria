/**
 * \file   interfazContactos_actualizaciones.h
 * \brief  Contiene funciones de actualizaciones.
 */


#ifndef INTERFAZCONTACTOS_ACTUALIZACIONES_H_INCLUDED
#define INTERFAZCONTACTOS_ACTUALIZACIONES_H_INCLUDED


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

#include "../recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"
#include "interfazContactos_estructuras.h"
#include "interfazContactos_controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * Procesar las diferentes posibles respuestas que se recibio del servidor.
*/
void _interfazContactos_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta, t_resultadoRecepcion resultadoRecepcion);


#endif // INTERFAZCONTACTOS_ACTUALIZACIONES_H_INCLUDED
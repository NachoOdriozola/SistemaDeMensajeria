/**
 * \file   actualizar.h
 * \brief  Contiene funciones de actualizacion. Captura y maneja los eventos no generados por el usuario directamente.
 */


#ifndef INTERFAZREGISTRO_ACTUALIZAR_H_INCLUDED
#define INTERFAZREGISTRO_ACTUALIZAR_H_INCLUDED


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
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazRegistro/estructuras.h"
#include "interfacesGraficas/interfazRegistro/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazRegistro_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);


#endif // INTERFAZREGISTRO_ACTUALIZAR_H_INCLUDED
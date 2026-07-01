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

#include "../recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"
#include "interfazContactos_estructuras.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \enum t_datosRecepcionMensaje
 * \brief Almacena los datos del mensaje recibido del servidor.
 */
typedef struct
{
   int idUsuarioEmisor;
   char mensaje [MAX_MENSAJE];
} t_datosRecepcionMensaje;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * Procesar las diferentes posibles respuestas que se recibio del servidor.
*/
void _interfazContactos_procesarRespuesta (t_interfazContactos *interfazContactos, const char *respuesta);


#endif // INTERFAZCONTACTOS_ACTUALIZACIONES_H_INCLUDED
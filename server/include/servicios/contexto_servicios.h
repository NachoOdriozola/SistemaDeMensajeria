/**
 * \file   contexto_servicios.h
 * \brief 
 */


#ifndef CONTEXTO_SERVICIOS_H_INCLUDED
#define CONTEXTO_SERVICIOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */

   
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constantes.h"

#include "logs.h"

#include "cola.h"

#include "nucleo/intercambio.h"

#include "bd/bd.h"
#include "clientes/registro_clientes.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


typedef struct
{
   Bd *bd;
   RegistroClientes *registroClientes;
   Cola respuestas;
} Servicios;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


CodigoRetorno servicios_guardar_respuesta (Servicios *servicios, const Cliente *destinatario, TipoRespuesta tipo, const void *datosRespuesta, size_t tamDatos);


#endif // CONTEXTO_SERVICIOS_H_INCLUDED
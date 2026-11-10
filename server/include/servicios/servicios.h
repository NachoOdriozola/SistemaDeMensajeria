/**
 * \file   servicios.h
 * \brief  Contiene funciones que procesan las solicitudes de los clientes.
 */


#ifndef SERVICIOS_H_INCLUDED
#define SERVICIOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sodium.h"

#include "constantes.h"

#include "nucleo/intercambio.h"

#include "bd/bd.h"
#include "clientes/registro_clientes.h"

#include "servicios/contexto_servicios.h"
#include "servicios/autenticacion.h"
#include "servicios/registro.h"
#include "servicios/envio_mensaje.h"
#include "servicios/seleccion_chat.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


CodigoRetorno servicios_inicializar (Servicios *servicios, Bd *bd, RegistroClientes *registroClientes);
CodigoRetorno servicios_procesar (Servicios *servicios, Solicitud *solicitud);
bool servicios_siguiente_respuesta (Servicios *servicios, Respuesta *returnRespuesta);
void servicios_liberar (Servicios *servicios);



#endif // SERVICIOS_H_INCLUDED
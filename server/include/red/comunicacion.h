/**
 * \file   comunicacion.h
 * \brief 
 */


#ifndef COMUNICACION_H_INCLUDED
#define COMUNICACION_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "constantes.h"

#include "logs.h"

#include "cola.h"

#include "frame.h"
#include "sockets.h"

#include "nucleo/intercambio.h"

#include "clientes/cliente.h"
#include "clientes/registro_clientes.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


typedef struct
{
   Socket socket;
   RegistroClientes *registroClientes;
   Cola solicitudes;
} Comunicacion;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


CodigoRetorno comunicacion_inicializar (Comunicacion *comunicacion, RegistroClientes *registroClientes);
CodigoRetorno comunicacion_aceptar_nuevo_cliente (Comunicacion *comunicacion);
CodigoRetorno comunicacion_recibir_solicitudes (Comunicacion *comunicacion);
bool comunicacion_siguiente_solicitud (Comunicacion *comunicacion, Solicitud *returnSolicitud);
CodigoRetorno comunicacion_enviar_respuesta (Comunicacion *comunicacion, const Respuesta *respuesta);
void comunicacion_liberar (Comunicacion *comunicacion);


#endif // COMUNICACION_H_INCLUDED
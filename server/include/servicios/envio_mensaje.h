/**
 * \file   envio_mensaje.h
 * \brief 
 */


#ifndef ENVIO_MENSAJE_H_INCLUDED
#define ENVIO_MENSAJE_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constantes.h"
#include "mensajes.h"

#include "bd/bd.h"
#include "servicios/contexto_servicios.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudEnvioMensaje.
 * 
 * Antes de enviar el mensaje, verifica que el ID del emisor o del receptor sean validos y que no sean los mismos.
 * El mensaje es almacenado en la base de datos antes de ser reenviado al receptor.
 * Si el receptor se encuentra conectado, le reenvia el mensaje con una cadena compuesta de la siguiente manera:
 * tipo respuesta mensaje|id del emisor|texto del mensaje
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaEnvioMensaje.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_ENVIO_MENSAJE|SOLICITUD_EXITO #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_ENVIO_MENSAJE|SOLICITUD_ERROR_OPERACION_INVALIDA #En caso que sean datos de envio de mensaje invalidos o que el emisor sea el receptor.
 */
CodigoRetorno envio_mensaje_procesar (Servicios *servicios, Cliente *cliente, const SolicitudEnvioMensaje *solicitudEnvioMensaje);


#endif // ENVIO_MENSAJE_H_INCLUDED
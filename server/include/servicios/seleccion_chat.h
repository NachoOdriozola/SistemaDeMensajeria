/**
 * \file   seleccion_chat.h
 * \brief 
 */


#ifndef SELECCION_CHAT_H_INCLUDED
#define SELECCION_CHAT_H_INCLUDED


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
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudSeleccionChat.
 *
 * Verificar que el usuario seleccionado existe.
 * Verificar que el usuario no haya seleccionado su propio chat.
 *
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaSeleccionChat.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_SELECCION_CHAT|SOLICITUD_EXITO|ID del usuario del chat seleccionado #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_SELECCION_CHAT|SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido #En caso que sean datos de seleccion de chat invalidos, que el usuario seleccionado no exista o que el usuario selecciono su propio chat.
 */
CodigoRetorno seleccion_chat_procesar (Servicios *servicios, Cliente *cliente, const SolicitudSeleccionChat *solicitudSeleccionChat);


#endif // SELECCION_CHAT_H_INCLUDED
/**
 * \file   frame.h
 * \brief 
 */


#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <string.h>

#include "mensajes.h"


/* ============================================================================================================================================
   TAMANIOS DE BUFFERS DE COMUNICACION
   ============================================================================================================================================ */


/**
 * \def MAX_BUFFER_SOLICITUD
 * \brief Tamanio maximo del buffer para comunicar solicitudes entre el cliente y el servidor. Incluye el '0'.
 */
#define MAX_BUFFER_SOLICITUD sizeof (Header) + sizeof (PayloadSolicitud)

/**
 * \def MAX_BUFFER_RESPUESTA
 * \brief Tamanio maximo del buffer para comunicar respuestas entre el cliente y el servidor. Incluye el '0'.
 */
#define MAX_BUFFER_RESPUESTA sizeof (Header) + sizeof (PayloadRespuesta)


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


typedef struct
{
   char tipo;
   size_t longitud;
} Header;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


size_t frame_armar_solicitud (char *returnBufferSalida, TipoSolicitud tipoSolicitud, const PayloadSolicitud *payloadSolicitud);
void frame_extraer_solicitud (const char *bufferEntrada, TipoSolicitud *returnTipoSolicitud, PayloadSolicitud *returnPayloadSolicitud);
size_t frame_armar_respuesta (char *returnBufferSalida, TipoRespuesta tipoRespuesta, const PayloadRespuesta *payloadRespuesta);
void frame_extraer_respuesta (const char *bufferEntrada, TipoRespuesta *returnTipoRespuesta, PayloadRespuesta *returnPayloadRespuesta);


#endif // FRAME_H_INCLUDED
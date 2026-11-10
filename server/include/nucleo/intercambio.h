/**
 * \file   intercambio.h
 * \brief  
 */


#ifndef INTERCAMBIO_H_INCLUDED
#define INTERCAMBIO_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "mensajes.h"

#include "clientes/cliente.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


typedef struct
{
   Cliente *cliente;
   TipoSolicitud tipo;
   PayloadSolicitud payload;
} Solicitud;

typedef struct
{
   Cliente *cliente;
   TipoRespuesta tipo;
   PayloadRespuesta payload;
} Respuesta;



#endif // INTERCAMBIO_H_INCLUDED
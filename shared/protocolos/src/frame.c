#include "frame.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static size_t tam_respuesta (TipoRespuesta tipoRespuesta);
static size_t tam_solicitud (TipoSolicitud tipoSolicitud);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


size_t frame_armar_solicitud (char *returnBufferSalida, TipoSolicitud tipoSolicitud, const PayloadSolicitud *payloadSolicitud)
{
    Header header;

    header.tipo = tipoSolicitud;
    header.longitud = tam_solicitud (tipoSolicitud);

    memcpy (returnBufferSalida, &header, sizeof(Header));
    memcpy (returnBufferSalida + sizeof (Header), payloadSolicitud, header.longitud);

    return sizeof(Header) + header.longitud;
}

void frame_extraer_solicitud (const char *bufferEntrada, TipoSolicitud *returnTipoSolicitud, PayloadSolicitud *returnPayloadSolicitud)
{
    Header header;

    memcpy (&header, bufferEntrada, sizeof(Header));
    *returnTipoSolicitud = header.tipo;
    memcpy (returnPayloadSolicitud, bufferEntrada + sizeof(Header), header.longitud);
}

size_t frame_armar_respuesta (char *returnBufferSalida, TipoRespuesta tipoRespuesta, const PayloadRespuesta *payloadRespuesta)
{
    Header header;

    header.tipo = tipoRespuesta;
    header.longitud = tam_respuesta (tipoRespuesta);

    memcpy (returnBufferSalida, &header, sizeof(Header));
    memcpy (returnBufferSalida + sizeof (Header), payloadRespuesta, header.longitud);

    return sizeof(Header) + header.longitud;
}

void frame_extraer_respuesta (const char *bufferEntrada, TipoRespuesta *returnTipoRespuesta, PayloadRespuesta *returnPayloadRespuesta)
{
    Header header;

    memcpy (&header, bufferEntrada, sizeof(Header));
    *returnTipoRespuesta = header.tipo;
    memcpy (returnPayloadRespuesta, bufferEntrada + sizeof(Header), header.longitud);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static size_t tam_solicitud (TipoSolicitud tipoSolicitud)
{
    switch (tipoSolicitud)
    {
    case SOLICITUD_AUTENTICACION:
        return sizeof (SolicitudAutenticacion);

    case SOLICITUD_REGISTRO:
        return sizeof (SolicitudRegistro);

    case SOLICITUD_ENVIO_MENSAJE:
        return sizeof (SolicitudEnvioMensaje);

    case SOLICITUD_SELECCION_CHAT:
        return sizeof (SolicitudSeleccionChat);

    default:
        return 0;
    }
}

static size_t tam_respuesta (TipoRespuesta tipoRespuesta)
{
    switch (tipoRespuesta)
    {
    case RESPUESTA_AUTENTICACION:
        return sizeof (RespuestaAutenticacion);

    case RESPUESTA_REGISTRO:
        return sizeof (RespuestaRegistro);

    case RESPUESTA_ENVIO_MENSAJE:
        return sizeof (RespuestaEnvioMensaje);

    case RESPUESTA_SELECCION_CHAT:
        return sizeof (RespuestaSeleccionChat);

    case RESPUESTA_RECEPCION_MENSAJE:
        return sizeof (RespuestaRecepcionMensaje);

    default:
        return 0;
    }
}

#include "servicios/contexto_servicios.h"


CodigoRetorno servicios_guardar_respuesta (Servicios *servicios, const Cliente *destinatario, TipoRespuesta tipo, const void *datosRespuesta, size_t tamDatos)
{
    Respuesta respuesta;

    respuesta.tipo = tipo;
    respuesta.cliente = (Cliente*)destinatario;
    memcpy (&(respuesta.payload), datosRespuesta, tamDatos);

    if (cola_insertar (&(servicios->respuestas), &respuesta, sizeof (Respuesta)) != EXITO)
    {
        logs_escribir (LOG_ERROR, "servicios", "Respuesta del cliente no almacenada.");
        return ERROR_SIN_MEMORIA;
    }
    return EXITO;
}

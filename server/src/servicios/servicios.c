#include "servicios/servicios.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static CodigoRetorno procesar_solicitud_invalida (Solicitud *solicitud);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno servicios_inicializar (Servicios *servicios, Bd *bd, RegistroClientes *registroClientes)
{
    servicios->bd = bd;
    servicios->registroClientes = registroClientes;
    cola_crear (&(servicios->respuestas));

    if (sodium_init () < 0)
    {
        logs_escribir (LOG_ERROR, "servicios", "Inicializacion: sodium.");
        return ERROR_INICIALIZACION;
    }

    return EXITO;
}

CodigoRetorno servicios_procesar (Servicios *servicios, Solicitud *solicitud)
{
    cola_vaciar (&(servicios->respuestas));
    switch (solicitud->tipo)
    {
        case SOLICITUD_AUTENTICACION:
            return autenticacion_procesar (servicios, solicitud->cliente, &(solicitud->payload.solicitudAutenticacion));

        case SOLICITUD_REGISTRO:
            return registro_procesar (servicios, solicitud->cliente, &(solicitud->payload.solicitudRegistro));

        case SOLICITUD_ENVIO_MENSAJE:
            return envio_mensaje_procesar (servicios, solicitud->cliente, &(solicitud->payload.solicitudEnvioMensaje));

        case SOLICITUD_SELECCION_CHAT:
            return seleccion_chat_procesar (servicios, solicitud->cliente, &(solicitud->payload.solicitudSeleccionChat));

        default:
            return procesar_solicitud_invalida (solicitud);
    }
}

bool servicios_siguiente_respuesta (Servicios *servicios, Respuesta *returnRespuesta)
{
    if (cola_no_esta_vacia (&(servicios->respuestas)))
    {
        cola_sacar (&(servicios->respuestas), returnRespuesta, sizeof (Respuesta));
        return 1;
    }
    return 0;
}

void servicios_liberar (Servicios *servicios)
{
    cola_vaciar (&(servicios->respuestas));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static CodigoRetorno procesar_solicitud_invalida (Solicitud *solicitud)
{
    cliente_marcar_desconectado (solicitud->cliente);
    logs_escribir (LOG_AVISO, "servicios", "Tipo de solicitud invalida: %c y cliente id=%d desconectado", solicitud->tipo, cliente_obtener_id (solicitud->cliente));
    return ERROR_OPERACION_INVALIDA;
}

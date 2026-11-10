#include "red/comunicacion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static CodigoRetorno encolar_si_envio_solicitud (void *a, void *b);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno comunicacion_inicializar (Comunicacion *comunicacion, RegistroClientes *registroClientes)
{
    comunicacion->registroClientes = registroClientes;
    cola_crear (&(comunicacion->solicitudes));

    if (
        (socket_inicializar () != EXITO) ||
        (socket_crear (&(comunicacion->socket)) != EXITO) ||
        (socket_conectar_servidor (&(comunicacion->socket)) != EXITO) ||
        (socket_establecer_keep_alive (&(comunicacion->socket)) != EXITO)
        )
        {
            logs_escribir (LOG_ERROR, "comunicacion", "Inicializacion fallida.");
            socket_cerrar (&(comunicacion->socket));
            socket_finalizar ();
            return ERROR_INICIALIZACION;
        }
    socket_establecer_modo_no_bloqueante (&(comunicacion->socket));
    
    return EXITO;
}

CodigoRetorno comunicacion_aceptar_nuevo_cliente (Comunicacion *comunicacion)
{
    Cliente nuevoCliente;
    Socket socket;

    socket = socket_aceptar_nuevo_cliente (comunicacion->socket);

    if (!socket_es_valido (socket))
        return EXITO;

    socket_establecer_modo_no_bloqueante (&socket);
    cliente_inicializar (&nuevoCliente, socket);
    if (registro_clientes_insertar_no_autenticado (comunicacion->registroClientes, &nuevoCliente) != EXITO)
    {
        cliente_liberar (&nuevoCliente);
        logs_escribir (LOG_ERROR, "comunicacion", "Aceptacion de nuevo cliente.");
        return ERROR_SIN_MEMORIA;
    }

    logs_escribir (LOG_INFO, "comunicacion", "Nuevo cliente conectado.");
    return EXITO;
}

CodigoRetorno comunicacion_recibir_solicitudes (Comunicacion *comunicacion)
{
    return registro_clientes_por_cada (comunicacion->registroClientes, encolar_si_envio_solicitud, &(comunicacion->solicitudes));
}

bool comunicacion_siguiente_solicitud (Comunicacion *comunicacion, Solicitud *returnSolicitud)
{
    if (cola_no_esta_vacia (&(comunicacion->solicitudes)))
    {
        cola_sacar (&(comunicacion->solicitudes), returnSolicitud, sizeof (Solicitud));
        return 1;
    }
    return 0;
}

CodigoRetorno comunicacion_enviar_respuesta (Comunicacion *comunicacion, const Respuesta *respuesta)
{
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    size_t tamRespuesta;
    ResultadoEnvio resultado;

    tamRespuesta = frame_armar_respuesta (bufferRespuesta, respuesta->tipo, &(respuesta->payload));
    resultado = socket_enviar (respuesta->cliente->socket, bufferRespuesta, tamRespuesta);
    if ((resultado == ENVIO_BLOQUEADO) || (resultado == ENVIO_ERROR_CONEXION))
    {
        cliente_marcar_desconectado (respuesta->cliente);
        logs_escribir (LOG_AVISO, "comunicacion", "Cliente id=%d desconectado.", cliente_obtener_id (respuesta->cliente));
        return ERROR_EJECUCION;
    }
    return EXITO;
}

void comunicacion_liberar (Comunicacion *comunicacion)
{
    cola_vaciar (&(comunicacion->solicitudes));
    socket_cerrar (&(comunicacion->socket));
    socket_finalizar ();
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static CodigoRetorno encolar_si_envio_solicitud (void *a, void *b)
{
    Cola *solicitudes = (Cola*)b;
    Solicitud solicitud;
    ResultadoRecepcion resultadoRecepcion;
    char bufferSolicitud [MAX_BUFFER_SOLICITUD];

    solicitud.cliente = (Cliente*)a;
    resultadoRecepcion = socket_recibir (solicitud.cliente->socket, bufferSolicitud, MAX_BUFFER_SOLICITUD);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
    {
        frame_extraer_solicitud (bufferSolicitud, &(solicitud.tipo), &(solicitud.payload));
        if (cola_insertar (solicitudes, &solicitud, sizeof (Solicitud)) != EXITO)
        {
            cliente_marcar_desconectado (solicitud.cliente);
            logs_escribir (LOG_AVISO, "comunicacion", "Cliente %d desconectado.", cliente_obtener_id (solicitud.cliente));
            return ERROR_SIN_MEMORIA;
        }
    } 

    if (resultadoRecepcion == RECEPCION_CERRADA_ORDENADA)
    {
        cliente_marcar_desconectado (solicitud.cliente);
        logs_escribir (LOG_INFO, "comunicacion", "Cliente %d desconectado.", cliente_obtener_id (solicitud.cliente));
    }

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        cliente_marcar_desconectado (solicitud.cliente);
        logs_escribir (LOG_AVISO, "comunicacion", "Cliente %d desconectado.", cliente_obtener_id (solicitud.cliente));
    }

    return EXITO;
}


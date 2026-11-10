#include "servicios/seleccion_chat.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool es_seleccion_chat_invalido (const SolicitudSeleccionChat *solicitudSeleccionChat);
static CodigoRetorno usuario_seleccionado_existe (Bd *bd, const SolicitudSeleccionChat *solicitudSeleccionChat, int *returnIdUsuarioChatSeleccionado);
static bool usuario_selecciono_su_propio_chat (int idCliente, int idUsuarioChatSeleccionado);
static CodigoRetorno guardar_respuesta (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado, int idUsuarioChatSeleccionado);
static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado);
static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno seleccion_chat_procesar (Servicios *servicios, Cliente *cliente, const SolicitudSeleccionChat *solicitudSeleccionChat)
{
    ResultadoBd resultadoBd;
    int idUsuarioChatSeleccionado;

    if (es_seleccion_chat_invalido (solicitudSeleccionChat))
        return rechazar (servicios, cliente, RESPUESTA_ERROR_OPERACION_INVALIDA);

    resultadoBd = usuario_seleccionado_existe (servicios->bd, solicitudSeleccionChat, &idUsuarioChatSeleccionado);
    if (resultadoBd == BD_NO_ENCONTRO)
        return rechazar (servicios, cliente, RESPUESTA_ERROR_OPERACION_INVALIDA);
    if (resultadoBd == BD_ERROR_EJECUCION)
        return fallar (servicios, cliente);

    if (usuario_selecciono_su_propio_chat (cliente_obtener_id (cliente), idUsuarioChatSeleccionado))
        return rechazar (servicios, cliente, RESPUESTA_ERROR_OPERACION_INVALIDA);

    if (guardar_respuesta (servicios, cliente, RESPUESTA_EXITO, idUsuarioChatSeleccionado) != EXITO)
        return ERROR_SIN_MEMORIA;

    logs_escribir (LOG_INFO, "seleccion chat", "Cliente id=%d selecciono el chat con el cliente id=%d.", cliente_obtener_id (cliente), idUsuarioChatSeleccionado);
    return EXITO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool son_todos_espacios (const char *cad)
{
    if (*cad == '\0')
        return false;

    while (*cad == ' ')
        cad ++;

    if (*cad == '\0')
        return true;
    return false;
}

static bool es_seleccion_chat_invalido (const SolicitudSeleccionChat *solicitudSeleccionChat)
{
    int largo;

    largo = strlen (solicitudSeleccionChat->nombreUsuarioChatSeleccionado);
    return ((largo < 3) || (largo > MAX_NOMBRE_USUARIO) || (son_todos_espacios (solicitudSeleccionChat->nombreUsuarioChatSeleccionado)));
}

static CodigoRetorno usuario_seleccionado_existe (Bd *bd, const SolicitudSeleccionChat *solicitudSeleccionChat, int *returnIdUsuarioChatSeleccionado)
{
    return (bd_buscar_id_usuario_por_nombre (bd, solicitudSeleccionChat->nombreUsuarioChatSeleccionado, returnIdUsuarioChatSeleccionado));
}

static bool usuario_selecciono_su_propio_chat (int idCliente, int idUsuarioChatSeleccionado)
{
    return (idCliente == idUsuarioChatSeleccionado);
}

static CodigoRetorno guardar_respuesta (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado, int idUsuarioChatSeleccionado)
{
    RespuestaSeleccionChat respuesta;

    respuesta.estado = estado;
    respuesta.idUsuarioChatSeleccionado = idUsuarioChatSeleccionado;

    if (servicios_guardar_respuesta (servicios, cliente, RESPUESTA_SELECCION_CHAT, &respuesta, sizeof (respuesta)) != EXITO)
    {
        cliente_marcar_desconectado (cliente);
        logs_escribir (LOG_ERROR, "seleccion chat", "Seleccion de chat fallido y cliente id=%d desconectado.", cliente_obtener_id (cliente));
        return ERROR_SIN_MEMORIA;
    }
    return EXITO;
}

static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado)
{
    if (guardar_respuesta (servicios, cliente, estado, ID_INVALIDO) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_AVISO, "seleccion chat", "Seleccion de chat rechazado.");
    return ERROR_OPERACION_INVALIDA;
}

static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente)
{
    if (guardar_respuesta (servicios, cliente, RESPUESTA_ERROR_SERVIDOR, ID_INVALIDO) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_ERROR, "seleccion chat", "Seleccion de chat fallido.");
    return ERROR_EJECUCION;
}


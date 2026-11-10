#include "servicios/envio_mensaje.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool es_envio_mensaje_invalido (const SolicitudEnvioMensaje *solicitudEnvioMensaje);
static ResultadoBd insertar_mensaje (Bd *bd, const SolicitudEnvioMensaje *solicitudEnvioMensaje);
static bool receptor_esta_conectado (RegistroClientes *registroClientes, int idReceptor, Cliente **returnReceptor);
static CodigoRetorno guardar_respuesta_emisor (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado);
static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado);
static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente);
static CodigoRetorno guardar_respuesta_receptor (Servicios *servicios, Cliente *cliente, const SolicitudEnvioMensaje *solicitudEnvioMensaje);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno envio_mensaje_procesar (Servicios *servicios, Cliente *cliente, const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    Cliente *receptor;

    if (es_envio_mensaje_invalido (solicitudEnvioMensaje))
        return rechazar (servicios, cliente, RESPUESTA_ERROR_OPERACION_INVALIDA);

    if (insertar_mensaje (servicios->bd, solicitudEnvioMensaje) != BD_EXITO)
        return fallar (servicios, cliente);

    if (guardar_respuesta_emisor (servicios, cliente, RESPUESTA_EXITO) != EXITO)
        return ERROR_SIN_MEMORIA;

    if (receptor_esta_conectado (servicios->registroClientes, solicitudEnvioMensaje->idReceptor, &receptor))
        guardar_respuesta_receptor (servicios, receptor, solicitudEnvioMensaje);

    logs_escribir (LOG_INFO, "envio mensaje", "Cliente id=%d envio un mensaje al cliente id=%d.", cliente_obtener_id (cliente), cliente_obtener_id (receptor));
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

static bool son_emisor_o_receptor_invalidos (const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    return ((solicitudEnvioMensaje->idEmisor == ID_NO_AUTENTICADO) || (solicitudEnvioMensaje->idReceptor == ID_NO_AUTENTICADO));
}

static bool emisor_es_receptor (const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    return (solicitudEnvioMensaje->idEmisor == solicitudEnvioMensaje->idReceptor);
}

static bool es_envio_mensaje_invalido (const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    return ((*(solicitudEnvioMensaje->texto) == '\0') || 
                (son_todos_espacios (solicitudEnvioMensaje->texto)) ||
                (son_emisor_o_receptor_invalidos (solicitudEnvioMensaje)) || 
                (emisor_es_receptor (solicitudEnvioMensaje)));
}

static ResultadoBd insertar_mensaje (Bd *bd, const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    ParametrosInsertarMensaje parametrosInsertarMensaje;

    parametrosInsertarMensaje.idEmisor = solicitudEnvioMensaje->idEmisor;
    parametrosInsertarMensaje.idReceptor = solicitudEnvioMensaje->idReceptor;
    strcpy (parametrosInsertarMensaje.texto, solicitudEnvioMensaje->texto);

    return bd_insertar_mensaje (bd, &parametrosInsertarMensaje);
}

static bool receptor_esta_conectado (RegistroClientes *registroClientes, int idReceptor, Cliente **returnReceptor)
{
    return registro_clientes_buscar_autenticado (registroClientes, idReceptor, returnReceptor);
}

static CodigoRetorno guardar_respuesta_emisor (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado)
{
    RespuestaEnvioMensaje respuesta;

    respuesta.estado = estado;

    if (servicios_guardar_respuesta (servicios, cliente, RESPUESTA_ENVIO_MENSAJE, &respuesta, sizeof (respuesta)) != EXITO)
    {
        cliente_marcar_desconectado (cliente);
        logs_escribir (LOG_ERROR, "envio mensaje", "Envio de mensaje fallido y cliente id=%d desconectado.", cliente_obtener_id (cliente));
        return ERROR_SIN_MEMORIA;
    }
    return EXITO;
}

static CodigoRetorno rechazar (Servicios *servicios, Cliente *cliente, EstadoRespuesta estado)
{
    if (guardar_respuesta_emisor (servicios, cliente, estado) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_AVISO, "envio mensaje", "Envio de mensaje rechazado.");
    return ERROR_OPERACION_INVALIDA;
}

static CodigoRetorno fallar (Servicios *servicios, Cliente *cliente)
{
    if (guardar_respuesta_emisor (servicios, cliente, RESPUESTA_ERROR_SERVIDOR) != EXITO)
        return ERROR_SIN_MEMORIA;
    logs_escribir (LOG_ERROR, "envio mensaje", "Envio de mensaje fallido.");
    return ERROR_EJECUCION;
}

static CodigoRetorno guardar_respuesta_receptor (Servicios *servicios, Cliente *cliente, const SolicitudEnvioMensaje *solicitudEnvioMensaje)
{
    RespuestaRecepcionMensaje respuesta;

    respuesta.idEmisor = solicitudEnvioMensaje->idEmisor;
    strcpy (respuesta.texto, solicitudEnvioMensaje->texto);

    if (servicios_guardar_respuesta (servicios, cliente, RESPUESTA_RECEPCION_MENSAJE, &respuesta, sizeof (respuesta)) != EXITO)
    {
        logs_escribir (LOG_ERROR, "envio mensaje", "Reenvio de mensaje fallido.");
        return ERROR_SIN_MEMORIA;
    }
    return EXITO;
}

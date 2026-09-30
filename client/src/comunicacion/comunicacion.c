#include "comunicacion/comunicacion.h"


/* ============================================================================================================================================
   FUNCIONES DE INFRAESTRUCTURA
   ============================================================================================================================================ */


void comunicacion_inicializar (ContextoAplicacion *contextoAplicacion)
{
    contextoAplicacion->sock = SOCKET_INVALIDO;
    contextoAplicacion->solicitudEnCurso = false;
}

static bool socketConectado;

EstadoSolicitud comunicacion_intentar_conectar_con_servidor (Socket *returnSock)
{
    if (*returnSock == SOCKET_INVALIDO)
    {
        if (socket_crear (returnSock) == ERROR_INICIALIZACION)
            return SOLICITUD_ERROR_CONEXION;
        socketConectado = false;
    }
    
    if (!socketConectado)
    {
        if (socket_conectar_cliente (returnSock) == EXITO)
        {
            socket_establecer_timeout (returnSock, 5000);
            socket_establecer_modo_no_bloqueante (returnSock);
            socketConectado = true;
        }
        else
        {
            socket_cerrar (returnSock);
            return SOLICITUD_ERROR_CONEXION;
        }
    }

    return SOLICITUD_EXITO;
}


/* ============================================================================================================================================
   FUNCIONES DE RECEPCION Y ENVIO DE SOLICITUDES
   ============================================================================================================================================ */


ResultadoRecepcion comunicacion_recibir_respuesta (Socket sock, char *bufferRespuesta)
{
    return (socket_recibir_todo (sock, bufferRespuesta));
}

void comunicacion_enviar_solicitud_autenticacion (ContextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia)
{
    SolicitudAutenticacion solicitudAutenticacion;

    solicitudAutenticacion.header.tipoPaquete = SOLICITUD_AUTENTICACION;
    solicitudAutenticacion.header.bytesTransmitidos = sizeof (SolicitudAutenticacion);

    strcpy (solicitudAutenticacion.nombreUsuario, nombreUsuario);
    strcpy (solicitudAutenticacion.contrasenia, contrasenia);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviar_todo (contextoAplicacion->sock, (char*)(&solicitudAutenticacion), sizeof (SolicitudAutenticacion)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%s|%s\n", solicitudAutenticacion.header.tipoPaquete, solicitudAutenticacion.nombreUsuario, solicitudAutenticacion.contrasenia);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

void comunicacion_enviar_solicitud_registro (ContextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    SolicitudRegistro solicitudRegistro;

    solicitudRegistro.header.tipoPaquete = SOLICITUD_REGISTRO;
    solicitudRegistro.header.bytesTransmitidos = sizeof (SolicitudRegistro);

    strcpy (solicitudRegistro.nombreUsuario, nombreUsuario);
    strcpy (solicitudRegistro.contrasenia, contrasenia);
    strcpy (solicitudRegistro.correoElectronico, correoElectronico);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviar_todo (contextoAplicacion->sock, (char*)(&solicitudRegistro), sizeof (SolicitudRegistro)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%s|%s|%s\n", solicitudRegistro.header.tipoPaquete, solicitudRegistro.nombreUsuario, solicitudRegistro.contrasenia, solicitudRegistro.correoElectronico);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

void comunicacion_enviar_solicitud_envio_mensaje (ContextoAplicacion *contextoAplicacion, int idUsuario, int idReceptor, const char* mensaje)
{
    SolicitudEnvioMensaje solicitudEnvioMensaje;

    solicitudEnvioMensaje.header.tipoPaquete = SOLICITUD_ENVIO_MENSAJE;
    solicitudEnvioMensaje.header.bytesTransmitidos = sizeof (SolicitudEnvioMensaje);

    solicitudEnvioMensaje.idEmisor = idUsuario;
    solicitudEnvioMensaje.idReceptor = idReceptor;
    strcpy (solicitudEnvioMensaje.texto, mensaje);
    
    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviar_todo (contextoAplicacion->sock, (char*)(&solicitudEnvioMensaje), sizeof (SolicitudEnvioMensaje)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%d|%d|%s\n", solicitudEnvioMensaje.header.tipoPaquete, solicitudEnvioMensaje.idEmisor, solicitudEnvioMensaje.idReceptor, solicitudEnvioMensaje.texto);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        puts ("\nYa hay una solicitud en curso.");
}

void comunicacion_enviar_solicitud_seleccion_chat (ContextoAplicacion *contextoAplicacion, const char *nombreUsuarioChatSeleccionado)
{
    SolicitudSeleccionChat solicitudSeleccionChat;

    solicitudSeleccionChat.header.tipoPaquete = SOLICITUD_SELECCION_CHAT;
    solicitudSeleccionChat.header.bytesTransmitidos = sizeof (SolicitudSeleccionChat);

    strcpy (solicitudSeleccionChat.nombreUsuarioChatSeleccionado, nombreUsuarioChatSeleccionado);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviar_todo (contextoAplicacion->sock, (char*)(&solicitudSeleccionChat), sizeof (SolicitudSeleccionChat)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%s\n", solicitudSeleccionChat.header.tipoPaquete, solicitudSeleccionChat.nombreUsuarioChatSeleccionado);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}


/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */


bool comunicacion_hay_solicitud_en_curso (const ContextoAplicacion *contextoAplicacion)
{
    return (contextoAplicacion->solicitudEnCurso);
}

void comunicacion_finalizar_solicitud_en_curso (ContextoAplicacion *contextoAplicacion)
{
    contextoAplicacion->solicitudEnCurso = false;
}

void comunicacion_finalizar (Socket *sock)
{
    socket_cerrar (sock);
}


/* ============================================================================================================================================
   FUNCIONES DE EXTRACCION DE DATOS
   ============================================================================================================================================ */


TipoRespuesta comunicacion_obtener_tipo_respuesta (const char *respuesta)
{
    Header header;

    memcpy (&header, respuesta, sizeof (Header));

    return header.tipoPaquete;
}


void comunicacion_extraer_respuesta_autenticacion (const char *respuesta, RespuestaAutenticacion *returnRespuestaAutenticacion)
{
    memcpy (returnRespuestaAutenticacion, respuesta, sizeof (RespuestaAutenticacion));
}

void comunicacion_extraer_respuesta_registro (const char *respuesta, RespuestaRegistro *returnRespuestaRegistro)
{
    memcpy (returnRespuestaRegistro, respuesta, sizeof (RespuestaRegistro));
}

void comunicacion_extraer_respuesta_seleccion_chat (const char *respuesta, RespuestaSeleccionChat *returnRespuestaSeleccionChat)
{
    memcpy (returnRespuestaSeleccionChat, respuesta, sizeof (RespuestaSeleccionChat));
}

void comunicacion_extraer_respuesta_envio_mensaje (const char *respuesta, RespuestaEnvioMensaje *returnRespuestaEnvioMensaje)
{
    memcpy (returnRespuestaEnvioMensaje, respuesta, sizeof (RespuestaEnvioMensaje));
}

void comunicacion_extraer_respuesta_recepcion_mensaje (const char *respuesta, RespuestaRecepcionMensaje *returnRespuestaRecepcionMensaje)
{
    memcpy (returnRespuestaRecepcionMensaje, respuesta, sizeof (RespuestaRecepcionMensaje));
}


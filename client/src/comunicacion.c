#include "../include/comunicacion.h"


bool recibioRespuesta (SOCKET sock, char *bufferRespuesta)
{
    int bytesRecibidos;

    bytesRecibidos = recv (sock, bufferRespuesta, MAX_BUFFER_RESPUESTA, 0);
    if (bytesRecibidos > 0)
    {
        bufferRespuesta += bytesRecibidos;
        *bufferRespuesta = '\0';

        bufferRespuesta -= bytesRecibidos; // Retroceder la cantidad de bytes avanzados para poder hacer el log.
        printf ("\nRespuesta recibida: %s\n", bufferRespuesta);
        return RECIBIO_RESPUESTA;
    }
    return NO_RECIBIO_RESPUESTA;
}

void enviarSolicitudYRecibirRespuesta (SOCKET sock, t_buffersComunicacion *buffersComunicacion)
{
    u_long modoSocket = 0; //Socket modo bloqueante
    int bytesRecibidos;

    ioctlsocket (sock, FIONBIO, &modoSocket);
    send (sock, buffersComunicacion->solicitud, strlen(buffersComunicacion->solicitud), 0);
    printf ("\nSolicitud enviada: %s\n", buffersComunicacion->solicitud);
    bytesRecibidos = recv (sock, buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, 0);
    buffersComunicacion->respuesta[bytesRecibidos] = '\0';
    printf ("Respuesta recibida: %s\n", buffersComunicacion->respuesta);
    modoSocket = 1; // Socket modo no bloqueante
    ioctlsocket (sock, FIONBIO, &modoSocket);
}

t_respuestaAutenticacion enviarSolicitudAutenticacion (SOCKET sock, const char *nombreUsuario, const char *contrasenia)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaAutenticacion respuestaAutenticacion;

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s", SOLICITUD_AUTENTICACION, nombreUsuario, contrasenia);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaAutenticacion.estado), &(respuestaAutenticacion.idUsuario));

    return respuestaAutenticacion;
}

t_respuestaRegistro enviarSolicitudRegistro (SOCKET sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaRegistro respuestaRegistro;

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s|%s", SOLICITUD_REGISTRO, nombreUsuario, contrasenia, correoElectronico);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaRegistro.estado), &(respuestaRegistro.idUsuario));

    return respuestaRegistro;
}

char enviarSolicitudEnvioMensaje (SOCKET sock, int idUsuario, int idReceptor, const char* mensaje)
{
    t_buffersComunicacion buffersComunicacion;
    char estadoSolicitud;

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%d|%d|%s", SOLICITUD_ENVIO_MENSAJE, idUsuario, idReceptor, mensaje);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c", &estadoSolicitud);

    return estadoSolicitud;
}

t_respuestaSeleccionChat enviarSolicitudSeleccionChat (SOCKET sock, const char *nombreUsuarioChatSeleccionado)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaSeleccionChat respuestaSeleccionChat;

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s", SOLICITUD_SELECCION_CHAT, nombreUsuarioChatSeleccionado);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaSeleccionChat.estado), &(respuestaSeleccionChat.idUsuarioChatSeleccionado));

    return respuestaSeleccionChat;
}

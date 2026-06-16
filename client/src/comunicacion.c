#include "../include/comunicacion.h"



bool recibirRespuesta (SOCKET sock, char *bufferRespuesta, unsigned int tamMaxBufferRespuesta)
{
    int bytesRecibidos;

    bytesRecibidos = recv (sock, bufferRespuesta, tamMaxBufferRespuesta, 0);
    if (bytesRecibidos > 0)
    {
        bufferRespuesta += bytesRecibidos;
        *bufferRespuesta = '\0';
        return RECIBIO_RESPUESTA;
    }

    return NO_RECIBIO_RESPUESTA;
}

void enviarSolicitudYRecibirRespuesta (SOCKET sock, const char *solicitud, char *respuesta)
{
    u_long modoSocket = 0; //Socket modo bloqueante
    int bytesRecibidos;

    ioctlsocket (sock, FIONBIO, &modoSocket);
    send (sock, solicitud, strlen(solicitud), 0);
    bytesRecibidos = recv (sock, respuesta, MAX_BUFFER_RESPUESTA, 0);
    respuesta += bytesRecibidos;
    *respuesta = '\0';
    modoSocket = 1; // Socket modo no bloqueante
    ioctlsocket (sock, FIONBIO, &modoSocket);
}

t_respuestaAutenticacion enviarSolicitudAutenticar (SOCKET sock, const char *nombreUsuario, const char *contrasenia)
{
    char solicitud [MAX_BUFFER_SOLICITUD];
    char respuesta [MAX_BUFFER_RESPUESTA];
    t_respuestaAutenticacion respuestaAutenticacion;

    snprintf (solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s", SOLICITUD_AUTENTICACION, nombreUsuario, contrasenia);
    enviarSolicitudYRecibirRespuesta (sock, solicitud, respuesta);
    sscanf (respuesta, "%c|%d", &(respuestaAutenticacion.estado), &(respuestaAutenticacion.idUsuario));

    return respuestaAutenticacion;
}

t_respuestaRegistro enviarSolicitudRegistrar (SOCKET sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    char solicitud [MAX_BUFFER_SOLICITUD];
    char respuesta [MAX_BUFFER_RESPUESTA];
    t_respuestaRegistro respuestaRegistro;

    snprintf (solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s|%s", SOLICITUD_REGISTRO, nombreUsuario, contrasenia, correoElectronico);
    enviarSolicitudYRecibirRespuesta (sock, solicitud, respuesta);
    sscanf (respuesta, "%c|%d", &(respuestaRegistro.estado), &(respuestaRegistro.idUsuario));

    return respuestaRegistro;
}

char enviarSolicitudMensaje (SOCKET sock, int idUsuario, int idReceptor, const char* mensaje)
{
    char solicitud [MAX_BUFFER_SOLICITUD];
    char respuesta [MAX_BUFFER_RESPUESTA];
    char estadoRespuesta;

    if ((idReceptor == ID_INVALIDO) || (idUsuario == idReceptor))
        return SOLICITUD_ERROR_OPERACION_INVALIDA;

    snprintf (solicitud, MAX_BUFFER_SOLICITUD, "%c|%d|%d|%s", SOLICITUD_MENSAJE, idUsuario, idReceptor, mensaje);
    enviarSolicitudYRecibirRespuesta (sock, solicitud, respuesta);
    sscanf (respuesta, "%c", &estadoRespuesta);

    return estadoRespuesta;
}

t_respuestaSeleccionContacto enviarSolicitudSeleccionarContacto (SOCKET sock, const char *nombreUsuario, const char *nombreContacto)
{
    char solicitud [MAX_BUFFER_SOLICITUD];
    char respuesta [MAX_BUFFER_RESPUESTA];
    t_respuestaSeleccionContacto respuestaSeleccionContacto;

    if (strcmp (nombreUsuario, nombreContacto) == 0)
    {
        respuestaSeleccionContacto.estado = SOLICITUD_ERROR_OPERACION_INVALIDA;
        respuestaSeleccionContacto.idUsuario = ID_INVALIDO;
        return respuestaSeleccionContacto;
    }

    snprintf (solicitud, MAX_BUFFER_SOLICITUD, "%c|%s", SOLICITUD_SELECCIONAR_CONTACTO, nombreContacto);
    enviarSolicitudYRecibirRespuesta (sock, solicitud, respuesta);
    sscanf (respuesta, "%c|%d", &(respuestaSeleccionContacto.estado), &(respuestaSeleccionContacto.idUsuario));

    return respuestaSeleccionContacto;
}


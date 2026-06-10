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

void enviarSolicitudYRecibirRespuesta (SOCKET sock, t_buffersComunicacion *buffersComunicacion)
{
    u_long modoSocket = 0; //Socket modo bloqueante
    int bytesRecibidos;

    ioctlsocket (sock, FIONBIO, &modoSocket);
    send (sock, buffersComunicacion->solicitud, strlen (buffersComunicacion->solicitud), 0);
    bytesRecibidos = recv (sock, buffersComunicacion->respuesta, MAX_BUFFER_RESPUESTA, 0);
    buffersComunicacion->respuesta[bytesRecibidos] = '\0';
    modoSocket = 1; // Socket modo no bloqueante
    ioctlsocket (sock, FIONBIO, &modoSocket);
}

t_respuestaAutenticacion enviarSolicitudAutenticar (SOCKET sock, const char *nombreUsuario, const char *contrasenia)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaAutenticacion respuestaAutenticacion;

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s", SOLICITUD_AUTENTICACION, nombreUsuario, contrasenia);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaAutenticacion.estado), &(respuestaAutenticacion.idUsuario));

    return respuestaAutenticacion;
}

t_respuestaRegistro enviarSolicitudRegistrar (SOCKET sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaRegistro respuestaRegistro;

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s|%s", SOLICITUD_REGISTRO, nombreUsuario, contrasenia, correoElectronico);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaRegistro.estado), &(respuestaRegistro.idUsuario));

    return respuestaRegistro;
}

char enviarSolicitudMensaje (SOCKET sock, int idUsuario, int idReceptor, const char* mensaje)
{
    t_buffersComunicacion buffersComunicacion;
    char estadoRespuesta;

    if ((idReceptor == ID_INVALIDO) || (idUsuario == idReceptor))
        return RESPUESTA_ERROR_OPERACION_INVALIDA; 

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%d|%d|%s", SOLICITUD_MENSAJE, idUsuario, idReceptor, mensaje);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c", &estadoRespuesta);

    return estadoRespuesta;
}

t_respuestaSeleccionContacto enviarSolicitudSeleccionarContacto (SOCKET sock, const char *nombreUsuario, const char *nombreContacto)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaSeleccionContacto respuestaSeleccionContacto;

    if (strcmp (nombreUsuario, nombreContacto) == 0)
    {
        respuestaSeleccionContacto.estado = RESPUESTA_ERROR_OPERACION_INVALIDA;
        respuestaSeleccionContacto.idUsuario = ID_INVALIDO;
        return respuestaSeleccionContacto;
    }

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s", SOLICITUD_SELECCIONAR_CONTACTO, nombreContacto);
    enviarSolicitudYRecibirRespuesta (sock, &buffersComunicacion);
    sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaSeleccionContacto.estado), &(respuestaSeleccionContacto.idUsuario));

    return respuestaSeleccionContacto;
}


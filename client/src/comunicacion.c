#include "../include/comunicacion.h"


static bool socketConectado;

t_estadoSolicitud intentarConectarConServidor (t_socket *returnSock)
{
    if (*returnSock == SOCKET_INVALIDO)
    {
        if (socket_crear (returnSock) == ERROR_INICIALIZACION)
            return SOLICITUD_ERROR_CONEXION;
        socketConectado = false;
    }
    
    if (!socketConectado)
    {
        if (socket_conectarCliente (returnSock) == EXITO)
            socketConectado = true;
        else
        {
            socket_cerrar (returnSock);
            return SOLICITUD_ERROR_CONEXION;
        }
    }

    socket_establecerTimeout (returnSock, 5000);

    return SOLICITUD_EXITO;
}

bool recibioRespuesta (t_socket sock, char *bufferRespuesta)
{
    int bytesRecibidos;

    bytesRecibidos = socket_recibir (sock, bufferRespuesta);
    if (bytesRecibidos > 0)
    {
        bufferRespuesta += bytesRecibidos;
        *bufferRespuesta = '\0';

        bufferRespuesta -= bytesRecibidos; // Retroceder la cantidad de bytes avanzados para poder hacer el log.
        printf ("\nRespuesta recibida: %s\n", bufferRespuesta);
        return true;
    }
    return false;
}

t_respuestaAutenticacion enviarSolicitudAutenticacion (t_socket sock, const char *nombreUsuario, const char *contrasenia)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaAutenticacion respuestaAutenticacion;
    int bytesRecibidos;

    socket_establecerModoBloqueante (&sock);

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s", SOLICITUD_AUTENTICACION, nombreUsuario, contrasenia);
    socket_enviar (sock, buffersComunicacion.solicitud);
    printf ("\nSolicitud enviada: %s\n", buffersComunicacion.solicitud);

    bytesRecibidos = socket_recibir (sock, buffersComunicacion.respuesta);
    if (socket_perdioConexion (sock, bytesRecibidos))
    {
        respuestaAutenticacion.estado = SOLICITUD_ERROR_CONEXION;
        respuestaAutenticacion.idUsuario = ID_INVALIDO;
        puts ("Se perdio la conexion con el servidor.");
    }
    else
    {
        buffersComunicacion.respuesta[bytesRecibidos] = '\0';
        sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaAutenticacion.estado), &(respuestaAutenticacion.idUsuario));
        printf ("Respuesta recibida: %s\n", buffersComunicacion.respuesta);
    }

    socket_establecerModoNoBloqueante (&sock);

    return respuestaAutenticacion;
}

t_respuestaRegistro enviarSolicitudRegistro (t_socket sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaRegistro respuestaRegistro;
    int bytesRecibidos;
    
    socket_establecerModoBloqueante (&sock);

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s|%s|%s", SOLICITUD_REGISTRO, nombreUsuario, contrasenia, correoElectronico);
    socket_enviar (sock, buffersComunicacion.solicitud);
    printf ("\nSolicitud enviada: %s\n", buffersComunicacion.solicitud);

    bytesRecibidos = socket_recibir (sock, buffersComunicacion.respuesta);
    if (socket_perdioConexion (sock, bytesRecibidos))
    {
        respuestaRegistro.estado = SOLICITUD_ERROR_CONEXION;
        respuestaRegistro.idUsuario = ID_INVALIDO;
        puts ("Se perdio la conexion con el servidor.\n");
    }
    else
    {
        buffersComunicacion.respuesta[bytesRecibidos] = '\0';
        sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaRegistro.estado), &(respuestaRegistro.idUsuario));
        printf ("Respuesta recibida: %s\n", buffersComunicacion.respuesta);
    }

    socket_establecerModoNoBloqueante (&sock);

    return respuestaRegistro;
}

char enviarSolicitudEnvioMensaje (t_socket sock, int idUsuario, int idReceptor, const char* mensaje)
{
    t_buffersComunicacion buffersComunicacion;
    char estadoSolicitud;
    int bytesRecibidos;
    
    socket_establecerModoBloqueante (&sock);

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%d|%d|%s", SOLICITUD_ENVIO_MENSAJE, idUsuario, idReceptor, mensaje);
    socket_enviar (sock, buffersComunicacion.solicitud);
    printf ("\nSolicitud enviada: %s\n", buffersComunicacion.solicitud);

    bytesRecibidos = socket_recibir (sock, buffersComunicacion.respuesta);
    if (socket_perdioConexion (sock, bytesRecibidos))
    {
        estadoSolicitud = SOLICITUD_ERROR_CONEXION;
        puts ("Se perdio la conexion con el servidor.");
    }
    else
    {
        buffersComunicacion.respuesta[bytesRecibidos] = '\0';
        sscanf (buffersComunicacion.respuesta, "%c", &estadoSolicitud);
        printf ("Respuesta recibida: %s\n", buffersComunicacion.respuesta);
    }

    socket_establecerModoNoBloqueante (&sock);

    return estadoSolicitud;
}

t_respuestaSeleccionChat enviarSolicitudSeleccionChat (t_socket sock, const char *nombreUsuarioChatSeleccionado)
{
    t_buffersComunicacion buffersComunicacion;
    t_respuestaSeleccionChat respuestaSeleccionChat;
    int bytesRecibidos;
    
    socket_establecerModoBloqueante (&sock);

    snprintf (buffersComunicacion.solicitud, MAX_BUFFER_SOLICITUD, "%c|%s", SOLICITUD_SELECCION_CHAT, nombreUsuarioChatSeleccionado);
    socket_enviar (sock, buffersComunicacion.solicitud);
    printf ("\nSolicitud enviada: %s\n", buffersComunicacion.solicitud);

    bytesRecibidos = socket_recibir (sock, buffersComunicacion.respuesta);
    if (socket_perdioConexion (sock, bytesRecibidos))
    {
        respuestaSeleccionChat.estado = SOLICITUD_ERROR_CONEXION;
        respuestaSeleccionChat.idUsuarioChatSeleccionado = ID_INVALIDO;
        puts ("Se perdio la conexion con el servidor.");
    }
    else
    {
        buffersComunicacion.respuesta[bytesRecibidos] = '\0';
        sscanf (buffersComunicacion.respuesta, "%c|%d", &(respuestaSeleccionChat.estado), &(respuestaSeleccionChat.idUsuarioChatSeleccionado));
        printf ("Respuesta recibida: %s\n", buffersComunicacion.respuesta);
    }

    socket_establecerModoNoBloqueante (&sock);

    return respuestaSeleccionChat;
}

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
        return true;
    }
    return false;
}

t_respuestaAutenticacion enviarSolicitudAutenticacion (t_socket sock, const char *nombreUsuario, const char *contrasenia)
{
    t_datosEnvioSolicitudAutenticacion datosEnvioSolicitudAutenticacion;
    t_datosRespuestaSolicitudAutenticacion datosRespuestaSolicitudAutenticacion;
    t_buffersComunicacion buffersComunicacion;
    int bytesRecibidos;
    t_respuestaAutenticacion respuestaAutenticacion;

    socket_establecerModoBloqueante (&sock);

    datosEnvioSolicitudAutenticacion.headerTipoSolicitud = SOLICITUD_AUTENTICACION;
    strcpy (datosEnvioSolicitudAutenticacion.nombreUsuario, nombreUsuario);
    strcpy (datosEnvioSolicitudAutenticacion.contrasenia, contrasenia);

    socket_enviar (sock, (char*)(&datosEnvioSolicitudAutenticacion), sizeof (t_datosEnvioSolicitudAutenticacion));
    printf ("\nSolicitud enviada: %c|%s|%s\n", datosEnvioSolicitudAutenticacion.headerTipoSolicitud, datosEnvioSolicitudAutenticacion.nombreUsuario, datosEnvioSolicitudAutenticacion.contrasenia);

    bytesRecibidos = socket_recibir (sock, buffersComunicacion.respuesta);
    if (socket_perdioConexion (sock, bytesRecibidos))
    {
        datosRespuestaSolicitudAutenticacion.estadoSolicitud = SOLICITUD_ERROR_CONEXION;
        datosRespuestaSolicitudAutenticacion.idUsuario = ID_INVALIDO;
        puts ("Se perdio la conexion con el servidor.");
    }
    else
    {
        buffersComunicacion.respuesta[bytesRecibidos] = '\0';
        memcpy (&datosRespuestaSolicitudAutenticacion, buffersComunicacion.respuesta, sizeof (t_datosRespuestaSolicitudAutenticacion));
        printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudAutenticacion.headerTipoRespuesta, datosRespuestaSolicitudAutenticacion.estadoSolicitud, datosRespuestaSolicitudAutenticacion.idUsuario);
        
        respuestaAutenticacion.estado = datosRespuestaSolicitudAutenticacion.estadoSolicitud;
        respuestaAutenticacion.idUsuario = datosRespuestaSolicitudAutenticacion.idUsuario;
    }

    socket_establecerModoNoBloqueante (&sock);

    return respuestaAutenticacion;
}

t_respuestaRegistro enviarSolicitudRegistro (t_socket sock, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    t_datosEnvioSolicitudRegistro datosEnvioSolicitudRegistro;
    t_datosRespuestaSolicitudRegistro datosRespuestaSolicitudRegistro;
    t_respuestaRegistro respuestaRegistro;
    t_buffersComunicacion buffersComunicacion;
    int bytesRecibidos;
    
    socket_establecerModoBloqueante (&sock);

    datosEnvioSolicitudRegistro.headerTipoSolicitud = SOLICITUD_REGISTRO;
    strcpy (datosEnvioSolicitudRegistro.nombreUsuario, nombreUsuario);
    strcpy (datosEnvioSolicitudRegistro.contrasenia, contrasenia);
    strcpy (datosEnvioSolicitudRegistro.correoElectronico, correoElectronico);

    socket_enviar (sock, (char*)(&datosEnvioSolicitudRegistro), sizeof (t_datosEnvioSolicitudRegistro));
    printf ("\nSolicitud enviada: %c|%s|%s|%s\n", datosEnvioSolicitudRegistro.headerTipoSolicitud, datosEnvioSolicitudRegistro.nombreUsuario, datosEnvioSolicitudRegistro.contrasenia, datosEnvioSolicitudRegistro.correoElectronico);

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
        memcpy (&datosRespuestaSolicitudRegistro, buffersComunicacion.respuesta, sizeof (t_datosRespuestaSolicitudRegistro));
        printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudRegistro.headerTipoRespuesta, datosRespuestaSolicitudRegistro.estadoSolicitud, datosRespuestaSolicitudRegistro.idUsuario);

        respuestaRegistro.estado = datosRespuestaSolicitudRegistro.estadoSolicitud;
        respuestaRegistro.idUsuario = datosRespuestaSolicitudRegistro.idUsuario;
    }

    socket_establecerModoNoBloqueante (&sock);


    return respuestaRegistro;
}

char enviarSolicitudEnvioMensaje (t_socket sock, int idUsuario, int idReceptor, const char* mensaje)
{
    t_datosEnvioSolicitudEnvioMensaje datosEnvioSolicitudEnvioMensaje;
    t_datosRespuestaSolicitudEnvioMensaje datosRespuestaSolicitudEnvioMensaje;
    t_buffersComunicacion buffersComunicacion;
    int bytesRecibidos;
    
    socket_establecerModoBloqueante (&sock);

    datosEnvioSolicitudEnvioMensaje.headerTipoSolicitud = SOLICITUD_ENVIO_MENSAJE;
    datosEnvioSolicitudEnvioMensaje.idEmisor = idUsuario;
    datosEnvioSolicitudEnvioMensaje.idReceptor = idReceptor;
    strcpy (datosEnvioSolicitudEnvioMensaje.texto, mensaje);
    
    socket_enviar (sock, (char*)(&datosEnvioSolicitudEnvioMensaje), sizeof (t_datosEnvioSolicitudEnvioMensaje));
    printf ("\nSolicitud enviada: %c|%d|%d|%s\n", datosEnvioSolicitudEnvioMensaje.headerTipoSolicitud, datosEnvioSolicitudEnvioMensaje.idEmisor, datosEnvioSolicitudEnvioMensaje.idReceptor, datosEnvioSolicitudEnvioMensaje.texto);

    bytesRecibidos = socket_recibir (sock, buffersComunicacion.respuesta);
    if (socket_perdioConexion (sock, bytesRecibidos))
    {
        datosRespuestaSolicitudEnvioMensaje.estadoSolicitud = SOLICITUD_ERROR_CONEXION;
        puts ("Se perdio la conexion con el servidor.");
    }
    else
    {
        buffersComunicacion.respuesta[bytesRecibidos] = '\0';
        memcpy (&datosRespuestaSolicitudEnvioMensaje, buffersComunicacion.respuesta, sizeof (t_datosRespuestaSolicitudEnvioMensaje));
        printf ("Respuesta recibida: %c|%c\n", datosRespuestaSolicitudEnvioMensaje.headerTipoRespuesta, datosRespuestaSolicitudEnvioMensaje.estadoSolicitud);
    }

    socket_establecerModoNoBloqueante (&sock);

    return datosRespuestaSolicitudEnvioMensaje.estadoSolicitud;
}

t_respuestaSeleccionChat enviarSolicitudSeleccionChat (t_socket sock, const char *nombreUsuarioChatSeleccionado)
{
    t_datosEnvioSolicitudSeleccionChat datosEnvioSolicitudSeleccionChat;
    t_datosRespuestaSolicitudSeleccionChat datosRespuestaSolicitudSeleccionChat;
    t_respuestaSeleccionChat respuestaSeleccionChat;
    t_buffersComunicacion buffersComunicacion;
    int bytesRecibidos;
    
    socket_establecerModoBloqueante (&sock);

    datosEnvioSolicitudSeleccionChat.headerTipoSolicitud = SOLICITUD_SELECCION_CHAT;
    strcpy (datosEnvioSolicitudSeleccionChat.nombreUsuarioChatSeleccionado, nombreUsuarioChatSeleccionado);

    socket_enviar (sock, (char*)(&datosEnvioSolicitudSeleccionChat), sizeof (t_datosEnvioSolicitudSeleccionChat));
    printf ("\nSolicitud enviada: %c|%s\n", datosEnvioSolicitudSeleccionChat.headerTipoSolicitud, datosEnvioSolicitudSeleccionChat.nombreUsuarioChatSeleccionado);

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
        memcpy (&datosRespuestaSolicitudSeleccionChat, buffersComunicacion.respuesta, sizeof (t_datosRespuestaSolicitudSeleccionChat));
        printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudSeleccionChat.headerTipoRespuesta, datosRespuestaSolicitudSeleccionChat.estadoSolicitud, datosRespuestaSolicitudSeleccionChat.idUsuarioDelChatSeleccionado);
        
        respuestaSeleccionChat.estado = datosRespuestaSolicitudSeleccionChat.estadoSolicitud;
        respuestaSeleccionChat.idUsuarioChatSeleccionado = datosRespuestaSolicitudSeleccionChat.idUsuarioDelChatSeleccionado;
    }

    socket_establecerModoNoBloqueante (&sock);

    return respuestaSeleccionChat;
}

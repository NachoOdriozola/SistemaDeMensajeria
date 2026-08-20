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
    socket_establecerModoNoBloqueante (returnSock);

    return SOLICITUD_EXITO;
}

t_resultadoRecepcion recibirRespuesta (t_socket sock, char *bufferRespuesta)
{
    int bytesRecibidos;

    bytesRecibidos = socket_recibir (sock, bufferRespuesta);

    if (socket_noRecibioDatos (sock, bytesRecibidos))
        return RECEPCION_NO_RECIBIO_DATOS;

    if (socket_perdioConexion (sock, bytesRecibidos))
        return RECEPCION_ERROR_CONEXION;

    bufferRespuesta += bytesRecibidos;
    *bufferRespuesta = '\0';
    
    return RECEPCION_RECIBIO_DATOS;
}

void enviarSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia)
{
    t_datosEnvioSolicitudAutenticacion datosEnvioSolicitudAutenticacion;

    datosEnvioSolicitudAutenticacion.headerTipoSolicitud = SOLICITUD_AUTENTICACION;
    strcpy (datosEnvioSolicitudAutenticacion.nombreUsuario, nombreUsuario);
    strcpy (datosEnvioSolicitudAutenticacion.contrasenia, contrasenia);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        socket_enviar (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudAutenticacion), sizeof (t_datosEnvioSolicitudAutenticacion));
        printf ("\nSolicitud enviada: %c|%s|%s\n", datosEnvioSolicitudAutenticacion.headerTipoSolicitud, datosEnvioSolicitudAutenticacion.nombreUsuario, datosEnvioSolicitudAutenticacion.contrasenia);
        contextoAplicacion->solicitudEnCurso = true;
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

void enviarSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    t_datosEnvioSolicitudRegistro datosEnvioSolicitudRegistro;

    datosEnvioSolicitudRegistro.headerTipoSolicitud = SOLICITUD_REGISTRO;
    strcpy (datosEnvioSolicitudRegistro.nombreUsuario, nombreUsuario);
    strcpy (datosEnvioSolicitudRegistro.contrasenia, contrasenia);
    strcpy (datosEnvioSolicitudRegistro.correoElectronico, correoElectronico);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        socket_enviar (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudRegistro), sizeof (t_datosEnvioSolicitudRegistro));
        printf ("\nSolicitud enviada: %c|%s|%s|%s\n", datosEnvioSolicitudRegistro.headerTipoSolicitud, datosEnvioSolicitudRegistro.nombreUsuario, datosEnvioSolicitudRegistro.contrasenia, datosEnvioSolicitudRegistro.correoElectronico);
        contextoAplicacion->solicitudEnCurso = true;
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

void enviarSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, int idUsuario, int idReceptor, const char* mensaje)
{
    t_datosEnvioSolicitudEnvioMensaje datosEnvioSolicitudEnvioMensaje;

    datosEnvioSolicitudEnvioMensaje.headerTipoSolicitud = SOLICITUD_ENVIO_MENSAJE;
    datosEnvioSolicitudEnvioMensaje.idEmisor = idUsuario;
    datosEnvioSolicitudEnvioMensaje.idReceptor = idReceptor;
    strcpy (datosEnvioSolicitudEnvioMensaje.texto, mensaje);
    
    if (!(contextoAplicacion->solicitudEnCurso))
    {
        socket_enviar (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudEnvioMensaje), sizeof (t_datosEnvioSolicitudEnvioMensaje));
        printf ("\nSolicitud enviada: %c|%d|%d|%s\n", datosEnvioSolicitudEnvioMensaje.headerTipoSolicitud, datosEnvioSolicitudEnvioMensaje.idEmisor, datosEnvioSolicitudEnvioMensaje.idReceptor, datosEnvioSolicitudEnvioMensaje.texto);
        contextoAplicacion->solicitudEnCurso = true;
    }
    else
        puts ("\nYa hay una solicitud en curso.");
}

void enviarSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuarioChatSeleccionado)
{
    t_datosEnvioSolicitudSeleccionChat datosEnvioSolicitudSeleccionChat;

    datosEnvioSolicitudSeleccionChat.headerTipoSolicitud = SOLICITUD_SELECCION_CHAT;
    strcpy (datosEnvioSolicitudSeleccionChat.nombreUsuarioChatSeleccionado, nombreUsuarioChatSeleccionado);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        socket_enviar (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudSeleccionChat), sizeof (t_datosEnvioSolicitudSeleccionChat));
        printf ("\nSolicitud enviada: %c|%s\n", datosEnvioSolicitudSeleccionChat.headerTipoSolicitud, datosEnvioSolicitudSeleccionChat.nombreUsuarioChatSeleccionado);
        contextoAplicacion->solicitudEnCurso = true;
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

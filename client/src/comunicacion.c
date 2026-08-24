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
    return (socket_recibirTodo (sock, bufferRespuesta));
}

void enviarSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia)
{
    t_datosEnvioSolicitudAutenticacion datosEnvioSolicitudAutenticacion;

    datosEnvioSolicitudAutenticacion.header.tipo = SOLICITUD_AUTENTICACION;
    datosEnvioSolicitudAutenticacion.header.bytesTransmitidos = sizeof (t_datosEnvioSolicitudAutenticacion);

    strcpy (datosEnvioSolicitudAutenticacion.nombreUsuario, nombreUsuario);
    strcpy (datosEnvioSolicitudAutenticacion.contrasenia, contrasenia);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviarTodo (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudAutenticacion), sizeof (t_datosEnvioSolicitudAutenticacion)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%s|%s\n", datosEnvioSolicitudAutenticacion.header.tipo, datosEnvioSolicitudAutenticacion.nombreUsuario, datosEnvioSolicitudAutenticacion.contrasenia);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

void enviarSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuario, const char *contrasenia, const char *correoElectronico)
{
    t_datosEnvioSolicitudRegistro datosEnvioSolicitudRegistro;

    datosEnvioSolicitudRegistro.header.tipo = SOLICITUD_REGISTRO;
    datosEnvioSolicitudRegistro.header.bytesTransmitidos = sizeof (t_datosEnvioSolicitudRegistro);

    strcpy (datosEnvioSolicitudRegistro.nombreUsuario, nombreUsuario);
    strcpy (datosEnvioSolicitudRegistro.contrasenia, contrasenia);
    strcpy (datosEnvioSolicitudRegistro.correoElectronico, correoElectronico);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviarTodo (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudRegistro), sizeof (t_datosEnvioSolicitudRegistro)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%s|%s|%s\n", datosEnvioSolicitudRegistro.header.tipo, datosEnvioSolicitudRegistro.nombreUsuario, datosEnvioSolicitudRegistro.contrasenia, datosEnvioSolicitudRegistro.correoElectronico);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

void enviarSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, int idUsuario, int idReceptor, const char* mensaje)
{
    t_datosEnvioSolicitudEnvioMensaje datosEnvioSolicitudEnvioMensaje;

    datosEnvioSolicitudEnvioMensaje.header.tipo = SOLICITUD_ENVIO_MENSAJE;
    datosEnvioSolicitudEnvioMensaje.header.bytesTransmitidos = sizeof (t_datosEnvioSolicitudEnvioMensaje);

    datosEnvioSolicitudEnvioMensaje.idEmisor = idUsuario;
    datosEnvioSolicitudEnvioMensaje.idReceptor = idReceptor;
    strcpy (datosEnvioSolicitudEnvioMensaje.texto, mensaje);
    
    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviarTodo (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudEnvioMensaje), sizeof (t_datosEnvioSolicitudEnvioMensaje)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%d|%d|%s\n", datosEnvioSolicitudEnvioMensaje.header.tipo, datosEnvioSolicitudEnvioMensaje.idEmisor, datosEnvioSolicitudEnvioMensaje.idReceptor, datosEnvioSolicitudEnvioMensaje.texto);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        puts ("\nYa hay una solicitud en curso.");
}

void enviarSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, const char *nombreUsuarioChatSeleccionado)
{
    t_datosEnvioSolicitudSeleccionChat datosEnvioSolicitudSeleccionChat;

    datosEnvioSolicitudSeleccionChat.header.tipo = SOLICITUD_SELECCION_CHAT;
    datosEnvioSolicitudSeleccionChat.header.bytesTransmitidos = sizeof (t_datosEnvioSolicitudSeleccionChat);

    strcpy (datosEnvioSolicitudSeleccionChat.nombreUsuarioChatSeleccionado, nombreUsuarioChatSeleccionado);

    if (!(contextoAplicacion->solicitudEnCurso))
    {
        if (socket_enviarTodo (contextoAplicacion->sock, (char*)(&datosEnvioSolicitudSeleccionChat), sizeof (t_datosEnvioSolicitudSeleccionChat)) == ENVIO_COMPLETO)
        {
            printf ("\nSolicitud enviada: %c|%s\n", datosEnvioSolicitudSeleccionChat.header.tipo, datosEnvioSolicitudSeleccionChat.nombreUsuarioChatSeleccionado);
            contextoAplicacion->solicitudEnCurso = true;
        }
    }
    else
        printf ("\nYa hay una solicitud en curso.\n");
}

#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos_actualizaciones.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuestaSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);
static void procesarRespuestaSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);
static void procesarRespuestaRecepcionMensaje (t_interfazContactos *interfazContactos, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazContactos_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta, t_resultadoRecepcion resultadoRecepcion)
{
    t_header header;
    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazContactos_manejarErrorConexion (contextoAplicacion, interfazContactos);
        puts ("\nSe perdio la conexion con el servidor.");
        return;
    }

    memcpy (&header, respuesta, sizeof (t_header));
    switch (header.tipo)
    {
        case RESPUESTA_SOLICITUD_ENVIO_MENSAJE:
            procesarRespuestaSolicitudEnvioMensaje (contextoAplicacion, interfazContactos, respuesta);
            break;

        case RESPUESTA_SOLICITUD_SELECCION_CHAT:
            procesarRespuestaSolicitudSeleccionChat (contextoAplicacion, interfazContactos, respuesta);
            break;

        case RESPUESTA_RECEPCION_MENSAJE:
            procesarRespuestaRecepcionMensaje (interfazContactos, respuesta);
            break;

        default:
            break;
    }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/* ============================================================================================================================================
   FUNCIONES RESPUESTA SOLICITUD ENVIO MENSAJE
   ============================================================================================================================================ */


static void extraerDatosRespuestaSolicitudEnvioMensaje (const char *respuesta, t_datosRespuestaSolicitudEnvioMensaje *returnDatosRespuestaSolicitudEnvioMensaje)
{
    memcpy (returnDatosRespuestaSolicitudEnvioMensaje, respuesta, sizeof (t_datosRespuestaSolicitudEnvioMensaje));
}

static void procesarRespuestaSegunEstadoSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, t_datosRespuestaSolicitudEnvioMensaje *datosRespuestaSolicitudEnvioMensaje)
{
    switch (datosRespuestaSolicitudEnvioMensaje->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            interfazContactos_insertarMensajeAListaMensajes (&(interfazContactos->logica.contextoMensajes), interfazContactos->logica.contextoMensajes.mensaje, MENSAJE_PROPIO, &(interfazContactos->fuentes));
            _interfazContactos_resetearBarraDeEscritura (interfazContactos);
            sfText_setString (interfazContactos->textos.feedbackUsuario, "");
            break;

        default:
            break;
    }
}

/*
 * Recibe los datos de la respuesta con la estructura de datos t_datosRespuestaSolicitudEnvioMensaje.
*/
static void procesarRespuestaSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRespuestaSolicitudEnvioMensaje datosRespuestaSolicitudEnvioMensaje;

    extraerDatosRespuestaSolicitudEnvioMensaje (respuesta, &datosRespuestaSolicitudEnvioMensaje);
    printf ("Respuesta recibida: %c|%c\n", datosRespuestaSolicitudEnvioMensaje.header.tipo, datosRespuestaSolicitudEnvioMensaje.estadoSolicitud);
    procesarRespuestaSegunEstadoSolicitudEnvioMensaje (contextoAplicacion, interfazContactos, &datosRespuestaSolicitudEnvioMensaje);
    contextoAplicacion->solicitudEnCurso = false;
}


/* ============================================================================================================================================
   FUNCIONES RESPUESTA SOLICITUD SELECCION CHAT
   ============================================================================================================================================ */


static void extraerDatosRespuestaSolicitudSeleccionChat (const char *respuesta, t_datosRespuestaSolicitudSeleccionChat *returnDatosRespuestaSolicitudSeleccionChat)
{
    memcpy (returnDatosRespuestaSolicitudSeleccionChat, respuesta, sizeof (t_datosRespuestaSolicitudSeleccionChat));
}

static void setearNuevoChatLogicamente (t_interfazContactos *interfazContactos, const t_datosRespuestaSolicitudSeleccionChat *datosRespuestaSolicitudSeleccionChat)
{
    interfazContactos->logica.idUsuarioDelChatSeleccionado = datosRespuestaSolicitudSeleccionChat->idUsuarioDelChatSeleccionado;
    strcpy (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, &(interfazContactos->logica.contextoMensajes.mensaje[1]));
}

static void setearNuevoChatGraficamente (t_interfazContactos *interfazContactos)
{
    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, interfazContactos->logica.nombreUsuarioDelChatSeleccionado);
    centrarTextoEnArea (interfazContactos->textos.auxContactoSeleccionado, 852, 25, 600, 40);
    interfazContactos_vaciarListaMensajes (&(interfazContactos->logica.contextoMensajes));
    sfText_setString (interfazContactos->textos.informacionSeleccionChat, "");
}

static void procesarRespuestaSegunEstadoSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, t_datosRespuestaSolicitudSeleccionChat *datosRespuestaSolicitudSeleccionChat)
{
    switch (datosRespuestaSolicitudSeleccionChat->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            setearNuevoChatLogicamente (interfazContactos, datosRespuestaSolicitudSeleccionChat);
            setearNuevoChatGraficamente (interfazContactos);
            _interfazContactos_resetearBarraDeEscritura (interfazContactos);
            sfText_setString (interfazContactos->textos.feedbackUsuario, "");
            break;

        default:
            break;
    }
}

/*
 * Recibe los datos de la respuesta con la estructura de datos t_datosRespuestaSolicitudSeleccionChat.
*/
static void procesarRespuestaSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRespuestaSolicitudSeleccionChat datosRespuestaSolicitudSeleccionChat;

    extraerDatosRespuestaSolicitudSeleccionChat (respuesta, &datosRespuestaSolicitudSeleccionChat);
    printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudSeleccionChat.header.tipo, datosRespuestaSolicitudSeleccionChat.estadoSolicitud, datosRespuestaSolicitudSeleccionChat.idUsuarioDelChatSeleccionado);
    procesarRespuestaSegunEstadoSolicitudSeleccionChat (contextoAplicacion, interfazContactos, &datosRespuestaSolicitudSeleccionChat);
    contextoAplicacion->solicitudEnCurso = false;
}


/* ============================================================================================================================================
   FUNCIONES RESPUESTA RECEPCION MENSAJE
   ============================================================================================================================================ */


static void extraerDatosRespuestaRecepcionMensaje (const char *respuesta, t_datosRespuestaRecepcionMensaje *returnDatosRespuestaRecepcionMensaje)
{
    memcpy (returnDatosRespuestaRecepcionMensaje, respuesta, sizeof (t_datosRespuestaRecepcionMensaje));
}

static bool elUsuarioDelChatSeleccionadoEsElEmisor (int idUsuarioEmisor, int idUsuarioDelChatSeleccionado)
{
    return (idUsuarioEmisor == idUsuarioDelChatSeleccionado);
}

static void procesarRespuestaSegunEstadoRecepcionMensaje (t_interfazContactos *interfazContactos, t_datosRespuestaRecepcionMensaje *datosRespuestaRecepcionMensaje)
{
    if (elUsuarioDelChatSeleccionadoEsElEmisor (datosRespuestaRecepcionMensaje->idEmisor, interfazContactos->logica.idUsuarioDelChatSeleccionado))
        interfazContactos_insertarMensajeAListaMensajes (&(interfazContactos->logica.contextoMensajes), datosRespuestaRecepcionMensaje->texto, MENSAJE_REMOTO, &(interfazContactos->fuentes));
}

/*
 * Recibe los datos de la respuesta con la estructura de datos t_datosRespuestaRecepcionMensaje.
*/
static void procesarRespuestaRecepcionMensaje (t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRespuestaRecepcionMensaje datosRespuestaRecepcionMensaje;

    extraerDatosRespuestaRecepcionMensaje (respuesta, &datosRespuestaRecepcionMensaje);
    printf ("\nRespuesta recibida: %c|%d|%s\n", datosRespuestaRecepcionMensaje.header.tipo, datosRespuestaRecepcionMensaje.idEmisor, datosRespuestaRecepcionMensaje.texto);
    procesarRespuestaSegunEstadoRecepcionMensaje (interfazContactos, &datosRespuestaRecepcionMensaje);
}


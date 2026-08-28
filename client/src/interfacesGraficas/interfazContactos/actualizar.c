#include "interfacesGraficas/interfazContactos/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);

static void procesarRespuestaSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);
static void procesarRespuestaSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);
static void procesarRespuestaRecepcionMensaje (t_interfazContactos *interfazContactos, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazContactos_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    // --------------- RECIBIR Y PROCESAR RESPUESTAS DEL SERVIDOR ---------------

    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    t_resultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = recibirRespuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
        procesarRespuesta (contextoAplicacion, interfazContactos, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazContactos_manejarErrorConexion (contextoAplicacion, interfazContactos);
        puts ("\nSe perdio la conexion con el servidor.");
    }

    // --------------- PUNTO DE INSERCION ---------------

    if (interfazContactos->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(interfazContactos->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazContactos->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazContactos->logica.puntoInsercion));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_header header;

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

static void resetearBarraDeEscritura (t_interfazContactos *interfazContactos)
{
    *(interfazContactos->logica.contextoMensajes.mensaje) = '\0';
    sfText_setString (interfazContactos->textos.auxEscribirMensaje, "");
    sfRectangleShape_setPosition (interfazContactos->elementos.puntoInsercion, (sfVector2f){451, 942});
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD ENVIO MENSAJE
   ============================================================================================================================================ */


static void extraerDatosRespuestaSolicitudEnvioMensaje (const char *respuesta, t_datosRespuestaSolicitudEnvioMensaje *returnDatosRespuestaSolicitudEnvioMensaje)
{
    memcpy (returnDatosRespuestaSolicitudEnvioMensaje, respuesta, sizeof (t_datosRespuestaSolicitudEnvioMensaje));
}

static void procesarRespuestaSegunEstadoSolicitudEnvioMensaje (t_interfazContactos *interfazContactos, const t_datosRespuestaSolicitudEnvioMensaje *datosRespuestaSolicitudEnvioMensaje)
{
    switch (datosRespuestaSolicitudEnvioMensaje->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            _interfazContactos_listaMensajes_insertarMensaje (&(interfazContactos->logica.contextoMensajes), interfazContactos->logica.contextoMensajes.mensaje, MENSAJE_PROPIO, &(interfazContactos->fuentes));
            resetearBarraDeEscritura (interfazContactos);
            sfText_setString (interfazContactos->textos.feedbackUsuario, "");
            break;

        default:
            break;
    }
}

static void procesarRespuestaSolicitudEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRespuestaSolicitudEnvioMensaje datosRespuestaSolicitudEnvioMensaje;

    extraerDatosRespuestaSolicitudEnvioMensaje (respuesta, &datosRespuestaSolicitudEnvioMensaje);
    printf ("Respuesta recibida: %c|%c\n", datosRespuestaSolicitudEnvioMensaje.header.tipo, datosRespuestaSolicitudEnvioMensaje.estadoSolicitud);
    procesarRespuestaSegunEstadoSolicitudEnvioMensaje (interfazContactos, &datosRespuestaSolicitudEnvioMensaje);
    contextoAplicacion->solicitudEnCurso = false;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD SELECCION CHAT
   ============================================================================================================================================ */


static void extraerDatosRespuestaSolicitudSeleccionChat (const char *respuesta, t_datosRespuestaSolicitudSeleccionChat *returnDatosRespuestaSolicitudSeleccionChat)
{
    memcpy (returnDatosRespuestaSolicitudSeleccionChat, respuesta, sizeof (t_datosRespuestaSolicitudSeleccionChat));
}

static void procesarRespuestaSegunEstadoSolicitudSeleccionChat (t_interfazContactos *interfazContactos, const t_datosRespuestaSolicitudSeleccionChat *datosRespuestaSolicitudSeleccionChat)
{
    switch (datosRespuestaSolicitudSeleccionChat->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            _interfazContactos_setearNuevoChatSeleccionado (interfazContactos, datosRespuestaSolicitudSeleccionChat);
            resetearBarraDeEscritura (interfazContactos);
            sfText_setString (interfazContactos->textos.feedbackUsuario, "");
            break;

        default:
            break;
    }
}

static void procesarRespuestaSolicitudSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRespuestaSolicitudSeleccionChat datosRespuestaSolicitudSeleccionChat;

    extraerDatosRespuestaSolicitudSeleccionChat (respuesta, &datosRespuestaSolicitudSeleccionChat);
    printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudSeleccionChat.header.tipo, datosRespuestaSolicitudSeleccionChat.estadoSolicitud, datosRespuestaSolicitudSeleccionChat.idUsuarioDelChatSeleccionado);
    procesarRespuestaSegunEstadoSolicitudSeleccionChat (interfazContactos, &datosRespuestaSolicitudSeleccionChat);
    contextoAplicacion->solicitudEnCurso = false;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA RECEPCION MENSAJE
   ============================================================================================================================================ */


static void extraerDatosRespuestaRecepcionMensaje (const char *respuesta, t_datosRespuestaRecepcionMensaje *returnDatosRespuestaRecepcionMensaje)
{
    memcpy (returnDatosRespuestaRecepcionMensaje, respuesta, sizeof (t_datosRespuestaRecepcionMensaje));
}

static bool elUsuarioDelChatSeleccionadoEsElEmisor (int idUsuarioEmisor, int idUsuarioDelChatSeleccionado)
{
    return (idUsuarioEmisor == idUsuarioDelChatSeleccionado);
}

static void procesarRespuestaSegunEstadoRecepcionMensaje (t_interfazContactos *interfazContactos, const t_datosRespuestaRecepcionMensaje *datosRespuestaRecepcionMensaje)
{
    if (elUsuarioDelChatSeleccionadoEsElEmisor (datosRespuestaRecepcionMensaje->idEmisor, interfazContactos->logica.idUsuarioDelChatSeleccionado))
        _interfazContactos_listaMensajes_insertarMensaje (&(interfazContactos->logica.contextoMensajes), datosRespuestaRecepcionMensaje->texto, MENSAJE_REMOTO, &(interfazContactos->fuentes));
}

static void procesarRespuestaRecepcionMensaje (t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRespuestaRecepcionMensaje datosRespuestaRecepcionMensaje;

    extraerDatosRespuestaRecepcionMensaje (respuesta, &datosRespuestaRecepcionMensaje);
    printf ("\nRespuesta recibida: %c|%d|%s\n", datosRespuestaRecepcionMensaje.header.tipo, datosRespuestaRecepcionMensaje.idEmisor, datosRespuestaRecepcionMensaje.texto);
    procesarRespuestaSegunEstadoRecepcionMensaje (interfazContactos, &datosRespuestaRecepcionMensaje);
}


#include "interfacesGraficas/interfazContactos/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibirYProcesarRespuestaServidor (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);
static void puntoInsercion (t_interfazContactos *interfazContactos);
static void textoDeCarga (const t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static void solicitudEnvioMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);
static void solicitudSeleccionChat_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);
static void recepcionMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazContactos_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    recibirYProcesarRespuestaServidor (contextoAplicacion, interfazContactos);
    puntoInsercion (interfazContactos);
    textoDeCarga (contextoAplicacion, interfazContactos);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibirYProcesarRespuestaServidor (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    t_resultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = recibirRespuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
    {
        switch (comunicacion_obtenerTipoRespuesta (bufferRespuesta))
        {
            case RESPUESTA_SOLICITUD_ENVIO_MENSAJE:
                solicitudEnvioMensaje_procesarRespuesta (contextoAplicacion, interfazContactos, bufferRespuesta);
                break;

            case RESPUESTA_RECEPCION_MENSAJE:
                recepcionMensaje_procesarRespuesta (contextoAplicacion, interfazContactos, bufferRespuesta);
                break;

            case RESPUESTA_SOLICITUD_SELECCION_CHAT:
                solicitudSeleccionChat_procesarRespuesta (contextoAplicacion, interfazContactos, bufferRespuesta);
                break;

            default:
                log_warning_respuestaRecibidaDeOtraInterfaz ();
                break;
        }
    }

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
        _interfazContactos_manejarError_conexion (contextoAplicacion, interfazContactos);
}

static void puntoInsercion (t_interfazContactos *interfazContactos)
{
    if (interfazContactos->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(interfazContactos->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazContactos->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazContactos->logica.puntoInsercion));
}

static void textoDeCarga (const t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    char texto [] = "Enviando";

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
    {
        if (textoDeCarga_actualizar (&(interfazContactos->logica.textoDeCarga)))
        {
            textoDeCarga_modificarTextoSegunEstado (&(interfazContactos->logica.textoDeCarga), texto);
            sfText_setString (interfazContactos->textos.feedbackUsuario, texto);
        }
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


static void solicitudEnvioMensaje_procesarRespuestaSegunEstado (t_interfazContactos *interfazContactos, const _t_datosUI_respuesta_solicitudEnvioMensaje *datosUI_respuesta_solicitudEnvioMensaje)
{
    switch (datosUI_respuesta_solicitudEnvioMensaje->estadoSolicitud)
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

static void solicitudEnvioMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    _t_datosUI_respuesta_solicitudEnvioMensaje datosUI_respuesta_solicitudEnvioMensaje;

    datosUI_respuesta_solicitudEnvioMensaje = _interfazContactos_solicitudEnvioMensaje_procesarRespuesta (contextoAplicacion, respuesta);
    solicitudEnvioMensaje_procesarRespuestaSegunEstado (interfazContactos, &datosUI_respuesta_solicitudEnvioMensaje);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD SELECCION CHAT
   ============================================================================================================================================ */


static void mostrar_nuevoChatSeleccionado (t_interfazContactos *interfazContactos)
{
    sfView_setCenter (interfazContactos->vistas.mensajes, (sfVector2f){1152, 480});
    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, interfazContactos->logica.nombreUsuarioDelChatSeleccionado);
    centrarTextoEnArea (interfazContactos->textos.auxContactoSeleccionado, 852, 25, 600, 40);
    _interfazContactos_listaMensajes_vaciar (&(interfazContactos->logica.contextoMensajes));
    sfText_setString (interfazContactos->textos.informacionSeleccionChat, "");
}

static void solicitudSeleccionChat_procesarRespuestaSegunEstado (t_interfazContactos *interfazContactos, const _t_datosUI_respuesta_solicitudSeleccionChat *datosUI_respuesta_solicitudSeleccionChat)
{
    switch (datosUI_respuesta_solicitudSeleccionChat->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            _interfazContactos_setearNuevoChatSeleccionado (interfazContactos, datosUI_respuesta_solicitudSeleccionChat);
            mostrar_nuevoChatSeleccionado (interfazContactos);
            resetearBarraDeEscritura (interfazContactos);
            sfText_setString (interfazContactos->textos.feedbackUsuario, "");
            break;

        default:
            break;
    }
}

static void solicitudSeleccionChat_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    _t_datosUI_respuesta_solicitudSeleccionChat datosUI_respuesta_solicitudSeleccionChat;

    datosUI_respuesta_solicitudSeleccionChat = _interfazContactos_solicitudSeleccionChat_procesarRespuesta (contextoAplicacion, respuesta);
    solicitudSeleccionChat_procesarRespuestaSegunEstado (interfazContactos, &datosUI_respuesta_solicitudSeleccionChat);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA RECEPCION MENSAJE
   ============================================================================================================================================ */


static bool elUsuarioDelChatSeleccionadoEsElEmisor (int idUsuarioEmisor, int idUsuarioDelChatSeleccionado)
{
    return (idUsuarioEmisor == idUsuarioDelChatSeleccionado);
}

static void recepcionMensaje_procesarRespuestaSegunEstado (t_interfazContactos *interfazContactos, const _t_datosUI_respuesta_recepcionMensaje *datosUI_respuesta_recepcionMensaje)
{
    if (elUsuarioDelChatSeleccionadoEsElEmisor (datosUI_respuesta_recepcionMensaje->idEmisor, interfazContactos->logica.idUsuarioDelChatSeleccionado))
        _interfazContactos_listaMensajes_insertarMensaje (&(interfazContactos->logica.contextoMensajes), datosUI_respuesta_recepcionMensaje->texto, MENSAJE_REMOTO, &(interfazContactos->fuentes));
}

static void recepcionMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, const char *respuesta)
{
    _t_datosUI_respuesta_recepcionMensaje datosUI_respuesta_recepcionMensaje;

    datosUI_respuesta_recepcionMensaje = _interfazContactos_recepcionMensaje_procesarRespuesta (contextoAplicacion, respuesta);
    recepcionMensaje_procesarRespuestaSegunEstado (interfazContactos, &datosUI_respuesta_recepcionMensaje);
}


#include "interfacesGraficas/interfazContactos/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibir_y_procesar_respuesta_servidor (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos);
static void punto_insercion (UiContactos *uiContactos);
static void texto_de_carga (const ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos);

static void procesar_respuesta_envio_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, const char *respuesta);
static void procesar_respuesta_seleccion_chat (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, const char *respuesta);
static void procesar_respuesta_recepcion_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_contactos_actualizar (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    recibir_y_procesar_respuesta_servidor (contextoAplicacion, uiContactos);
    punto_insercion (uiContactos);
    texto_de_carga (contextoAplicacion, uiContactos);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibir_y_procesar_respuesta_servidor (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    ResultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = comunicacion_recibir_respuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
    {
        switch (comunicacion_obtener_tipo_respuesta (bufferRespuesta))
        {
            case RESPUESTA_SOLICITUD_ENVIO_MENSAJE:
                procesar_respuesta_envio_mensaje (contextoAplicacion, uiContactos, bufferRespuesta);
                break;

            case RESPUESTA_RECEPCION_MENSAJE:
                procesar_respuesta_recepcion_mensaje (contextoAplicacion, uiContactos, bufferRespuesta);
                break;

            case RESPUESTA_SOLICITUD_SELECCION_CHAT:
                procesar_respuesta_seleccion_chat (contextoAplicacion, uiContactos, bufferRespuesta);
                break;

            default:
                log_warning_respuesta_recibida_otra_ui ();
                break;
        }
    }

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
        _ui_contactos_manejar_error_conexion (contextoAplicacion, uiContactos);
}

static void punto_insercion (UiContactos *uiContactos)
{
    if (uiContactos->foco == ESCRIBIR_MENSAJE)
        punto_insercion_actualizar (&(uiContactos->logica.puntoInsercion));
    else if (punto_insercion_esta_habilitado (&(uiContactos->logica.puntoInsercion)))
        punto_insercion_resetear (&(uiContactos->logica.puntoInsercion));
}

static void texto_de_carga (const ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    char texto [] = "Enviando";

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
    {
        if (texto_de_carga_actualizar (&(uiContactos->logica.textoDeCarga)))
        {
            texto_de_carga_modificar_texto (&(uiContactos->logica.textoDeCarga), texto);
            sfText_setString (uiContactos->textos.feedbackUsuario, texto);
        }
    }
}


static void resetear_barra_escritura (UiContactos *uiContactos)
{
    *(uiContactos->logica.contextoMensajes.mensaje) = '\0';
    sfText_setString (uiContactos->textos.auxEscribirMensaje, "");
    sfRectangleShape_setPosition (uiContactos->elementos.puntoInsercion, (sfVector2f){451, 942});
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD ENVIO MENSAJE
   ============================================================================================================================================ */


static void reaccionar_respuesta_envio_mensaje (UiContactos *uiContactos, const RespuestaEnvioMensajeUi *respuestaEnvioMensajeUi)
{
    switch (respuestaEnvioMensajeUi->estado)
    {
        case SOLICITUD_EXITO:
            _ui_contactos_lista_mensajes_insertar (&(uiContactos->logica.contextoMensajes), uiContactos->logica.contextoMensajes.mensaje, MENSAJE_PROPIO, &(uiContactos->fuentes));
            resetear_barra_escritura (uiContactos);
            sfText_setString (uiContactos->textos.feedbackUsuario, "");
            break;

        default:
            break;
    }
}

static void procesar_respuesta_envio_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, const char *respuesta)
{
    RespuestaEnvioMensajeUi respuestaEnvioMensajeUi;

    respuestaEnvioMensajeUi = _ui_contactos_procesar_respuesta_envio_mensaje (contextoAplicacion, respuesta);
    reaccionar_respuesta_envio_mensaje (uiContactos, &respuestaEnvioMensajeUi);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD SELECCION CHAT
   ============================================================================================================================================ */


static void mostrar_nuevo_chat_seleccionado (UiContactos *uiContactos)
{
    sfView_setCenter (uiContactos->vistas.mensajes, (sfVector2f){1152, 480});
    sfText_setString (uiContactos->textos.auxContactoSeleccionado, uiContactos->logica.nombreUsuarioDelChatSeleccionado);
    centrar_texto_en_area (uiContactos->textos.auxContactoSeleccionado, 852, 25, 600, 40);
    _ui_contactos_lista_mensajes_vaciar (&(uiContactos->logica.contextoMensajes));
    sfText_setString (uiContactos->textos.informacionSeleccionChat, "");
}

static void reaccionar_respuesta_seleccion_chat (UiContactos *uiContactos, const RespuestaSeleccionChatUi *respuestaSeleccionChatUi)
{
    switch (respuestaSeleccionChatUi->estado)
    {
        case SOLICITUD_EXITO:
            _ui_contactos_setear_nuevo_chat_seleccionado (uiContactos, respuestaSeleccionChatUi);
            mostrar_nuevo_chat_seleccionado (uiContactos);
            resetear_barra_escritura (uiContactos);
            sfText_setString (uiContactos->textos.feedbackUsuario, "");
            break;

        case SOLICITUD_ERROR_OPERACION_INVALIDA:
            resetear_barra_escritura (uiContactos);
            sfText_setString (uiContactos->textos.feedbackUsuario, "El usuario no existe");
            break;

        default:
            break;
    }
}

static void procesar_respuesta_seleccion_chat (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, const char *respuesta)
{
    RespuestaSeleccionChatUi respuestaSeleccionChatUi;

    respuestaSeleccionChatUi = _ui_contactos_procesar_respuesta_seleccion_chat (contextoAplicacion, respuesta);
    reaccionar_respuesta_seleccion_chat (uiContactos, &respuestaSeleccionChatUi);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA RECEPCION MENSAJE
   ============================================================================================================================================ */


static bool usuario_chat_seleccionado_es_emisor (int idUsuarioEmisor, int idUsuarioChatSeleccionado)
{
    return (idUsuarioEmisor == idUsuarioChatSeleccionado);
}

static void reacccionar_respuesta_recepcion_mensaje (UiContactos *uiContactos, const RespuestaRecepcionMensajeUi *respuestaRecepcionMensajeUi)
{
    if (usuario_chat_seleccionado_es_emisor (respuestaRecepcionMensajeUi->idEmisor, uiContactos->logica.idUsuarioChatSeleccionado))
        _ui_contactos_lista_mensajes_insertar (&(uiContactos->logica.contextoMensajes), respuestaRecepcionMensajeUi->texto, MENSAJE_REMOTO, &(uiContactos->fuentes));
}

static void procesar_respuesta_recepcion_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, const char *respuesta)
{
    RespuestaRecepcionMensajeUi respuestaRecepcionMensajeUi;

    respuestaRecepcionMensajeUi = _ui_contactos_procesar_respuesta_recepcion_mensaje (contextoAplicacion, respuesta);
    reacccionar_respuesta_recepcion_mensaje (uiContactos, &respuestaRecepcionMensajeUi);
}


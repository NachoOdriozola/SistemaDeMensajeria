#include "interfacesGraficas/interfazAutenticacion/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibir_y_procesar_respuesta_servidor (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);
static void punto_insercion (UiAutenticacion *uiAutenticacion);
static void texto_de_carga (const ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion);

static void mostrar_feedback_error_conexion (UiAutenticacion *uiAutenticacion);

static void procesar_respuesta_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_autenticacion_actualizar (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    recibir_y_procesar_respuesta_servidor (contextoAplicacion, uiAutenticacion);
    punto_insercion (uiAutenticacion);
    texto_de_carga (contextoAplicacion, uiAutenticacion);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibir_y_procesar_respuesta_servidor (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    ResultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = comunicacion_recibir_respuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
    {
        switch (comunicacion_obtener_tipo_respuesta (bufferRespuesta))
        {
            case RESPUESTA_SOLICITUD_AUTENTICACION:
                procesar_respuesta_autenticacion (contextoAplicacion, uiAutenticacion, bufferRespuesta);
                break;

            default:
                log_warning_respuesta_recibida_otra_ui ();
                break;
        }
    }

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _ui_autenticacion_manejar_error_conexion (contextoAplicacion);
        mostrar_feedback_error_conexion (uiAutenticacion);
    }
}

static void punto_insercion (UiAutenticacion *uiAutenticacion)
{
    if ((uiAutenticacion->uiAcceso->foco == ESCRIBIR_NOMBRE) ||
        (uiAutenticacion->uiAcceso->foco == ESCRIBIR_CONTRASENIA))
        punto_insercion_actualizar (&(uiAutenticacion->uiAcceso->logica.puntoInsercion));
    else if (punto_insercion_esta_habilitado (&(uiAutenticacion->uiAcceso->logica.puntoInsercion)))
        punto_insercion_resetear (&(uiAutenticacion->uiAcceso->logica.puntoInsercion));
}

static void texto_de_carga (const ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    char texto [] = "Cargando";

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
    {
        if (texto_de_carga_actualizar (&(uiAutenticacion->uiAcceso->logica.textoDeCarga)))
        {
            texto_de_carga_modificar_texto (&(uiAutenticacion->uiAcceso->logica.textoDeCarga), texto);
            sfText_setString (uiAutenticacion->uiAcceso->textos.feedbackUsuario, texto);
            centrar_texto_en_area (uiAutenticacion->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 130);
        }
    }
}


static void mostrar_feedback_error_conexion (UiAutenticacion *uiAutenticacion)
{
    uint32_t bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (uiAutenticacion->uiAcceso->textos.feedbackUsuario, bufferErrorConexion);
    centrar_texto_en_area (uiAutenticacion->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 130);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD AUTENTICACION
   ============================================================================================================================================ */


static void mostrar_feedback_credenciales_invalidas (UiAutenticacion *uiAutenticacion)
{
    uint32_t bufferErrorCredenciales [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
    sfText_setUnicodeString (uiAutenticacion->uiAcceso->textos.feedbackUsuario, bufferErrorCredenciales);
    centrar_texto_en_area (uiAutenticacion->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void mostrar_feedback_operacion_invalida (UiAutenticacion *uiAutenticacion)
{
    sfText_setString (uiAutenticacion->uiAcceso->textos.feedbackUsuario, "Usuario ya conectado");
    centrar_texto_en_area (uiAutenticacion->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void reaccionar_respuesta_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, RespuestaAutenticacionUi *respuestaAutenticacionUi)
{
    switch (respuestaAutenticacionUi->estado)
    {
        case SOLICITUD_EXITO:
            _ui_autenticacion_cambiar_a_ui_contactos (contextoAplicacion, uiAutenticacion, respuestaAutenticacionUi);
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credenciales_invalidas (uiAutenticacion);
            break;

        case SOLICITUD_ERROR_OPERACION_INVALIDA:
            mostrar_feedback_operacion_invalida (uiAutenticacion);
            break;

        default:
            break;
    }
}

static void procesar_respuesta_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, const char *respuesta)
{
    RespuestaAutenticacionUi respuestaAutenticacionUi;

    respuestaAutenticacionUi = _ui_autenticacion_procesar_respuesta_autenticacion (contextoAplicacion, respuesta);
    reaccionar_respuesta_autenticacion (contextoAplicacion, uiAutenticacion, &respuestaAutenticacionUi);
}

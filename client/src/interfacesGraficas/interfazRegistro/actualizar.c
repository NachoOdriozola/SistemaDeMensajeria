#include "interfacesGraficas/interfazRegistro/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibir_y_procesar_respuesta_servidor (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);
static void punto_insercion (UiRegistro *uiRegistro);
static void texto_de_carga (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);

static void procesar_respuesta_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, const char *respuesta);

static void mostrar_feedback_error_conexion (UiRegistro *uiRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_registro_actualizar (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    recibir_y_procesar_respuesta_servidor (contextoAplicacion, uiRegistro);
    punto_insercion (uiRegistro);
    texto_de_carga (contextoAplicacion, uiRegistro);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibir_y_procesar_respuesta_servidor (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    ResultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = comunicacion_recibir_respuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
    {
        switch (comunicacion_obtener_tipo_respuesta (bufferRespuesta))
        {
            case RESPUESTA_SOLICITUD_REGISTRO:
                procesar_respuesta_registro (contextoAplicacion, uiRegistro, bufferRespuesta);
                break;

            default:
                log_warning_respuesta_recibida_otra_ui ();
                break;
        }
    }

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _ui_registro_manejar_error_conexion (contextoAplicacion);
        mostrar_feedback_error_conexion (uiRegistro);
    }
}

static void punto_insercion (UiRegistro *uiRegistro)
{
    if ((uiRegistro->uiAcceso->foco == ESCRIBIR_NOMBRE) ||
        (uiRegistro->uiAcceso->foco == ESCRIBIR_CONTRASENIA ||
         uiRegistro->foco == ESCRIBIR_CORREO))
        punto_insercion_actualizar (&(uiRegistro->uiAcceso->logica.puntoInsercion));
    else if (punto_insercion_esta_habilitado (&(uiRegistro->uiAcceso->logica.puntoInsercion)))
        punto_insercion_resetear (&(uiRegistro->uiAcceso->logica.puntoInsercion));
}

static void texto_de_carga (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    char texto [] = "Cargando";

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
    {
        if (texto_de_carga_actualizar (&(uiRegistro->uiAcceso->logica.textoDeCarga)))
        {
            texto_de_carga_modificar_texto (&(uiRegistro->uiAcceso->logica.textoDeCarga), texto);
            sfText_setString (uiRegistro->uiAcceso->textos.feedbackUsuario, texto);
            centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
        }
    }
}


static void mostrar_feedback_error_conexion (UiRegistro *uiRegistro)
{
    uint32_t bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (uiRegistro->uiAcceso->textos.feedbackUsuario, bufferErrorConexion);
    centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD REGISTRO
   ============================================================================================================================================ */


static void mostrar_feedback_credenciales_invalidas (UiRegistro *uiRegistro)
{
    uint32_t bufferDatosInvalidos [] = {'D', 'a', 't', 'o', 's', ' ', 'i', 'n', 'v', 0x00e1, 'l', 'i', 'd', 'o', 's', 0};
    sfText_setUnicodeString (uiRegistro->uiAcceso->textos.feedbackUsuario, bufferDatosInvalidos);
    centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_nombre_ya_existente (UiRegistro *uiRegistro)
{
    sfText_setString (uiRegistro->uiAcceso->textos.feedbackUsuario, "Nombre de usuario ya existente");
    centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_correo_ya_existente (UiRegistro *uiRegistro)
{
    uint32_t bufferCorreoYaExistente [] = {'C', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00f3, 'n', 'i', 'c', 'o', ' ', 'y', 'a', ' ', 'e', 'x', 'i', 's', 't', 'e', 'n', 't', 'e', 0};
    sfText_setUnicodeString (uiRegistro->uiAcceso->textos.feedbackUsuario, bufferCorreoYaExistente);
    centrar_texto_en_area (uiRegistro->uiAcceso->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void reaccionar_respuesta_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, RespuestaRegistroUi *respuestaRegistroUi)
{
    switch (respuestaRegistroUi->estado)
    {
        case SOLICITUD_EXITO:
            _ui_registro_cambiar_a_ui_contactos (contextoAplicacion, uiRegistro, respuestaRegistroUi);
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credenciales_invalidas (uiRegistro);
            break;

        case SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE:
            mostrar_feedback_nombre_ya_existente (uiRegistro);
            break;

        case SOLICITUD_ERROR_CORREO_YA_EXISTENTE:
            mostrar_feedback_correo_ya_existente (uiRegistro);
            break;

        default:
            break;
    }
}

static void procesar_respuesta_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, const char *respuesta)
{
    RespuestaRegistroUi respuestaRegistroUi;

    respuestaRegistroUi = _ui_registro_procesar_respuesta_registro (contextoAplicacion, respuesta);
    reaccionar_respuesta_registro (contextoAplicacion, uiRegistro, &respuestaRegistroUi);
}


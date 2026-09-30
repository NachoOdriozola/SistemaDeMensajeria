#include "interfacesGraficas/interfazAutenticacion/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool es_autenticacion_valida (const UiAutenticacion *uiAutenticacion);

static void resetear_interfaz (UiAutenticacion *uiAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


ResultadoIntentoAutenticacion _ui_autenticacion_intentar_autenticacion (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    if (!es_autenticacion_valida (uiAutenticacion))
        return INTENTO_AUTENTICACION_CREDENCIALES_INVALIDAS;

    if (comunicacion_intentar_conectar_con_servidor (&(contextoAplicacion->sock)) == SOLICITUD_ERROR_CONEXION)
    {
        _ui_autenticacion_manejar_error_conexion (contextoAplicacion);
        return INTENTO_AUTENTICACION_ERROR_CONEXION;
    }
    
    comunicacion_enviar_solicitud_autenticacion (contextoAplicacion, uiAutenticacion->uiAcceso->logica.nombreUsuario, uiAutenticacion->uiAcceso->logica.contrasenia);
    return INTENTO_AUTENTICACION_SOLICITUD_ENVIADA;
}


RespuestaAutenticacionUi _ui_autenticacion_procesar_respuesta_autenticacion (ContextoAplicacion *contextoAplicacion, const char *respuesta)
{
    RespuestaAutenticacion respuestaAutenticacion;
    RespuestaAutenticacionUi respuestaAutenticacionUi;

    comunicacion_extraer_respuesta_autenticacion (respuesta, &respuestaAutenticacion);
    printf ("Respuesta recibida: %c|%c|%d\n", respuestaAutenticacion.header.tipoPaquete, respuestaAutenticacion.estado, respuestaAutenticacion.idUsuario);
    comunicacion_finalizar_solicitud_en_curso (contextoAplicacion);

    respuestaAutenticacionUi.estado = respuestaAutenticacion.estado;
    respuestaAutenticacionUi.idUsuario = respuestaAutenticacion.idUsuario;

    return respuestaAutenticacionUi;
}


void _ui_autenticacion_manejar_error_conexion (ContextoAplicacion *contextoAplicacion)
{
    comunicacion_finalizar (&(contextoAplicacion->sock));
    log_error_conexion ();
}


void _ui_autenticacion_cambiar_a_ui_contactos (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion, const RespuestaAutenticacionUi *respuestaAutenticacionUi)
{
    contextoAplicacion->usuario.id = respuestaAutenticacionUi->idUsuario;
    strcpy (contextoAplicacion->usuario.nombre, uiAutenticacion->uiAcceso->logica.nombreUsuario);
    
    contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
}

void _ui_autenticacion_cambiar_a_ui_registro (ContextoAplicacion *contextoAplicacion, UiAutenticacion *uiAutenticacion)
{
    omitir_eventos_pendientes (contextoAplicacion->renderizado);
    resetear_interfaz (uiAutenticacion);
    ui_acceso_activar_interfaz_registro (uiAutenticacion->uiAcceso);
    
    contextoAplicacion->interfazActual = INTERFAZ_REGISTRO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool es_autenticacion_valida (const UiAutenticacion *uiAutenticacion)
{
    return ((es_nombre_valido (uiAutenticacion->uiAcceso->logica.nombreUsuario)) && (es_contrasenia_valida (uiAutenticacion->uiAcceso->logica.contrasenia)));
}


static void resetear_interfaz (UiAutenticacion *uiAutenticacion)
{
    uiAutenticacion->foco = UI_AUTENTICACION_NINGUNO;
}


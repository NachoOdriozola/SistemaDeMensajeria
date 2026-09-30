#include "interfacesGraficas/interfazRegistro/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static ValidacionRegistro validar_registro (const UiRegistro *uiRegistro);
static void establecer_datos_registro_validos (ValidacionRegistro *validacionRegistro);

static void resetear_interfaz (UiRegistro *uiRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


ResultadoIntentoRegistro _ui_registro_intentar_registro (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    ResultadoIntentoRegistro resultadoIntentoRegistro;

    resultadoIntentoRegistro.validacion = validar_registro (uiRegistro);
    if ((!resultadoIntentoRegistro.validacion.nombreValido) || (!resultadoIntentoRegistro.validacion.contraseniaValida) || (!resultadoIntentoRegistro.validacion.correoValido))
    {
        resultadoIntentoRegistro.estado = INTENTO_REGISTRO_CREDENCIALES_INVALIDAS;
        return resultadoIntentoRegistro;
    }

    if (comunicacion_intentar_conectar_con_servidor (&(contextoAplicacion->sock)) == SOLICITUD_ERROR_CONEXION)
    {
        _ui_registro_manejar_error_conexion (contextoAplicacion);
        resultadoIntentoRegistro.estado = INTENTO_REGISTRO_ERROR_CONEXION;
        establecer_datos_registro_validos (&(resultadoIntentoRegistro.validacion));
        return resultadoIntentoRegistro;
    }

    comunicacion_enviar_solicitud_registro (contextoAplicacion, uiRegistro->uiAcceso->logica.nombreUsuario, uiRegistro->uiAcceso->logica.contrasenia, uiRegistro->logica.correoElectronico);
    resultadoIntentoRegistro.estado = INTENTO_REGISTRO_SOLICITUD_ENVIADA;
    establecer_datos_registro_validos (&(resultadoIntentoRegistro.validacion));
    
    return resultadoIntentoRegistro;
}


RespuestaRegistroUi _ui_registro_procesar_respuesta_registro (ContextoAplicacion *contextoAplicacion, const char *respuesta)
{
    RespuestaRegistro respuestaRegistro;
    RespuestaRegistroUi respuestaRegistroUi;

    comunicacion_extraer_respuesta_registro (respuesta, &respuestaRegistro);
    printf ("Respuesta recibida: %c|%c|%d\n", respuestaRegistro.header.tipoPaquete, respuestaRegistro.estado, respuestaRegistro.idUsuario);
    comunicacion_finalizar_solicitud_en_curso (contextoAplicacion);

    respuestaRegistroUi.estado = respuestaRegistro.estado;
    respuestaRegistroUi.idUsuario = respuestaRegistro.idUsuario;

    return respuestaRegistroUi;
}


void _ui_registro_manejar_error_conexion (ContextoAplicacion *contextoAplicacion)
{
    comunicacion_finalizar (&(contextoAplicacion->sock));
    log_error_conexion ();
}


void _ui_registro_cambiar_a_ui_contactos (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro, const RespuestaRegistroUi *respuestaRegistroUi)
{
    contextoAplicacion->usuario.id = respuestaRegistroUi->idUsuario;
    strcpy (contextoAplicacion->usuario.nombre, uiRegistro->uiAcceso->logica.nombreUsuario);
    
    contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
}

void _ui_registro_cambiar_a_ui_autenticacion (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro)
{
    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return;

    omitir_eventos_pendientes (contextoAplicacion->renderizado);
    resetear_interfaz (uiRegistro);
    ui_acceso_activar_interfaz_autenticacion (uiRegistro->uiAcceso);

    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static ValidacionRegistro validar_registro (const UiRegistro *uiRegistro)
{
    ValidacionRegistro validacionRegistro;

    validacionRegistro.nombreValido = es_nombre_valido (uiRegistro->uiAcceso->logica.nombreUsuario);
    validacionRegistro.contraseniaValida = es_contrasenia_valida (uiRegistro->uiAcceso->logica.contrasenia);
    validacionRegistro.correoValido = es_correo_electronico_valido (uiRegistro->logica.correoElectronico);
    
    return validacionRegistro;
}

static void establecer_datos_registro_validos (ValidacionRegistro *validacionRegistro)
{
    validacionRegistro->nombreValido = 1;
    validacionRegistro->contraseniaValida = 1;
    validacionRegistro->correoValido = 1;
}


static void resetear_interfaz (UiRegistro *uiRegistro)
{
    // INTERFAZ
    uiRegistro->foco = UI_REGISTRO_NINGUNO;
    *(uiRegistro->logica.correoElectronico) = '\0';

    // TEXTOS
    sfText_setString (uiRegistro->textos.auxEscribirCorreo, "");
    sfText_setFillColor (uiRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
}

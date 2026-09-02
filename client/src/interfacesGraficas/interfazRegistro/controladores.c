#include "interfacesGraficas/interfazRegistro/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static _t_resultado_validacionDatosRegistro validarDatosRegistroUsuario (const t_interfazRegistro *interfazRegistro);
static void establecerDatosRegistroUsuarioValidos (_t_resultado_validacionDatosRegistro *resultado_validacionDatosRegistro);

static void resetearInterfaz (t_interfazRegistro *interfazRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


_t_resultado_intentarRegistrar _interfazRegsitro_intentar_registrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    _t_resultado_intentarRegistrar resultado_intentarRegistrar;

    resultado_intentarRegistrar.validacion = validarDatosRegistroUsuario (interfazRegistro);
    if ((!resultado_intentarRegistrar.validacion.nombreValido) || (!resultado_intentarRegistrar.validacion.contraseniaValida) || (!resultado_intentarRegistrar.validacion.correoValido))
    {
        resultado_intentarRegistrar.tipo = INTENTARREGISTRAR_RESULTADO_CREDENCIALES_INVALIDAS;
        return resultado_intentarRegistrar;
    }

    if (intentarConectarConServidor (&(contextoAplicacion->sock)) == SOLICITUD_ERROR_CONEXION)
    {
        _interfazRegistro_manejarError_conexion (contextoAplicacion);
        resultado_intentarRegistrar.tipo = INTENTARREGISTRAR_RESULTADO_ERROR_CONEXION;
        establecerDatosRegistroUsuarioValidos (&(resultado_intentarRegistrar.validacion));
        return resultado_intentarRegistrar;
    }

    enviarSolicitudRegistro (contextoAplicacion, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, interfazRegistro->logica.correoElectronico);
    resultado_intentarRegistrar.tipo = INTENTARREGISTRAR_RESULTADO_EXITO;
    establecerDatosRegistroUsuarioValidos (&(resultado_intentarRegistrar.validacion));
    
    return resultado_intentarRegistrar;
}


_t_datosUI_respuesta_solicitudRegistro _interfazRegistro_solicitudRegistro_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta)
{
    t_datosRespuestaSolicitudRegistro datos_respuesta_solicitudRegistro;
    _t_datosUI_respuesta_solicitudRegistro datosUI_respuesta_solicitudRegistro;

    comunicacion_extraerDatosRespuesta_solicitudRegistro (respuesta, &datos_respuesta_solicitudRegistro);
    printf ("Respuesta recibida: %c|%c|%d\n", datos_respuesta_solicitudRegistro.header.tipo, datos_respuesta_solicitudRegistro.estadoSolicitud, datos_respuesta_solicitudRegistro.idUsuario);
    comunicacion_finalizarSolicitudEnCurso (contextoAplicacion);

    datosUI_respuesta_solicitudRegistro.estadoSolicitud = datos_respuesta_solicitudRegistro.estadoSolicitud;
    datosUI_respuesta_solicitudRegistro.idUsuario = datos_respuesta_solicitudRegistro.idUsuario;

    return datosUI_respuesta_solicitudRegistro;
}


void _interfazRegistro_manejarError_conexion (t_contextoAplicacion *contextoAplicacion)
{
    comunicacion_finalizar (&(contextoAplicacion->sock));
    log_error_conexion ();
}


void _interfazRegistro_cambiarAInterfaz_contactos (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const _t_datosUI_respuesta_solicitudRegistro *datosUI_respuesta_solicitudRegistro)
{
    contextoAplicacion->usuario.id = datosUI_respuesta_solicitudRegistro->idUsuario;
    strcpy (contextoAplicacion->usuario.nombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
    
    contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
}

void _interfazRegistro_cambiarAInterfaz_autenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return;

    omitirEventosPendientes (contextoAplicacion->renderizado);
    resetearInterfaz (interfazRegistro);
    recursosComunesAutenticacionRegistro_activarInterfazAutenticacion (interfazRegistro->recursosComunesAutenticacionRegistro);

    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static _t_resultado_validacionDatosRegistro validarDatosRegistroUsuario (const t_interfazRegistro *interfazRegistro)
{
    _t_resultado_validacionDatosRegistro resultado_validacionDatosRegistro;

    resultado_validacionDatosRegistro.nombreValido = esNombreValido (interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
    resultado_validacionDatosRegistro.contraseniaValida = esContraseniaValida (interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia);
    resultado_validacionDatosRegistro.correoValido = esCorreoElectronicoValido (interfazRegistro->logica.correoElectronico);
    
    return resultado_validacionDatosRegistro;
}

static void establecerDatosRegistroUsuarioValidos (_t_resultado_validacionDatosRegistro *resultado_validacionDatosRegistro)
{
    resultado_validacionDatosRegistro->nombreValido = 1;
    resultado_validacionDatosRegistro->contraseniaValida = 1;
    resultado_validacionDatosRegistro->correoValido = 1;
}


static void resetearInterfaz (t_interfazRegistro *interfazRegistro)
{
    // INTERFAZ
    interfazRegistro->estadoFoco = IR_NINGUNO;
    *(interfazRegistro->logica.correoElectronico) = '\0';

    // TEXTOS
    sfText_setString (interfazRegistro->textos.auxEscribirCorreo, "");
    sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
}

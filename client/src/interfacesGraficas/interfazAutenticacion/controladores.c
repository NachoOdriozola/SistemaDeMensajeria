#include "interfacesGraficas/interfazAutenticacion/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool sonDatosAutenticacionUsuarioValidos (const t_interfazAutenticacion *interfazAutenticacion);

static void resetearInterfaz (t_interfazAutenticacion *interfazAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


_t_resultado_intentarAutenticar _interfazAutenticacion_intentar_autenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!sonDatosAutenticacionUsuarioValidos (interfazAutenticacion))
        return INTENTARAUTENTICAR_RESULTADO_CREDENCIALES_INVALIDAS;

    if (intentarConectarConServidor (&(contextoAplicacion->sock)) == SOLICITUD_ERROR_CONEXION)
    {
        _interfazAutenticacion_manejarError_conexion (contextoAplicacion);
        return INTENTARAUTENTICAR_RESULTADO_ERROR_CONEXION;
    }
    
    enviarSolicitudAutenticacion (contextoAplicacion, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia);
    return INTENTARAUTENTICAR_RESULTADO_EXITO;
}


_t_datosUI_respuesta_solicitudAutenticacion _interfazAutenticacion_solicitudAutenticacion_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta)
{
    t_datosRespuestaSolicitudAutenticacion datos_respuesta_solicitudAutenticacion;
    _t_datosUI_respuesta_solicitudAutenticacion datosUI_respuesta_solicitudAutenticacion;

    comunicacion_extraerDatosRespuesta_solicitudAutenticacion (respuesta, &datos_respuesta_solicitudAutenticacion);
    printf ("Respuesta recibida: %c|%c|%d\n", datos_respuesta_solicitudAutenticacion.header.tipo, datos_respuesta_solicitudAutenticacion.estadoSolicitud, datos_respuesta_solicitudAutenticacion.idUsuario);
    comunicacion_finalizarSolicitudEnCurso (contextoAplicacion);

    datosUI_respuesta_solicitudAutenticacion.estadoSolicitud = datos_respuesta_solicitudAutenticacion.estadoSolicitud;
    datosUI_respuesta_solicitudAutenticacion.idUsuario = datos_respuesta_solicitudAutenticacion.idUsuario;

    return datosUI_respuesta_solicitudAutenticacion;
}


void _interfazAutenticacion_manejarError_conexion (t_contextoAplicacion *contextoAplicacion)
{
    comunicacion_finalizar (&(contextoAplicacion->sock));
    log_error_conexion ();
}


void _interfazAutenticacion_cambiarAInterfaz_contactos (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const _t_datosUI_respuesta_solicitudAutenticacion *datosUI_respuesta_solicitudAutenticacion)
{
    contextoAplicacion->usuario.id = datosUI_respuesta_solicitudAutenticacion->idUsuario;
    strcpy (contextoAplicacion->usuario.nombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
    
    contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
}

void _interfazAutenticacion_cambiarAInterfaz_registro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    omitirEventosPendientes (contextoAplicacion->renderizado);
    resetearInterfaz (interfazAutenticacion);
    recursosComunesAutenticacionRegistro_activarInterfazRegistro (interfazAutenticacion->recursosComunesAutenticacionRegistro);
    
    contextoAplicacion->interfazActual = INTERFAZ_REGISTRO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool sonDatosAutenticacionUsuarioValidos (const t_interfazAutenticacion *interfazAutenticacion)
{
    return ((esNombreValido (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario)) && (esContraseniaValida (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia)));
}


static void resetearInterfaz (t_interfazAutenticacion *interfazAutenticacion)
{
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}


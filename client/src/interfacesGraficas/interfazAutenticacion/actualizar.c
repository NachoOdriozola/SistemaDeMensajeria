#include "interfacesGraficas/interfazAutenticacion/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibirYProcesarRespuestaServidor (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);
static void puntoInsercion (t_interfazAutenticacion *interfazAutenticacion);
static void textoDeCarga (const t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

static void mostrar_feedback_errorConexion (t_interfazAutenticacion *interfazAutenticacion);

static void solicitudAutenticacion_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazAutenticacion_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    recibirYProcesarRespuestaServidor (contextoAplicacion, interfazAutenticacion);
    puntoInsercion (interfazAutenticacion);
    textoDeCarga (contextoAplicacion, interfazAutenticacion);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibirYProcesarRespuestaServidor (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    t_resultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = recibirRespuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
    {
        switch (comunicacion_obtenerTipoRespuesta (bufferRespuesta))
        {
            case RESPUESTA_SOLICITUD_AUTENTICACION:
                solicitudAutenticacion_procesarRespuesta (contextoAplicacion, interfazAutenticacion, bufferRespuesta);
                break;

            default:
                log_warning_respuestaRecibidaDeOtraInterfaz ();
                break;
        }
    }

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazAutenticacion_manejarError_conexion (contextoAplicacion);
        mostrar_feedback_errorConexion (interfazAutenticacion);
    }
}

static void puntoInsercion (t_interfazAutenticacion *interfazAutenticacion)
{
    if ((interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA))
        actualizarPuntoInsercion (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
}

static void textoDeCarga (const t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    char texto [] = "Cargando";

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
    {
        if (textoDeCarga_actualizar (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.textoDeCarga)))
        {
            textoDeCarga_modificarTextoSegunEstado (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.textoDeCarga), texto);
            sfText_setString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, texto);
            centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
        }
    }
}


static void mostrar_feedback_errorConexion (t_interfazAutenticacion *interfazAutenticacion)
{
    uint32_t bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorConexion);
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD AUTENTICACION
   ============================================================================================================================================ */


static void mostrar_feedback_credencialesInvalidas (t_interfazAutenticacion *interfazAutenticacion)
{
    uint32_t bufferErrorCredenciales [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
    sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorCredenciales);
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void mostrar_feedback_operacionInvalida (t_interfazAutenticacion *interfazAutenticacion)
{
    sfText_setString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "Usuario ya conectado");
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}

static void solicitudAutenticacion_procesarRespuestaSegunEstado (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, _t_datosUI_respuesta_solicitudAutenticacion *datosUI_respuesta_solicitudAutenticacion)
{
    switch (datosUI_respuesta_solicitudAutenticacion->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            _interfazAutenticacion_cambiarAInterfaz_contactos (contextoAplicacion, interfazAutenticacion, datosUI_respuesta_solicitudAutenticacion);
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credencialesInvalidas (interfazAutenticacion);
            break;

        case SOLICITUD_ERROR_OPERACION_INVALIDA:
            mostrar_feedback_operacionInvalida (interfazAutenticacion);
            break;

        default:
            break;
    }
}

static void solicitudAutenticacion_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta)
{
    _t_datosUI_respuesta_solicitudAutenticacion datosUI_respuesta_solicitudAutenticacion;

    datosUI_respuesta_solicitudAutenticacion = _interfazAutenticacion_solicitudAutenticacion_procesarRespuesta (contextoAplicacion, respuesta);
    solicitudAutenticacion_procesarRespuestaSegunEstado (contextoAplicacion, interfazAutenticacion, &datosUI_respuesta_solicitudAutenticacion);
}

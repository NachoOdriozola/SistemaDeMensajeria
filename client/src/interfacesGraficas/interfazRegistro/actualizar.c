#include "interfacesGraficas/interfazRegistro/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibirYProcesarRespuestaServidor (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);
static void puntoInsercion (t_interfazRegistro *interfazRegistro);
static void textoDeCarga (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

static void solicitudRegistro_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta);

static void mostrar_feedback_errorConexion (t_interfazRegistro *interfazRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazRegistro_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    recibirYProcesarRespuestaServidor (contextoAplicacion, interfazRegistro);
    puntoInsercion (interfazRegistro);
    textoDeCarga (contextoAplicacion, interfazRegistro);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void recibirYProcesarRespuestaServidor (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    t_resultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = recibirRespuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
    {
        switch (comunicacion_obtenerTipoRespuesta (bufferRespuesta))
        {
            case RESPUESTA_SOLICITUD_REGISTRO:
                solicitudRegistro_procesarRespuesta (contextoAplicacion, interfazRegistro, bufferRespuesta);
                break;

            default:
                log_warning_respuestaRecibidaDeOtraInterfaz ();
                break;
        }
    }

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazRegistro_manejarError_conexion (contextoAplicacion);
        mostrar_feedback_errorConexion (interfazRegistro);
    }
}

static void puntoInsercion (t_interfazRegistro *interfazRegistro)
{
    if ((interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA ||
         interfazRegistro->estadoFoco == ESCRIBIR_CORREO))
        actualizarPuntoInsercion (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
}

static void textoDeCarga (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    char texto [] = "Cargando";

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
    {
        if (textoDeCarga_actualizar (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.textoDeCarga)))
        {
            textoDeCarga_modificarTextoSegunEstado (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.textoDeCarga), texto);
            sfText_setString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, texto);
            centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
        }
    }
}


static void procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta)
{
    t_header header;

    memcpy (&header, respuesta, sizeof (t_header));
    switch (header.tipo)
    {
        case RESPUESTA_SOLICITUD_REGISTRO:
            procesarRespuestaSolicitudRegistro (contextoAplicacion, interfazRegistro, respuesta);
            break;

        default:
            break;
    }
}


static void mostrar_feedback_errorConexion (t_interfazRegistro *interfazRegistro)
{
    sfUint32 bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorConexion);
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD REGISTRO
   ============================================================================================================================================ */


static void mostrar_feedback_credencialesInvalidas (t_interfazRegistro *interfazRegistro)
{
     sfUint32 bufferDatosInvalidos [] = {'D', 'a', 't', 'o', 's', ' ', 'i', 'n', 'v', 0x00e1, 'l', 'i', 'd', 'o', 's', 0};
    sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferDatosInvalidos);
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_nombreYaExistente (t_interfazRegistro *interfazRegistro)
{
    sfText_setString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "Nombre de usuario ya existente");
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void mostrar_feedback_correoYaExistente (t_interfazRegistro *interfazRegistro)
{
    sfUint32 bufferCorreoYaExistente [] = {'C', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00f3, 'n', 'i', 'c', 'o', ' ', 'y', 'a', ' ', 'e', 'x', 'i', 's', 't', 'e', 'n', 't', 'e', 0};
    sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferCorreoYaExistente);
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}

static void solicitudRegistro_procesarRespuestaSegunEstado (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, _t_datosUI_respuesta_solicitudRegistro *datosUI_respuesta_solicitudRegistro)
{
    switch (datosUI_respuesta_solicitudRegistro->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            _interfazRegistro_cambiarAInterfaz_contactos (contextoAplicacion, interfazRegistro, datosUI_respuesta_solicitudRegistro);
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            mostrar_feedback_credencialesInvalidas (interfazRegistro);
            break;

        case SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE:
            mostrar_feedback_nombreYaExistente (interfazRegistro);
            break;

        case SOLICITUD_ERROR_CORREO_YA_EXISTENTE:
            mostrar_feedback_correoYaExistente (interfazRegistro);
            break;

        default:
            break;
    }
}

static void solicitudRegistro_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta)
{
    _t_datosUI_respuesta_solicitudRegistro datosUI_respuesta_solicitudRegistro;

    datosUI_respuesta_solicitudRegistro = _interfazRegistro_solicitudRegistro_procesarRespuesta (contextoAplicacion, respuesta);
    solicitudRegistro_procesarRespuestaSegunEstado (contextoAplicacion, interfazRegistro, &datosUI_respuesta_solicitudRegistro);
}


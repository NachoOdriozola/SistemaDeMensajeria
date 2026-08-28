#include "interfacesGraficas/interfazAutenticacion/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta);

static void procesarRespuestaSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazAutenticacion_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- RECIBIR Y PROCESAR RESPUESTAS DEL SERVIDOR ---------------

    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    t_resultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = recibirRespuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
        procesarRespuesta (contextoAplicacion, interfazAutenticacion, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazAutenticacion_manejarErrorConexion (contextoAplicacion, interfazAutenticacion);
        puts ("\nSe perdio la conexion con el servidor.");
    }

    // --------------- PUNTO DE INSERCION ---------------

    if ((interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA))
        actualizarPuntoInsercion (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta)
{
    t_header header;

    memcpy (&header, respuesta, sizeof (t_header));
    switch (header.tipo)
    {
        case RESPUESTA_SOLICITUD_AUTENTICACION:
            procesarRespuestaSolicitudAutenticacion (contextoAplicacion, interfazAutenticacion, respuesta);
            break;

        default:
            break;
    }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD AUTENTICACION
   ============================================================================================================================================ */


static void extraerDatosRespuestaSolicitudAutenticacion (const char *respuesta, t_datosRespuestaSolicitudAutenticacion *returnDatosRespuestaSolicitudAutenticacion)
{
    memcpy (returnDatosRespuestaSolicitudAutenticacion, respuesta, sizeof (t_datosRespuestaSolicitudAutenticacion));
}

static void procesarRespuestaSegunEstadoSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, t_datosRespuestaSolicitudAutenticacion *datosRespuestaSolicitudAutenticacion)
{
    switch (datosRespuestaSolicitudAutenticacion->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            _interfazAutenticacion_accederAContactos (contextoAplicacion, interfazAutenticacion, datosRespuestaSolicitudAutenticacion);
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            sfUint32 bufferErrorCredenciales [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
            sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorCredenciales);
            centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
            break;

        case SOLICITUD_ERROR_OPERACION_INVALIDA:
            sfText_setString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "Usuario ya conectado");
            centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
            break;

        default:
            break;
    }
}

static void procesarRespuestaSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta)
{
    t_datosRespuestaSolicitudAutenticacion datosRespuestaSolicitudAutenticacion;

    extraerDatosRespuestaSolicitudAutenticacion (respuesta, &datosRespuestaSolicitudAutenticacion);
    printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudAutenticacion.header.tipo, datosRespuestaSolicitudAutenticacion.estadoSolicitud, datosRespuestaSolicitudAutenticacion.idUsuario);
    procesarRespuestaSegunEstadoSolicitudAutenticacion (contextoAplicacion, interfazAutenticacion, &datosRespuestaSolicitudAutenticacion);
    contextoAplicacion->solicitudEnCurso = false;
}


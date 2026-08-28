#include "interfacesGraficas/interfazRegistro/actualizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta);

static void procesarRespuestaSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazRegistro_actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    // --------------- RECIBIR Y PROCESAR RESPUESTAS DEL SERVIDOR ---------------

    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    t_resultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = recibirRespuesta (contextoAplicacion->sock, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_RECIBIO_DATOS)
        procesarRespuesta (contextoAplicacion, interfazRegistro, bufferRespuesta);

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazRegistro_manejarErrorConexion (contextoAplicacion, interfazRegistro);
        puts ("\nSe perdio la conexion con el servidor.");
    }

    // --------------- PUNTO DE INSERCION ---------------

    if ((interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_NOMBRE) ||
        (interfazRegistro->recursosComunesAutenticacionRegistro->estadoFoco == ESCRIBIR_CONTRASENIA ||
         interfazRegistro->estadoFoco == ESCRIBIR_CORREO))
        actualizarPuntoInsercion (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


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


/* ============================================================================================================================================
   FUNCIONES PRIVADAS RESPUESTA SOLICITUD REGISTRO
   ============================================================================================================================================ */


static void extraerDatosRespuestaSolicitudRegistro (const char *respuesta, t_datosRespuestaSolicitudRegistro *returnDatosRespuestaSolicitudRegistro)
{
    memcpy (returnDatosRespuestaSolicitudRegistro, respuesta, sizeof (t_datosRespuestaSolicitudRegistro));
}

static void procesarRespuestaSegunEstadoSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, t_datosRespuestaSolicitudRegistro *datosRespuestaSolicitudRegistro)
{
    switch (datosRespuestaSolicitudRegistro->estadoSolicitud)
    {
        case SOLICITUD_EXITO:
            _interfazRegistro_accederAContactos (contextoAplicacion, interfazRegistro, datosRespuestaSolicitudRegistro);
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            _interfazRegistro_accederAContactos (contextoAplicacion, interfazRegistro, datosRespuestaSolicitudRegistro);
            break;

        case SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE:
            sfText_setString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, "Nombre de usuario ya existente");
            centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
            break;

        case SOLICITUD_ERROR_CORREO_YA_EXISTENTE:
            sfUint32 bufferCorreoYaExistente [] = {'C', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00f3, 'n', 'i', 'c', 'o', ' ', 'y', 'a', ' ', 'e', 'x', 'i', 's', 't', 'e', 'n', 't', 'e', 0};
            sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferCorreoYaExistente);
            centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
            break;

        default:
            break;
    }
}

static void procesarRespuestaSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta)
{
    t_datosRespuestaSolicitudRegistro datosRespuestaSolicitudRegistro;

    extraerDatosRespuestaSolicitudRegistro (respuesta, &datosRespuestaSolicitudRegistro);
    printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudRegistro.header.tipo, datosRespuestaSolicitudRegistro.estadoSolicitud, datosRespuestaSolicitudRegistro.idUsuario);
    procesarRespuestaSegunEstadoSolicitudRegistro (contextoAplicacion, interfazRegistro, &datosRespuestaSolicitudRegistro);
    contextoAplicacion->solicitudEnCurso = false;
}


#include "interfacesGraficas/interfazRegistro/actualizaciones.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuestaSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazRegistro_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta, t_resultadoRecepcion resultadoRecepcion)
{
    t_header header;

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazRegistro_manejarErrorConexion (contextoAplicacion, interfazRegistro);
        puts ("\nSe perdio la conexion con el servidor.");
        return;
    }

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
   FUNCIONES PRIVADAS
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
            contextoAplicacion->usuario.id = datosRespuestaSolicitudRegistro->idUsuario;
            strcpy (contextoAplicacion->usuario.nombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
            contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            sfUint32 bufferDatosInvalidos [] = {'D', 'a', 't', 'o', 's', ' ', 'i', 'n', 'v', 0x00e1, 'l', 'i', 'd', 'o', 's', 0};
            sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferDatosInvalidos);
            centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 180);
            break;

        case SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE:
            sfText_setString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "Nombre de usuario ya existente");
            centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 180);
            break;

        case SOLICITUD_ERROR_CORREO_YA_EXISTENTE:
            sfUint32 bufferCorreoYaExistente [] = {'C', 'o', 'r', 'r', 'e', 'o', ' ', 'e', 'l', 'e', 'c', 't', 'r', 0x00f3, 'n', 'i', 'c', 'o', ' ', 'y', 'a', ' ', 'e', 'x', 'i', 's', 't', 'e', 'n', 't', 'e', 0};
            sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferCorreoYaExistente);
            centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 180);
            break;

        default:
            break;
    }
}

/*
 * Recibe los datos de la respuesta con la estructura de datos t_datosRespuestaSolicitudRegistro.
*/
static void procesarRespuestaSolicitudRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, const char *respuesta)
{
    t_datosRespuestaSolicitudRegistro datosRespuestaSolicitudRegistro;

    extraerDatosRespuestaSolicitudRegistro (respuesta, &datosRespuestaSolicitudRegistro);
    printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudRegistro.header.tipo, datosRespuestaSolicitudRegistro.estadoSolicitud, datosRespuestaSolicitudRegistro.idUsuario);
    procesarRespuestaSegunEstadoSolicitudRegistro (contextoAplicacion, interfazRegistro, &datosRespuestaSolicitudRegistro);
    contextoAplicacion->solicitudEnCurso = false;
}


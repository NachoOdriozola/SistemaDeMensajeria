#include "../../../include/interfacesGraficas/interfazAutenticacion/interfazAutenticacion_actualizaciones.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRespuestaSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazAutenticacion_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta, t_resultadoRecepcion resultadoRecepcion)
{
    char headerTipoRespuesta;

    if (resultadoRecepcion == RECEPCION_ERROR_CONEXION)
    {
        _interfazAutenticacion_manejarErrorConexion (contextoAplicacion, interfazAutenticacion);
        puts ("\nSe perdio la conexion con el servidor.");
        return;
    }

    headerTipoRespuesta = *respuesta;
    switch (headerTipoRespuesta)
    {
        case RESPUESTA_SOLICITUD_AUTENTICACION:
            procesarRespuestaSolicitudAutenticacion (contextoAplicacion, interfazAutenticacion, respuesta);
            break;

        default:
            break;
    }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
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
            contextoAplicacion->usuario.id = datosRespuestaSolicitudAutenticacion->idUsuario;
            strcpy (contextoAplicacion->usuario.nombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
            contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
            break;

        case SOLICITUD_ERROR_CREDENCIALES_INVALIDAS:
            sfUint32 bufferErrorCredenciales [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
            sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferErrorCredenciales);
            centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
            break;

        case SOLICITUD_ERROR_OPERACION_INVALIDA:
            sfText_setString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, "Usuario ya conectado");
            centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
            break;

        default:
            break;
    }
}

/*
 * Recibe los datos de la respuesta con la estructura de datos t_datosRespuestaSolicitudAutenticacion.
*/
static void procesarRespuestaSolicitudAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const char *respuesta)
{
    t_datosRespuestaSolicitudAutenticacion datosRespuestaSolicitudAutenticacion;

    extraerDatosRespuestaSolicitudAutenticacion (respuesta, &datosRespuestaSolicitudAutenticacion);
    printf ("Respuesta recibida: %c|%c|%d\n", datosRespuestaSolicitudAutenticacion.headerTipoRespuesta, datosRespuestaSolicitudAutenticacion.estadoSolicitud, datosRespuestaSolicitudAutenticacion.idUsuario);
    procesarRespuestaSegunEstadoSolicitudAutenticacion (contextoAplicacion, interfazAutenticacion, &datosRespuestaSolicitudAutenticacion);
}


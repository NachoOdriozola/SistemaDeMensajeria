#include "interfacesGraficas/interfazAutenticacion/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool sonDatosAutenticacionUsuarioValidos (const char *nombreUsuario, const char *contrasenia);
static void mostrarErrorCredencialesInvalidas (t_interfazAutenticacion *interfazAutenticacion);

static void resetearInterfaz (t_interfazAutenticacion *interfazAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazAutenticacion_intentarAutenticar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (sonDatosAutenticacionUsuarioValidos (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia))
    {
        if (intentarConectarConServidor (&(contextoAplicacion->sock)) == SOLICITUD_EXITO)
            enviarSolicitudAutenticacion (contextoAplicacion, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia);
        else
            _interfazAutenticacion_manejarErrorConexion (contextoAplicacion, interfazAutenticacion);
    }
    else
        mostrarErrorCredencialesInvalidas (interfazAutenticacion);
}

void _interfazAutenticacion_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    socket_cerrar (&(contextoAplicacion->sock));
    sfUint32 bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorConexion);
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}

void _interfazAutenticacion_accederAContactos (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, t_datosRespuestaSolicitudAutenticacion *datosRespuestaSolicitudAutenticacion)
{
    contextoAplicacion->usuario.id = datosRespuestaSolicitudAutenticacion->idUsuario;
    strcpy (contextoAplicacion->usuario.nombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
    
    contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
}

void _interfazAutenticacion_cambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    omitirEventosPendientes (contextoAplicacion->renderizado);
    resetearInterfaz (interfazAutenticacion);
    
    contextoAplicacion->interfazActual = INTERFAZ_REGISTRO;
    recursosComunesAutenticacionRegistro_activarInterfazRegistro (interfazAutenticacion->recursosComunesAutenticacionRegistro);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
 * Si los datos de autenticacion que envio el usuario son validos segun las restricciones del dominio.
*/
static bool sonDatosAutenticacionUsuarioValidos (const char *nombreUsuario, const char *contrasenia)
{
    return ((strlen (nombreUsuario) >= 3) && 
                (strlen (contrasenia) >= 8) &&
                (!sonTodosEspacios (nombreUsuario)) &&
                (!sonTodosEspacios (contrasenia)));
}

static void mostrarErrorCredencialesInvalidas (t_interfazAutenticacion *interfazAutenticacion)
{
    sfUint32 bufferErrorCredenciales [] = {'N', 'o', 'm', 'b', 'r', 'e', ' ', 'o', ' ', 'c', 'o', 'n', 't', 'r', 'a', 's', 'e', 0x00f1, 'a', ' ', 'i', 'n', 'c', 'o', 'r', 'r', 'e', 'c', 't', 'o', 's', 0};
    sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorCredenciales);
    centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 130);
}


static void resetearInterfaz (t_interfazAutenticacion *interfazAutenticacion)
{
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}

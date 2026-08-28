#include "interfacesGraficas/interfazRegistro/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool sonDatosRegistroUsuarioValidos (t_interfazRegistro *interfazRegistro);
static void mostrarErrorCredencialesInvalidas (t_interfazRegistro *interfazRegistro);

static void resetearInterfaz (t_interfazRegistro *interfazRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazRegsitro_intentarRegistrar (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    if (sonDatosRegistroUsuarioValidos (interfazRegistro))
    {
        if (intentarConectarConServidor (&(contextoAplicacion->sock)) == SOLICITUD_EXITO)
            enviarSolicitudRegistro (contextoAplicacion, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazRegistro->recursosComunesAutenticacionRegistro->logica.contrasenia, interfazRegistro->logica.correoElectronico);
        else
            _interfazRegistro_manejarErrorConexion (contextoAplicacion, interfazRegistro);
    }
    else
        mostrarErrorCredencialesInvalidas (interfazRegistro);
}

void _interfazRegistro_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    socket_cerrar (&(contextoAplicacion->sock));
    sfUint32 bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
    sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferErrorConexion);
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}

void _interfazRegistro_accederAContactos (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro, t_datosRespuestaSolicitudRegistro *datosRespuestaSolicitudRegistro)
{
    contextoAplicacion->usuario.id = datosRespuestaSolicitudRegistro->idUsuario;
    strcpy (contextoAplicacion->usuario.nombre, interfazRegistro->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
    
    contextoAplicacion->interfazActual = INTERFAZ_CONTACTOS;
}

void _interfazRegistro_cambiarAInterfazAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro)
{
    omitirEventosPendientes (contextoAplicacion->renderizado);
    resetearInterfaz (interfazRegistro);

    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
    recursosComunesAutenticacionRegistro_activarInterfazAutenticacion (interfazRegistro->recursosComunesAutenticacionRegistro);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool noEsNombreValido (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((strlen (recursosComunesAutenticacionRegistro->logica.nombreUsuario) < 3) || (sonTodosEspacios (recursosComunesAutenticacionRegistro->logica.nombreUsuario)))
    {
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (160, 100, 90));
        return true;
    }
    return false;
}

static bool noEsContraseniaValida (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    if ((strlen (recursosComunesAutenticacionRegistro->logica.contrasenia) < 8) || (sonTodosEspacios (recursosComunesAutenticacionRegistro->logica.contrasenia)))
    {
        sfText_setColor (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, sfColor_fromRGB (160, 100, 90));
        return true;
    }
    return false;
}

static bool noEsCorreoElectronicoValido (t_interfazRegistro *interfazRegistro)
{
    char *ptr = strchr (interfazRegistro->logica.correoElectronico, '@'); // Se posiciona en el @

    if ((ptr == NULL) ||                                                                    // Si no tiene @
        (ptr == interfazRegistro->logica.correoElectronico) ||         // O empieza con @
        (strchr (ptr, '.') == NULL) ||                                                   // O no tiene un punto despues del @
        (strchr (ptr + 1, '@') != NULL))                                             // O tiene 2 arrobas
    {
        sfText_setColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (160, 100, 90));
        return true;
    }
    return false;
}

/*
 * Verificar si los datos de registro que envio el usuario son validos segun las restricciones del dominio. En caso de no ser validos, se modifica el color del texto grafico de input.
 */
static bool sonDatosRegistroUsuarioValidos (t_interfazRegistro *interfazRegistro)
{
    bool flag = true;

    if (noEsNombreValido (interfazRegistro->recursosComunesAutenticacionRegistro))
        flag = false;

    if (noEsContraseniaValida (interfazRegistro->recursosComunesAutenticacionRegistro))    
        flag = false;

    if (noEsCorreoElectronicoValido (interfazRegistro))
        flag = false;
    
    return flag;
}

/*
 * Procesa la respuesta de la solicitud de registro como estado de credenciales invalidas debido a verificaciones anteriores para evitar enviar solicitudes innecesarias.
*/
static void mostrarErrorCredencialesInvalidas (t_interfazRegistro *interfazRegistro)
{
    sfUint32 bufferDatosInvalidos [] = {'D', 'a', 't', 'o', 's', ' ', 'i', 'n', 'v', 0x00e1, 'l', 'i', 'd', 'o', 's', 0};
    sfText_setUnicodeString (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, bufferDatosInvalidos);
    centrarTextoEnArea (interfazRegistro->recursosComunesAutenticacionRegistro->textos.feedbackUsuario, 0, 440, 500, 180);
}


static void resetearInterfaz (t_interfazRegistro *interfazRegistro)
{
    interfazRegistro->estadoFoco = IR_NINGUNO;
    *(interfazRegistro->logica.correoElectronico) = '\0';

    sfText_setString (interfazRegistro->textos.auxEscribirCorreo, "");
    sfText_setFillColor (interfazRegistro->textos.auxEscribirCorreo, sfColor_fromRGB (53, 53, 53));
}

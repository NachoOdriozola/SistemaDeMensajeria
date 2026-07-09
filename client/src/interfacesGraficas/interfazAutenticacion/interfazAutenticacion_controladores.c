#include "../../../include/interfacesGraficas/interfazAutenticacion/interfazAutenticacion_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void desactivarRecursosInterfazAutenticacion (t_interfazAutenticacion *interfazAutenticacion);

static void posicionarPuntoInsercionBarraEscrituraNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
static void posicionarPuntoInsercionBarraEscrituraContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

static bool sonDatosAutenticacionUsuarioValidos (const char *nombreUsuario, const char *contrasenia);
static t_respuestaAutenticacion fabricarRespuestaAutenticacionInvalida ();
static t_respuestaAutenticacion fabricarRespuestaErrorConexion ();
static void procesarRespuestaSegunEstadoAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const t_respuestaAutenticacion *respuestaAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazAutenticacion_resetear (sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion)
{
    // --------------- RESETEAR INTERFAZ ---------------

    omitirEventosPendientes (renderizado);
    _interfazAutenticacion_deshabilitarFocos (interfazAutenticacion);
}

void _interfazAutenticacion_deshabilitarFocos (t_interfazAutenticacion *interfazAutenticacion)
{
    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = RCAR_NINGUNO;
    interfazAutenticacion->estadoFoco = IA_NINGUNO;
}


bool _interfazAutenticacion_manejarClickEscribirNombre (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.barraEscribirNombre))
        return EVENTO_NO_MANEJADO;

    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_NOMBRE;
    posicionarPuntoInsercionBarraEscrituraNombre (interfazAutenticacion->recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

bool _interfazAutenticacion_manejarClickEscribirContrasenia (const sfRenderWindow *renderizado, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnRectangulo (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.barraEscribirContrasenia))
        return EVENTO_NO_MANEJADO;

    interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco = ESCRIBIR_CONTRASENIA;
    posicionarPuntoInsercionBarraEscrituraContrasenia (interfazAutenticacion->recursosComunesAutenticacionRegistro);

    return EVENTO_MANEJADO;
}

bool _interfazAutenticacion_manejarClickIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    t_respuestaAutenticacion respuestaAutenticacion;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.botonIngresar))
        return EVENTO_NO_MANEJADO;
    _interfazAutenticacion_deshabilitarFocos (interfazAutenticacion);

    if (sonDatosAutenticacionUsuarioValidos (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia))
    {
        if (intentarConectarConServidor (&(contextoAplicacion->sock)) == SOLICITUD_EXITO)
            respuestaAutenticacion = enviarSolicitudAutenticacion (contextoAplicacion->sock, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia);
        else
            respuestaAutenticacion = fabricarRespuestaErrorConexion ();
    }
    else
        respuestaAutenticacion = fabricarRespuestaAutenticacionInvalida ();

    procesarRespuestaSegunEstadoAutenticacion (contextoAplicacion, interfazAutenticacion, &respuestaAutenticacion);

    return EVENTO_MANEJADO;
}

bool _interfazAutenticacion_manejarClickCambiarAInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    if (!clickEnTexto (contextoAplicacion->renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.textoCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    interfazAutenticacion_resetear (contextoAplicacion->renderizado, interfazAutenticacion);
    recursosComunesAutenticacionRegistro_activarInterfazRegistro (interfazAutenticacion->recursosComunesAutenticacionRegistro);
    contextoAplicacion->usuario.interfazActual = INTERFAZ_REGISTRO;

    return EVENTO_MANEJADO;
}


bool _interfazAutenticacion_manejarEscribirNombre (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazAutenticacion->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}

bool _interfazAutenticacion_manejarEscribirContrasenia (t_interfazAutenticacion *interfazAutenticacion, sfEvent eventoChar)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazAutenticacion->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}


bool _interfazAutenticacion_manejarEnterIntentarAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion)
{
    t_respuestaAutenticacion respuestaAutenticacion;

    if ((interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE) &&
        (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA))
        return EVENTO_NO_MANEJADO;

    if (sonDatosAutenticacionUsuarioValidos (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia))
    {
        if (intentarConectarConServidor (&(contextoAplicacion->sock)) == SOLICITUD_EXITO)
            respuestaAutenticacion = enviarSolicitudAutenticacion (contextoAplicacion->sock, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia);
        else
            respuestaAutenticacion = fabricarRespuestaErrorConexion ();
    }
    else
        respuestaAutenticacion = fabricarRespuestaAutenticacionInvalida ();

    procesarRespuestaSegunEstadoAutenticacion (contextoAplicacion, interfazAutenticacion, &respuestaAutenticacion);

    return EVENTO_MANEJADO;
}


bool _interfazAutenticacion_manejarPegarTextoDesdePortapapelesAEscribirNombre (t_interfazAutenticacion *interfazAutenticacion)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_NOMBRE)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, MAX_NOMBRE_USUARIO) == EXITO)
    {
        sfText_setColor (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, sfColor_fromRGB (53, 53, 53));
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirNombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario, 415);
        posicionarPuntoInsercionBarraEscrituraNombre (interfazAutenticacion->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}
 
bool _interfazAutenticacion_manejarPegarTextoDesdePortapapelesAEscribirContrasenia (t_interfazAutenticacion *interfazAutenticacion)
{
    if (interfazAutenticacion->recursosComunesAutenticacionRegistro->estadoFoco != ESCRIBIR_CONTRASENIA)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, MAX_CONTRASENIA) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.contrasenia, 415);
        posicionarPuntoInsercionBarraEscrituraContrasenia (interfazAutenticacion->recursosComunesAutenticacionRegistro);
    }

    return EVENTO_MANEJADO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void posicionarPuntoInsercionBarraEscrituraNombre (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limitesAuxEscribirNombre;

    limitesAuxEscribirNombre = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirNombre);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirNombre.width, 208});
}

static void posicionarPuntoInsercionBarraEscrituraContrasenia (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro)
{
    sfFloatRect limitesAuxEscribirContrasenia;

    limitesAuxEscribirContrasenia = sfText_getGlobalBounds (recursosComunesAutenticacionRegistro->textos.auxEscribirContrasenia);
    sfRectangleShape_setPosition (recursosComunesAutenticacionRegistro->elementos.puntoInsercion, (sfVector2f){44 + limitesAuxEscribirContrasenia.width, 343});
}


static bool noSonTodosEspacios (const char *mensaje)
{
    if (*mensaje == '\0')
        return true;

    while (*mensaje == ' ')
        mensaje ++;

    if (*mensaje == '\0')
        return false;
    return true;
}

/*
 * Si los datos de autenticacion que envio el usuario son validos segun las restricciones del dominio.
*/
static bool sonDatosAutenticacionUsuarioValidos (const char *nombreUsuario, const char *contrasenia)
{
    return ((strlen (nombreUsuario) >= 3) && 
                (strlen (contrasenia) >= 8) &&
                (noSonTodosEspacios (nombreUsuario)) &&
                (noSonTodosEspacios (contrasenia)));
}

/*
 * Fabricar una respuesta de autenticacion invalida en caso de no tener que enviar una solicitud al servidor por la invalidez de los datos.
*/
static t_respuestaAutenticacion fabricarRespuestaAutenticacionInvalida ()
{
    t_respuestaAutenticacion respuestaAutenticacionInvalida = {SOLICITUD_ERROR_CREDENCIALES_INVALIDAS, ID_INVALIDO};
    return respuestaAutenticacionInvalida;
}

/*
 * Fabricar una respuesta de error de conexion en caso de perder la conexion con el servidor.
*/
static t_respuestaAutenticacion fabricarRespuestaErrorConexion ()
{
    t_respuestaAutenticacion respuestaErrorConexion = {SOLICITUD_ERROR_CONEXION, ID_INVALIDO};
    return respuestaErrorConexion;
}

static void procesarRespuestaSegunEstadoAutenticacion (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion, const t_respuestaAutenticacion *respuestaAutenticacion)
{
    switch (respuestaAutenticacion->estado)
    {
        case SOLICITUD_EXITO:
            contextoAplicacion->usuario.id = respuestaAutenticacion->idUsuario;
            strcpy (contextoAplicacion->usuario.nombre, interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.nombreUsuario);
            contextoAplicacion->usuario.interfazActual = INTERFAZ_CONTACTOS;
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

        case SOLICITUD_ERROR_CONEXION:
            socket_cerrar (&(contextoAplicacion->sock));
            sfUint32 bufferErrorConexion [] = {'S', 'e', ' ', 'p', 'e', 'r', 'd', 'i', 0x00f3, ' ', 'l', 'a', ' ', 'c', 'o', 'n', 'e', 'x', 'i', 0x00f3, 'n', ' ', 'c', 'o', 'n', ' ', 'e', 'l', ' ','s', 'e', 'r', 'v', 'i', 'd', 'o', 'r', 0};
            sfText_setUnicodeString (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, bufferErrorConexion);
            centrarTextoEnArea (interfazAutenticacion->recursosComunesAutenticacionRegistro->textos.ingresoIncorrecto, 0, 440, 500, 130);
            break;

        default:
            break;
    }
}



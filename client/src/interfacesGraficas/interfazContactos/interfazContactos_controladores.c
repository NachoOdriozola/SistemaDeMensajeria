#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool esUnComando (const char *mensaje);

static void realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static void realizarEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazContactos_resetear (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    // --------------- RESETEAR INTERFAZ ---------------

    omitirEventosPendientes (renderizado);
    interfazContactos->logica.idUsuarioDelChatSeleccionado = ID_INVALIDO; // Establecer un id invalido al usuario del chat seleccionado
    *(interfazContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';
    _interfazContactos_deshabilitarFocos (interfazContactos);

    // --------------- RESETEAR TEXTOS ---------------

    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, "");
    sfText_setString (interfazContactos->textos.textoInformativoSeleccionChat, "Seleccione un chat con un usuario");

    // --------------- RESETEAR LISTA DE MENSAJES ---------------

    recursosComunesContactosSalas_vaciarListaMensajes (&(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes));
}

void _interfazContactos_deshabilitarFocos (t_interfazContactos *interfazContactos)
{
    interfazContactos->recursosComunesContactosSalas->estadoFoco = RCCS_NINGUNO;
    interfazContactos->estadoFoco = ICT_NINGUNO;
}


bool _interfazContactos_manejarClickEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazContactos->recursosComunesContactosSalas->elementos.botonEnviar))
        return EVENTO_NO_MANEJADO;

    if (esUnComando (interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje))
        realizarSeleccionChat (contextoAplicacion, interfazContactos);
    else
        realizarEnvioMensaje (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}

bool _interfazContactos_manejarClickCambiarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    sfEvent evento;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazContactos->recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    if (contextoAplicacion->solicitudEnCurso)
        sfText_setString (interfazContactos->recursosComunesContactosSalas->textos.textoFeedbackUsuario, "No se puede cambiar de interfaz, hay una solicitud en curso . . .");
    else
    {
        interfazContactos_resetear (contextoAplicacion->renderizado, interfazContactos);
        recursosComunesContactosSalas_activarInterfazSalas (interfazContactos->recursosComunesContactosSalas);
        contextoAplicacion->interfazActual = INTERFAZ_SALAS;
    }

    return EVENTO_MANEJADO;
}


bool _interfazContactos_manejarEnterEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (interfazContactos->recursosComunesContactosSalas->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (esUnComando (interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje))
        realizarSeleccionChat (contextoAplicacion, interfazContactos);
    else
        realizarEnvioMensaje (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}


void _interfazContactos_resetearBarraDeEscritura (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    *(recursosComunesContactosSalas->logica.contextoMensajes.mensaje) = '\0';
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, "");
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451, 942});
}


void _interfazContactos_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    interfazContactos_resetear (contextoAplicacion->renderizado, interfazContactos);
    //resetear los rc tambien
    socket_cerrar (&(contextoAplicacion->sock));
    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool esUnComando (const char *mensaje)
{
    return  (*mensaje == '/');
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


static bool esNombreValido (const char *nombreUsuarioChatSeleccionado)
{
    int largoNombreUsuarioChatSeleccionado = strlen (nombreUsuarioChatSeleccionado);

    return ((largoNombreUsuarioChatSeleccionado >= 3) && (largoNombreUsuarioChatSeleccionado < MAX_NOMBRE_USUARIO));
}

static bool usuarioNoSeleccionoSuPropioChat (const char *nombreUsuarioPropio, const char *nombreUsuarioChatSeleccionado)
{
    return (strcmp (nombreUsuarioPropio, nombreUsuarioChatSeleccionado) != 0);
}

static bool noEsChatYaSeleccionado (const char *nombreUsuarioChatYaSeleccionado, const char *nombreUsuarioChatASeleccionar)
{
    return (strcmp (nombreUsuarioChatYaSeleccionado, nombreUsuarioChatASeleccionar) != 0);
}

/*
 * Si los datos de seleccion de chat que envio el usuario son validos segun las restricciones del dominio.
*/
static bool sonDatosSeleccionChatValidos (t_interfazContactos *interfazContactos, const char *nombreUsuarioPropio)
{
    char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje[1]);

    return ((esNombreValido (nombreUsuarioChatSeleccionadoSinBarraDeComando)) &&
                (noSonTodosEspacios (nombreUsuarioChatSeleccionadoSinBarraDeComando)) && 
                (usuarioNoSeleccionoSuPropioChat (nombreUsuarioPropio, nombreUsuarioChatSeleccionadoSinBarraDeComando)) &&
                (noEsChatYaSeleccionado (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, nombreUsuarioChatSeleccionadoSinBarraDeComando)));
}

static void realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje[1]);

    if (sonDatosSeleccionChatValidos (interfazContactos, contextoAplicacion->usuario.nombre))
        enviarSolicitudSeleccionChat (contextoAplicacion, nombreUsuarioChatSeleccionadoSinBarraDeComando);
}


static bool noEsMensajeVacio (const char *mensaje)
{
    return (*mensaje != '\0');
}

static bool sonEmisorYReceptorValidos (int idEmisor, int idReceptor)
{
    return ((idEmisor != ID_INVALIDO) && (idReceptor != ID_INVALIDO));
}

static bool elEmisorNoEsElReceptor (int idEmisor, int idReceptor)
{
    return (idEmisor != idReceptor);
}

/*
 * Si los datos de envio de mensaje que envio el usuario son validos segun las restricciones del dominio.
*/
static bool sonDatosEnvioMensajeValidos (int idUsuario, int idUsuarioDelChatSeleccionado, const char *mensaje)
{
    return ((noEsMensajeVacio (mensaje)) && 
                (noSonTodosEspacios (mensaje)) && 
                (sonEmisorYReceptorValidos (idUsuario, idUsuarioDelChatSeleccionado)) && 
                (elEmisorNoEsElReceptor (idUsuario, idUsuarioDelChatSeleccionado)));
}

static void realizarEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (sonDatosEnvioMensajeValidos (contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje))
        enviarSolicitudEnvioMensaje (contextoAplicacion, contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje);
}


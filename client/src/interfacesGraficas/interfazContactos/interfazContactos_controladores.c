#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void desactivarRecursosInterfazContactos (t_interfazContactos *interfazContactos);

static bool esUnComando (const char *mensaje);

static void realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static void realizarEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static void resetearBarraDeEscritura (t_recursosComunesContactosSalas *recursosComunesContactosSalas);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


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

    resetearBarraDeEscritura (interfazContactos->recursosComunesContactosSalas);

    return EVENTO_MANEJADO;
}

bool _interfazContactos_manejarClickCambiarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    sfEvent evento;

    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazContactos->recursosComunesContactosSalas->elementos.solapaCambiarInterfaz))
        return EVENTO_NO_MANEJADO;

    omitirEventosPendientes (contextoAplicacion->renderizado);
    desactivarRecursosInterfazContactos (interfazContactos);
    recursosComunesContactosSalas_activarInterfazSalas (interfazContactos->recursosComunesContactosSalas);
    contextoAplicacion->usuario.interfazActual = INTERFAZ_SALAS;

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

    resetearBarraDeEscritura (interfazContactos->recursosComunesContactosSalas);

    return EVENTO_MANEJADO;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void resetearInterfaz (t_interfazContactos *interfazContactos)
{
    // Establecer un id invalido al usuario del chat seleccionado
    interfazContactos->logica.idUsuarioDelChatSeleccionado = ID_INVALIDO;

    // Setear cadena vacia
    *(interfazContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';

    // Deshabilitar foco
    interfazContactos->estadoFoco = ICT_NINGUNO;
}

/*
 * Desactivar y resetear los recursos de la interfaz de contactos en situaciones que la interfaz no continue con su actividad.
 */
static void desactivarRecursosInterfazContactos (t_interfazContactos *interfazContactos)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    resetearInterfaz (interfazContactos);
}


static bool esUnComando (const char *mensaje)
{
    return  (*mensaje == '/');
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
                (usuarioNoSeleccionoSuPropioChat (nombreUsuarioPropio, nombreUsuarioChatSeleccionadoSinBarraDeComando)) &&
                (noEsChatYaSeleccionado (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, nombreUsuarioChatSeleccionadoSinBarraDeComando)));
}

/*
 * Fabricar una respuesta de seleccion de chat invalida en caso de no tener que enviar una solicitud al servidor por la invalidez de los datos.
*/
static t_respuestaSeleccionChat fabricarRespuestaSeleccionChatInvalida ()
{
    t_respuestaSeleccionChat respuestaSeleccionChatInvalida = {SOLICITUD_ERROR_OPERACION_INVALIDA, ID_INVALIDO};
    return respuestaSeleccionChatInvalida;
}

static void setearNuevoChatLogicamente (t_interfazContactos *interfazContactos, const t_respuestaSeleccionChat *respuestaSeleccionChat)
{
    interfazContactos->logica.idUsuarioDelChatSeleccionado = respuestaSeleccionChat->idUsuarioChatSeleccionado;
    strcpy (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, &(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje[1]));
}

static void setearNuevoChatGraficamente (t_interfazContactos *interfazContactos)
{
    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, interfazContactos->logica.nombreUsuarioDelChatSeleccionado);
    centrarTextoEnArea (interfazContactos->textos.auxContactoSeleccionado, 852, 25, 600, 40);
    mapListaCircular (&(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.listaMensajes), vaciarMensaje);
}

static void procesarSegunRespuestaSeleccionChat (t_interfazContactos *interfazContactos, t_respuestaSeleccionChat *respuestaSeleccionChat)
{
    if (respuestaSeleccionChat->estado == SOLICITUD_EXITO)
    {
        setearNuevoChatLogicamente (interfazContactos, respuestaSeleccionChat);
        setearNuevoChatGraficamente (interfazContactos);
    }
}

static void realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    t_respuestaSeleccionChat respuestaSeleccionChat;
    char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje[1]);

    if (sonDatosSeleccionChatValidos (interfazContactos, contextoAplicacion->usuario.nombre))
        respuestaSeleccionChat = enviarSolicitudSeleccionChat (contextoAplicacion->sock, nombreUsuarioChatSeleccionadoSinBarraDeComando);
    else
        respuestaSeleccionChat = fabricarRespuestaSeleccionChatInvalida ();

    procesarSegunRespuestaSeleccionChat (interfazContactos, &respuestaSeleccionChat);
}


static bool noEsMensajeVacio (const char *mensaje)
{
    return (mensaje != NULL);
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
    return ((noEsMensajeVacio (mensaje)) && (sonEmisorYReceptorValidos (idUsuario, idUsuarioDelChatSeleccionado)) && (elEmisorNoEsElReceptor (idUsuario, idUsuarioDelChatSeleccionado)));
}

static void procesarSegunRespuestaEnvioMensaje (t_interfazContactos *interfazContactos, char *estadoRespuestaEnvioMensaje)
{
    if (*estadoRespuestaEnvioMensaje == SOLICITUD_EXITO)
        insertarMensaje (&(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes), interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje, MENSAJE_PROPIO);
}

static void realizarEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    char estadoRespuestaEnvioMensaje;

    if (sonDatosEnvioMensajeValidos (contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje))
        estadoRespuestaEnvioMensaje = enviarSolicitudEnvioMensaje (contextoAplicacion->sock, contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes.mensaje);
    else
        estadoRespuestaEnvioMensaje = SOLICITUD_ERROR_OPERACION_INVALIDA;

    procesarSegunRespuestaEnvioMensaje (interfazContactos, &estadoRespuestaEnvioMensaje);
}


static void resetearBarraDeEscritura (t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    *(recursosComunesContactosSalas->logica.contextoMensajes.mensaje) = '\0';
    sfText_setString (recursosComunesContactosSalas->textos.auxEscribirMensaje, "");
    sfRectangleShape_setPosition (recursosComunesContactosSalas->elementos.puntoInsercion, (sfVector2f){451, 942});
}


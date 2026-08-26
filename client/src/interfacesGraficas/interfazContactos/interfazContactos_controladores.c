#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos_controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool esUnComando (const char *mensaje);

static void realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static void realizarEnvioMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);



static void posicionarPuntoInsercion (t_interfazContactos *interfazContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazContactos_deshabilitarFocos (t_interfazContactos *interfazContactos)
{
    interfazContactos->estadoFoco = ICT_NINGUNO;
}


bool _interfazContactos_manejarClickEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazContactos->elementos.botonEnviar))
        return EVENTO_NO_MANEJADO;

    if (esUnComando (interfazContactos->logica.contextoMensajes.mensaje))
        realizarSeleccionChat (contextoAplicacion, interfazContactos);
    else
        realizarEnvioMensaje (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}


bool _interfazContactos_manejarEnterEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (esUnComando (interfazContactos->logica.contextoMensajes.mensaje))
        realizarSeleccionChat (contextoAplicacion, interfazContactos);
    else
        realizarEnvioMensaje (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}


void _interfazContactos_resetearBarraDeEscritura (t_interfazContactos *interfazContactos)
{
    *(interfazContactos->logica.contextoMensajes.mensaje) = '\0';
    sfText_setString (interfazContactos->textos.auxEscribirMensaje, "");
    sfRectangleShape_setPosition (interfazContactos->elementos.puntoInsercion, (sfVector2f){451, 942});
}


void interfazContactos_resetear (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    // --------------- RESETEAR INTERFAZ ---------------

    omitirEventosPendientes (renderizado);
    interfazContactos->logica.idUsuarioDelChatSeleccionado = ID_INVALIDO; // Establecer un id invalido al usuario del chat seleccionado
    *(interfazContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';
    _interfazContactos_deshabilitarFocos (interfazContactos);

    // --------------- RESETEAR TEXTOS ---------------

    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, "");
    sfText_setString (interfazContactos->textos.informacionSeleccionChat, "Seleccione un chat con un usuario");

    // --------------- RESETEAR LISTA DE MENSAJES ---------------

    interfazContactos_vaciarListaMensajes (&(interfazContactos->logica.contextoMensajes));
}

void _interfazContactos_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    interfazContactos_resetear (contextoAplicacion->renderizado, interfazContactos);
    socket_cerrar (&(contextoAplicacion->sock));
    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
}


void _interfazContactos_manejarRedimensionamientoVentana (sfRenderWindow *renderizado, t_interfazContactosVistas *vistas, sfEvent eventoRedimensionamiento)
{
    sfVector2u nuevoTamVentana;

    if (eventoRedimensionamiento.size.width < ANCHO_MINIMO_VENTANA)
        nuevoTamVentana.x = ANCHO_MINIMO_VENTANA;
    else
        nuevoTamVentana.x = eventoRedimensionamiento.size.width;

    if (eventoRedimensionamiento.size.height < ALTO_MINIMO_VENTANA)
        nuevoTamVentana.y = ALTO_MINIMO_VENTANA;
    else
        nuevoTamVentana.y = eventoRedimensionamiento.size.height;

    sfRenderWindow_setSize (renderizado, nuevoTamVentana);

    // Redimensionar vista UI.
    sfView_setSize (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});
}


void _interfazContactos_establecerNombreUsuario (t_interfazContactos *interfazContactos, const char *nombreUsuario)
{
    sfText_setString (interfazContactos->textos.nombreUsuario, nombreUsuario);
}

void _interfazContactos_posicionarNombreUsuario (t_interfazContactos *interfazContactos)
{
    sfFloatRect limitesNombreUsuario;
    unsigned short int pixeles = 32;
    
    do
    {
        sfText_setCharacterSize (interfazContactos->textos.nombreUsuario, pixeles);
        centrarTextoEnArea (interfazContactos->textos.nombreUsuario, 44, 888, 254, 120);
        limitesNombreUsuario = sfText_getLocalBounds (interfazContactos->textos.nombreUsuario);
        pixeles -= 2;
    } while (limitesNombreUsuario.width > 254);
}






bool _interfazContactos_manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (renderizado, interfazContactos->elementos.barraEscribirMensaje))
        return EVENTO_NO_MANEJADO;

    interfazContactos->estadoFoco = ESCRIBIR_MENSAJE;
    posicionarPuntoInsercion (interfazContactos);

    return EVENTO_MANEJADO;
}

bool _interfazContactos_manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (renderizado, interfazContactos->elementos.areaMensajes))
        return EVENTO_NO_MANEJADO;

    interfazContactos->estadoFoco = AREA_MENSAJES;

    return EVENTO_MANEJADO;
}


bool _interfazContactos_manejarEscribirMensaje (t_interfazContactos *interfazContactos, sfEvent eventoChar)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (ingresarCaracterABuffer (interfazContactos->logica.contextoMensajes.mensaje, MAX_MENSAJE, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazContactos->textos.auxEscribirMensaje, interfazContactos->logica.contextoMensajes.mensaje, 1250);
        posicionarPuntoInsercion (interfazContactos);
    }

    return EVENTO_MANEJADO;
}


bool _interfazContactos_manejarPegarTextoDesdePortapapelesAEscribirMensaje (t_interfazContactos *interfazContactos)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazContactos->logica.contextoMensajes.mensaje, MAX_MENSAJE) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazContactos->textos.auxEscribirMensaje, interfazContactos->logica.contextoMensajes.mensaje, 1250);
        posicionarPuntoInsercion (interfazContactos);
    }

    return EVENTO_MANEJADO;
}


bool _interfazContactos_manejarDesplazarArribaAreaMensajes (t_interfazContactos *interfazContactos)
{
    sfVector2f tamVista, posCentroVista;
    sfVector2f posUltimoMensaje;

    if (interfazContactos->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (interfazContactos->vistas.mensajes);
    posCentroVista = sfView_getCenter (interfazContactos->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)(interfazContactos->logica.contextoMensajes.ultimoMensaje->dato)));

    if (posCentroVista.y - tamVista.y / 2.f > posUltimoMensaje.y)
        sfView_move (interfazContactos->vistas.mensajes, (sfVector2f){0, -VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}

bool _interfazContactos_manejarDesplazarAbajoAreaMensajes (t_interfazContactos *interfazContactos)
{
    sfVector2f tamVista, posCentroVista;

    if (interfazContactos->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (interfazContactos->vistas.mensajes);
    posCentroVista = sfView_getCenter (interfazContactos->vistas.mensajes);

    if (posCentroVista.y + tamVista.y / 2.f < 870)
        sfView_move (interfazContactos->vistas.mensajes, (sfVector2f){0, VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}


bool _interfazContactos_manejarScrollAreaMensajes (t_interfazContactos *interfazContactos, sfEvent eventoScroll)
{
    sfVector2f tamVista, posCentro;
    sfVector2f posUltimoMensaje;
    float desplazamientoY;
    float superiorVista, inferiorVista;
    float limiteSuperior, limiteInferior;

    if (interfazContactos->estadoFoco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (interfazContactos->vistas.mensajes);
    posCentro = sfView_getCenter (interfazContactos->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)(interfazContactos->logica.contextoMensajes.ultimoMensaje->dato)));

    desplazamientoY = -eventoScroll.mouseWheelScroll.delta * VELOCIDAD_SCROLL;

    superiorVista = posCentro.y - tamVista.y / 2.f;
    inferiorVista = posCentro.y + tamVista.y / 2.f;

    limiteSuperior = posUltimoMensaje.y;
    limiteInferior = 870;

    if ((desplazamientoY < 0) && (superiorVista + desplazamientoY < limiteSuperior))
        desplazamientoY = limiteSuperior - superiorVista;

    if ((desplazamientoY > 0) && (inferiorVista + desplazamientoY > limiteInferior))
        desplazamientoY = limiteInferior - inferiorVista;

    if (desplazamientoY != 0)
        sfView_move (interfazContactos->vistas.mensajes, (sfVector2f){0, desplazamientoY});

    return EVENTO_MANEJADO;
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
    char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->logica.contextoMensajes.mensaje[1]);

    return ((esNombreValido (nombreUsuarioChatSeleccionadoSinBarraDeComando)) &&
                (noSonTodosEspacios (nombreUsuarioChatSeleccionadoSinBarraDeComando)) && 
                (usuarioNoSeleccionoSuPropioChat (nombreUsuarioPropio, nombreUsuarioChatSeleccionadoSinBarraDeComando)) &&
                (noEsChatYaSeleccionado (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, nombreUsuarioChatSeleccionadoSinBarraDeComando)));
}

static void realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->logica.contextoMensajes.mensaje[1]);

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
    if (sonDatosEnvioMensajeValidos (contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->logica.contextoMensajes.mensaje))
        enviarSolicitudEnvioMensaje (contextoAplicacion, contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->logica.contextoMensajes.mensaje);
}




static void posicionarPuntoInsercion (t_interfazContactos *interfazContactos)
{
    sfFloatRect limitesAuxEscribirMensaje;

    limitesAuxEscribirMensaje = sfText_getGlobalBounds (interfazContactos->textos.auxEscribirMensaje);
    sfRectangleShape_setPosition (interfazContactos->elementos.puntoInsercion, (sfVector2f){451 + limitesAuxEscribirMensaje.width, 942});
}


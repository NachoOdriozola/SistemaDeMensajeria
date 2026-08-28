#include "interfacesGraficas/interfazContactos/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool sonDatosSeleccionChatValidos (const t_interfazContactos *interfazContactos, const char *nombreUsuarioPropio);

static bool sonDatosEnvioMensajeValidos (int idUsuario, int idUsuarioDelChatSeleccionado, const char *mensaje);

static void resetearInterfaz (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);

static void configurarMensaje (sfText *mensajeGrafico, const sfFont *fuente);
static void establecerTextoConSaltosDeLineaAlMensaje (sfText *mensajeGrafico, const char *cadenaMensaje, float anchoMaxMensaje);
static void desplazarHaciaArribaTodosLosMensajes (t_listaDoble *mensajes, float desplazamientoY);
static void establecerPosicionMensajeSegunOrigen (sfText *mensaje, t_origenMensaje origenMensaje);
static bool esElPrimerMensaje (t_contextoMensajes *contextoMensajes);
static void guardarSuReferencia (t_contextoMensajes *contextoMensajes);
static void liberarMensaje (void *mensaje);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


bool _interfazContactos_esUnComando (const char *mensaje)
{
    return  (*mensaje == '/');
}

void _interfazContactos_realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos)
{
    const char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->logica.contextoMensajes.mensaje[1]);

    if (sonDatosSeleccionChatValidos (interfazContactos, contextoAplicacion->usuario.nombre))
        enviarSolicitudSeleccionChat (contextoAplicacion, nombreUsuarioChatSeleccionadoSinBarraDeComando);
}

void _interfazContactos_realizarEnvioMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos)
{
    if (sonDatosEnvioMensajeValidos (contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->logica.contextoMensajes.mensaje))
        enviarSolicitudEnvioMensaje (contextoAplicacion, contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->logica.contextoMensajes.mensaje);
}


void _interfazContactos_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    resetearInterfaz (contextoAplicacion->renderizado, interfazContactos);
    socket_cerrar (&(contextoAplicacion->sock));
    *(contextoAplicacion->usuario.nombre) = '\0';
    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
}


void _interfazContactos_setearNuevoChatSeleccionado (t_interfazContactos *interfazContactos, const t_datosRespuestaSolicitudSeleccionChat *datosRespuestaSolicitudSeleccionChat)
{
    // LOGICAMENTE
    interfazContactos->logica.idUsuarioDelChatSeleccionado = datosRespuestaSolicitudSeleccionChat->idUsuarioDelChatSeleccionado;
    strcpy (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, &(interfazContactos->logica.contextoMensajes.mensaje[1]));

    // GRAFICAMENTE
    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, interfazContactos->logica.nombreUsuarioDelChatSeleccionado);
    centrarTextoEnArea (interfazContactos->textos.auxContactoSeleccionado, 852, 25, 600, 40);
    _interfazContactos_listaMensajes_vaciar (&(interfazContactos->logica.contextoMensajes));
    sfText_setString (interfazContactos->textos.informacionSeleccionChat, "");
}


void _interfazContactos_listaMensajes_crear (t_contextoMensajes *contextoMensajes)
{
    crearListaDoble (&(contextoMensajes->mensajes));
    contextoMensajes->ultimoMensaje = NULL;
}

t_codigoRetorno _interfazContactos_listaMensajes_insertarMensaje (t_contextoMensajes *contextoMensajes, const char *mensaje, t_origenMensaje origenMensaje, const t_interfazContactosFuentes *fuentes)
{
    sfText *mensajeGrafico;

    mensajeGrafico = sfText_create ();
    if (!mensajeGrafico)
    {
        perror ("\nERROR - Interfaz contactos, crear mensaje grafico.\n");
        return ERROR_SIN_MEMORIA;
    } 
    configurarMensaje (mensajeGrafico, fuentes->cuerpo);
    establecerTextoConSaltosDeLineaAlMensaje (mensajeGrafico, mensaje, 700);
    desplazarHaciaArribaTodosLosMensajes (&(contextoMensajes->mensajes), (sfText_getLocalBounds (mensajeGrafico)).height + 35);
    establecerPosicionMensajeSegunOrigen (mensajeGrafico, origenMensaje);
    if (insertarAlInicioListaDoble (&(contextoMensajes->mensajes), &mensajeGrafico, sizeof (sfText*)) != 0) // 0 es exito.
        return ERROR_SIN_MEMORIA;
    if (esElPrimerMensaje (contextoMensajes))
        guardarSuReferencia (contextoMensajes);

    return EXITO;
}

void _interfazContactos_listaMensajes_vaciar (t_contextoMensajes *contextoMensajes)
{
    vaciarListaDobleConAccion (&(contextoMensajes->mensajes), liberarMensaje);
    contextoMensajes->ultimoMensaje = NULL;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */

   
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

static bool sonDatosSeleccionChatValidos (const t_interfazContactos *interfazContactos, const char *nombreUsuarioPropio)
{
    const char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->logica.contextoMensajes.mensaje[1]);

    return ((esNombreValido (nombreUsuarioChatSeleccionadoSinBarraDeComando)) &&
                (!sonTodosEspacios (nombreUsuarioChatSeleccionadoSinBarraDeComando)) && 
                (usuarioNoSeleccionoSuPropioChat (nombreUsuarioPropio, nombreUsuarioChatSeleccionadoSinBarraDeComando)) &&
                (noEsChatYaSeleccionado (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, nombreUsuarioChatSeleccionadoSinBarraDeComando)));
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

static bool sonDatosEnvioMensajeValidos (int idUsuario, int idUsuarioDelChatSeleccionado, const char *mensaje)
{
    return ((noEsMensajeVacio (mensaje)) && 
                (!sonTodosEspacios (mensaje)) && 
                (sonEmisorYReceptorValidos (idUsuario, idUsuarioDelChatSeleccionado)) && 
                (elEmisorNoEsElReceptor (idUsuario, idUsuarioDelChatSeleccionado)));
}



static void resetearInterfaz (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    // --------------- RESETEAR INTERFAZ ---------------

    omitirEventosPendientes (renderizado);
    interfazContactos->logica.idUsuarioDelChatSeleccionado = ID_INVALIDO; // Establecer un id invalido al usuario del chat seleccionado
    *(interfazContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';
    *(interfazContactos->logica.contextoMensajes.mensaje) = '\0';
    interfazContactos->estadoFoco = ICT_NINGUNO;

    // --------------- RESETEAR TEXTOS ---------------

    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, "");
    sfText_setString (interfazContactos->textos.auxEscribirMensaje, "");
    sfText_setString (interfazContactos->textos.feedbackUsuario, "");
    sfText_setString (interfazContactos->textos.nombreUsuario, "");
    sfText_setString (interfazContactos->textos.informacionSeleccionChat, "Seleccione un chat con un usuario");

    // --------------- RESETEAR LISTA DE MENSAJES ---------------

    _interfazContactos_listaMensajes_vaciar (&(interfazContactos->logica.contextoMensajes));
}



/*
 * Aun no establece la posicion en ventana ni el contenido del mensaje.
*/
static void configurarMensaje (sfText *mensajeGrafico, const sfFont *fuente)
{
    sfText_setFont (mensajeGrafico, fuente);
    sfText_setFillColor (mensajeGrafico, sfColor_fromRGB (53, 53, 53));
    sfText_setCharacterSize (mensajeGrafico, 22);
    sfText_setLineSpacing (mensajeGrafico, 1.3);
}

static int encontrarUnaPalabraYRetornarSuLargo (const char *cadena)
{
    int largoPalabra = 0;

    while ((cadena[largoPalabra] != '\0') && (cadena[largoPalabra] != ' '))
        largoPalabra++;

    return largoPalabra;
}

static bool palabraSobrepasoAnchoPermitido (sfVector2f posUltimoCaracter, float anchoMaxMensaje)
{
    return (posUltimoCaracter.x >= anchoMaxMensaje);
}

static void agregarSaltoDeLinea (char *cadena)
{
    strcat (cadena, "\n");
}

/*
 * Si la palabra sobrepasa el ancho permitido, agrega un salto de linea.
*/
static void procesarPalabra (sfText *mensajeGrafico, const char *cadenaMensaje, char *auxCadenaMensaje, float anchoMaxMensaje, int largoPalabra)
{
    int largoAuxCadenaMensaje, i;
    sfVector2f posUltimoCaracter;

    for (i = 0; i < largoPalabra; i++)
    {
        largoAuxCadenaMensaje = strlen (auxCadenaMensaje);

        auxCadenaMensaje[largoAuxCadenaMensaje] = cadenaMensaje[i];
        auxCadenaMensaje[largoAuxCadenaMensaje + 1] = '\0';

        sfText_setString (mensajeGrafico, auxCadenaMensaje);
        posUltimoCaracter = sfText_findCharacterPos (mensajeGrafico, largoAuxCadenaMensaje + 1);

        if (palabraSobrepasoAnchoPermitido (posUltimoCaracter, anchoMaxMensaje))
            agregarSaltoDeLinea (auxCadenaMensaje);
    }
}

static void encontrarPrimerCaracterProximaPalabra (const char **cadenaMensaje, char *auxCadenaMensaje, int largoUltimaPalabra)
{
    (*cadenaMensaje) += largoUltimaPalabra;
    while (**cadenaMensaje == ' ')
    {
        strcat (auxCadenaMensaje, " ");
        (*cadenaMensaje) ++;
    }
}

/*
* El ancho maximo del mensaje tiene que ser enviado en pixeles.
*/
static void establecerTextoConSaltosDeLineaAlMensaje (sfText *mensajeGrafico, const char *cadenaMensaje, float anchoMaxMensaje)
{
    char auxCadenaMensaje [MAX_MENSAJE + 100] = ""; // Almacena la cadena del mensaje mas los saltos de linea a agregar.
    int largoPalabra;

    sfText_setPosition (mensajeGrafico, (sfVector2f){0, 0}); // Establece una posicion ficticia al mensaje para que pueda ser procesado.

    while (*cadenaMensaje != '\0')
    {
        largoPalabra = encontrarUnaPalabraYRetornarSuLargo (cadenaMensaje);
        procesarPalabra (mensajeGrafico, cadenaMensaje, auxCadenaMensaje, anchoMaxMensaje, largoPalabra);
        encontrarPrimerCaracterProximaPalabra (&cadenaMensaje, auxCadenaMensaje, largoPalabra);
    }

    sfText_setString(mensajeGrafico, auxCadenaMensaje);
}

static void modificarPosMensaje (void *mensaje, void *desplazamientoY)
{
    sfVector2f pos;

    pos = sfText_getPosition (*((sfText**)mensaje));
    pos.y -= *((float*)desplazamientoY);
    sfText_setPosition (*((sfText**)mensaje), pos);
}

static void desplazarHaciaArribaTodosLosMensajes (t_listaDoble *mensajes, float desplazamientoY)
{
    mapListaDobleConComplemento (mensajes, modificarPosMensaje, &desplazamientoY);
}

static void establecerPosicionMensajeSegunOrigen (sfText *mensaje, t_origenMensaje origenMensaje)
{
    sfFloatRect limitesMensaje = sfText_getLocalBounds (mensaje);

    if (origenMensaje == MENSAJE_PROPIO)
        sfText_setPosition (mensaje, (sfVector2f){1824 - limitesMensaje.width - limitesMensaje.left, 825 - limitesMensaje.height});
    else
        sfText_setPosition (mensaje, (sfVector2f){485, 825 - limitesMensaje.height});
}

static bool esElPrimerMensaje (t_contextoMensajes *contextoMensajes)
{
    return (contextoMensajes->ultimoMensaje == NULL);
}

static void guardarSuReferencia (t_contextoMensajes *contextoMensajes)
{
    contextoMensajes->ultimoMensaje = contextoMensajes->mensajes;
}

static void liberarMensaje (void *mensaje)
{
    DESTRUCTOR_SEGURO_TEXTO (*((sfText**)mensaje));
}


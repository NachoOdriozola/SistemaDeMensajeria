#include "interfacesGraficas/interfazContactos/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static _t_resultado_validacionDatosSeleccionChat validarDatosSeleccionChat (const t_interfazContactos *interfazContactos, const char *nombreUsuarioPropio);
static _t_resultado_validacionDatosEnvioMensaje validarDatosEnvioMensaje (const t_interfazContactos *interfazContactos, int idUsuario);

static void resetearInterfaz (t_interfazContactos *interfazContactos);

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

_t_resultado_intentarSeleccionarChat _interfazContactos_intentar_seleccionarChat (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos)
{
    _t_resultado_intentarSeleccionarChat resultado_intentarSeleccionarChat;
    const char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->logica.contextoMensajes.mensaje[1]);

    resultado_intentarSeleccionarChat.validacion = validarDatosSeleccionChat (interfazContactos, contextoAplicacion->usuario.nombre);
    if (resultado_intentarSeleccionarChat.validacion == INTENTARSELECCIONARCHAT_RESULTADODATOS_EXITO)
    {
        resultado_intentarSeleccionarChat.tipo = INTENTARSELECCIONARCHAT_RESULTADO_EXITO;
        enviarSolicitudSeleccionChat (contextoAplicacion, nombreUsuarioChatSeleccionadoSinBarraDeComando);
    }
    else
        resultado_intentarSeleccionarChat.tipo = INTENTARSELECCIONARCHAT_RESULTADO_DATOS_INVALIDOS;

    return resultado_intentarSeleccionarChat;
}

_t_resultado_intentarEnviarMensaje _interfazContactos_intentar_enviarMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos)
{
    _t_resultado_intentarEnviarMensaje resultado_intentarEnviarMensaje;

    resultado_intentarEnviarMensaje.validacion = validarDatosEnvioMensaje (interfazContactos, contextoAplicacion->usuario.id);
    if (resultado_intentarEnviarMensaje.validacion == INTENTARENVIARMENSAJE_RESULTADODATOS_EXITO)
    {
        resultado_intentarEnviarMensaje.tipo = INTENTARENVIARMENSAJE_RESULTADO_EXITO;
        enviarSolicitudEnvioMensaje (contextoAplicacion, contextoAplicacion->usuario.id, interfazContactos->logica.idUsuarioDelChatSeleccionado, interfazContactos->logica.contextoMensajes.mensaje);
    }
    else
        resultado_intentarEnviarMensaje.tipo = INTENTARENVIARMENSAJE_RESULTADO_DATOS_INVALIDOS;

    return resultado_intentarEnviarMensaje;
}


_t_datosUI_respuesta_solicitudEnvioMensaje _interfazContactos_solicitudEnvioMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta)
{
    t_datosRespuestaSolicitudEnvioMensaje datos_respuesta_solicitudEnvioMensaje;
    _t_datosUI_respuesta_solicitudEnvioMensaje datosUI_respuesta_solicitudEnvioMensaje;

    comunicacion_extraerDatosRespuesta_solicitudEnvioMensaje (respuesta, &datos_respuesta_solicitudEnvioMensaje);
    printf ("Respuesta recibida: %c|%c\n", datos_respuesta_solicitudEnvioMensaje.header.tipo, datos_respuesta_solicitudEnvioMensaje.estadoSolicitud);
    comunicacion_finalizarSolicitudEnCurso (contextoAplicacion);

    datosUI_respuesta_solicitudEnvioMensaje.estadoSolicitud = datos_respuesta_solicitudEnvioMensaje.estadoSolicitud;

    return datosUI_respuesta_solicitudEnvioMensaje;
}

_t_datosUI_respuesta_recepcionMensaje _interfazContactos_recepcionMensaje_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta)
{
    t_datosRespuestaRecepcionMensaje datos_respuesta_recepcionMensaje;
    _t_datosUI_respuesta_recepcionMensaje datosUI_respuesta_recepcionMensaje;

    comunicacion_extraerDatosRespuesta_recepcionMensaje (respuesta, &datos_respuesta_recepcionMensaje);
    printf ("\nRespuesta recibida: %c|%d|%s\n", datos_respuesta_recepcionMensaje.header.tipo, datos_respuesta_recepcionMensaje.idEmisor, datos_respuesta_recepcionMensaje.texto);

    datosUI_respuesta_recepcionMensaje.idEmisor = datos_respuesta_recepcionMensaje.idEmisor;
    strcpy (datosUI_respuesta_recepcionMensaje.texto, datos_respuesta_recepcionMensaje.texto);

    return datosUI_respuesta_recepcionMensaje;
}

_t_datosUI_respuesta_solicitudSeleccionChat _interfazContactos_solicitudSeleccionChat_procesarRespuesta (t_contextoAplicacion *contextoAplicacion, const char *respuesta)
{
    t_datosRespuestaSolicitudSeleccionChat datos_respuesta_solicitudSeleccionChat;
    _t_datosUI_respuesta_solicitudSeleccionChat datosUI_respuesta_solicitudSeleccionChat;

    comunicacion_extraerDatosRespuesta_solicitudSeleccionChat (respuesta, &datos_respuesta_solicitudSeleccionChat);
    printf ("Respuesta recibida: %c|%c|%d\n", datos_respuesta_solicitudSeleccionChat.header.tipo, datos_respuesta_solicitudSeleccionChat.estadoSolicitud, datos_respuesta_solicitudSeleccionChat.idUsuarioDelChatSeleccionado);
    comunicacion_finalizarSolicitudEnCurso (contextoAplicacion);

    datosUI_respuesta_solicitudSeleccionChat.estadoSolicitud = datos_respuesta_solicitudSeleccionChat.estadoSolicitud;
    datosUI_respuesta_solicitudSeleccionChat.idUsuarioDelChatSeleccionado = datos_respuesta_solicitudSeleccionChat.idUsuarioDelChatSeleccionado;

    return datosUI_respuesta_solicitudSeleccionChat;
}


void _interfazContactos_manejarError_conexion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    omitirEventosPendientes (contextoAplicacion->renderizado);
    resetearInterfaz (interfazContactos);
    
    log_error_conexion ();
    comunicacion_finalizar (&(contextoAplicacion->sock));
    *(contextoAplicacion->usuario.nombre) = '\0';
    contextoAplicacion->usuario.id = ID_INVALIDO;
    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
}


void _interfazContactos_setearNuevoChatSeleccionado (t_interfazContactos *interfazContactos, const _t_datosUI_respuesta_solicitudSeleccionChat *datosUI_respuesta_solicitudSeleccionChat)
{
    interfazContactos->logica.idUsuarioDelChatSeleccionado = datosUI_respuesta_solicitudSeleccionChat->idUsuarioDelChatSeleccionado;
    strcpy (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, &(interfazContactos->logica.contextoMensajes.mensaje[1]));
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


static bool esMensajeVacio (const char *mensaje)
{
    return (*mensaje == '\0');
}


static bool usuarioSeleccionoSuPropioChat (const char *nombreUsuarioPropio, const char *nombreUsuarioChatSeleccionado)
{
    return (strcmp (nombreUsuarioPropio, nombreUsuarioChatSeleccionado) == 0);
}

static bool esChatYaSeleccionado (const char *nombreUsuarioChatYaSeleccionado, const char *nombreUsuarioChatASeleccionar)
{
    return (strcmp (nombreUsuarioChatYaSeleccionado, nombreUsuarioChatASeleccionar) == 0);
}

static _t_resultado_validacionDatosSeleccionChat validarDatosSeleccionChat (const t_interfazContactos *interfazContactos, const char *nombreUsuarioPropio)
{
    const char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(interfazContactos->logica.contextoMensajes.mensaje[1]);

    if (esMensajeVacio (nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTARSELECCIONARCHAT_RESULTADODATOS_NOMBREVACIO;

    if (!esNombreValido (nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTARSELECCIONARCHAT_RESULTADODATOS_NOMBREINVALIDO;

    if (usuarioSeleccionoSuPropioChat (nombreUsuarioPropio, nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTARSELECCIONARCHAT_RESULTADODATOS_SELECCIONPROPIOCHAT;

    if (esChatYaSeleccionado (interfazContactos->logica.nombreUsuarioDelChatSeleccionado, nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTARSELECCIONARCHAT_RESULTADODATOS_CHATYASELECCIONADO;

    return INTENTARSELECCIONARCHAT_RESULTADODATOS_EXITO;
}



static bool sonEmisorYReceptorValidos (int idEmisor, int idReceptor)
{
    return ((idEmisor != ID_INVALIDO) && (idReceptor != ID_INVALIDO));
}

static bool elEmisorEsElReceptor (int idEmisor, int idReceptor)
{
    return (idEmisor == idReceptor);
}

static _t_resultado_validacionDatosEnvioMensaje validarDatosEnvioMensaje (const t_interfazContactos *interfazContactos, int idUsuario)
{
    if (esMensajeVacio (interfazContactos->logica.contextoMensajes.mensaje))
        return INTENTARENVIARMENSAJE_RESULTADODATOS_MENSAJEVACIO;

    if (sonTodosEspacios (interfazContactos->logica.contextoMensajes.mensaje))
        return INTENTARENVIARMENSAJE_RESULTADODATOS_SONTODOSESPACIOS;

    if (!sonEmisorYReceptorValidos (idUsuario, interfazContactos->logica.idUsuarioDelChatSeleccionado))
        return INTENTARENVIARMENSAJE_RESULTADODATOS_EMISORYRECEPTORINVALIDOS;

    if (elEmisorEsElReceptor (idUsuario, interfazContactos->logica.idUsuarioDelChatSeleccionado))
        return INTENTARENVIARMENSAJE_RESULTADODATOS_EMISORESELRECEPTOR;

    return INTENTARENVIARMENSAJE_RESULTADODATOS_EXITO;
}



static void resetearInterfaz (t_interfazContactos *interfazContactos)
{
    // --------------- RESETEAR INTERFAZ ---------------

    interfazContactos->logica.idUsuarioDelChatSeleccionado = ID_INVALIDO; // Establecer un id invalido al usuario del chat seleccionado
    *(interfazContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';
    *(interfazContactos->logica.contextoMensajes.mensaje) = '\0';
    interfazContactos->estadoFoco = ICT_NINGUNO;

    // --------------- RESETEAR TEXTOS ---------------

    sfText_setString (interfazContactos->textos.auxContactoSeleccionado, "");
    sfText_setString (interfazContactos->textos.auxEscribirMensaje, "");
    sfText_setString (interfazContactos->textos.feedbackUsuario, "");
    sfText_setString (interfazContactos->textos.informacionSeleccionChat, "Seleccione un chat con un usuario");
    sfText_setString (interfazContactos->textos.nombreUsuario, "");

    // --------------- RESETEAR LISTA DE MENSAJES ---------------

    _interfazContactos_listaMensajes_vaciar (&(interfazContactos->logica.contextoMensajes));

    // --------------- RESETEAR VISTA ---------------

    sfView_setCenter (interfazContactos->vistas.mensajes, (sfVector2f){1152, 480});
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


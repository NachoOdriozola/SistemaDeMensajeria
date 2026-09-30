#include "interfacesGraficas/interfazContactos/controladores.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static ValidacionSeleccionChat validar_seleccion_chat (const UiContactos *uiContactos, const char *nombreUsuarioPropio);
static ValidacionEnvioMensaje validar_envio_mensaje (const UiContactos *uiContactos, int idUsuario);

static void resetear_interfaz (UiContactos *uiContactos);

static void mensaje_configurar (sfText *mensajeGrafico);
static void mensaje_establecer_mensaje (sfText *mensajeGrafico, const char *cadenaMensaje, float anchoMaxMensaje);
static void lista_mensajes_desplazar_mensajes_hacia_arriba (ListaDoble *mensajes, float desplazamientoY);
static void mensaje_establecer_posicion (sfText *mensaje, OrigenMensaje origenMensaje);
static bool es_primer_mensaje (ContextoMensajes *contextoMensajes);
static void lista_mensajes_guardar_referencia (ContextoMensajes *contextoMensajes);
static void mensaje_liberar (void *mensaje);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


bool _ui_contactos_es_comando (const char *mensaje)
{
    return  (*mensaje == '/');
}

ResultadoIntentoSeleccionChat _ui_contactos_intentar_seleccion_chat (ContextoAplicacion *contextoAplicacion, const UiContactos *uiContactos)
{
    ResultadoIntentoSeleccionChat resultadoIntentoSeleccionChat;
    const char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(uiContactos->logica.contextoMensajes.mensaje[1]);

    resultadoIntentoSeleccionChat.validacion = validar_seleccion_chat (uiContactos, contextoAplicacion->usuario.nombre);
    if (resultadoIntentoSeleccionChat.validacion == INTENTO_SELECCION_CHAT_DATOS_VALIDOS)
    {
        resultadoIntentoSeleccionChat.estado = INTENTO_SELECCION_CHAT_SOLICITUD_ENVIADA;
        comunicacion_enviar_solicitud_seleccion_chat (contextoAplicacion, nombreUsuarioChatSeleccionadoSinBarraDeComando);
    }
    else
        resultadoIntentoSeleccionChat.estado = INTENTO_SELECCION_CHAT_DATOS_INVALIDOS;

    return resultadoIntentoSeleccionChat;
}

ResultadoIntentoEnvioMensaje _ui_contactos_intentar_envio_mensaje (ContextoAplicacion *contextoAplicacion, const UiContactos *uiContactos)
{
    ResultadoIntentoEnvioMensaje resultadoIntentoEnvioMensaje;

    resultadoIntentoEnvioMensaje.validacion = validar_envio_mensaje (uiContactos, contextoAplicacion->usuario.id);
    if (resultadoIntentoEnvioMensaje.validacion == INTENTO_ENVIO_MENSAJE_DATOS_VALIDOS)
    {
        resultadoIntentoEnvioMensaje.estado = INTENTO_ENVIO_MENSAJE_SOLICITUD_ENVIADA;
        comunicacion_enviar_solicitud_envio_mensaje (contextoAplicacion, contextoAplicacion->usuario.id, uiContactos->logica.idUsuarioChatSeleccionado, uiContactos->logica.contextoMensajes.mensaje);
    }
    else
        resultadoIntentoEnvioMensaje.estado = INTENTO_ENVIO_MENSAJE_DATOS_INVALIDOS;

    return resultadoIntentoEnvioMensaje;
}


RespuestaEnvioMensajeUi _ui_contactos_procesar_respuesta_envio_mensaje (ContextoAplicacion *contextoAplicacion, const char *respuesta)
{
    RespuestaEnvioMensaje respuestaEnvioMensaje;
    RespuestaEnvioMensajeUi respuestaEnvioMensajeUi;

    comunicacion_extraer_respuesta_envio_mensaje (respuesta, &respuestaEnvioMensaje);
    printf ("Respuesta recibida: %c|%c\n", respuestaEnvioMensaje.header.tipoPaquete, respuestaEnvioMensaje.estado);
    comunicacion_finalizar_solicitud_en_curso (contextoAplicacion);

    respuestaEnvioMensajeUi.estado = respuestaEnvioMensaje.estado;

    return respuestaEnvioMensajeUi;
}

RespuestaRecepcionMensajeUi _ui_contactos_procesar_respuesta_recepcion_mensaje (ContextoAplicacion *contextoAplicacion, const char *respuesta)
{
    RespuestaRecepcionMensaje respuestaRecepcionMensaje;
    RespuestaRecepcionMensajeUi respuestaRecepcionMensajeUi;

    comunicacion_extraer_respuesta_recepcion_mensaje (respuesta, &respuestaRecepcionMensaje);
    printf ("\nRespuesta recibida: %c|%d|%s\n", respuestaRecepcionMensaje.header.tipoPaquete, respuestaRecepcionMensaje.idEmisor, respuestaRecepcionMensaje.texto);

    respuestaRecepcionMensajeUi.idEmisor = respuestaRecepcionMensaje.idEmisor;
    strcpy (respuestaRecepcionMensajeUi.texto, respuestaRecepcionMensaje.texto);

    return respuestaRecepcionMensajeUi;
}

RespuestaSeleccionChatUi _ui_contactos_procesar_respuesta_seleccion_chat (ContextoAplicacion *contextoAplicacion, const char *respuesta)
{
    RespuestaSeleccionChat respuestaSeleccionChat;
    RespuestaSeleccionChatUi respuestaSeleccionChatUi;

    comunicacion_extraer_respuesta_seleccion_chat (respuesta, &respuestaSeleccionChat);
    printf ("Respuesta recibida: %c|%c|%d\n", respuestaSeleccionChat.header.tipoPaquete, respuestaSeleccionChat.estado, respuestaSeleccionChat.idUsuarioChatSeleccionado);
    comunicacion_finalizar_solicitud_en_curso (contextoAplicacion);

    respuestaSeleccionChatUi.estado = respuestaSeleccionChat.estado;
    respuestaSeleccionChatUi.idUsuarioChatSeleccionado = respuestaSeleccionChat.idUsuarioChatSeleccionado;

    return respuestaSeleccionChatUi;
}


void _ui_contactos_manejar_error_conexion (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    omitir_eventos_pendientes (contextoAplicacion->renderizado);
    resetear_interfaz (uiContactos);
    
    log_error_conexion ();
    comunicacion_finalizar (&(contextoAplicacion->sock));
    *(contextoAplicacion->usuario.nombre) = '\0';
    contextoAplicacion->usuario.id = ID_INVALIDO;
    contextoAplicacion->interfazActual = INTERFAZ_AUTENTICACION;
}


void _ui_contactos_setear_nuevo_chat_seleccionado (UiContactos *uiContactos, const RespuestaSeleccionChatUi *respuestaSeleccionChatUi)
{
    uiContactos->logica.idUsuarioChatSeleccionado = respuestaSeleccionChatUi->idUsuarioChatSeleccionado;
    strcpy (uiContactos->logica.nombreUsuarioDelChatSeleccionado, &(uiContactos->logica.contextoMensajes.mensaje[1]));
}


void _ui_contactos_lista_mensajes_crear (ContextoMensajes *contextoMensajes)
{
    lista_doble_crear (&(contextoMensajes->mensajes));
    contextoMensajes->ultimoMensaje = NULL;
}

CodigoRetorno _ui_contactos_lista_mensajes_insertar (ContextoMensajes *contextoMensajes, const char *mensaje, OrigenMensaje origenMensaje, const UiContactosFuentes *fuentes)
{
    sfText *mensajeGrafico;

    mensajeGrafico = sfText_create (fuentes->cuerpo);
    if (!mensajeGrafico)
    {
        perror ("\nERROR - Interfaz contactos, crear mensaje grafico.\n");
        return ERROR_SIN_MEMORIA;
    } 
    mensaje_configurar (mensajeGrafico);
    mensaje_establecer_mensaje (mensajeGrafico, mensaje, 700);

    lista_mensajes_desplazar_mensajes_hacia_arriba (&(contextoMensajes->mensajes), (sfText_getLocalBounds (mensajeGrafico)).size.y + 35);
    mensaje_establecer_posicion (mensajeGrafico, origenMensaje);

    if (lista_doble_insertar_al_inicio (&(contextoMensajes->mensajes), &mensajeGrafico, sizeof (sfText*)) != 0) // 0 es exito.
        return ERROR_SIN_MEMORIA;

    if (es_primer_mensaje (contextoMensajes))
        lista_mensajes_guardar_referencia (contextoMensajes);

    return EXITO;
}

void _ui_contactos_lista_mensajes_vaciar (ContextoMensajes *contextoMensajes)
{
    lista_doble_vaciar_con_accion (&(contextoMensajes->mensajes), mensaje_liberar);
    contextoMensajes->ultimoMensaje = NULL;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static bool es_mensaje_vacio (const char *mensaje)
{
    return (*mensaje == '\0');
}


static bool usuario_selecciono_su_propio_chat (const char *nombreUsuarioPropio, const char *nombreUsuarioChatSeleccionado)
{
    return (strcmp (nombreUsuarioPropio, nombreUsuarioChatSeleccionado) == 0);
}

static bool es_chat_ya_seleccionado (const char *nombreUsuarioChatYaSeleccionado, const char *nombreUsuarioChatASeleccionar)
{
    return (strcmp (nombreUsuarioChatYaSeleccionado, nombreUsuarioChatASeleccionar) == 0);
}

static ValidacionSeleccionChat validar_seleccion_chat (const UiContactos *uiContactos, const char *nombreUsuarioPropio)
{
    const char *nombreUsuarioChatSeleccionadoSinBarraDeComando = &(uiContactos->logica.contextoMensajes.mensaje[1]);

    if (es_mensaje_vacio (nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTO_SELECCION_CHAT_NOMBRE_VACIO;

    if (!es_nombre_valido (nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTO_SELECCION_CHAT_NOMBRE_INVALIDO;

    if (usuario_selecciono_su_propio_chat (nombreUsuarioPropio, nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTO_SELECCION_CHAT_SELECCIONO_CHAT_PROPIO;

    if (es_chat_ya_seleccionado (uiContactos->logica.nombreUsuarioDelChatSeleccionado, nombreUsuarioChatSeleccionadoSinBarraDeComando))
        return INTENTO_SELECCION_CHAT_CHAT_YA_SELECCIONADO;

    return INTENTO_SELECCION_CHAT_DATOS_VALIDOS;
}



static bool son_emisor_receptor_validos (int idEmisor, int idReceptor)
{
    return ((idEmisor != ID_INVALIDO) && (idReceptor != ID_INVALIDO));
}

static bool emisor_es_receptor (int idEmisor, int idReceptor)
{
    return (idEmisor == idReceptor);
}

static ValidacionEnvioMensaje validar_envio_mensaje (const UiContactos *uiContactos, int idUsuario)
{
    if (es_mensaje_vacio (uiContactos->logica.contextoMensajes.mensaje))
        return INTENTO_ENVIO_MENSAJE_MENSAJE_VACIO;

    if (son_todos_espacios (uiContactos->logica.contextoMensajes.mensaje))
        return INTENTO_ENVIO_MENSAJE_SON_TODOS_ESPACIOS;

    if (!son_emisor_receptor_validos (idUsuario, uiContactos->logica.idUsuarioChatSeleccionado))
        return INTENTO_ENVIO_MENSAJE_EMISOR_RECEPTOR_INVALIDOS;

    if (emisor_es_receptor (idUsuario, uiContactos->logica.idUsuarioChatSeleccionado))
        return INTENTO_ENVIO_MENSAJE_EMISOR_ES_RECEPTOR;

    return INTENTO_ENVIO_MENSAJE_DATOS_VALIDOS;
}



static void resetear_interfaz (UiContactos *uiContactos)
{
    // --------------- RESETEAR INTERFAZ ---------------

    uiContactos->logica.idUsuarioChatSeleccionado = ID_INVALIDO; // Establecer un id invalido al usuario del chat seleccionado
    *(uiContactos->logica.nombreUsuarioDelChatSeleccionado) = '\0';
    *(uiContactos->logica.contextoMensajes.mensaje) = '\0';
    uiContactos->foco = UI_CONTACTOS_NINGUNO;

    // --------------- RESETEAR TEXTOS ---------------

    sfText_setString (uiContactos->textos.auxContactoSeleccionado, "");
    sfText_setString (uiContactos->textos.auxEscribirMensaje, "");
    sfText_setString (uiContactos->textos.feedbackUsuario, "");
    sfText_setString (uiContactos->textos.informacionSeleccionChat, "Seleccione un chat con un usuario");
    sfText_setString (uiContactos->textos.nombreUsuario, "");

    // --------------- RESETEAR LISTA DE MENSAJES ---------------

    _ui_contactos_lista_mensajes_vaciar (&(uiContactos->logica.contextoMensajes));

    // --------------- RESETEAR VISTA ---------------

    sfView_setCenter (uiContactos->vistas.mensajes, (sfVector2f){1152, 480});
}



/*
 * Aun no establece la posicion en ventana ni el contenido del mensaje.
*/
static void mensaje_configurar (sfText *mensajeGrafico)
{
    sfText_setFillColor (mensajeGrafico, sfColor_fromRGB (53, 53, 53));
    sfText_setCharacterSize (mensajeGrafico, 22);
    sfText_setLineSpacing (mensajeGrafico, 1.3);
}

static int calcular_largo_palabra (const char *cadena)
{
    int largoPalabra = 0;

    while ((cadena[largoPalabra] != '\0') && (cadena[largoPalabra] != ' '))
        largoPalabra++;

    return largoPalabra;
}

static bool palabra_sobrepaso_ancho_permitido (sfVector2f posUltimoCaracter, float anchoMaxMensaje)
{
    return (posUltimoCaracter.x >= anchoMaxMensaje);
}

static void agregar_salto_de_linea (char *cadena)
{
    strcat (cadena, "\n");
}

/*
 * Si la palabra sobrepasa el ancho permitido, agrega un salto de linea.
*/
static void procesar_palabra (sfText *mensajeGrafico, const char *cadenaMensaje, char *auxCadenaMensaje, float anchoMaxMensaje, int largoPalabra)
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

        if (palabra_sobrepaso_ancho_permitido (posUltimoCaracter, anchoMaxMensaje))
            agregar_salto_de_linea (auxCadenaMensaje);
    }
}

static void encontrar_proxima_palabra (const char **cadenaMensaje, char *auxCadenaMensaje, int largoUltimaPalabra)
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
static void mensaje_establecer_mensaje (sfText *mensajeGrafico, const char *cadenaMensaje, float anchoMaxMensaje)
{
    char auxCadenaMensaje [MAX_MENSAJE + 100] = ""; // Almacena la cadena del mensaje mas los saltos de linea a agregar.
    int largoPalabra;

    sfText_setPosition (mensajeGrafico, (sfVector2f){0, 0}); // Establece una posicion ficticia al mensaje para que pueda ser procesado ya que sino genera un bug.

    while (*cadenaMensaje != '\0')
    {
        largoPalabra = calcular_largo_palabra (cadenaMensaje);
        procesar_palabra (mensajeGrafico, cadenaMensaje, auxCadenaMensaje, anchoMaxMensaje, largoPalabra);
        encontrar_proxima_palabra (&cadenaMensaje, auxCadenaMensaje, largoPalabra);
    }

    sfText_setString (mensajeGrafico, auxCadenaMensaje);
}

static void modificarPosMensaje (void *mensaje, void *desplazamientoY)
{
    sfVector2f pos;

    pos = sfText_getPosition (*((sfText**)mensaje));
    pos.y -= *((float*)desplazamientoY);
    sfText_setPosition (*((sfText**)mensaje), pos);
}

static void lista_mensajes_desplazar_mensajes_hacia_arriba (ListaDoble *mensajes, float desplazamientoY)
{
    lista_doble_map_con_complemento (mensajes, modificarPosMensaje, &desplazamientoY);
}

static void mensaje_establecer_posicion (sfText *mensaje, OrigenMensaje origenMensaje)
{
    sfFloatRect limitesMensaje = sfText_getLocalBounds (mensaje);

    if (origenMensaje == MENSAJE_PROPIO)
        sfText_setPosition (mensaje, (sfVector2f){1824 - limitesMensaje.size.x - limitesMensaje.position.x, 825 - limitesMensaje.size.y});
    else
        sfText_setPosition (mensaje, (sfVector2f){485, 825 - limitesMensaje.size.y});
}

static bool es_primer_mensaje (ContextoMensajes *contextoMensajes)
{
    return (contextoMensajes->ultimoMensaje == NULL);
}

static void lista_mensajes_guardar_referencia (ContextoMensajes *contextoMensajes)
{
    contextoMensajes->ultimoMensaje = contextoMensajes->mensajes;
}

static void mensaje_liberar (void *mensaje)
{
    DESTRUCTOR_SEGURO_TEXTO (*((sfText**)mensaje));
}


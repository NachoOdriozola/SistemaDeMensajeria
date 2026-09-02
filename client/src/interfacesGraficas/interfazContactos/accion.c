#include "interfacesGraficas/interfazContactos/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_redimensionamiento_ventana (sfRenderWindow *renderizado, t_interfazContactosVistas *vistas, sfEvent eventoRedimensionamiento);

static bool procesar_click_escribirMensaje (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);
static bool procesar_click_areaMensajes (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);
static bool procesar_click_enviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static bool procesar_escribir_mensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, sfEvent eventoChar);

static bool procesar_enter_enviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static bool procesar_pegarTextoDesdePortapapeles_escribir_mensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

static bool procesar_desplazar_arriba_areaMensajes (t_interfazContactos *interfazContactos);
static bool procesar_desplazar_abajo_areaMensajes (t_interfazContactos *interfazContactos);

static bool procesar_scroll_areaMensajes (t_interfazContactos *interfazContactos, sfEvent eventoScroll);

static void deshabilitarFoco (t_interfazContactos *interfazContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazContactos_accion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    sfEvent evento;

    while (sfRenderWindow_pollEvent (contextoAplicacion->renderizado, &evento))
    {
        switch (evento.type)
        {

        case sfEvtClosed:
            sfRenderWindow_close (contextoAplicacion->renderizado);
            break;


        case sfEvtResized:
            procesar_redimensionamiento_ventana (contextoAplicacion->renderizado, &(interfazContactos->vistas), evento);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (procesar_click_escribirMensaje (contextoAplicacion->renderizado, interfazContactos)) break;
                if (procesar_click_areaMensajes (contextoAplicacion->renderizado, interfazContactos)) break;
                if (procesar_click_enviarMensaje (contextoAplicacion, interfazContactos)) break;
                deshabilitarFoco (interfazContactos);
            }
            break;


        case sfEvtTextEntered:
            if (procesar_escribir_mensaje (contextoAplicacion, interfazContactos, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_enviarMensaje (contextoAplicacion, interfazContactos)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (procesar_pegarTextoDesdePortapapeles_escribir_mensaje (contextoAplicacion, interfazContactos)) break;

            if (evento.key.code == sfKeyUp)
                if (procesar_desplazar_arriba_areaMensajes (interfazContactos)) break;

            if (evento.key.code == sfKeyDown)
                if (procesar_desplazar_abajo_areaMensajes (interfazContactos)) break;

            break;


        case sfEvtMouseWheelScrolled:
            if (procesar_scroll_areaMensajes (interfazContactos, evento)) break;
            break;


        default:
            break;
        }
    }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_redimensionamiento_ventana (sfRenderWindow *renderizado, t_interfazContactosVistas *vistas, sfEvent eventoRedimensionamiento)
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


static void posicionarPuntoInsercion_escribirMensaje (t_interfazContactos *interfazContactos)
{
    sfFloatRect limitesAuxEscribirMensaje;

    limitesAuxEscribirMensaje = sfText_getGlobalBounds (interfazContactos->textos.auxEscribirMensaje);
    sfRectangleShape_setPosition (interfazContactos->elementos.puntoInsercion, (sfVector2f){451 + limitesAuxEscribirMensaje.width, 942});
}

static void resetearBarraEscritura (t_interfazContactos *interfazContactos)
{
    *(interfazContactos->logica.contextoMensajes.mensaje) = '\0';
    sfText_setString (interfazContactos->textos.auxEscribirMensaje, "");
}

static void mostrarFeedback_enviando (t_interfazContactos *interfazContactos)
{
    textoDeCarga_iniciar (&(interfazContactos->logica.textoDeCarga));
    sfText_setString (interfazContactos->textos.feedbackUsuario, "Enviando");
}


static void mostrarFeedback_datosInvalidosSeleccionChat (t_interfazContactos *interfazContactos, const _t_resultado_validacionDatosSeleccionChat *resultado_validacionDatosSeleccionChat)
{
    switch (*resultado_validacionDatosSeleccionChat)
    {
        case INTENTARSELECCIONARCHAT_RESULTADODATOS_NOMBREVACIO:
            sfUint32 bufferEsMensajeVacio [] = {'N', 'o', ' ', 's', 'e', ' ', 'p', 'u', 'e', 'd', 'e', ' ', 'e', 'n', 'v', 'i', 'a', 'r', ' ', 'u', 'n', ' ', 'n', 'o', 'm', 'b', 'r', 'e', ' ', 'd','e',' ','u','s','u','a','r','i','o', ' ','v', 'a', 'c', 0x00ED, 'o', 0};
            sfText_setUnicodeString (interfazContactos->textos.feedbackUsuario, bufferEsMensajeVacio);
            break;

        case INTENTARSELECCIONARCHAT_RESULTADODATOS_NOMBREINVALIDO:
            sfUint32 bufferNoEsNombreValido[] = {'N','o',' ','e','s',' ','u','n',' ','n','o','m','b','r','e',' ','d','e',' ','u','s','u','a','r','i','o',' ','v',0x00e1,'l','i','d','o',0};
            sfText_setUnicodeString (interfazContactos->textos.feedbackUsuario, bufferNoEsNombreValido);
            break;

        case INTENTARSELECCIONARCHAT_RESULTADODATOS_SELECCIONPROPIOCHAT:
            sfText_setString (interfazContactos->textos.feedbackUsuario, "No se puede seleccionar un chat con su propio usuario");
            break;

        case INTENTARSELECCIONARCHAT_RESULTADODATOS_CHATYASELECCIONADO:
            sfText_setString (interfazContactos->textos.feedbackUsuario, "El chat con el usuario ya se encuentra seleccionado");
            break;

        default:
            break;
    }
}

static void intentarSeleccionarChatYProcesarResultadoOperacion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    _t_resultado_intentarSeleccionarChat resultado_intentarSeleccionarChat;

    resultado_intentarSeleccionarChat = _interfazContactos_intentar_seleccionarChat (contextoAplicacion, interfazContactos);
    switch (resultado_intentarSeleccionarChat.tipo)
    {
        case INTENTARSELECCIONARCHAT_RESULTADO_EXITO:
            mostrarFeedback_enviando (interfazContactos);
            break;

        case INTENTARSELECCIONARCHAT_RESULTADO_DATOS_INVALIDOS:
            resetearBarraEscritura (interfazContactos);
            posicionarPuntoInsercion_escribirMensaje (interfazContactos);
            mostrarFeedback_datosInvalidosSeleccionChat (interfazContactos, &(resultado_intentarSeleccionarChat.validacion));
            break;

        default:
            break;
    }
}


static void mostrarFeedback_datosInvalidosEnvioMensaje (t_interfazContactos *interfazContactos, _t_resultado_validacionDatosEnvioMensaje *resultado_validacionDatosEnvioMensaje)
{
    switch (*resultado_validacionDatosEnvioMensaje)
    {
        case INTENTARENVIARMENSAJE_RESULTADODATOS_MENSAJEVACIO:
            sfUint32 bufferEsMensajeVacio [] = {'N', 'o', ' ', 's', 'e', ' ', 'p', 'u', 'e', 'd', 'e', ' ', 'e', 'n', 'v', 'i', 'a', 'r', ' ', 'u', 'n', ' ', 'm', 'e', 'n', 's', 'a', 'j', 'e', ' ', 'v', 'a', 'c', 0x00ED, 'o', 0};
            sfText_setUnicodeString (interfazContactos->textos.feedbackUsuario, bufferEsMensajeVacio);
            break;

        case INTENTARENVIARMENSAJE_RESULTADODATOS_SONTODOSESPACIOS:
            sfText_setString (interfazContactos->textos.feedbackUsuario, "No se puede enviar un mensaje de todos espacios");
            break;
        
        case INTENTARENVIARMENSAJE_RESULTADODATOS_EMISORYRECEPTORINVALIDOS:
            sfText_setString (interfazContactos->textos.feedbackUsuario, "Se debe seleccionar un chat con un usuario antes de enviar un mensaje");
            break;

        default:
            break;
    }
}

static void intentarEnviarMensajeYProcesarResultadoOperacion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    _t_resultado_intentarEnviarMensaje resultado_intentarEnviarMensaje;

    resultado_intentarEnviarMensaje = _interfazContactos_intentar_enviarMensaje (contextoAplicacion, interfazContactos);
    switch (resultado_intentarEnviarMensaje.tipo)
    {
        case INTENTARENVIARMENSAJE_RESULTADO_EXITO:
            mostrarFeedback_enviando (interfazContactos);
            break;

        case INTENTARENVIARMENSAJE_RESULTADO_DATOS_INVALIDOS:
            resetearBarraEscritura (interfazContactos);
            posicionarPuntoInsercion_escribirMensaje (interfazContactos);
            mostrarFeedback_datosInvalidosEnvioMensaje (interfazContactos, &(resultado_intentarEnviarMensaje.validacion));
            break;

        default:
            break;
    }
}


static bool procesar_click_escribirMensaje (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (renderizado, interfazContactos->elementos.barraEscribirMensaje))
        return EVENTO_NO_MANEJADO;

    interfazContactos->estadoFoco = ESCRIBIR_MENSAJE;
    posicionarPuntoInsercion_escribirMensaje (interfazContactos);

    return EVENTO_MANEJADO;
}

static bool procesar_click_areaMensajes (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (renderizado, interfazContactos->elementos.areaMensajes))
        return EVENTO_NO_MANEJADO;

    interfazContactos->estadoFoco = AREA_MENSAJES;

    return EVENTO_MANEJADO;
}

static bool procesar_click_enviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazContactos->elementos.botonEnviar))
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (_interfazContactos_esUnComando (interfazContactos->logica.contextoMensajes.mensaje))
        intentarSeleccionarChatYProcesarResultadoOperacion (contextoAplicacion, interfazContactos);
    else
        intentarEnviarMensajeYProcesarResultadoOperacion (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_mensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos, sfEvent eventoChar)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresarCaracterABuffer (interfazContactos->logica.contextoMensajes.mensaje, MAX_MENSAJE, eventoChar) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazContactos->textos.auxEscribirMensaje, interfazContactos->logica.contextoMensajes.mensaje, 1250);
        posicionarPuntoInsercion_escribirMensaje (interfazContactos);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_enviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (_interfazContactos_esUnComando (interfazContactos->logica.contextoMensajes.mensaje))
        intentarSeleccionarChatYProcesarResultadoOperacion (contextoAplicacion, interfazContactos);
    else
        intentarEnviarMensajeYProcesarResultadoOperacion (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}


static bool procesar_pegarTextoDesdePortapapeles_escribir_mensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_haySolicitudEnCurso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegarTextoDesdePortapapelesABuffer (interfazContactos->logica.contextoMensajes.mensaje, MAX_MENSAJE) == EXITO)
    {
        limitarVisualizacionTextoSobreBarraEscritura (interfazContactos->textos.auxEscribirMensaje, interfazContactos->logica.contextoMensajes.mensaje, 1250);
        posicionarPuntoInsercion_escribirMensaje (interfazContactos);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_desplazar_arriba_areaMensajes (t_interfazContactos *interfazContactos)
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

static bool procesar_desplazar_abajo_areaMensajes (t_interfazContactos *interfazContactos)
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


static bool procesar_scroll_areaMensajes (t_interfazContactos *interfazContactos, sfEvent eventoScroll)
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


static void deshabilitarFoco (t_interfazContactos *interfazContactos)
{
    interfazContactos->estadoFoco = ICT_NINGUNO;
}

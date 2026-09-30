#include "interfacesGraficas/interfazContactos/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_redimensionamiento_ventana (sfRenderWindow *renderizado, UiContactosVistas *vistas, sfEvent eventoRedimensionamiento);

static bool procesar_click_escribir_mensaje (const sfRenderWindow *renderizado, UiContactos *uiContactos);
static bool procesar_click_area_mensajes (const sfRenderWindow *renderizado, UiContactos *uiContactos);
static bool procesar_click_enviar_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos);

static bool procesar_escribir_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, sfEvent eventoChar);

static bool procesar_enter_enviar_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos);

static bool procesar_pegar_mensaje_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos);

static bool procesar_desplazamiento_arriba_area_mensajes (UiContactos *uiContactos);
static bool procesar_desplazamiento_abajo_area_mensajes (UiContactos *uiContactos);

static bool procesar_scroll_area_mensajes (UiContactos *uiContactos, sfEvent eventoScroll);

static void deshabilitar_focos (UiContactos *uiContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_contactos_accionar (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
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
            procesar_redimensionamiento_ventana (contextoAplicacion->renderizado, &(uiContactos->vistas), evento);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (procesar_click_escribir_mensaje (contextoAplicacion->renderizado, uiContactos)) break;
                if (procesar_click_area_mensajes (contextoAplicacion->renderizado, uiContactos)) break;
                if (procesar_click_enviar_mensaje (contextoAplicacion, uiContactos)) break;
                deshabilitar_focos (uiContactos);
            }
            break;


        case sfEvtTextEntered:
            if (procesar_escribir_mensaje (contextoAplicacion, uiContactos, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_enviar_mensaje (contextoAplicacion, uiContactos)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (procesar_pegar_mensaje_desde_portapapeles (contextoAplicacion, uiContactos)) break;

            if (evento.key.code == sfKeyUp)
                if (procesar_desplazamiento_arriba_area_mensajes (uiContactos)) break;

            if (evento.key.code == sfKeyDown)
                if (procesar_desplazamiento_abajo_area_mensajes (uiContactos)) break;

            break;


        case sfEvtMouseWheelScrolled:
            if (procesar_scroll_area_mensajes (uiContactos, evento)) break;
            break;


        default:
            break;
        }
    }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_redimensionamiento_ventana (sfRenderWindow *renderizado, UiContactosVistas *vistas, sfEvent eventoRedimensionamiento)
{
    sfVector2u nuevoTamVentana;

    if (eventoRedimensionamiento.size.size.x < ANCHO_MINIMO_VENTANA)
        nuevoTamVentana.x = ANCHO_MINIMO_VENTANA;
    else
        nuevoTamVentana.x = eventoRedimensionamiento.size.size.x;

    if (eventoRedimensionamiento.size.size.y < ALTO_MINIMO_VENTANA)
        nuevoTamVentana.y = ALTO_MINIMO_VENTANA;
    else
        nuevoTamVentana.y = eventoRedimensionamiento.size.size.y;

    sfRenderWindow_setSize (renderizado, nuevoTamVentana);

    // Redimensionar vista UI.
    sfView_setSize (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA, ALTO_LOGICO_VENTANA});
    sfView_setCenter (vistas->ui, (sfVector2f){ANCHO_LOGICO_VENTANA / 2.0f, ALTO_LOGICO_VENTANA / 2.0f});
}


static void posicionar_punto_insercion_mensaje (UiContactos *uiContactos)
{
    sfFloatRect limitesAuxEscribirMensaje;

    limitesAuxEscribirMensaje = sfText_getGlobalBounds (uiContactos->textos.auxEscribirMensaje);
    sfRectangleShape_setPosition (uiContactos->elementos.puntoInsercion, (sfVector2f){451 + limitesAuxEscribirMensaje.size.x, 942});
}

static void resetear_barra_escritura (UiContactos *uiContactos)
{
    *(uiContactos->logica.contextoMensajes.mensaje) = '\0';
    sfText_setString (uiContactos->textos.auxEscribirMensaje, "");
}

static void mostrar_feedback_enviando_solicitud (UiContactos *uiContactos)
{
    texto_de_carga_iniciar (&(uiContactos->logica.textoDeCarga));
    sfText_setString (uiContactos->textos.feedbackUsuario, "Enviando");
}


static void mostrar_feedback_nombre_vacio (UiContactos *uiContactos)
{
    uint32_t bufferMensajeVacio [] = {'N', 'o', ' ', 's', 'e', ' ', 'p', 'u', 'e', 'd', 'e', ' ', 'e', 'n', 'v', 'i', 'a', 'r', ' ', 'u', 'n', ' ', 'n', 'o', 'm', 'b', 'r', 'e', ' ', 'd','e',' ','u','s','u','a','r','i','o', ' ','v', 'a', 'c', 0x00ED, 'o', 0};
    sfText_setUnicodeString (uiContactos->textos.feedbackUsuario, bufferMensajeVacio);
}

static void mostrar_feedback_nombre_invalido (UiContactos *uiContactos)
{
    uint32_t bufferNombreInvalido[] = {'N','o',' ','e','s',' ','u','n',' ','n','o','m','b','r','e',' ','d','e',' ','u','s','u','a','r','i','o',' ','v',0x00e1,'l','i','d','o',0};
    sfText_setUnicodeString (uiContactos->textos.feedbackUsuario, bufferNombreInvalido);
}

static void mostrar_feedback_selecciono_propio_chat (UiContactos *uiContactos)
{
    sfText_setString (uiContactos->textos.feedbackUsuario, "No se puede seleccionar un chat con su propio usuario");
}

static void mostrar_feedback_chat_ya_seleccionado (UiContactos *uiContactos)
{
    sfText_setString (uiContactos->textos.feedbackUsuario, "El chat con el usuario ya se encuentra seleccionado");
}

static void mostrar_feedback_seleccion_chat_invalido (UiContactos *uiContactos, const ValidacionSeleccionChat *validacionSeleccionChat)
{
    switch (*validacionSeleccionChat)
    {
        case INTENTO_SELECCION_CHAT_NOMBRE_VACIO:
            mostrar_feedback_nombre_vacio (uiContactos);
            break;

        case INTENTO_SELECCION_CHAT_NOMBRE_INVALIDO:
            mostrar_feedback_nombre_invalido (uiContactos);
            break;

        case INTENTO_SELECCION_CHAT_SELECCIONO_CHAT_PROPIO:
            mostrar_feedback_selecciono_propio_chat (uiContactos);
            break;

        case INTENTO_SELECCION_CHAT_CHAT_YA_SELECCIONADO:
            mostrar_feedback_chat_ya_seleccionado (uiContactos);
            break;

        default:
            break;
    }
}

static void procesar_resultado_seleccion_chat (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, ResultadoIntentoSeleccionChat resultadoIntentoSeleccionChat)
{
    switch (resultadoIntentoSeleccionChat.estado)
    {
        case INTENTO_SELECCION_CHAT_SOLICITUD_ENVIADA:
            mostrar_feedback_enviando_solicitud (uiContactos);
            break;

        case INTENTO_SELECCION_CHAT_DATOS_INVALIDOS:
            resetear_barra_escritura (uiContactos);
            posicionar_punto_insercion_mensaje (uiContactos);
            mostrar_feedback_seleccion_chat_invalido (uiContactos, &(resultadoIntentoSeleccionChat.validacion));
            break;

        default:
            break;
    }
}


static void mostrar_feedback_mensaje_vacio (UiContactos *uiContactos)
{
    uint32_t bufferMensajeVacio [] = {'N', 'o', ' ', 's', 'e', ' ', 'p', 'u', 'e', 'd', 'e', ' ', 'e', 'n', 'v', 'i', 'a', 'r', ' ', 'u', 'n', ' ', 'm', 'e', 'n', 's', 'a', 'j', 'e', ' ', 'v', 'a', 'c', 0x00ED, 'o', 0};
    sfText_setUnicodeString (uiContactos->textos.feedbackUsuario, bufferMensajeVacio);
}

static void mostrar_feedback_son_todos_espacios (UiContactos *uiContactos)
{
    sfText_setString (uiContactos->textos.feedbackUsuario, "No se puede enviar un mensaje de todos espacios");
}

static void mostrar_feedback_emisor_receptor_invalidos (UiContactos *uiContactos)
{
    sfText_setString (uiContactos->textos.feedbackUsuario, "Se debe seleccionar un chat con un usuario antes de enviar un mensaje");
}

static void mostrar_feedback_envio_mensaje_invalido (UiContactos *uiContactos, ValidacionEnvioMensaje *resultado_validacionDatosEnvioMensaje)
{
    switch (*resultado_validacionDatosEnvioMensaje)
    {
        case INTENTO_ENVIO_MENSAJE_MENSAJE_VACIO:
            mostrar_feedback_mensaje_vacio (uiContactos);
            break;

        case INTENTO_ENVIO_MENSAJE_SON_TODOS_ESPACIOS:
            mostrar_feedback_son_todos_espacios (uiContactos);
            break;
        
        case INTENTO_ENVIO_MENSAJE_EMISOR_RECEPTOR_INVALIDOS:
            mostrar_feedback_emisor_receptor_invalidos (uiContactos);
            break;

        default:
            break;
    }
}

static void procesar_resultado_envio_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, ResultadoIntentoEnvioMensaje resultadoIntentoEnvioMensaje)
{
    switch (resultadoIntentoEnvioMensaje.estado)
    {
        case INTENTO_ENVIO_MENSAJE_SOLICITUD_ENVIADA:
            mostrar_feedback_enviando_solicitud (uiContactos);
            break;

        case INTENTO_ENVIO_MENSAJE_DATOS_INVALIDOS:
            resetear_barra_escritura (uiContactos);
            posicionar_punto_insercion_mensaje (uiContactos);
            mostrar_feedback_envio_mensaje_invalido (uiContactos, &(resultadoIntentoEnvioMensaje.validacion));
            break;

        default:
            break;
    }
}


static bool procesar_click_escribir_mensaje (const sfRenderWindow *renderizado, UiContactos *uiContactos)
{
    if (!se_clickeo_en_rectangulo (renderizado, uiContactos->elementos.barraEscribirMensaje))
        return EVENTO_NO_MANEJADO;

    uiContactos->foco = ESCRIBIR_MENSAJE;
    posicionar_punto_insercion_mensaje (uiContactos);

    return EVENTO_MANEJADO;
}

static bool procesar_click_area_mensajes (const sfRenderWindow *renderizado, UiContactos *uiContactos)
{
    if (!se_clickeo_en_rectangulo (renderizado, uiContactos->elementos.areaMensajes))
        return EVENTO_NO_MANEJADO;

    uiContactos->foco = AREA_MENSAJES;

    return EVENTO_MANEJADO;
}

static bool procesar_click_enviar_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    if (!se_clickeo_en_rectangulo (contextoAplicacion->renderizado, uiContactos->elementos.botonEnviar))
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (_ui_contactos_es_comando (uiContactos->logica.contextoMensajes.mensaje))
    {
        ResultadoIntentoSeleccionChat resultadoIntentoSeleccionChat;

        resultadoIntentoSeleccionChat = _ui_contactos_intentar_seleccion_chat (contextoAplicacion, uiContactos);
        procesar_resultado_seleccion_chat (contextoAplicacion, uiContactos, resultadoIntentoSeleccionChat);
    }
    else
    {
        ResultadoIntentoEnvioMensaje resultadoIntentoEnvioMensaje;

        resultadoIntentoEnvioMensaje = _ui_contactos_intentar_envio_mensaje (contextoAplicacion, uiContactos);
        procesar_resultado_envio_mensaje (contextoAplicacion, uiContactos, resultadoIntentoEnvioMensaje);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos, sfEvent eventoChar)
{
    if (uiContactos->foco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (ingresar_caracter_a_buffer (uiContactos->logica.contextoMensajes.mensaje, MAX_MENSAJE, eventoChar) == EXITO)
    {
        limitar_visualizacion_texto_sobre_barra_escritura (uiContactos->textos.auxEscribirMensaje, uiContactos->logica.contextoMensajes.mensaje, 1250);
        posicionar_punto_insercion_mensaje (uiContactos);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_enter_enviar_mensaje (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    if (uiContactos->foco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (_ui_contactos_es_comando (uiContactos->logica.contextoMensajes.mensaje))
    {
        ResultadoIntentoSeleccionChat resultadoIntentoSeleccionChat;

        resultadoIntentoSeleccionChat = _ui_contactos_intentar_seleccion_chat (contextoAplicacion, uiContactos);
        procesar_resultado_seleccion_chat (contextoAplicacion, uiContactos, resultadoIntentoSeleccionChat);
    }
    else
    {
        ResultadoIntentoEnvioMensaje resultadoIntentoEnvioMensaje;

        resultadoIntentoEnvioMensaje = _ui_contactos_intentar_envio_mensaje (contextoAplicacion, uiContactos);
        procesar_resultado_envio_mensaje (contextoAplicacion, uiContactos, resultadoIntentoEnvioMensaje);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_pegar_mensaje_desde_portapapeles (ContextoAplicacion *contextoAplicacion, UiContactos *uiContactos)
{
    if (uiContactos->foco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (comunicacion_hay_solicitud_en_curso (contextoAplicacion))
        return EVENTO_MANEJADO;

    if (pegar_texto_desde_portapapeles_a_buffer (uiContactos->logica.contextoMensajes.mensaje, MAX_MENSAJE) == EXITO)
    {
        limitar_visualizacion_texto_sobre_barra_escritura (uiContactos->textos.auxEscribirMensaje, uiContactos->logica.contextoMensajes.mensaje, 1250);
        posicionar_punto_insercion_mensaje (uiContactos);
    }

    return EVENTO_MANEJADO;
}


static bool procesar_desplazamiento_arriba_area_mensajes (UiContactos *uiContactos)
{
    sfVector2f tamVista, posCentroVista;
    sfVector2f posUltimoMensaje;

    if (uiContactos->foco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (uiContactos->vistas.mensajes);
    posCentroVista = sfView_getCenter (uiContactos->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)(uiContactos->logica.contextoMensajes.ultimoMensaje->dato)));

    if (posCentroVista.y - tamVista.y / 2.f > posUltimoMensaje.y)
        sfView_move (uiContactos->vistas.mensajes, (sfVector2f){0, -VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}

static bool procesar_desplazamiento_abajo_area_mensajes (UiContactos *uiContactos)
{
    sfVector2f tamVista, posCentroVista;

    if (uiContactos->foco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (uiContactos->vistas.mensajes);
    posCentroVista = sfView_getCenter (uiContactos->vistas.mensajes);

    if (posCentroVista.y + tamVista.y / 2.f < 870)
        sfView_move (uiContactos->vistas.mensajes, (sfVector2f){0, VELOCIDAD_SCROLL});

    return EVENTO_MANEJADO;
}


static bool procesar_scroll_area_mensajes (UiContactos *uiContactos, sfEvent eventoScroll)
{
    sfVector2f tamVista, posCentro;
    sfVector2f posUltimoMensaje;
    float desplazamientoY;
    float superiorVista, inferiorVista;
    float limiteSuperior, limiteInferior;

    if (uiContactos->foco != AREA_MENSAJES)
        return EVENTO_NO_MANEJADO;

    tamVista = sfView_getSize (uiContactos->vistas.mensajes);
    posCentro = sfView_getCenter (uiContactos->vistas.mensajes);
    posUltimoMensaje = sfText_getPosition (*((sfText**)(uiContactos->logica.contextoMensajes.ultimoMensaje->dato)));

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
        sfView_move (uiContactos->vistas.mensajes, (sfVector2f){0, desplazamientoY});

    return EVENTO_MANEJADO;
}


static void deshabilitar_focos (UiContactos *uiContactos)
{
    uiContactos->foco = UI_CONTACTOS_NINGUNO;
}

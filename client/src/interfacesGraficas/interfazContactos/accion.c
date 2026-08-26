#include "interfacesGraficas/interfazContactos/accion.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesar_redimensionamiento_ventana (sfRenderWindow *renderizado, t_interfazContactosVistas *vistas, sfEvent eventoRedimensionamiento);

static bool procesar_click_escribirMensaje (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);
static bool procesar_click_areaMensajes (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);
static bool procesar_click_enviarMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos);

static bool procesar_escribir_mensaje (t_interfazContactos *interfazContactos, sfEvent eventoChar);

static bool procesar_enter_enviarMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos);

static bool procesar_pegarTextoDesdePortapapeles_escribirMensaje (t_interfazContactos *interfazContactos);

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
            if (procesar_escribir_mensaje (interfazContactos, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (procesar_enter_enviarMensaje (contextoAplicacion, interfazContactos)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (procesar_pegarTextoDesdePortapapeles_escribirMensaje (interfazContactos)) break;

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


static void posicionarPuntoInsercion (t_interfazContactos *interfazContactos)
{
    sfFloatRect limitesAuxEscribirMensaje;

    limitesAuxEscribirMensaje = sfText_getGlobalBounds (interfazContactos->textos.auxEscribirMensaje);
    sfRectangleShape_setPosition (interfazContactos->elementos.puntoInsercion, (sfVector2f){451 + limitesAuxEscribirMensaje.width, 942});
}

static bool procesar_click_escribirMensaje (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (renderizado, interfazContactos->elementos.barraEscribirMensaje))
        return EVENTO_NO_MANEJADO;

    interfazContactos->estadoFoco = ESCRIBIR_MENSAJE;
    posicionarPuntoInsercion (interfazContactos);

    return EVENTO_MANEJADO;
}

static bool procesar_click_areaMensajes (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (renderizado, interfazContactos->elementos.areaMensajes))
        return EVENTO_NO_MANEJADO;

    interfazContactos->estadoFoco = AREA_MENSAJES;

    return EVENTO_MANEJADO;
}

static bool procesar_click_enviarMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos)
{
    if (!clickEnRectangulo (contextoAplicacion->renderizado, interfazContactos->elementos.botonEnviar))
        return EVENTO_NO_MANEJADO;

    if (_interfazContactos_esUnComando (interfazContactos->logica.contextoMensajes.mensaje))
        _interfazContactos_realizarSeleccionChat (contextoAplicacion, interfazContactos);
    else
        _interfazContactos_realizarEnvioMensaje (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}


static bool procesar_escribir_mensaje (t_interfazContactos *interfazContactos, sfEvent eventoChar)
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


static bool procesar_enter_enviarMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos)
{
    if (interfazContactos->estadoFoco != ESCRIBIR_MENSAJE)
        return EVENTO_NO_MANEJADO;

    if (_interfazContactos_esUnComando (interfazContactos->logica.contextoMensajes.mensaje))
        _interfazContactos_realizarSeleccionChat (contextoAplicacion, interfazContactos);
    else
        _interfazContactos_realizarEnvioMensaje (contextoAplicacion, interfazContactos);

    return EVENTO_MANEJADO;
}


static bool procesar_pegarTextoDesdePortapapeles_escribirMensaje (t_interfazContactos *interfazContactos)
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

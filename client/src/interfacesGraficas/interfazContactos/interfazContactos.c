#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);
static void actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);
static void renderizar (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazContactos_inicializarValoresNulos (t_interfazContactos *interfazContactos)
{
    //FUENTES
    _interfazContactos_inicializarValoresNulosFuentes (&(interfazContactos->fuentes));

    // TEXTOS
    _interfazContactos_inicializarValoresNulosTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_inicializarValoresNulosElementos (&(interfazContactos->elementos));

    //VISTAS
    _interfazContactos_inicializarValoresNulosVistas (&(interfazContactos->vistas));
}

t_codigoRetorno interfazContactos_inicializar (t_interfazContactos *interfazContactos)
{
    //FUENTES
    if (_interfazContactos_inicializarFuentes (&(interfazContactos->fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // TEXTOS
    if (_interfazContactos_inicializarTextos (&(interfazContactos->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazContactos_inicializarElementos (&(interfazContactos->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //VISTAS
    if (_interfazContactos_inicializarVistas (&(interfazContactos->vistas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //LISTA DE MENSAJES
    interfazContactos_crearListaMensajes (&(interfazContactos->logica.contextoMensajes));

    return EXITO;
}

void interfazContactos_configurar (t_interfazContactos *interfazContactos)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazContactos_configurarInterfaz (interfazContactos);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazContactos_configurarTextos (&(interfazContactos->textos), &(interfazContactos->fuentes));

    // ELEMENTOS
    _interfazContactos_configurarElementos (&(interfazContactos->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------
    // TEXTO
    _interfazContactos_tamYPosVentanaTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_tamYPosVentanaElementos (&(interfazContactos->elementos));

    //VISTAS
    _interfazContactos_tamVistas (&(interfazContactos->vistas));
}

void ejecutarInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    accion (contextoAplicacion, interfazContactos);
    actualizar (contextoAplicacion, interfazContactos);
    renderizar (contextoAplicacion->renderizado, interfazContactos);
}

void interfazContactos_liberar (t_interfazContactos *interfazContactos)
{
    //FUENTES
    _interfazContactos_liberarFuentes (&(interfazContactos->fuentes));

    // TEXTOS
    _interfazContactos_liberarTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_liberarElementos (&(interfazContactos->elementos));

    //VISTAS
    _interfazContactos_liberarVistas (&(interfazContactos->vistas));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
 * Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
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
            _interfazContactos_manejarRedimensionamientoVentana (contextoAplicacion->renderizado, &(interfazContactos->vistas), evento);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (_interfazContactos_manejarClickEscribirMensaje (contextoAplicacion->renderizado, interfazContactos)) break;
                if (_interfazContactos_manejarClickAreaMensajes (contextoAplicacion->renderizado, interfazContactos)) break;
                if (_interfazContactos_manejarClickEnviarMensaje (contextoAplicacion, interfazContactos)) break;
                _interfazContactos_deshabilitarFocos (interfazContactos);
            }
            break;


        case sfEvtTextEntered:
            if (_interfazContactos_manejarEscribirMensaje (interfazContactos, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (_interfazContactos_manejarEnterEnviarMensaje (contextoAplicacion, interfazContactos)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (_interfazContactos_manejarPegarTextoDesdePortapapelesAEscribirMensaje (interfazContactos)) break;

            if (evento.key.code == sfKeyUp)
                if (_interfazContactos_manejarDesplazarArribaAreaMensajes (interfazContactos)) break;

            if (evento.key.code == sfKeyDown)
                if (_interfazContactos_manejarDesplazarAbajoAreaMensajes (interfazContactos)) break;

            break;


        case sfEvtMouseWheelScrolled:
            if (_interfazContactos_manejarScrollAreaMensajes (interfazContactos, evento)) break;
            break;


        default:
            break;
        }
    }
}

/*
*Capturar y manejar los eventos no generados por el usuario directamente.
* Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    // --------------- RECIBIR Y PROCESAR RESPUESTAS DEL SERVIDOR ---------------

    char bufferRespuesta [MAX_BUFFER_RESPUESTA];
    t_resultadoRecepcion resultadoRecepcion;

    resultadoRecepcion = recibirRespuesta (contextoAplicacion->sock, bufferRespuesta);
    if (resultadoRecepcion != RECEPCION_NO_RECIBIO_DATOS)
        _interfazContactos_procesarRespuesta (contextoAplicacion, interfazContactos, bufferRespuesta, resultadoRecepcion);

    // --------------- PUNTO DE INSERCION ---------------

    if (interfazContactos->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(interfazContactos->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazContactos->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazContactos->logica.puntoInsercion));
}

/*
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de contactos y de los recursos comunes (compartidos) entre las interfaces de contactos y salas.
 * Ademas, si se encuentra habilitado, renderiza el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 */
static void interfazContactos_setearVistaUIYRenderizarUI (sfRenderWindow *renderizado, const t_interfazContactos *interfazContactos)
{
    // --------------- ESTABLECER VISTA DE UI ---------------
    sfRenderWindow_setView (renderizado, interfazContactos->vistas.ui);

    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    _interfazContactos_renderizarElementos (renderizado, &(interfazContactos->elementos));

    // TEXTOS
    _interfazContactos_renderizarTextos (renderizado, &(interfazContactos->textos));

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (puntoInsercionHabilitado (&(interfazContactos->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, interfazContactos->elementos.puntoInsercion, NULL);
}

/*
 *Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de contactos en la ventana.
 * Primero renderiza las vistas moviles y luego la vista inmovil.
 * Procurar el orden de los renderizados para que no se superpongan.
*/
static void renderizar (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------
    interfazContactos_setearVistaMensajesYRenderizarListaMensajes (renderizado, interfazContactos);

    // --------------- RENDERIZAR VISTA DE UI ---------------
    interfazContactos_setearVistaUIYRenderizarUI (renderizado, interfazContactos);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}

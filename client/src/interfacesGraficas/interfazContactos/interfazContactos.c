#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);
static void actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);
static void renderizar (sfRenderWindow *renderizado, const t_interfazContactos *interfazContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazContactos_inicializarValoresNulos (t_interfazContactos *interfazContactos)
{
    // TEXTOS
    _interfazContactos_inicializarValoresNulosTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_inicializarValoresNulosElementos (&(interfazContactos->elementos));
}

t_codigoRetorno interfazContactos_inicializar (t_interfazContactos *interfazContactos)
{
    // TEXTOS
    if (_interfazContactos_inicializarTextos (&(interfazContactos->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazContactos_inicializarElementos (&(interfazContactos->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void interfazContactos_configurar (t_interfazContactos *interfazContactos, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazContactos_configurarInterfaz (interfazContactos, recursosComunesContactosSalas);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazContactos_configurarTextos (&(interfazContactos->textos), &(interfazContactos->recursosComunesContactosSalas->fuentes));

    // ELEMENTOS
    _interfazContactos_configurarElementos (&(interfazContactos->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN PANTALLA DE LOS RECURSOS GRAFICOS ---------------
    // TEXTO
    _interfazContactos_tamYPosVentanaTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_tamYPosVentanaElementos (&(interfazContactos->elementos));
}

void ejecutarInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    accion (contextoAplicacion, interfazContactos);
    actualizar (contextoAplicacion, interfazContactos);
    renderizar (contextoAplicacion->renderizado, interfazContactos);
}

void interfazContactos_liberar (t_interfazContactos *interfazContactos)
{
    // TEXTOS
    _interfazContactos_liberarTextos (&(interfazContactos->textos));

    // ELEMENTOS
    _interfazContactos_liberarElementos (&(interfazContactos->elementos));
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
            recursosComunesContactosSalas_manejarRedimensionamientoVentana (contextoAplicacion->renderizado, &(interfazContactos->recursosComunesContactosSalas->vistas), evento);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (recursosComunesContactosSalas_manejarClickEscribirMensaje (contextoAplicacion->renderizado, interfazContactos->recursosComunesContactosSalas)) break;
                if (_interfazContactos_manejarClickCambiarInterfazSalas (contextoAplicacion, interfazContactos)) break;
                if (recursosComunesContactosSalas_manejarClickAreaMensajes (contextoAplicacion->renderizado, interfazContactos->recursosComunesContactosSalas)) break;
                if (_interfazContactos_manejarClickEnviarMensaje (contextoAplicacion, interfazContactos)) break;
                _interfazContactos_deshabilitarFocos (interfazContactos);
            }
            break;


        case sfEvtTextEntered:
            if (recursosComunesContactosSalas_manejarEscribirMensaje (interfazContactos->recursosComunesContactosSalas, evento)) break;
            break;


        case sfEvtKeyPressed:
            if (evento.key.code == sfKeyEnter)
                if (_interfazContactos_manejarEnterEnviarMensaje (contextoAplicacion, interfazContactos)) break;

            if (evento.key.control && evento.key.code == sfKeyV)
                if (recursosComunesContactosSalas_manejarPegarTextoDesdePortapapelesAEscribirMensaje (interfazContactos->recursosComunesContactosSalas)) break;

            if (evento.key.code == sfKeyUp)
                if (recursosComunesContactosSalas_manejarDesplazarArribaAreaMensajes (interfazContactos->recursosComunesContactosSalas)) break;

            if (evento.key.code == sfKeyDown)
                if (recursosComunesContactosSalas_manejarDesplazarAbajoAreaMensajes (interfazContactos->recursosComunesContactosSalas)) break;

            break;


        case sfEvtMouseWheelScrolled:
            if (recursosComunesContactosSalas_manejarScrollAreaMensajes (interfazContactos->recursosComunesContactosSalas, evento)) break;
            break;


        default:
            break;
        }
    }
}

/*
*Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
* Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void actualizar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos)
{
    // --------------- RECIBIR Y PROCESAR RESPUESTAS DEL SERVIDOR ---------------

    char bufferRespuesta [MAX_BUFFER_RESPUESTA];

    if (recibioRespuesta (contextoAplicacion->sock, bufferRespuesta))
        _interfazContactos_procesarRespuesta (interfazContactos, bufferRespuesta);

    // --------------- PUNTO DE INSERCION ---------------

    if (interfazContactos->recursosComunesContactosSalas->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(interfazContactos->recursosComunesContactosSalas->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazContactos->recursosComunesContactosSalas->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazContactos->recursosComunesContactosSalas->logica.puntoInsercion));
}

/*
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de contactos y de los recursos comunes (compartidos) entre las interfaces de contactos y salas.
 * Ademas, si se encuentra habilitado, renderiza el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 */
static void interfazContactos_setearVistaUIYRenderizarUI (sfRenderWindow *renderizado, const t_interfazContactos *interfazContactos)
{
    // --------------- ESTABLECER VISTA DE UI ---------------
    sfRenderWindow_setView (renderizado, interfazContactos->recursosComunesContactosSalas->vistas.ui);

    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    recursosComunesContactosSalas_renderizarElementos (renderizado, &(interfazContactos->recursosComunesContactosSalas->elementos));
    _interfazContactos_renderizarElementos (renderizado, &(interfazContactos->elementos));

    // TEXTOS
    recursosComunesContactosSalas_renderizarTextos (renderizado, &(interfazContactos->recursosComunesContactosSalas->textos));
    _interfazContactos_renderizarTextos (renderizado, &(interfazContactos->textos));

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (puntoInsercionHabilitado (&(interfazContactos->recursosComunesContactosSalas->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, interfazContactos->recursosComunesContactosSalas->elementos.puntoInsercion, NULL);
}

/*
 *Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de contactos en la ventana.
 * Primero renderiza las vistas moviles y luego la vista inmovil.
 * Procurar el orden de los renderizados para que no se superpongan.
*/
static void renderizar (sfRenderWindow *renderizado, const t_interfazContactos *interfazContactos)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------
    recursosComunesContactosSalas_setearVistaMensajesYRenderizarListaMensajes (renderizado, interfazContactos->recursosComunesContactosSalas);

    // --------------- RENDERIZAR VISTA DE UI ---------------
    interfazContactos_setearVistaUIYRenderizarUI (renderizado, interfazContactos);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}

#include "../../../include/interfacesGraficas/interfazSalas/interfazSalas.h"


/* ============================================================================================================================================
   DECLARACIONES DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazSalas *interfazSalas);
static void actualizar (t_interfazSalas *interfazSalas);
static void renderizar (sfRenderWindow *renderizado, const t_interfazSalas *interfazSalas);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void interfazSalas_inicializarValoresNulos (t_interfazSalas *interfazSalas)
{
    // TEXTOS
    _interfazSalas_inicializarValoresNulosTextos (&(interfazSalas->textos));

    // ELEMENTOS
    _interfazSalas_inicializarValoresNulosElementos (&(interfazSalas->elementos));
}

t_codigoRetorno interfazSalas_inicializar (t_interfazSalas *interfazSalas)
{
    // TEXTOS
    if (_interfazSalas_inicializarTextos (&(interfazSalas->textos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    // ELEMENTOS
    if (_interfazSalas_inicializarElementos (&(interfazSalas->elementos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    return EXITO;
}

void interfazSalas_configurar (t_interfazSalas *interfazSalas, t_recursosComunesContactosSalas *recursosComunesContactosSalas)
{
    // --------------- CONFIGURAR INTERFAZ ---------------
    _interfazSalas_configurarInterfaz (interfazSalas, recursosComunesContactosSalas);

    // --------------- CONFIGURAR RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazSalas_configurarTextos (&(interfazSalas->textos), &(interfazSalas->recursosComunesContactosSalas->fuentes));

    // ELEMENTOS
    _interfazSalas_configurarElementos (&(interfazSalas->elementos));

    // --------------- ESTABLECER TAMANIO Y POSICION EN VENTANA DE RECURSOS GRAFICOS ---------------
    // TEXTOS
    _interfazSalas_tamYPosVentanaTextos (&(interfazSalas->textos));

    // ELEMENTOS
    _interfazSalas_tamYPosVentanaElementos (&(interfazSalas->elementos));
}

void ejecutarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_interfazSalas *interfazSalas)
{
    accion (contextoAplicacion, interfazSalas);
    actualizar (interfazSalas);
    renderizar (contextoAplicacion->renderizado, interfazSalas);
}

void interfazSalas_liberar (t_interfazSalas *interfazSalas)
{
    // TEXTOS
    _interfazSalas_liberarTextos (&(interfazSalas->textos));

    // ELEMENTOS
    _interfazSalas_liberarElementos (&(interfazSalas->elementos));
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


/*
 * Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
*/
static void accion (t_contextoAplicacion *contextoAplicacion, t_interfazSalas *interfazSalas)
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
            recursosComunesContactosSalas_manejarRedimensionamientoVentana (contextoAplicacion->renderizado, &(interfazSalas->recursosComunesContactosSalas->vistas), evento);
            break;


        case sfEvtMouseButtonPressed:
            if (evento.mouseButton.button == sfMouseLeft)
            {
                if (_interfazSalas_manejarClickCambiarAInterfazContactos (contextoAplicacion, interfazSalas)) break;
                _interfazSalas_deshabilitarFocos (interfazSalas);
            }
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
static void actualizar (t_interfazSalas *interfazSalas)
{
    // --------------- PUNTO DE INSERCION ---------------
    if (interfazSalas->recursosComunesContactosSalas->estadoFoco == ESCRIBIR_MENSAJE)
        actualizarPuntoInsercion (&(interfazSalas->recursosComunesContactosSalas->logica.puntoInsercion));
    else if (puntoInsercionHabilitado (&(interfazSalas->recursosComunesContactosSalas->logica.puntoInsercion)))
        resetearPuntoInsercion (&(interfazSalas->recursosComunesContactosSalas->logica.puntoInsercion));
}

/*
 * Establecer la vista de UI en el renderizado, y renderizar los elementos y textos graficos de la interfaz de salas y de los recursos comunes (compartidos) entre las interfaces de contactos y salas.
 * Ademas, si se encuentra habilitado, renderiza el punto de insercion.
 * No se limpia ni muestra la pantalla, solo los renderiza.
 */
static void interfazSalas_renderizarVistaUI (sfRenderWindow *renderizado, const t_interfazSalas *interfazSalas)
{
    // --------------- ESTABLECER VISTA DE UI ---------------
    sfRenderWindow_setView (renderizado, interfazSalas->recursosComunesContactosSalas->vistas.ui);

    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    recursosComunesContactosSalas_renderizarElementos (renderizado, &(interfazSalas->recursosComunesContactosSalas->elementos));
    _interfazSalas_renderizarElementos (renderizado, &(interfazSalas->elementos));

    // TEXTOS
    recursosComunesContactosSalas_renderizarTextos (renderizado, &(interfazSalas->recursosComunesContactosSalas->textos));
    _interfazSalas_renderizarTextos (renderizado, &(interfazSalas->textos));

    sfRenderWindow_drawRectangleShape (renderizado, interfazSalas->elementos.taparBarraEscribirMensaje, NULL); // TAPAR LOS ELEMENTOS GRAFICOS QUE NO SE ENCUENTREN ACTIVOS EN EL INCREMENTO 1.

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (puntoInsercionHabilitado (&(interfazSalas->recursosComunesContactosSalas->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, interfazSalas->recursosComunesContactosSalas->elementos.puntoInsercion, NULL);
}

/*
 *Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de salas en la ventana.
 * Primero renderiza las vistas moviles y luego la vista inmovil.
 * Procurar el orden de los renderizados para que no se superpongan.
*/
static void renderizar (sfRenderWindow *renderizado, const t_interfazSalas *interfazSalas)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR VISTA DE UI ---------------
    interfazSalas_renderizarVistaUI (renderizado, interfazSalas);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}


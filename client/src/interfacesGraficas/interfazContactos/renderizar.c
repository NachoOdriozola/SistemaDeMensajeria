#include "interfacesGraficas/interfazContactos/renderizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */

   
static void renderizarUI (sfRenderWindow *renderizado, const t_interfazContactos *interfazContactos);

static void renderizarMensajes (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazContactos_renderizar (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------
    sfRenderWindow_setView (renderizado, interfazContactos->vistas.mensajes);
    renderizarMensajes (renderizado, interfazContactos);

    // --------------- RENDERIZAR VISTA DE UI ---------------
    sfRenderWindow_setView (renderizado, interfazContactos->vistas.ui);
    renderizarUI (renderizado, interfazContactos);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizarTextos (sfRenderWindow *renderizado, const t_interfazContactosTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxContactoSeleccionado, NULL);
    sfRenderWindow_drawText (renderizado, textos->auxEscribirMensaje, NULL);
    sfRenderWindow_drawText (renderizado, textos->botonEnviar, NULL);
    sfRenderWindow_drawText (renderizado, textos->feedbackUsuario, NULL);
    sfRenderWindow_drawText (renderizado, textos->informacionSeleccionChat, NULL);
    sfRenderWindow_drawText (renderizado, textos->nombreUsuario, NULL);
    sfRenderWindow_drawText (renderizado, textos->tituloContactos, NULL);
}

static void renderizarElementos (sfRenderWindow *renderizado, const t_interfazContactosElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->areaContactoSeleccionado, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->areaMensajes, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirMensaje, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->botonEnviar, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->carpetaDecorativaFondo3, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->carpetaDecorativaFondo2, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->carpetaDecorativaFondo1, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->panelInterfaz, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->separacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (renderizado, elementos->separacionTitulo, NULL);
}

static void renderizarUI (sfRenderWindow *renderizado, const t_interfazContactos *interfazContactos)
{
    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    renderizarElementos (renderizado, &(interfazContactos->elementos));

    // TEXTOS
    renderizarTextos (renderizado, &(interfazContactos->textos));

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (puntoInsercionHabilitado (&(interfazContactos->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, interfazContactos->elementos.puntoInsercion, NULL);
}


static void renderizarMensaje (void *mensaje, void *renderizado)
{
   sfRenderWindow_drawText ((sfRenderWindow*)renderizado, *((sfText**)mensaje), NULL);
}

static void renderizarMensajes (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos)
{
   mapListaDobleConComplemento (&(interfazContactos->logica.contextoMensajes.mensajes), renderizarMensaje, renderizado);
}


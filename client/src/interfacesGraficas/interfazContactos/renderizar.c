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


static void renderizarUI (sfRenderWindow *renderizado, const t_interfazContactos *interfazContactos)
{
    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    _interfazContactos_renderizarElementos (renderizado, &(interfazContactos->elementos));

    // TEXTOS
    _interfazContactos_renderizarTextos (renderizado, &(interfazContactos->textos));

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


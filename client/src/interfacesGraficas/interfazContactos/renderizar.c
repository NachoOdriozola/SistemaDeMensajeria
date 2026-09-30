#include "interfacesGraficas/interfazContactos/renderizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */

   
static void renderizar_ui (sfRenderWindow *renderizado, const UiContactos *uiContactos);

static void renderizar_lista_mensajes (sfRenderWindow *renderizado, UiContactos *uiContactos);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_contactos_renderizar (sfRenderWindow *renderizado, UiContactos *uiContactos)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR VISTA DE MENSAJES ---------------
    sfRenderWindow_setView (renderizado, uiContactos->vistas.mensajes);
    renderizar_lista_mensajes (renderizado, uiContactos);

    // --------------- RENDERIZAR VISTA DE UI ---------------
    sfRenderWindow_setView (renderizado, uiContactos->vistas.ui);
    renderizar_ui (renderizado, uiContactos);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizar_textos (sfRenderWindow *renderizado, const UiContactosTextos *textos)
{
   sfRenderWindow_drawText (renderizado, textos->auxContactoSeleccionado, NULL);
   sfRenderWindow_drawText (renderizado, textos->auxEscribirMensaje, NULL);
   sfRenderWindow_drawText (renderizado, textos->botonEnviar, NULL);
   sfRenderWindow_drawText (renderizado, textos->feedbackUsuario, NULL);
   sfRenderWindow_drawText (renderizado, textos->informacionSeleccionChat, NULL);
   sfRenderWindow_drawText (renderizado, textos->nombreUsuario, NULL);
   sfRenderWindow_drawText (renderizado, textos->tituloContactos, NULL);
}

static void renderizar_elementos (sfRenderWindow *renderizado, const UiContactosElementos *elementos)
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

static void renderizar_ui (sfRenderWindow *renderizado, const UiContactos *uiContactos)
{
   // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
   // ELEMENTOS
   renderizar_elementos (renderizado, &(uiContactos->elementos));

   // TEXTOS
   renderizar_textos (renderizado, &(uiContactos->textos));

   // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
   if (punto_insercion_esta_habilitado (&(uiContactos->logica.puntoInsercion)))
      sfRenderWindow_drawRectangleShape (renderizado, uiContactos->elementos.puntoInsercion, NULL);
}


static void renderizar_mensaje (void *mensaje, void *renderizado)
{
   sfRenderWindow_drawText ((sfRenderWindow*)renderizado, *((sfText**)mensaje), NULL);
}

static void renderizar_lista_mensajes (sfRenderWindow *renderizado, UiContactos *uiContactos)
{
   lista_doble_map_con_complemento (&(uiContactos->logica.contextoMensajes.mensajes), renderizar_mensaje, renderizado);
}


#include "interfacesGraficas/interfazRegistro/renderizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizar_ui (sfRenderWindow *renderizado, const UiRegistro *uiRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_registro_renderizar (sfRenderWindow *renderizado, const UiRegistro *uiRegistro)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR VISTA DE UI ---------------
    sfRenderWindow_setView (renderizado, uiRegistro->uiAcceso->vistas.ui);
   renderizar_ui (renderizado, uiRegistro);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizar_textos (sfRenderWindow *renderizado, const UiRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->informacionContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->informacionNombre, NULL);
}

static void renderizar_elementos (sfRenderWindow *renderizado, const UiRegistroElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirCorreo, NULL);
}

static void renderizar_ui (sfRenderWindow *renderizado, const UiRegistro *uiRegistro)
{
    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    ui_acceso_renderizar_Elementos (renderizado, &(uiRegistro->uiAcceso->elementos));
    renderizar_elementos (renderizado, &(uiRegistro->elementos));

    // TEXTOS
    ui_acceso_renderizar_textos (renderizado, &(uiRegistro->uiAcceso->textos));
    renderizar_textos (renderizado, &(uiRegistro->textos));

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (punto_insercion_esta_habilitado (&(uiRegistro->uiAcceso->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, uiRegistro->uiAcceso->elementos.puntoInsercion, NULL);
}


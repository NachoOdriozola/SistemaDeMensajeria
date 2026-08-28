#include "interfacesGraficas/interfazRegistro/renderizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizarUI (sfRenderWindow *renderizado, const t_interfazRegistro *interfazRegistro);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazRegistro_renderizar (sfRenderWindow *renderizado, const t_interfazRegistro *interfazRegistro)
{
    // --------------- LIMPIAR VENTANA ---------------
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

    // --------------- RENDERIZAR VISTA DE UI ---------------
    sfRenderWindow_setView (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->vistas.ui);
   renderizarUI (renderizado, interfazRegistro);

    // --------------- MOSTRAR VENTANA ---------------
    sfRenderWindow_display (renderizado);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizarTextos (sfRenderWindow *renderizado, const t_interfazRegistroTextos *textos)
{
    sfRenderWindow_drawText (renderizado, textos->auxEscribirCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->ingresarCorreo, NULL);
    sfRenderWindow_drawText (renderizado, textos->informacionContrasenia, NULL);
    sfRenderWindow_drawText (renderizado, textos->informacionNombre, NULL);
}

static void renderizarElementos (sfRenderWindow *renderizado, const t_interfazRegistroElementos *elementos)
{
    sfRenderWindow_drawRectangleShape (renderizado, elementos->barraEscribirCorreo, NULL);
}

static void renderizarUI (sfRenderWindow *renderizado, const t_interfazRegistro *interfazRegistro)
{
    // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
    // ELEMENTOS
    recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(interfazRegistro->recursosComunesAutenticacionRegistro->elementos));
    renderizarElementos (renderizado, &(interfazRegistro->elementos));

    // TEXTOS
    recursosComunesAutenticacionRegistro_renderizarTextos (renderizado, &(interfazRegistro->recursosComunesAutenticacionRegistro->textos));
    renderizarTextos (renderizado, &(interfazRegistro->textos));

    // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
    if (puntoInsercionHabilitado (&(interfazRegistro->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
        sfRenderWindow_drawRectangleShape (renderizado, interfazRegistro->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);
}


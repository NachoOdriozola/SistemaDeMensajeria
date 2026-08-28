#include "interfacesGraficas/interfazAutenticacion/renderizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizarUI (sfRenderWindow *renderizado, const t_interfazAutenticacion *interfazAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazAutenticacion_renderizar (sfRenderWindow *renderizado, const t_interfazAutenticacion *interfazAutenticacion)
{
   // --------------- LIMPIAR VENTANA ---------------
   sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

   // --------------- RENDERIZAR VISTA DE UI ---------------
   sfRenderWindow_setView (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->vistas.ui);
   renderizarUI (renderizado, interfazAutenticacion);

   // --------------- MOSTRAR VENTANA ---------------
   sfRenderWindow_display (renderizado);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizarTextos (sfRenderWindow *renderizado, const t_interfazAutenticacionTextos *textos)
{

}

static void renderizarElementos (sfRenderWindow *renderizado, const t_interfazAutenticacionElementos *elementos)
{

}

static void renderizarUI (sfRenderWindow *renderizado, const t_interfazAutenticacion *interfazAutenticacion)
{
   // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
   // ELEMENTOS
   recursosComunesAutenticacionRegistro_renderizarElementos (renderizado, &(interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos));
   renderizarElementos (renderizado, &(interfazAutenticacion->elementos));

   // TEXTOS
   recursosComunesAutenticacionRegistro_renderizarTextos (renderizado, &(interfazAutenticacion->recursosComunesAutenticacionRegistro->textos));
   renderizarTextos (renderizado, &(interfazAutenticacion->textos));

   // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
   if (puntoInsercionHabilitado (&(interfazAutenticacion->recursosComunesAutenticacionRegistro->logica.puntoInsercion)))
      sfRenderWindow_drawRectangleShape (renderizado, interfazAutenticacion->recursosComunesAutenticacionRegistro->elementos.puntoInsercion, NULL);
}

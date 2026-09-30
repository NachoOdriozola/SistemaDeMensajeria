#include "interfacesGraficas/interfazAutenticacion/renderizar.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizar_ui (sfRenderWindow *renderizado, const UiAutenticacion *uiAutenticacion);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _ui_autenticacion_renderizar (sfRenderWindow *renderizado, const UiAutenticacion *uiAutenticacion)
{
   // --------------- LIMPIAR VENTANA ---------------
   sfRenderWindow_clear (renderizado, sfColor_fromRGB (244, 241, 236));

   // --------------- RENDERIZAR VISTA DE UI ---------------
   sfRenderWindow_setView (renderizado, uiAutenticacion->uiAcceso->vistas.ui);
   renderizar_ui (renderizado, uiAutenticacion);

   // --------------- MOSTRAR VENTANA ---------------
   sfRenderWindow_display (renderizado);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void renderizar_textos (sfRenderWindow *renderizado, const UiAutenticacionTextos *textos)
{

}

static void renderizar_elementos (sfRenderWindow *renderizado, const UiAutenticacionElementos *elementos)
{

}

static void renderizar_ui (sfRenderWindow *renderizado, const UiAutenticacion *uiAutenticacion)
{
   // --------------- RENDERIZAR RECURSOS GRAFICOS ---------------
   // ELEMENTOS
   ui_acceso_renderizar_Elementos (renderizado, &(uiAutenticacion->uiAcceso->elementos));
   renderizar_elementos (renderizado, &(uiAutenticacion->elementos));

   // TEXTOS
   ui_acceso_renderizar_textos (renderizado, &(uiAutenticacion->uiAcceso->textos));
   renderizar_textos (renderizado, &(uiAutenticacion->textos));

   // --------------- RENDERIZAR PUNTO DE INSERCION ---------------
   if (punto_insercion_esta_habilitado (&(uiAutenticacion->uiAcceso->logica.puntoInsercion)))
      sfRenderWindow_drawRectangleShape (renderizado, uiAutenticacion->uiAcceso->elementos.puntoInsercion, NULL);
}

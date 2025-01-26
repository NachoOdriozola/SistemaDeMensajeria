#include "especificas.h"


///FUNCIONES DE INICIALIZACION ESPECIFICAS


void crearEscalaElementos (s_aplicacion *app)
{
    app->ventana.escalaElementos.x = app->ventana.tamOriginalPantalla.x / (float)RESOLUCION_BASE_MAXIMIZADO_X;
    app->ventana.escalaElementos.y = app->ventana.tamOriginalPantalla.y / (float)RESOLUCION_BASE_MAXIMIZADO_Y;
}

void crearEscalaPixeles (s_aplicacion *app)
{
    app->ventana.escalaPixeles = fminf (app->ventana.tamOriginalPantalla.x / (float)RESOLUCION_BASE_MAXIMIZADO_X, app->ventana.tamOriginalPantalla.y / (float)RESOLUCION_BASE_MAXIMIZADO_Y);
}

void eventoMaximizadoAutomatico (s_aplicacion *app)
{
    sfEvent eventoPrimerMaximizado;
    sfVector2f nuevoTamPantalla;

    //Proceso todos los eventos acumulados hasta encontrar el maximizado.
    while (sfRenderWindow_pollEvent (app->renderizado, &eventoPrimerMaximizado))
    {
        if (eventoPrimerMaximizado.type == sfEvtResized)
        {
            nuevoTamPantalla.x = eventoPrimerMaximizado.size.width;
            nuevoTamPantalla.y = eventoPrimerMaximizado.size.height;
        }
    }
    app->ventana.tamOriginalPantalla = nuevoTamPantalla;
    app->ventana.tamActualPantalla = nuevoTamPantalla;
}

void maximizadoAutomaticoVentana (s_aplicacion *app)
{
    HWND hwnd;

    hwnd = sfRenderWindow_getSystemHandle (app->renderizado);
    ShowWindow (hwnd, SW_MAXIMIZE);

    eventoMaximizadoAutomatico (app);
    ajustarVista (app, app->ventana.tamOriginalPantalla);
    crearEscalaElementos (app);
    crearEscalaPixeles (app);
}














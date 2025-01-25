#include "funcionesGenerales.h"


void ajustarVista (s_aplicacion *app, sfVector2f nuevoTamPantalla)
{
    sfView *nuevaVista;

    nuevaVista = sfView_create ();
    if (!nuevaVista)
    {
        perror ("ERROR - Crear nueva vista para redimensionar ventana.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
        return;
    }

    sfView_setSize (nuevaVista, nuevoTamPantalla);
    sfView_setCenter (nuevaVista, (sfVector2f){nuevoTamPantalla.x / 2.0f, nuevoTamPantalla.y / 2.0f});
    sfRenderWindow_setView (app->renderizado, nuevaVista);

    sfView_destroy (nuevaVista);
}

void crearEscalaElementos (s_aplicacion *app)
{
    app->ventana.escalaElementos.x = app->ventana.tamOriginalPantalla.x / (float)RESOLUCION_BASE_X;
    app->ventana.escalaElementos.y = app->ventana.tamOriginalPantalla.y / (float)RESOLUCION_BASE_Y;
}

void crearEscalaPixeles (s_aplicacion *app)
{
    app->ventana.escalaPixeles = fminf (app->ventana.tamOriginalPantalla.x / (float)RESOLUCION_BASE_X, app->ventana.tamOriginalPantalla.y / (float)RESOLUCION_BASE_Y);
}

bool clickEnRectangulo (sfRenderWindow *renderizado, sfRectangleShape *rectangulo)
{
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (rectangulo);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}



























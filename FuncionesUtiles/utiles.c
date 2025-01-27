#include "utiles.h"


///FUNCIONES UTILES


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

bool clickEnRectangulo (sfRenderWindow *renderizado, sfRectangleShape *rectangulo)
{
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (rectangulo);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}

void ingresoTexto (char *buffer, int maxIngreso, sfEvent evento)
{
    int largoBuffer;

    largoBuffer = strlen (buffer);

    if ((evento.text.unicode != 13) && (evento.text.unicode != 8)) //Detecta que no sea la tecla "Enter" ni "Backspace"
    {
        if (largoBuffer < maxIngreso)
        {
            buffer [largoBuffer] = (char)evento.text.unicode;
            buffer [largoBuffer + 1] = '\0';
        }
    }
    else if ((evento.text.unicode == 8) && (largoBuffer > 0)) //Detecta que sea la tecla "Backspace"
        buffer [largoBuffer - 1] = '\0';
}

























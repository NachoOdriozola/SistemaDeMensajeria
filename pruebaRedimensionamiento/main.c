#include "main.h"

int main()
{
    inicializar ();
    setup ();

    cerrar = TRUE;
    while (cerrar == TRUE)
    {
        accion ();
        actualizar ();
        renderizar ();
    }
    liberar ();

    return 0;
}

void inicializar ()
{
    sfVideoMode tamPantalla;
    tamPantalla = sfVideoMode_getDesktopMode ();
    //tamPantalla.height -= 1;
    renderizado = sfRenderWindow_create (tamPantalla, "App", sfDefaultStyle, NULL);
    tamOriginalVentana.x = tamPantalla.width;
    tamOriginalVentana.y = tamPantalla.height;
    printf ("x: %.2f\ty: %.2f\n", tamOriginalVentana.x, tamOriginalVentana.y);

    rectangulo = sfRectangleShape_create ();
    texto = sfText_create ();
    fuente = sfFont_createFromFile ("fuente.ttf");
}

void setup ()
{
    sfRenderWindow_setFramerateLimit (renderizado, 60);

    sfRectangleShape_setFillColor (rectangulo, sfColor_fromRGB(255, 255, 255));
    sfRectangleShape_setSize (rectangulo, (sfVector2f){300, 250});
    sfRectangleShape_setPosition (rectangulo, (sfVector2f){900, 500});

    sfText_setString (texto, "hola");
    sfText_setCharacterSize (texto, 30);
    sfText_setPosition (texto, (sfVector2f){980, 520});
    sfText_setColor (texto, sfColor_fromRGB(100, 100, 100));
    sfText_setFont (texto, fuente);
}

void accion ()
{
    sfVector2f nuevoTamPantalla;
    sfVector2u pantalla;
    sfEvent evento;

    sfRenderWindow_pollEvent (renderizado, &evento);
    if (evento.type == sfEvtClosed)
        cerrar = FALSE;
    if (evento.type == sfEvtResized)
    {
        nuevoTamPantalla.x = evento.size.width;
        nuevoTamPantalla.y = evento.size.height;
        pantalla.x = evento.size.width;
        pantalla.y = evento.size.height;
        //sfRenderWindow_setSize (renderizado, pantalla);
        ajustarVista (nuevoTamPantalla);
    }
}

void actualizar ()
{

}

void renderizar ()
{
    sfRenderWindow_clear (renderizado, sfColor_fromRGB (0, 0, 0));

    sfRenderWindow_drawRectangleShape (renderizado, rectangulo, NULL);
    //sfRenderWindow_drawText (renderizado, texto, NULL);

    sfRenderWindow_display (renderizado);
}

void liberar ()
{
    sfText_destroy (texto);
    sfFont_destroy (fuente);
    sfRectangleShape_destroy (rectangulo);
    sfRenderWindow_destroy (renderizado);
}

void ajustarVista (sfVector2f nuevoTamPantalla)
{
    sfView *vista;

    vista = sfView_create ();
    sfView_setSize (vista, nuevoTamPantalla);
    sfView_setCenter (vista, (sfVector2f){nuevoTamPantalla.x / 2, nuevoTamPantalla.y / 2});
    sfRenderWindow_setView (renderizado, vista);
    sfView_destroy (vista);
}



















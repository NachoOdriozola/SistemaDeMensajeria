#include "interfazRegistro.h"


///FUNCIONES ESTRUCTURALES


int inicializarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    ///INICIALIZAR TEXTO
    recursosGraficosRegistro->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosRegistro->texto.fuente)
    {
        perror ("ERROR - Crear fuente.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.registrarse = sfText_create ();
    if (!recursosGraficosRegistro->texto.registrarse)
    {
        perror ("ERROR - Crear texto registrarse.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR RECURSOS
    recursosGraficosRegistro->elementos.rectanguloInvisibleVolver = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.rectanguloInvisibleVolver)
    {
        perror ("ERROR - Crear rectangulo inivisible para volver.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    ///SETUP TEXTO
    //Texto registrarse
    sfText_setFont (recursosGraficosRegistro->texto.registrarse, recursosGraficosRegistro->texto.fuente);
    sfText_setString (recursosGraficosRegistro->texto.registrarse, "REGISTRARSE");
    sfText_setColor (recursosGraficosRegistro->texto.registrarse, sfColor_fromRGB (34, 48, 48));


    ///SETUP ELEMENTOS
    //Rectangulo invisible para volver
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, sfColor_fromRGB (0, 0, 0));


    ///SETUP POS Y TAM
    tamYPosPantallaRegistro (recursosGraficosRegistro);
}

void tamYPosPantallaRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    ///SETUP POS Y TAM TEXTO
    //Texto registrarse
    sfText_setPosition (recursosGraficosRegistro->texto.registrarse, (sfVector2f){190, 25});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.registrarse, 36);


    ///SETUP POS Y TAM ELEMENTOS
    //Rectangulo invisible para volver
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, (sfVector2f){300, 250});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, (sfVector2f){100, 70});
}

void accionRegistro (s_aplicacion *app, s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;

    sfRenderWindow_pollEvent (app->renderizado, &evento);
    switch (evento.type)
    {
        case sfEvtClosed:
        app->aplicacionEjecutandose = CERRAR_APLICACION;
        break;

        case sfEvtResized:
        nuevoTamPantalla.x = evento.size.width;
        nuevoTamPantalla.y = evento.size.height;
        app->ventana.tamActualPantalla = nuevoTamPantalla;
        ajustarVista (app, nuevoTamPantalla);
        break;

        case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (clickEnRectangulo (app->renderizado, recursosGraficosRegistro->elementos.rectanguloInvisibleVolver))
                app->interfaz = INTERFAZ_INICIO;
        }

        default:
            break;
    }
}

void actualizarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{

}

void renderizarRegistro (s_aplicacion *app, s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));

    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.registrarse, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosRegistro->texto.fuente);
    sfText_destroy (recursosGraficosRegistro->texto.registrarse);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver);
}
































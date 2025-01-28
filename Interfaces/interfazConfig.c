#include "interfazConfig.h"


///FUNCIONES ESTRUCTURALES


int inicializarConfig (s_recursosGraficosConfig *recursosGraficosConfig)
{
    ///INICIALIZAR TEXTO
    recursosGraficosConfig->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosConfig->texto.fuente)
    {
        perror ("ERROR - Crear fuente.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosConfig->texto.textoConfig = sfText_create ();
    if (!recursosGraficosConfig->texto.textoConfig)
    {
        perror ("ERROR - Crear texto config.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosConfig->elementos.rectanguloVolver = sfRectangleShape_create ();
    if (!recursosGraficosConfig->elementos.rectanguloVolver)
    {
        perror ("ERROR - Crear rectangulo para volver.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig)
{
    ///SETUP TEXTO
    //Texto config
    sfText_setFont (recursosGraficosConfig->texto.textoConfig, recursosGraficosConfig->texto.fuente);
    sfText_setString (recursosGraficosConfig->texto.textoConfig, "CONFIGURACIONES");
    sfText_setFillColor (recursosGraficosConfig->texto.textoConfig, sfColor_fromRGB (0, 0, 0));


    ///SETUP ELEMENTOS
    //Rectangulo para volver
    sfRectangleShape_setFillColor (recursosGraficosConfig->elementos.rectanguloVolver, sfColor_fromRGB (0, 0, 0));


    ///SETUP TAM Y POS
    tamYPosPantallaConfig (app, recursosGraficosConfig);
}

void tamYPosPantallaConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig)
{
    ///TAM Y POS TEXTO
    //Texto config
    sfText_setPosition (recursosGraficosConfig->texto.textoConfig, (sfVector2f){1000 * app->ventana.escalaElementos.x, 500 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosConfig->texto.textoConfig, 36 * app->ventana.escalaPixeles);


    ///TAM Y POS ELEMENTOS
    //Rectangulo para volver
    sfRectangleShape_setPosition (recursosGraficosConfig->elementos.rectanguloVolver, (sfVector2f){1000 * app->ventana.escalaElementos.x, 650 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosConfig->elementos.rectanguloVolver, (sfVector2f){60 * app->ventana.escalaElementos.x, 60 * app->ventana.escalaElementos.y});
}

void accionConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig)
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
            if (clickEnRectangulo (app->renderizado, recursosGraficosConfig->elementos.rectanguloVolver))
                app->interfaz = app->usuario.ultimaInterfaz;
        }

    default:
        break;
    }
}

void actualizarConfig (s_recursosGraficosConfig *recursosGraficosConfig)
{

}

void renderizarConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosConfig->elementos.rectanguloVolver, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosConfig->texto.textoConfig, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarConfig (s_recursosGraficosConfig *recursosGraficosConfig)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosConfig->texto.fuente);
    sfText_destroy (recursosGraficosConfig->texto.textoConfig);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosConfig->elementos.rectanguloVolver);
}



















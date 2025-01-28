#include "interfazSalas.h"

int inicializarSalas (s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///INICIALIZAR TEXTO
    recursosGraficosSalas->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosSalas->texto.fuente)
    {
        perror ("ERROR - Crear fuente.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->texto.salas = sfText_create ();
    if (!recursosGraficosSalas->texto.salas)
    {
        perror ("ERROR - Crear texto salas.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosSalas->elementos.rectanguloAmigos = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.rectanguloAmigos)
    {
        perror ("ERROR - Crear rectangulo para ir a amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosSalas->elementos.rectanguloConfig = sfRectangleShape_create ();
    if (!recursosGraficosSalas->elementos.rectanguloConfig)
    {
        perror ("ERROR - Crear rectangulo para ir a las config.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///SETUP TEXTO
    //Texto salas
    sfText_setFont (recursosGraficosSalas->texto.salas, recursosGraficosSalas->texto.fuente);
    sfText_setString (recursosGraficosSalas->texto.salas, "SALAS");
    sfText_setFillColor (recursosGraficosSalas->texto.salas, sfColor_fromRGB (0, 0, 0));


    ///SETUP ELEMENTOS
    //Rectangulo para ir a amigos
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.rectanguloAmigos, sfColor_fromRGB (0, 0, 0));

    //Rectangulo para ir a las config
    sfRectangleShape_setFillColor (recursosGraficosSalas->elementos.rectanguloConfig, sfColor_fromRGB (0, 150, 150));
}

void tamYPosPantallaSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///TAM Y POS TEXTO
    //Texto salas
    sfText_setPosition (recursosGraficosSalas->texto.salas, (sfVector2f){1000 * app->ventana.escalaElementos.x, 500 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosSalas->texto.salas, 36 * app->ventana.escalaPixeles);


    ///TAM Y POS ELEMENTOS
    //Rectangulo para ir a amigos
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.rectanguloAmigos, (sfVector2f){1200 * app->ventana.escalaElementos.x, 600 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.rectanguloAmigos, (sfVector2f){60 * app->ventana.escalaElementos.x, 60 * app->ventana.escalaElementos.y});

    //Rectangulo para ir a las config
    sfRectangleShape_setPosition (recursosGraficosSalas->elementos.rectanguloConfig, (sfVector2f){1200 * app->ventana.escalaElementos.x, 750 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosSalas->elementos.rectanguloConfig, (sfVector2f){60 * app->ventana.escalaElementos.x, 60 * app->ventana.escalaElementos.y});
}

void accionSalas (s_aplicacion *app, s_socket *sock, s_recursosGraficosSalas *recursosGraficosSalas)
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
            if (clickEnRectangulo (app->renderizado, recursosGraficosSalas->elementos.rectanguloAmigos))
                app->interfaz = INTERFAZ_AMIGOS;

            if (clickEnRectangulo (app->renderizado, recursosGraficosSalas->elementos.rectanguloConfig))
                app->interfaz = INTERFAZ_CONFIG;
        }

    default:
        break;
    }
}

void actualizarSalas (s_aplicacion *app, s_socket *sock, s_recursosGraficosSalas *recursosGraficosSalas)
{

}

void renderizarSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.rectanguloAmigos, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosSalas->elementos.rectanguloConfig, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosSalas->texto.salas, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarSalas (s_recursosGraficosSalas *recursosGraficosSalas)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosSalas->texto.fuente);
    sfText_destroy (recursosGraficosSalas->texto.salas);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.rectanguloAmigos);
    sfRectangleShape_destroy (recursosGraficosSalas->elementos.rectanguloConfig);
}

















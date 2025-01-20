#include "interfazInicio.h"

///FUNCIONES ESTRUCTURALES

int inicializarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///INICIALIZAR TEXTO



    ///INICIALIZAR ELEMENTOS
    recursosGraficosInicio->elementos.rectanguloCentral = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.rectanguloCentral)
    {
        perror ("ERROR - Crear rectangulo central.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP TEXTO


    ///SETUP ELEMENTOS
    //Rectangulo central
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.rectanguloCentral, sfColor_fromRGB (232, 217, 205));


    ///SETUP EVENTO PRIMER MAXIMIZADO, POSICIONES Y TAMANIOS
    sfEvent eventoPrimerMaximizado;
    sfVector2f nuevoTamPantalla;

    sfRenderWindow_pollEvent (app->renderizado, &eventoPrimerMaximizado);
    if (eventoPrimerMaximizado.type == sfEvtResized)
    {
        nuevoTamPantalla.x = eventoPrimerMaximizado.size.width;
        nuevoTamPantalla.y = eventoPrimerMaximizado.size.height;
        app->ventana.tamOriginalPantalla = nuevoTamPantalla;
        modificarTamPantallaInicio (app, recursosGraficosInicio, nuevoTamPantalla);
    }
}

void accionInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
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
        modificarTamPantallaInicio (app, recursosGraficosInicio, nuevoTamPantalla);
        break;

        default:
            break;
    }
}

void actualizarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{

}

void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.rectanguloCentral, NULL);


    ///RENDERIZAR TEXTO


    sfRenderWindow_display (app->renderizado);
}

void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///LIBERAR TEXTO


    ///LIBERAR ELEMENTOS
    //Rectangulo central
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.rectanguloCentral);
}

///FUNCIONES LOGICAS

void modificarTamPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio, sfVector2f nuevoTamPantalla)
{
    ///AJUSTAR VISTA
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


    ///MODIFICAR ESCALA
    float escala;

    escala = sqrt ((nuevoTamPantalla.x * nuevoTamPantalla.y) / (app->ventana.tamOriginalPantalla.x * app->ventana.tamOriginalPantalla.y));
    app->ventana.escala = escala;


    ///MODIFICAR TAM TEXTO


    ///MODIFICAR TAM ELEMENTOS
    //Rectangulo central
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.rectanguloCentral, (sfVector2f){nuevoTamPantalla.x / 1.45, nuevoTamPantalla.y / 3.5});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.rectanguloCentral, (sfVector2f){nuevoTamPantalla.x / 3.2, nuevoTamPantalla.y / 2});


    ///MODIFICAR TAM ACTUAL PANTALLA
    app->ventana.tamActualPantalla = nuevoTamPantalla;
}









































#include "interfazInicio.h"


///FUNCIONES ESTRUCTURALES


int inicializarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///INICIALIZAR TEXTO
    recursosGraficosInicio->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosInicio->texto.fuente)
    {
        perror ("ERROR - Crear fuente para recursos graficos de inicio.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.ingresarNombre = sfText_create ();
    if (!recursosGraficosInicio->texto.ingresarNombre)
    {
        perror ("ERROR - Crear texto ingresar nombre.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.auxEscribirNombre = sfText_create ();
    if (!recursosGraficosInicio->texto.auxEscribirNombre)
    {
        perror ("ERROR - Crear texto auxiliar escribir nombre.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosInicio->elementos.rectanguloCentral = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.rectanguloCentral)
    {
        perror ("ERROR - Crear rectangulo central.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->elementos.barraIngresarNombre = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.barraIngresarNombre)
    {
        perror ("ERROR - Crear barra para ingresar nombre.\n");
        return ERROR_INICIALIZACION;
    }

    return OK;
}

void setupInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP ESCRITURA
    recursosGraficosInicio->habilitarEscritura = DESHABILITAR_ESCRITURA;
    *(recursosGraficosInicio->bufferEscribirNombre) = '\0';


    ///SETUP TEXTO
    //Texto ingresar nombre
    sfText_setFont (recursosGraficosInicio->texto.ingresarNombre, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.ingresarNombre, "INGRESE SU NOMBRE DE USUARIO");
    sfText_setColor (recursosGraficosInicio->texto.ingresarNombre, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir nombre
    sfText_setFont (recursosGraficosInicio->texto.auxEscribirNombre, recursosGraficosInicio->texto.fuente);
    sfText_setColor (recursosGraficosInicio->texto.auxEscribirNombre, sfColor_fromRGB (40, 54, 54));


    ///SETUP ELEMENTOS
    //Rectangulo central
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.rectanguloCentral, sfColor_fromRGB (232, 217, 205));

    //Barra para ingresar nombre
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarNombre, sfColor_fromRGB (208, 208, 208));


    ///SETUP POSICIONES Y TAMANIOS
    tamYPosPantallaInicio (app, recursosGraficosInicio);
}

void accionInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;
    int largoBufferNombre;

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
            if (clickEnEscribirNombre (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre))
                recursosGraficosInicio->habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosInicio->habilitarEscritura = DESHABILITAR_ESCRITURA;
        }
        break;

        case sfEvtTextEntered:
        if ((recursosGraficosInicio->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (evento.text.unicode < 128) &&
            (evento.text.unicode != 13) && //Detecta que no sea la tecla "Enter"
            ((largoBufferNombre = strlen(recursosGraficosInicio->bufferEscribirNombre)) < MAX_NOMBRE_USUARIO - 1))
        {
            if (evento.text.unicode != 8) //Detecta que no sea la tecla "Backspace"
            {
                recursosGraficosInicio->bufferEscribirNombre [largoBufferNombre] = (char)evento.text.unicode;
                recursosGraficosInicio->bufferEscribirNombre [largoBufferNombre + 1] = '\0';
            }
            else if (largoBufferNombre > 0)
                recursosGraficosInicio->bufferEscribirNombre [largoBufferNombre - 1] = '\0';
        }

        if ((recursosGraficosInicio->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (evento.text.unicode == 8) && //Detecta que sea la tecla "Backspace"
            (largoBufferNombre == MAX_NOMBRE_USUARIO - 1)) //Es la ultima letra en el buffer
        {
            recursosGraficosInicio->bufferEscribirNombre [largoBufferNombre - 1] = '\0';
        }

        sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, recursosGraficosInicio->bufferEscribirNombre);
        break;

        case sfEvtKeyPressed:
        if ((recursosGraficosInicio->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (evento.key.code == sfKeyEnter) &&
            (strlen (recursosGraficosInicio->bufferEscribirNombre) > 0))
        {
            app->usuario.actividadUsuario = ACTIVO;
            strcpy (app->usuario.nombreUsuario, recursosGraficosInicio->bufferEscribirNombre);
        }
        break;

        default:
            break;
    }
}

void actualizarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    if ((recursosGraficosInicio->habilitarEscritura == DESHABILITAR_ESCRITURA) && ((strlen (recursosGraficosInicio->bufferEscribirNombre) == 0)))
        sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, "Escriba su nombre...");
}

void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.rectanguloCentral, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirNombre, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosInicio->texto.fuente);
    sfText_destroy (recursosGraficosInicio->texto.ingresarNombre);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirNombre);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.rectanguloCentral);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarNombre);
}


///FUNCIONES LOGICAS


void tamYPosPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///MODIFICAR TAM TEXTO
    //Texto ingresar nombre
    sfText_setPosition (recursosGraficosInicio->texto.ingresarNombre, (sfVector2f){800 * app->ventana.escalaElementos.x, 415 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarNombre, 36 * app->ventana.escalaPixeles);

    //Texto auxiliar escribir nombre
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirNombre, (sfVector2f){750 * app->ventana.escalaElementos.x, 555 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirNombre, 24 * app->ventana.escalaPixeles);


    ///MODIFICAR TAM ELEMENTOS
    //Rectangulo central
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.rectanguloCentral, (sfVector2f){660 * app->ventana.escalaElementos.x, 259 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.rectanguloCentral, (sfVector2f){600 * app->ventana.escalaElementos.x, 500 * app->ventana.escalaElementos.y});

    //Barra ingresar nombre
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){735 * app->ventana.escalaElementos.x, 550 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){450 * app->ventana.escalaElementos.x, 42 * app->ventana.escalaElementos.y});
}

bool clickEnEscribirNombre (sfRenderWindow *renderizado, sfRectangleShape *barraIngresarNombre)
{
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (barraIngresarNombre);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}







































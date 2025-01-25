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

    recursosGraficosInicio->texto.textoBotonAceptar = sfText_create ();
    if (!recursosGraficosInicio->texto.textoBotonAceptar)
    {
        perror ("ERROR - Crear texto para boton aceptar nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.textoInformativoTamNombre = sfText_create ();
    if (!recursosGraficosInicio->texto.textoInformativoTamNombre)
    {
        perror ("ERROR - Crear texto informativo para tam maximo del nombre.\n");
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

    recursosGraficosInicio->elementos.botonAceptar = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.botonAceptar)
    {
        perror ("ERROR - Crear boton aceptar.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->elementos.circuloTextoInformativo = sfCircleShape_create ();
    if (!recursosGraficosInicio->elementos.circuloTextoInformativo)
    {
        perror ("ERROR - Crear circulo de texto informativo.\n");
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

    //Texto boton aceptar nombre de usuario
    sfText_setFont (recursosGraficosInicio->texto.textoBotonAceptar, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoBotonAceptar, "ACEPTAR");

    //Texto informativo tam maximo nombre de usuaio
    sfText_setFont (recursosGraficosInicio->texto.textoInformativoTamNombre, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoInformativoTamNombre, "La longitud maxima del nombre es hasta 20 caracteres.");


    ///SETUP ELEMENTOS
    //Rectangulo central
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.rectanguloCentral, sfColor_fromRGB (232, 217, 205));

    //Barra para ingresar nombre
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarNombre, sfColor_fromRGB (208, 208, 208));

    //Boton aceptar nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.botonAceptar, sfColor_fromRGB (208, 208, 208));


    ///SETUP POS Y TAM
    tamYPosPantallaInicio (app, recursosGraficosInicio);
}

void tamYPosPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP POS Y TAM TEXTO
    //Texto ingresar nombre
    sfText_setPosition (recursosGraficosInicio->texto.ingresarNombre, (sfVector2f){800 * app->ventana.escalaElementos.x, 390 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarNombre, 36 * app->ventana.escalaPixeles);

    //Texto auxiliar escribir nombre
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirNombre, (sfVector2f){750 * app->ventana.escalaElementos.x, 554 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirNombre, 26 * app->ventana.escalaPixeles);

    //Texto boton aceptar nombre de usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoBotonAceptar, (sfVector2f){918 * app->ventana.escalaElementos.x, 657 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoBotonAceptar, 30 * app->ventana.escalaPixeles);

    //Texto informativo tam maximo nombre de usuaio
    sfText_setPosition (recursosGraficosInicio->texto.textoInformativoTamNombre, (sfVector2f){730 * app->ventana.escalaElementos.x, 475 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoInformativoTamNombre, 30 * app->ventana.escalaPixeles);


    ///SETUP POS Y TAM ELEMENTOS
    //Rectangulo central
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.rectanguloCentral, (sfVector2f){660 * app->ventana.escalaElementos.x, 259 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.rectanguloCentral, (sfVector2f){600 * app->ventana.escalaElementos.x, 500 * app->ventana.escalaElementos.y});

    //Barra ingresar nombre
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){735 * app->ventana.escalaElementos.x, 550 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){450 * app->ventana.escalaElementos.x, 42 * app->ventana.escalaElementos.y});

    //Boton aceptar nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.botonAceptar, (sfVector2f){880 * app->ventana.escalaElementos.x, 650 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.botonAceptar, (sfVector2f){150 * app->ventana.escalaElementos.x, 50 * app->ventana.escalaElementos.y});
    sfRectangleShape_setOutlineThickness (recursosGraficosInicio->elementos.botonAceptar, 5 * app->ventana.escalaPixeles);

    //Circulo de texto informativo
    sfCircleShape_setPosition (recursosGraficosInicio->elementos.circuloTextoInformativo, (sfVector2f){710 * app->ventana.escalaElementos.x, 489 * app->ventana.escalaElementos.y});
    sfCircleShape_setRadius (recursosGraficosInicio->elementos.circuloTextoInformativo, 6 * app->ventana.escalaPixeles);
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
            if (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre))
                recursosGraficosInicio->habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosInicio->habilitarEscritura = DESHABILITAR_ESCRITURA;

            if ((strlen (recursosGraficosInicio->bufferEscribirNombre) > 0) && (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.botonAceptar)))
            {
                app->usuario.actividadUsuario = ACTIVO;
                strcpy (app->usuario.nombreUsuario, recursosGraficosInicio->bufferEscribirNombre);
            }
        }
        break;

        case sfEvtTextEntered:
        if ((recursosGraficosInicio->habilitarEscritura == HABILITAR_ESCRITURA) && (evento.text.unicode < 128))
        {
            largoBufferNombre = strlen (recursosGraficosInicio->bufferEscribirNombre);

            if ((evento.text.unicode != 13) && (evento.text.unicode != 8)) //Detecta que no sea la tecla "Enter" ni "Backspace"
            {
                if (largoBufferNombre < MAX_NOMBRE_USUARIO - 1)
                {
                    recursosGraficosInicio->bufferEscribirNombre [largoBufferNombre] = (char)evento.text.unicode;
                    recursosGraficosInicio->bufferEscribirNombre [largoBufferNombre + 1] = '\0';
                }
                else
                {
                    sfText_setColor (recursosGraficosInicio->texto.textoInformativoTamNombre, sfColor_fromRGB (233, 12, 0));
                    sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativo, sfColor_fromRGB (233, 12, 0));
                }
            }

            if ((evento.text.unicode == 8) && (largoBufferNombre > 0)) //Detecta que sea la tecla "Backspace"
                recursosGraficosInicio->bufferEscribirNombre [largoBufferNombre - 1] = '\0';

            sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, recursosGraficosInicio->bufferEscribirNombre);
        }
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
    int largoBufferEscribirNombre;

    largoBufferEscribirNombre = strlen (recursosGraficosInicio->bufferEscribirNombre);


    if ((recursosGraficosInicio->habilitarEscritura == DESHABILITAR_ESCRITURA) && (largoBufferEscribirNombre == 0))
        sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, "Escriba su nombre...");


    if (largoBufferEscribirNombre > 0)
    {
        sfText_setColor (recursosGraficosInicio->texto.textoBotonAceptar, sfColor_fromRGB (40, 54, 54));
        sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonAceptar, sfColor_fromRGB (40, 54, 54));
    }
    else
    {
        sfText_setColor (recursosGraficosInicio->texto.textoBotonAceptar, sfColor_fromRGB (235, 235, 235));
        sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonAceptar, sfColor_fromRGB (235, 235, 235));
    }


    if (largoBufferEscribirNombre == 0)
    {
        sfText_setColor (recursosGraficosInicio->texto.textoInformativoTamNombre, sfColor_fromRGB (235, 235, 235));
        sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativo, sfColor_fromRGB (235, 235, 235));
    }
    else if ((largoBufferEscribirNombre > 0) && (largoBufferEscribirNombre < MAX_NOMBRE_USUARIO - 1))
    {
        sfText_setColor (recursosGraficosInicio->texto.textoInformativoTamNombre, sfColor_fromRGB (76, 175, 80));
        sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativo, sfColor_fromRGB (76, 175, 80));
    }
}

void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.rectanguloCentral, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.botonAceptar, NULL);
    sfRenderWindow_drawCircleShape (app->renderizado, recursosGraficosInicio->elementos.circuloTextoInformativo, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoBotonAceptar, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoInformativoTamNombre, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosInicio->texto.fuente);
    sfText_destroy (recursosGraficosInicio->texto.ingresarNombre);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirNombre);
    sfText_destroy (recursosGraficosInicio->texto.textoBotonAceptar);
    sfText_destroy (recursosGraficosInicio->texto.textoInformativoTamNombre);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.rectanguloCentral);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarNombre);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.botonAceptar);
    sfCircleShape_destroy (recursosGraficosInicio->elementos.circuloTextoInformativo);
}








































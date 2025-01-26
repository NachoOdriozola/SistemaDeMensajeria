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

    recursosGraficosInicio->texto.ingresarUsuario = sfText_create ();
    if (!recursosGraficosInicio->texto.ingresarUsuario)
    {
        perror ("ERROR - Crear texto ingresar usuario.\n");
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

    recursosGraficosInicio->texto.ingresarContrasenia = sfText_create ();
    if (!recursosGraficosInicio->texto.ingresarContrasenia)
    {
        perror ("ERROR - Crear texto ingresar contrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.auxEscribirContrasenia = sfText_create ();
    if (!recursosGraficosInicio->texto.auxEscribirContrasenia)
    {
        perror ("ERROR - Crear texto auxiliar escribir contrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.textoRegistrarUsuario = sfText_create ();
    if (!recursosGraficosInicio->texto.textoRegistrarUsuario)
    {
        perror ("ERROR - Crear texto registrar usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.textoBotonAceptar = sfText_create ();
    if (!recursosGraficosInicio->texto.textoBotonAceptar)
    {
        perror ("ERROR - Crear texto para boton aceptar nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.textoInformativoTam = sfText_create ();
    if (!recursosGraficosInicio->texto.textoInformativoTam)
    {
        perror ("ERROR - Crear texto informativo para tam maximo del nombre.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosInicio->elementos.barraIngresarNombre = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.barraIngresarNombre)
    {
        perror ("ERROR - Crear barra para ingresar nombre.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->elementos.barraIngresarContrasenia = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.barraIngresarContrasenia)
    {
        perror ("ERROR - Crear barra para ingresar contrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->elementos.botonAceptar = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.botonAceptar)
    {
        perror ("ERROR - Crear boton aceptar.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->elementos.circuloTextoInformativoTam = sfCircleShape_create ();
    if (!recursosGraficosInicio->elementos.circuloTextoInformativoTam)
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
    sfText_setFont (recursosGraficosInicio->texto.ingresarUsuario, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.ingresarUsuario, "INGRESE SU USUARIO");
    sfText_setColor (recursosGraficosInicio->texto.ingresarUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto ingresar nombre
    sfText_setFont (recursosGraficosInicio->texto.ingresarNombre, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.ingresarNombre, "Ingrese su nombre:");
    sfText_setColor (recursosGraficosInicio->texto.ingresarNombre, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir nombre
    sfText_setFont (recursosGraficosInicio->texto.auxEscribirNombre, recursosGraficosInicio->texto.fuente);
    sfText_setColor (recursosGraficosInicio->texto.auxEscribirNombre, sfColor_fromRGB (40, 54, 54));

    //Texto ingresar contrasenia
    sfText_setFont (recursosGraficosInicio->texto.ingresarContrasenia, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.ingresarContrasenia, "Ingrese su contraseña:");
    sfText_setColor (recursosGraficosInicio->texto.ingresarContrasenia, sfColor_fromRGB (40, 54, 54));

    //Texto auxiliar escribir contrasenia
    sfText_setFont (recursosGraficosInicio->texto.auxEscribirContrasenia, recursosGraficosInicio->texto.fuente);
    sfText_setColor (recursosGraficosInicio->texto.auxEscribirContrasenia, sfColor_fromRGB (40, 54, 54));

    //Texto registrar usuario
    sfText_setFont (recursosGraficosInicio->texto.textoRegistrarUsuario, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoRegistrarUsuario, "¿No tenes usuario? Registrate aca.");
    sfText_setColor (recursosGraficosInicio->texto.textoRegistrarUsuario, sfColor_fromRGB (40, 54, 54));

    //Texto boton aceptar nombre de usuario
    sfText_setFont (recursosGraficosInicio->texto.textoBotonAceptar, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoBotonAceptar, "ACEPTAR");

    //Texto informativo tam maximo nombre y contrasenia
    sfText_setFont (recursosGraficosInicio->texto.textoInformativoTam, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoInformativoTam, "La longitud maxima del nombre y de la contraseña es\nhasta 20 caracteres.");


    ///SETUP ELEMENTOS
    //Barra para ingresar nombre
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarNombre, sfColor_fromRGB (208, 208, 208));

    //Barra para ingresar contrasenia
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarContrasenia, sfColor_fromRGB (208, 208, 208));

    //Boton aceptar nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.botonAceptar, sfColor_fromRGB (208, 208, 208));


    ///SETUP POS Y TAM
    tamYPosPantallaInicio (app, recursosGraficosInicio);
}

void tamYPosPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP POS Y TAM TEXTO
    //Texto ingresar usuario
    sfText_setPosition (recursosGraficosInicio->texto.ingresarUsuario, (sfVector2f){170, 25});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarUsuario, 36);

    //Texto ingresar nombre
    sfText_setPosition (recursosGraficosInicio->texto.ingresarNombre, (sfVector2f){55, 180});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarNombre, 28);

    //Texto auxiliar escribir nombre
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirNombre, (sfVector2f){64, 227});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirNombre, 24);

    //Texto ingresar contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.ingresarContrasenia, (sfVector2f){55, 282});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarContrasenia, 28);

    //Texto auxiliar escribir contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirContrasenia, (sfVector2f){64, 329});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirContrasenia, 24);

    //Texto registrar usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoRegistrarUsuario, (sfVector2f){125, 386});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoRegistrarUsuario, 26);

    //Texto boton aceptar nombre de usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoBotonAceptar, (sfVector2f){255, 75});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoBotonAceptar, 30);

    //Texto informativo tam maximo nombre y contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.textoInformativoTam, (sfVector2f){55, 103});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoInformativoTam, 24);


    ///SETUP POS Y TAM ELEMENTOS
    //Barra ingresar nombre
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){55, 228});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){420, 30});

    //Barra ingresar contrasenia
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){55, 330});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){420, 30});

    //Boton aceptar nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.botonAceptar, (sfVector2f){250, 450});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.botonAceptar, (sfVector2f){100, 60});
    sfRectangleShape_setOutlineThickness (recursosGraficosInicio->elementos.botonAceptar, 3);

    //Circulo de texto informativo tam
    sfCircleShape_setPosition (recursosGraficosInicio->elementos.circuloTextoInformativoTam, (sfVector2f){40, 115});
    sfCircleShape_setRadius (recursosGraficosInicio->elementos.circuloTextoInformativoTam, 5);
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
                app->interfaz = INTERFAZ_MENSAJES;
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
                    sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (233, 12, 0));
                    sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (233, 12, 0));
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
            app->interfaz = INTERFAZ_MENSAJES;
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
        sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (34, 48, 48));
        sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (34, 48, 48));
    }
    else if ((largoBufferEscribirNombre > 0) && (largoBufferEscribirNombre < MAX_NOMBRE_USUARIO - 1))
    {
        sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (76, 175, 80));
        sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (76, 175, 80));
    }
}

void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.botonAceptar, NULL);
    sfRenderWindow_drawCircleShape (app->renderizado, recursosGraficosInicio->elementos.circuloTextoInformativoTam, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoRegistrarUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoBotonAceptar, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoInformativoTam, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosInicio->texto.fuente);
    sfText_destroy (recursosGraficosInicio->texto.ingresarUsuario);
    sfText_destroy (recursosGraficosInicio->texto.ingresarNombre);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirNombre);
    sfText_destroy (recursosGraficosInicio->texto.ingresarContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.textoRegistrarUsuario);
    sfText_destroy (recursosGraficosInicio->texto.textoBotonAceptar);
    sfText_destroy (recursosGraficosInicio->texto.textoInformativoTam);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarNombre);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarContrasenia);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.botonAceptar);
    sfCircleShape_destroy (recursosGraficosInicio->elementos.circuloTextoInformativoTam);
}








































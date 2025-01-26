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

    recursosGraficosInicio->texto.textoInformativoTam = sfText_create ();
    if (!recursosGraficosInicio->texto.textoInformativoTam)
    {
        perror ("ERROR - Crear texto informativo para tam maximo del nombre.\n");
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

    recursosGraficosInicio->texto.textoBotonIngresar = sfText_create ();
    if (!recursosGraficosInicio->texto.textoBotonIngresar)
    {
        perror ("ERROR - Crear texto para boton aceptar nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosInicio->elementos.subrayadoTitulo = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.subrayadoTitulo)
    {
        perror ("ERROR - Crear subrayado para titulo.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->elementos.circuloTextoInformativoTam = sfCircleShape_create ();
    if (!recursosGraficosInicio->elementos.circuloTextoInformativoTam)
    {
        perror ("ERROR - Crear circulo de texto informativo.\n");
        return ERROR_INICIALIZACION;
    }

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

    recursosGraficosInicio->elementos.botonIngresar = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.botonIngresar)
    {
        perror ("ERROR - Crear boton aceptar.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar)
    {
        perror ("ERROR - Crear rectangulo invisible para registrar usuario.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP ESCRITURA
    recursosGraficosInicio->habilitarEscrituraNombre = DESHABILITAR_ESCRITURA_NOMBRE;
    recursosGraficosInicio->habilitarEscrituraContrasenia = DESHABILITAR_ESCRITURA_CONTRASENIA;
    recursosGraficosInicio->habilitarIngreso = DESHABILITAR_INGRESO;
    *(recursosGraficosInicio->bufferEscribirNombre) = '\0';
    *(recursosGraficosInicio->bufferEscribirContrasenia) = '\0';


    ///SETUP TEXTO
    //Texto ingresar usuario
    sfText_setFont (recursosGraficosInicio->texto.ingresarUsuario, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.ingresarUsuario, "INGRESE SU USUARIO");
    sfText_setColor (recursosGraficosInicio->texto.ingresarUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto informativo tam maximo nombre y contrasenia
    sfText_setFont (recursosGraficosInicio->texto.textoInformativoTam, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoInformativoTam, "La longitud maxima del nombre y de la contraseña es\nhasta 20 caracteres.");

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
    sfText_setFont (recursosGraficosInicio->texto.textoBotonIngresar, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoBotonIngresar, "INGRESAR");


    ///SETUP ELEMENTOS
    //Subrayado para el titulo
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.subrayadoTitulo, sfColor_fromRGB (40, 54, 54));

    //Barra para ingresar nombre
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarNombre, sfColor_fromRGB (208, 208, 208));

    //Barra para ingresar contrasenia
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarContrasenia, sfColor_fromRGB (208, 208, 208));

    //Boton aceptar nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (208, 208, 208));

    //Rectangulo invisible para registrar usuario
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar, sfColor_fromRGB (223, 231, 233));


    ///SETUP POS Y TAM
    tamYPosPantallaInicio (app, recursosGraficosInicio);
}

void tamYPosPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP POS Y TAM TEXTO
    //Texto ingresar usuario
    sfText_setPosition (recursosGraficosInicio->texto.ingresarUsuario, (sfVector2f){170, 25});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarUsuario, 36);

    //Texto informativo tam maximo nombre y contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.textoInformativoTam, (sfVector2f){55, 106});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoInformativoTam, 24);

    //Texto ingresar nombre
    sfText_setPosition (recursosGraficosInicio->texto.ingresarNombre, (sfVector2f){55, 184});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarNombre, 28);

    //Texto auxiliar escribir nombre
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirNombre, (sfVector2f){64, 231});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirNombre, 24);

    //Texto ingresar contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.ingresarContrasenia, (sfVector2f){55, 282});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarContrasenia, 28);

    //Texto auxiliar escribir contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirContrasenia, (sfVector2f){64, 329});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirContrasenia, 24);

    //Texto registrar usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoRegistrarUsuario, (sfVector2f){130, 435});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoRegistrarUsuario, 26);

    //Texto boton aceptar nombre de usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoBotonIngresar, (sfVector2f){227, 385});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoBotonIngresar, 28);


    ///SETUP POS Y TAM ELEMENTOS
    //Subrayado para el titulo
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.subrayadoTitulo, (sfVector2f){160, 75});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.subrayadoTitulo, (sfVector2f){217, 2.5});

    //Circulo de texto informativo tam
    sfCircleShape_setPosition (recursosGraficosInicio->elementos.circuloTextoInformativoTam, (sfVector2f){40, 118});
    sfCircleShape_setRadius (recursosGraficosInicio->elementos.circuloTextoInformativoTam, 5);

    //Barra ingresar nombre
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){55, 232});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){420, 30});

    //Barra ingresar contrasenia
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){55, 330});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){420, 30});

    //Boton ingresar usuario
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.botonIngresar, (sfVector2f){195, 385});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.botonIngresar, (sfVector2f){140, 35});
    sfRectangleShape_setOutlineThickness (recursosGraficosInicio->elementos.botonIngresar, 2);

    //Rectangulo invisible para registrar usuario
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar, (sfVector2f){127, 437});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar, (sfVector2f){285, 30});
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
        app->ventana.tamActualPantalla = nuevoTamPantalla;
        ajustarVista (app, nuevoTamPantalla);
        break;

        case sfEvtMouseButtonPressed:
        if (evento.mouseButton.button == sfMouseLeft)
        {
            if (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre))
                recursosGraficosInicio->habilitarEscrituraNombre = HABILITAR_ESCRITURA_NOMBRE;
            else
                recursosGraficosInicio->habilitarEscrituraNombre = DESHABILITAR_ESCRITURA_NOMBRE;

            if (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.barraIngresarContrasenia))
                recursosGraficosInicio->habilitarEscrituraContrasenia = HABILITAR_ESCRITURA_CONTRASENIA;
            else
                recursosGraficosInicio->habilitarEscrituraContrasenia = DESHABILITAR_ESCRITURA_CONTRASENIA;

            if (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar)) //TEMPORAL
                printf ("Se clickeo el rectangulo de registrar usuario.\n");


            if ((recursosGraficosInicio->habilitarIngreso == HABILITAR_INGRESO) && (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.botonIngresar)))
            {
                app->interfaz = INTERFAZ_MENSAJES;
                strcpy (app->usuario.nombreUsuario, recursosGraficosInicio->bufferEscribirNombre);
            }
        }
        break;

        case sfEvtTextEntered:
        if ((recursosGraficosInicio->habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosInicio->bufferEscribirNombre, evento);
            sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, recursosGraficosInicio->bufferEscribirNombre);
        }
        if ((recursosGraficosInicio->habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosInicio->bufferEscribirContrasenia, evento);
            sfText_setString (recursosGraficosInicio->texto.auxEscribirContrasenia, recursosGraficosInicio->bufferEscribirContrasenia);
        }
        break;

        case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosInicio->habilitarIngreso == HABILITAR_INGRESO) &&
            ((recursosGraficosInicio->habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) || (recursosGraficosInicio->habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA)))
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
    int largoBufferEscribirNombre, largoBufferEscribirContrasenia;

    largoBufferEscribirNombre = strlen (recursosGraficosInicio->bufferEscribirNombre);
    largoBufferEscribirContrasenia = strlen (recursosGraficosInicio->bufferEscribirContrasenia);


    if ((recursosGraficosInicio->habilitarEscrituraNombre == DESHABILITAR_ESCRITURA_NOMBRE) && (largoBufferEscribirNombre == 0))
        sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, "Escriba su nombre...");

    if ((recursosGraficosInicio->habilitarEscrituraContrasenia == DESHABILITAR_ESCRITURA_CONTRASENIA) && (largoBufferEscribirContrasenia == 0))
        sfText_setString (recursosGraficosInicio->texto.auxEscribirContrasenia, "Escriba su contraseña...");


    if ((largoBufferEscribirNombre == 0) && (largoBufferEscribirContrasenia == 0))
    {
        recursosGraficosInicio->habilitarIngreso= DESHABILITAR_INGRESO;
        sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (34, 48, 48));
        sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (34, 48, 48));
        sfText_setColor (recursosGraficosInicio->texto.textoBotonIngresar, sfColor_fromRGB (34, 48, 48));
        sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (34, 48, 48));
    }
    else if (((largoBufferEscribirNombre > 0) && (largoBufferEscribirNombre < MAX_NOMBRE_USUARIO) &&
              (largoBufferEscribirContrasenia > 0) && (largoBufferEscribirContrasenia < MAX_CONTRASENIA_USUARIO)))
        {
            recursosGraficosInicio->habilitarIngreso= HABILITAR_INGRESO;
            sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (76, 175, 80));
            sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (76, 175, 80));
            sfText_setColor (recursosGraficosInicio->texto.textoBotonIngresar, sfColor_fromRGB (76, 175, 80));
            sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (76, 175, 80));
        }
        else
        {
            recursosGraficosInicio->habilitarIngreso= DESHABILITAR_INGRESO;
            sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (209, 0, 31));
            sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (209, 0, 31));
            sfText_setColor (recursosGraficosInicio->texto.textoBotonIngresar, sfColor_fromRGB (209, 0, 31));
            sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (209, 0, 31));
        }
}

void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.subrayadoTitulo, NULL);
    sfRenderWindow_drawCircleShape (app->renderizado, recursosGraficosInicio->elementos.circuloTextoInformativoTam, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.botonIngresar, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoInformativoTam, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoRegistrarUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoBotonIngresar, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosInicio->texto.fuente);
    sfText_destroy (recursosGraficosInicio->texto.ingresarUsuario);
    sfText_destroy (recursosGraficosInicio->texto.textoInformativoTam);
    sfText_destroy (recursosGraficosInicio->texto.ingresarNombre);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirNombre);
    sfText_destroy (recursosGraficosInicio->texto.ingresarContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.textoRegistrarUsuario);
    sfText_destroy (recursosGraficosInicio->texto.textoBotonIngresar);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.subrayadoTitulo);
    sfCircleShape_destroy (recursosGraficosInicio->elementos.circuloTextoInformativoTam);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarNombre);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarContrasenia);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.botonIngresar);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar);
}


///FUNCIONES LOGICAS


void ingresoTexto (char *buffer, sfEvent evento)
{
    int largoBuffer;

    largoBuffer = strlen (buffer);

    if ((evento.text.unicode != 13) && (evento.text.unicode != 8)) //Detecta que no sea la tecla "Enter" ni "Backspace"
    {
        if (largoBuffer < MAX_INGRESO_TECLADO - 1)
        {
            buffer [largoBuffer] = (char)evento.text.unicode;
            buffer [largoBuffer + 1] = '\0';
        }
    }
    if ((evento.text.unicode == 8) && (largoBuffer > 0)) //Detecta que sea la tecla "Backspace"
        buffer [largoBuffer - 1] = '\0';

}






































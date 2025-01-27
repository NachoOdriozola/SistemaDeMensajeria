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

    recursosGraficosInicio->texto.iniciarSesion = sfText_create ();
    if (!recursosGraficosInicio->texto.iniciarSesion)
    {
        perror ("ERROR - Crear texto iniciar sesion.\n");
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

    recursosGraficosInicio->texto.textoGuardarInicioSesion = sfText_create ();
    if (!recursosGraficosInicio->texto.textoGuardarInicioSesion)
    {
        perror ("ERROR - Crear texto para guardar inicio de sesion.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.auxGuardarInicioSesion = sfText_create ();
    if (!recursosGraficosInicio->texto.auxGuardarInicioSesion)
    {
        perror ("ERROR - Crear texto auxiliar para guardar inicio de sesion.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.textoBotonIngresar = sfText_create ();
    if (!recursosGraficosInicio->texto.textoBotonIngresar)
    {
        perror ("ERROR - Crear texto para boton aceptar nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosInicio->texto.textoRegistrarUsuario = sfText_create ();
    if (!recursosGraficosInicio->texto.textoRegistrarUsuario)
    {
        perror ("ERROR - Crear texto registrar usuario.\n");
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

    recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion = sfRectangleShape_create ();
    if (!recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion)
    {
        perror ("ERROR - Crear cuadrado para guardar inicio de sesion.\n");
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

void setupInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP ESCRITURA
    *(recursosGraficosInicio->bufferEscribirNombre) = '\0';
    *(recursosGraficosInicio->bufferEscribirContrasenia) = '\0';


    ///SETUP HABILITACIONES
    recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre = DESHABILITAR_ESCRITURA_NOMBRE;
    recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia = DESHABILITAR_ESCRITURA_CONTRASENIA;
    recursosGraficosInicio->habilitaciones.guardarInicioSesion = DESHABILITAR_GUARDAR_INICIO_SESION;
    recursosGraficosInicio->habilitaciones.habilitarIngreso = DESHABILITAR_INGRESO;


    ///SETUP TEXTO
    //Texto iniciar sesion
    sfText_setFont (recursosGraficosInicio->texto.iniciarSesion, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.iniciarSesion, "INICIAR SESION");
    sfText_setColor (recursosGraficosInicio->texto.iniciarSesion, sfColor_fromRGB (34, 48, 48));

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

    //Texto para guardar inicio de sesion
    sfText_setFont (recursosGraficosInicio->texto.textoGuardarInicioSesion, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoGuardarInicioSesion, "¿Desea guardar sus datos e iniciar sesion\nautomaticamente cuando inicie la aplicacion?");
    sfText_setColor (recursosGraficosInicio->texto.textoGuardarInicioSesion, sfColor_fromRGB (40, 54, 54));

    //Texto auxiliar para guardar inicio de sesion
    sfText_setFont (recursosGraficosInicio->texto.auxGuardarInicioSesion, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.auxGuardarInicioSesion, "X");
    sfText_setColor (recursosGraficosInicio->texto.auxGuardarInicioSesion, sfColor_fromRGB (209, 0, 31));

    //Texto boton ingresar usuario
    sfText_setFont (recursosGraficosInicio->texto.textoBotonIngresar, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoBotonIngresar, "INGRESAR");

    //Texto registrar usuario
    sfText_setFont (recursosGraficosInicio->texto.textoRegistrarUsuario, recursosGraficosInicio->texto.fuente);
    sfText_setString (recursosGraficosInicio->texto.textoRegistrarUsuario, "¿No tenes usuario? Registrate aca.");
    sfText_setColor (recursosGraficosInicio->texto.textoRegistrarUsuario, sfColor_fromRGB (40, 54, 54));


    ///SETUP ELEMENTOS
    //Subrayado para el titulo
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.subrayadoTitulo, sfColor_fromRGB (40, 54, 54));

    //Barra para ingresar nombre
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarNombre, sfColor_fromRGB (208, 208, 208));

    //Barra para ingresar contrasenia
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.barraIngresarContrasenia, sfColor_fromRGB (208, 208, 208));

    //Cuadrado para guardar inicio de sesion
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion, sfColor_fromRGB (208, 208, 208));

    //Boton aceptar nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (208, 208, 208));

    //Rectangulo invisible para registrar usuario
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar, sfColor_fromRGB (223, 231, 233));


    ///SETUP POS Y TAM
    tamYPosPantallaInicio (recursosGraficosInicio);
}

void tamYPosPantallaInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP POS Y TAM TEXTO
    //Texto iniciar sesion
    sfText_setPosition (recursosGraficosInicio->texto.iniciarSesion, (sfVector2f){190, 25});
    sfText_setCharacterSize (recursosGraficosInicio->texto.iniciarSesion, 36);

    //Texto informativo tam maximo nombre y contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.textoInformativoTam, (sfVector2f){55, 113});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoInformativoTam, 22);

    //Texto ingresar nombre
    sfText_setPosition (recursosGraficosInicio->texto.ingresarNombre, (sfVector2f){55, 184});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarNombre, 28);

    //Texto auxiliar escribir nombre
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirNombre, (sfVector2f){64, 231});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirNombre, 24);

    //Texto ingresar contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.ingresarContrasenia, (sfVector2f){55, 273});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarContrasenia, 28);

    //Texto auxiliar escribir contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirContrasenia, (sfVector2f){64, 320});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirContrasenia, 24);

    //Texto para guardar inicio de sesion
    sfText_setPosition (recursosGraficosInicio->texto.textoGuardarInicioSesion, (sfVector2f){55, 369});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoGuardarInicioSesion, 22);

    //Texto auxiliar guardar inicio de sesion
    sfText_setPosition (recursosGraficosInicio->texto.auxGuardarInicioSesion, (sfVector2f){415, 376});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxGuardarInicioSesion, 30);

    //Texto boton ingresar usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoBotonIngresar, (sfVector2f){227, 443});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoBotonIngresar, 28);

    //Texto registrar usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoRegistrarUsuario, (sfVector2f){126, 490});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoRegistrarUsuario, 26);
    sfText_setLetterSpacing (recursosGraficosInicio->texto.textoRegistrarUsuario, 1.3);


    ///SETUP POS Y TAM ELEMENTOS
    //Subrayado para el titulo
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.subrayadoTitulo, (sfVector2f){175, 75});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.subrayadoTitulo, (sfVector2f){172, 2.5});

    //Circulo de texto informativo tam
    sfCircleShape_setPosition (recursosGraficosInicio->elementos.circuloTextoInformativoTam, (sfVector2f){40, 125});
    sfCircleShape_setRadius (recursosGraficosInicio->elementos.circuloTextoInformativoTam, 4);

    //Barra ingresar nombre
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){55, 232});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){420, 30});

    //Barra ingresar contrasenia
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){55, 321});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){420, 30});

    //Cuadrado para guardar inicio de sesion
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion, (sfVector2f){406, 380});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion, (sfVector2f){30, 30});

    //Boton ingresar usuario
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.botonIngresar, (sfVector2f){195, 444});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.botonIngresar, (sfVector2f){140, 35});
    sfRectangleShape_setOutlineThickness (recursosGraficosInicio->elementos.botonIngresar, 2);

    //Rectangulo invisible para registrar usuario
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar, (sfVector2f){127, 492});
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
                recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre = HABILITAR_ESCRITURA_NOMBRE;
            else
                recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre = DESHABILITAR_ESCRITURA_NOMBRE;

            if (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.barraIngresarContrasenia))
                recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia = HABILITAR_ESCRITURA_CONTRASENIA;
            else
                recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia = DESHABILITAR_ESCRITURA_CONTRASENIA;

            if (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion))
            {
                if (recursosGraficosInicio->habilitaciones.guardarInicioSesion == DESHABILITAR_GUARDAR_INICIO_SESION)
                {
                    recursosGraficosInicio->habilitaciones.guardarInicioSesion = HABILITAR_GUARDAR_INICIO_SESION;
                    sfText_setString (recursosGraficosInicio->texto.auxGuardarInicioSesion, "V");
                    sfText_setColor (recursosGraficosInicio->texto.auxGuardarInicioSesion, sfColor_fromRGB (76, 175, 80));
                }
                else
                {
                    recursosGraficosInicio->habilitaciones.guardarInicioSesion = DESHABILITAR_GUARDAR_INICIO_SESION;
                    sfText_setString (recursosGraficosInicio->texto.auxGuardarInicioSesion, "X");
                    sfText_setColor (recursosGraficosInicio->texto.auxGuardarInicioSesion, sfColor_fromRGB (209, 0, 31));
                }
            }

            if (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar)) //TEMPORAL
                printf ("Se clickeo el rectangulo de registrar usuario.\n");


            if ((recursosGraficosInicio->habilitaciones.habilitarIngreso == HABILITAR_INGRESO) && (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.botonIngresar)))
            {
                app->interfaz = INTERFAZ_MENSAJES;
                strcpy (app->usuario.nombreUsuario, recursosGraficosInicio->bufferEscribirNombre);
                if (recursosGraficosInicio->habilitaciones.guardarInicioSesion == HABILITAR_GUARDAR_INICIO_SESION)
                    guardarDatosEnArchivo (recursosGraficosInicio->bufferEscribirNombre, recursosGraficosInicio->bufferEscribirContrasenia);
            }
        }
        break;

        case sfEvtTextEntered:
        if ((recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosInicio->bufferEscribirNombre, MAX_INGRESO_TECLADO - 1, evento);
            sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, recursosGraficosInicio->bufferEscribirNombre);
        }
        if ((recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosInicio->bufferEscribirContrasenia, MAX_INGRESO_TECLADO - 1, evento);
            sfText_setString (recursosGraficosInicio->texto.auxEscribirContrasenia, recursosGraficosInicio->bufferEscribirContrasenia);
        }
        break;

        case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosInicio->habilitaciones.habilitarIngreso == HABILITAR_INGRESO) &&
            ((recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) || (recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA)))
        {
            app->interfaz = INTERFAZ_MENSAJES;
            strcpy (app->usuario.nombreUsuario, recursosGraficosInicio->bufferEscribirNombre);
            if (recursosGraficosInicio->habilitaciones.guardarInicioSesion == HABILITAR_GUARDAR_INICIO_SESION)
                guardarDatosEnArchivo (recursosGraficosInicio->bufferEscribirNombre, recursosGraficosInicio->bufferEscribirContrasenia);
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


    if ((recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre == DESHABILITAR_ESCRITURA_NOMBRE) && (largoBufferEscribirNombre == 0))
        sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, "Escriba su nombre...");

    if ((recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia == DESHABILITAR_ESCRITURA_CONTRASENIA) && (largoBufferEscribirContrasenia == 0))
        sfText_setString (recursosGraficosInicio->texto.auxEscribirContrasenia, "Escriba su contraseña...");


    if ((largoBufferEscribirNombre == 0) && (largoBufferEscribirContrasenia == 0))
    {
        recursosGraficosInicio->habilitaciones.habilitarIngreso= DESHABILITAR_INGRESO;
        sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (34, 48, 48));
        sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (34, 48, 48));
        sfText_setColor (recursosGraficosInicio->texto.textoBotonIngresar, sfColor_fromRGB (34, 48, 48));
        sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (34, 48, 48));
    }
    else if (((largoBufferEscribirNombre > 0) && (largoBufferEscribirNombre < MAX_NOMBRE_USUARIO) &&
              (largoBufferEscribirContrasenia > 0) && (largoBufferEscribirContrasenia < MAX_CONTRASENIA_USUARIO)))
        {
            recursosGraficosInicio->habilitaciones.habilitarIngreso= HABILITAR_INGRESO;
            sfText_setColor (recursosGraficosInicio->texto.textoInformativoTam, sfColor_fromRGB (76, 175, 80));
            sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoInformativoTam, sfColor_fromRGB (76, 175, 80));
            sfText_setColor (recursosGraficosInicio->texto.textoBotonIngresar, sfColor_fromRGB (76, 175, 80));
            sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (76, 175, 80));
        }
        else
        {
            recursosGraficosInicio->habilitaciones.habilitarIngreso= DESHABILITAR_INGRESO;
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
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.botonIngresar, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.iniciarSesion, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoInformativoTam, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoGuardarInicioSesion, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxGuardarInicioSesion, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoBotonIngresar, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoRegistrarUsuario, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosInicio->texto.fuente);
    sfText_destroy (recursosGraficosInicio->texto.iniciarSesion);
    sfText_destroy (recursosGraficosInicio->texto.textoInformativoTam);
    sfText_destroy (recursosGraficosInicio->texto.ingresarNombre);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirNombre);
    sfText_destroy (recursosGraficosInicio->texto.ingresarContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.textoGuardarInicioSesion);
    sfText_destroy (recursosGraficosInicio->texto.auxGuardarInicioSesion);
    sfText_destroy (recursosGraficosInicio->texto.textoBotonIngresar);
    sfText_destroy (recursosGraficosInicio->texto.textoRegistrarUsuario);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.subrayadoTitulo);
    sfCircleShape_destroy (recursosGraficosInicio->elementos.circuloTextoInformativoTam);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarNombre);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarContrasenia);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.botonIngresar);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.rectanguloInvisibleRegistrar);
}


///FUNCIONES LOGICAS


int guardarDatosEnArchivo (const char *bufferNombre, const char *bufferContrasenia)
{
    s_datosGuardados datosGuardados;
    FILE *archDatos;

    archDatos = fopen ("Datos.dat", "wb");
    if (!archDatos)
    {
        perror ("ERROR - Crear archivo para guardar inicio de sesion.\n");
        return ERROR_INICIALIZACION;
    }

    strcpy (datosGuardados.nombre, bufferNombre);
    strcpy (datosGuardados.contrasenia, bufferContrasenia);
    fwrite (&datosGuardados, sizeof (s_datosGuardados), 1, archDatos);

    fclose (archDatos);

    return OK;
}




































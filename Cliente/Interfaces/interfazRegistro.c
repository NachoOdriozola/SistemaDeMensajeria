#include "interfazRegistro.h"


///FUNCIONES ESTRUCTURALES


int inicializarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    ///INICIALIZAR TEXTO
    recursosGraficosRegistro->texto.registrarse = sfText_create ();
    if (!recursosGraficosRegistro->texto.registrarse)
    {
        perror ("ERROR - Crear texto registrarse.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.ingresarNombre = sfText_create ();
    if (!recursosGraficosRegistro->texto.ingresarNombre)
    {
        perror ("ERROR - Crear texto ingresar nombre.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.textoInformativoNombre = sfText_create ();
    if (!recursosGraficosRegistro->texto.textoInformativoNombre)
    {
        perror ("ERROR - Crear texto informativo para nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.auxEscribirNombre = sfText_create ();
    if (!recursosGraficosRegistro->texto.auxEscribirNombre)
    {
        perror ("ERROR - Crear texto auxiliar nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.ingresarContrasenia = sfText_create ();
    if (!recursosGraficosRegistro->texto.ingresarContrasenia)
    {
        perror ("ERROR - Crear texto ingresar contrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.textoInformativoContrasenia = sfText_create ();
    if (!recursosGraficosRegistro->texto.textoInformativoContrasenia)
    {
        perror ("ERROR - Crear texto informativo para contrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.auxEscribirContrasenia = sfText_create ();
    if (!recursosGraficosRegistro->texto.auxEscribirContrasenia)
    {
        perror ("ERROR - Crear texto auxiliar contrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.textoBotonRegistrar = sfText_create ();
    if (!recursosGraficosRegistro->texto.textoBotonRegistrar)
    {
        perror ("ERROR - Crear texto de boton registrar.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->texto.textoErrorRegistro = sfText_create ();
    if (!recursosGraficosRegistro->texto.textoErrorRegistro)
    {
        perror ("ERROR - Crear texto de error registro.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR RECURSOS
    recursosGraficosRegistro->elementos.subrayadoTitulo = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.subrayadoTitulo)
    {
        perror ("ERROR - Crear subrayado para el titulo.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->elementos.flechaVolverBarra = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.flechaVolverBarra)
    {
        perror ("ERROR - Crear flecha volver barra.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->elementos.flechaVolverTriangulo1 = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.flechaVolverTriangulo1)
    {
        perror ("ERROR - Crear flecha para volver triangulo 1.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->elementos.flechaVolverTriangulo2 = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.flechaVolverTriangulo2)
    {
        perror ("ERROR - Crear flecha para volver triangulo 2.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->elementos.rectanguloInvisibleVolver = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.rectanguloInvisibleVolver)
    {
        perror ("ERROR - Crear rectangulo invisible para volver.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->elementos.barraIngresarNombre = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.barraIngresarNombre)
    {
        perror ("ERROR - Crear barra para ingresar nombre.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->elementos.barraIngresarContrasenia = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.barraIngresarContrasenia)
    {
        perror ("ERROR - Crear barra para ingresar contrasenia.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosRegistro->elementos.botonRegistrar = sfRectangleShape_create ();
    if (!recursosGraficosRegistro->elementos.botonRegistrar)
    {
        perror ("ERROR - Crear boton registrar.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro, s_fuentes fuentes)
{
    ///SETUP ESCRITURA
    *(recursosGraficosRegistro->bufferEscribirNombre) = '\0';
    *(recursosGraficosRegistro->bufferEscribirContrasenia) = '\0';


    ///SETUP HABILITACIONES
    recursosGraficosRegistro->habilitaciones.habilitarEscrituraNombre = DESHABILITAR_ESCRITURA_NOMBRE;
    recursosGraficosRegistro->habilitaciones.habilitarEscrituraContrasenia = DESHABILITAR_ESCRITURA_CONTRASENIA;
    recursosGraficosRegistro->habilitaciones.habilitarRegistro = DESHABILITAR_REGISTRO;


    ///SETUP TEXTO
    //Texto registrarse
    sfText_setFont (recursosGraficosRegistro->texto.registrarse, fuentes.fuente1);
    sfText_setString (recursosGraficosRegistro->texto.registrarse, "REGISTRARSE");
    sfText_setFillColor (recursosGraficosRegistro->texto.registrarse, sfColor_fromRGB (34, 48, 48));

    //Texto ingresar nombre
    sfText_setFont (recursosGraficosRegistro->texto.ingresarNombre, fuentes.fuente1);
    sfText_setString (recursosGraficosRegistro->texto.ingresarNombre, "Ingrese su nombre");
    sfText_setFillColor (recursosGraficosRegistro->texto.ingresarNombre, sfColor_fromRGB (34, 48, 48));

    //Texto informativo nombre
    sfText_setFont (recursosGraficosRegistro->texto.textoInformativoNombre, fuentes.fuente1);
    sfText_setString (recursosGraficosRegistro->texto.textoInformativoNombre, "La longitud maxima del nombre es hasta 25 caracteres");
    sfText_setFillColor (recursosGraficosRegistro->texto.textoInformativoNombre, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir nombre
    sfText_setFont (recursosGraficosRegistro->texto.auxEscribirNombre, fuentes.fuente1);
    sfText_setFillColor (recursosGraficosRegistro->texto.auxEscribirNombre, sfColor_fromRGB (34, 48, 48));

    //Texto ingresar contrasenia
    sfText_setFont (recursosGraficosRegistro->texto.ingresarContrasenia, fuentes.fuente1);
    sfText_setString (recursosGraficosRegistro->texto.ingresarContrasenia, "Ingrese su contraseña");
    sfText_setFillColor (recursosGraficosRegistro->texto.ingresarContrasenia, sfColor_fromRGB (34, 48, 48));

    //Texto informativo contrasenia
    sfText_setFont (recursosGraficosRegistro->texto.textoInformativoContrasenia, fuentes.fuente1);
    sfText_setString (recursosGraficosRegistro->texto.textoInformativoContrasenia, "La contraseña debe contener al menos 8 caracteres, 1 mayuscula,\n 1 numero y 1 caracter especial");
    sfText_setFillColor (recursosGraficosRegistro->texto.textoInformativoContrasenia, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir contrasenia
    sfText_setFont (recursosGraficosRegistro->texto.auxEscribirContrasenia, fuentes.fuente1);
    sfText_setFillColor (recursosGraficosRegistro->texto.auxEscribirContrasenia, sfColor_fromRGB (34, 48, 48));

    //Texto boton registrar
    sfText_setFont (recursosGraficosRegistro->texto.textoBotonRegistrar, fuentes.fuente1);
    sfText_setString (recursosGraficosRegistro->texto.textoBotonRegistrar, "REGISTRAR");
    sfText_setFillColor (recursosGraficosRegistro->texto.textoBotonRegistrar, sfColor_fromRGB (34, 48, 48));

    //Texto de error registro
    sfText_setFont (recursosGraficosRegistro->texto.textoErrorRegistro, fuentes.fuente1);
    sfText_setFillColor (recursosGraficosRegistro->texto.textoErrorRegistro, sfColor_fromRGB (34, 48, 48));


    ///SETUP ELEMENTOS
    //Subrayado para el titulo
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.subrayadoTitulo, sfColor_fromRGB (34, 48, 48));

    //Flecha para volver barra
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.flechaVolverBarra, sfColor_fromRGB (34, 48, 48));

    //Flecha para volver triangulo 1
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.flechaVolverTriangulo1, sfColor_fromRGB (34, 48, 48));
    sfRectangleShape_rotate (recursosGraficosRegistro->elementos.flechaVolverTriangulo1, 45);

    //Flecha para volver triangulo 2
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.flechaVolverTriangulo2, sfColor_fromRGB (34, 48, 48));
    sfRectangleShape_rotate (recursosGraficosRegistro->elementos.flechaVolverTriangulo2, -45);

    //Rectangulo invisible para volver
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, sfColor_fromRGB (223, 231, 233));

    //Barra para ingresar nombre
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.barraIngresarNombre, sfColor_fromRGB (208, 208, 208));

    //Barra para ingresar contrasenia
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.barraIngresarContrasenia, sfColor_fromRGB (208, 208, 208));

    //Boton registrar usuario
    sfRectangleShape_setFillColor (recursosGraficosRegistro->elementos.botonRegistrar, sfColor_fromRGB (208, 208, 208));
    sfRectangleShape_setOutlineColor (recursosGraficosRegistro->elementos.botonRegistrar, sfColor_fromRGB (34, 48, 48));


    ///SETUP POS Y TAM
    tamYPosPantallaRegistro (recursosGraficosRegistro);
}

void tamYPosPantallaRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    ///SETUP POS Y TAM TEXTO
    //Texto registrarse
    sfText_setPosition (recursosGraficosRegistro->texto.registrarse, (sfVector2f){196, 25});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.registrarse, 36);

    //Texto ingresar nombre
    sfText_setPosition (recursosGraficosRegistro->texto.ingresarNombre, (sfVector2f){55, 110});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.ingresarNombre, 28);

    //Texto informativo nombre de usuario
    sfText_setPosition (recursosGraficosRegistro->texto.textoInformativoNombre, (sfVector2f){55, 150});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.textoInformativoNombre, 24);

    //Texto auxiliar escribir nombre
    sfText_setPosition (recursosGraficosRegistro->texto.auxEscribirNombre, (sfVector2f){64, 193});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.auxEscribirNombre, 24);

    //Texto ingresar contrasenia
    sfText_setPosition (recursosGraficosRegistro->texto.ingresarContrasenia, (sfVector2f){55, 250});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.ingresarContrasenia, 28);

    //Texto informativo contrasenia
    sfText_setPosition (recursosGraficosRegistro->texto.textoInformativoContrasenia, (sfVector2f){55, 290});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.textoInformativoContrasenia, 24);

    //Texto auxiliar escribir contrasenia
    sfText_setPosition (recursosGraficosRegistro->texto.auxEscribirContrasenia, (sfVector2f){64, 364});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.auxEscribirContrasenia, 24);

    //Texto boton registrar
    sfText_setPosition (recursosGraficosRegistro->texto.textoBotonRegistrar, (sfVector2f){226, 451});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.textoBotonRegistrar, 28);

    //Texto de error registro
    sfText_setPosition (recursosGraficosRegistro->texto.textoErrorRegistro, (sfVector2f){55, 400});
    sfText_setCharacterSize (recursosGraficosRegistro->texto.textoErrorRegistro, 24);


    ///SETUP POS Y TAM ELEMENTOS
    //Subrayado para el titulo
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.subrayadoTitulo, (sfVector2f){175, 75});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.subrayadoTitulo, (sfVector2f){172, 2.5});

    //Flecha para volver barra
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.flechaVolverBarra, (sfVector2f){25, 20});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.flechaVolverBarra, (sfVector2f){25, 2.5});

    //Flecha para volver triangulo 1
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.flechaVolverTriangulo1, (sfVector2f){25, 20});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.flechaVolverTriangulo1, (sfVector2f){10, 2.5});

    //Flecha para volver triangulo 2
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.flechaVolverTriangulo2, (sfVector2f){23.5, 20.5});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.flechaVolverTriangulo2, (sfVector2f){10, 2.1});

    //Rectangulo invisible para volver
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, (sfVector2f){21, 12.5});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, (sfVector2f){31, 17});

    //Barra para ingresar nombre
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.barraIngresarNombre, (sfVector2f){55, 195});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.barraIngresarNombre, (sfVector2f){420, 30});

    //Barra para ingresar contrasenia
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.barraIngresarContrasenia, (sfVector2f){55, 366});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.barraIngresarContrasenia, (sfVector2f){420, 30});

    //Boton registrar usuario
    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.botonRegistrar, (sfVector2f){200, 452});
    sfRectangleShape_setSize (recursosGraficosRegistro->elementos.botonRegistrar, (sfVector2f){140, 35});
    sfRectangleShape_setOutlineThickness (recursosGraficosRegistro->elementos.botonRegistrar, 2);
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
            if (clickEnRectangulo (app->renderizado, recursosGraficosRegistro->elementos.barraIngresarNombre))
                recursosGraficosRegistro->habilitaciones.habilitarEscrituraNombre = HABILITAR_ESCRITURA_NOMBRE;
            else
                recursosGraficosRegistro->habilitaciones.habilitarEscrituraNombre = DESHABILITAR_ESCRITURA_NOMBRE;

            if (clickEnRectangulo (app->renderizado, recursosGraficosRegistro->elementos.barraIngresarContrasenia))
                recursosGraficosRegistro->habilitaciones.habilitarEscrituraContrasenia = HABILITAR_ESCRITURA_CONTRASENIA;
            else
                recursosGraficosRegistro->habilitaciones.habilitarEscrituraContrasenia = DESHABILITAR_ESCRITURA_CONTRASENIA;


            if (clickEnRectangulo (app->renderizado, recursosGraficosRegistro->elementos.rectanguloInvisibleVolver))
                app->interfaz = INTERFAZ_INICIO;

            if ((recursosGraficosRegistro->habilitaciones.habilitarRegistro == HABILITAR_REGISTRO) && (clickEnRectangulo (app->renderizado, recursosGraficosRegistro->elementos.botonRegistrar)))
            {
                if (enviarSolicitudUsuario (app->sock, recursosGraficosRegistro->bufferEscribirNombre, recursosGraficosRegistro->bufferEscribirContrasenia, INDICE_REGISTRO) == SOLICITUD_ACEPTADA)
                {
                    app->interfaz = INTERFAZ_AMIGOS;
                    strcpy (app->usuario.nombreUsuario, recursosGraficosRegistro->bufferEscribirNombre);
                }
                else
                {
                    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.botonRegistrar, (sfVector2f){200, 492});
                    sfText_setPosition (recursosGraficosRegistro->texto.textoBotonRegistrar, (sfVector2f){226, 491});
                }
            }
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosRegistro->habilitaciones.habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosRegistro->bufferEscribirNombre, MAX_INGRESO_TECLADO_NOMBRE - 1, evento);
            sfText_setString (recursosGraficosRegistro->texto.auxEscribirNombre, recursosGraficosRegistro->bufferEscribirNombre);
        }

        if ((recursosGraficosRegistro->habilitaciones.habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosRegistro->bufferEscribirContrasenia, MAX_INGRESO_TECLADO_CONTRASENIA - 1, evento);
            sfText_setString (recursosGraficosRegistro->texto.auxEscribirContrasenia, recursosGraficosRegistro->bufferEscribirContrasenia);
        }
        break;

    case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosRegistro->habilitaciones.habilitarRegistro == HABILITAR_REGISTRO) &&
            ((recursosGraficosRegistro->habilitaciones.habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) || (recursosGraficosRegistro->habilitaciones.habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA)))
        {
            if (enviarSolicitudUsuario (app->sock, recursosGraficosRegistro->bufferEscribirNombre, recursosGraficosRegistro->bufferEscribirContrasenia, INDICE_REGISTRO) == SOLICITUD_ACEPTADA)
                {
                    app->interfaz = INTERFAZ_AMIGOS;
                    strcpy (app->usuario.nombreUsuario, recursosGraficosRegistro->bufferEscribirNombre);
                }
                else
                {
                    sfRectangleShape_setPosition (recursosGraficosRegistro->elementos.botonRegistrar, (sfVector2f){200, 492});
                    sfText_setPosition (recursosGraficosRegistro->texto.textoBotonRegistrar, (sfVector2f){226, 491});
                }
        }
        break;

        default:
            break;
    }
}

void actualizarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    int largoBufferEscribirNombre, largoBufferEscribirContrasenia;

    largoBufferEscribirNombre = strlen (recursosGraficosRegistro->bufferEscribirNombre);
    largoBufferEscribirContrasenia = strlen (recursosGraficosRegistro->bufferEscribirContrasenia);


    if ((recursosGraficosRegistro->habilitaciones.habilitarEscrituraNombre == DESHABILITAR_ESCRITURA_NOMBRE) && (largoBufferEscribirNombre == 0))
        sfText_setString (recursosGraficosRegistro->texto.auxEscribirNombre, "Escriba su nombre...");

    if ((recursosGraficosRegistro->habilitaciones.habilitarEscrituraNombre == DESHABILITAR_ESCRITURA_CONTRASENIA) && (largoBufferEscribirContrasenia == 0))
        sfText_setString (recursosGraficosRegistro->texto.auxEscribirContrasenia, "Escriba su contraseña...");

    if ((largoBufferEscribirNombre > 0) && (largoBufferEscribirContrasenia > 0))
        recursosGraficosRegistro->habilitaciones.habilitarRegistro = HABILITAR_REGISTRO;
    else
        recursosGraficosRegistro->habilitaciones.habilitarRegistro = DESHABILITAR_REGISTRO;
}

void renderizarRegistro (s_aplicacion *app, s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.subrayadoTitulo, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.rectanguloInvisibleVolver, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.flechaVolverBarra, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.flechaVolverTriangulo1, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.flechaVolverTriangulo2, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.barraIngresarNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.barraIngresarContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosRegistro->elementos.botonRegistrar, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.registrarse, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.ingresarNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.textoInformativoNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.auxEscribirNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.ingresarContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.textoInformativoContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.textoBotonRegistrar, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosRegistro->texto.textoErrorRegistro, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro)
{
    ///LIBERAR TEXTO
    sfText_destroy (recursosGraficosRegistro->texto.registrarse);
    sfText_destroy (recursosGraficosRegistro->texto.ingresarNombre);
    sfText_destroy (recursosGraficosRegistro->texto.textoInformativoNombre);
    sfText_destroy (recursosGraficosRegistro->texto.auxEscribirNombre);
    sfText_destroy (recursosGraficosRegistro->texto.ingresarContrasenia);
    sfText_destroy (recursosGraficosRegistro->texto.textoInformativoContrasenia);
    sfText_destroy (recursosGraficosRegistro->texto.auxEscribirContrasenia);
    sfText_destroy (recursosGraficosRegistro->texto.textoBotonRegistrar);
    sfText_destroy (recursosGraficosRegistro->texto.textoErrorRegistro);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.subrayadoTitulo);
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.flechaVolverBarra);
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.flechaVolverTriangulo1);
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.flechaVolverTriangulo2);
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.rectanguloInvisibleVolver);
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.barraIngresarNombre);
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.barraIngresarContrasenia);
    sfRectangleShape_destroy (recursosGraficosRegistro->elementos.botonRegistrar);
}
































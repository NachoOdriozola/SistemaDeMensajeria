#include "interfazInicio.h"


///FUNCIONES ESTRUCTURALES


int inicializarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///INICIALIZAR TEXTO
    recursosGraficosInicio->texto.iniciarSesion = sfText_create ();
    if (!recursosGraficosInicio->texto.iniciarSesion)
    {
        perror ("ERROR - Crear texto iniciar sesion.\n");
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

    recursosGraficosInicio->texto.textoIngresoIncorrecto = sfText_create ();
    if (!recursosGraficosInicio->texto.textoIngresoIncorrecto)
    {
        perror ("ERROR - Crear texto de ingreso incorrecto.\n");
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

    recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto = sfCircleShape_create ();
    if (!recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto)
    {
        perror ("ERROR - Crear circulo de ingreso incorrecto.\n");
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


    return OK;
}

void setupInicio (s_recursosGraficosInicio *recursosGraficosInicio, s_fuentes fuentes)
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
    sfText_setFont (recursosGraficosInicio->texto.iniciarSesion, fuentes.fuente1);
    sfText_setString (recursosGraficosInicio->texto.iniciarSesion, "INICIAR SESION");
    sfText_setColor (recursosGraficosInicio->texto.iniciarSesion, sfColor_fromRGB (34, 48, 48));

    //Texto ingresar nombre
    sfText_setFont (recursosGraficosInicio->texto.ingresarNombre, fuentes.fuente1);
    sfText_setString (recursosGraficosInicio->texto.ingresarNombre, "Ingrese su nombre:");
    sfText_setColor (recursosGraficosInicio->texto.ingresarNombre, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir nombre
    sfText_setFont (recursosGraficosInicio->texto.auxEscribirNombre, fuentes.fuente1);
    sfText_setColor (recursosGraficosInicio->texto.auxEscribirNombre, sfColor_fromRGB (40, 54, 54));

    //Texto ingresar contrasenia
    sfText_setFont (recursosGraficosInicio->texto.ingresarContrasenia, fuentes.fuente1);
    sfText_setString (recursosGraficosInicio->texto.ingresarContrasenia, "Ingrese su contraseña:");
    sfText_setColor (recursosGraficosInicio->texto.ingresarContrasenia, sfColor_fromRGB (40, 54, 54));

    //Texto auxiliar escribir contrasenia
    sfText_setFont (recursosGraficosInicio->texto.auxEscribirContrasenia, fuentes.fuente1);
    sfText_setColor (recursosGraficosInicio->texto.auxEscribirContrasenia, sfColor_fromRGB (40, 54, 54));

    //Texto para guardar inicio de sesion
    sfText_setFont (recursosGraficosInicio->texto.textoGuardarInicioSesion, fuentes.fuente1);
    sfText_setString (recursosGraficosInicio->texto.textoGuardarInicioSesion, "¿Desea guardar sus datos e iniciar sesion\nautomaticamente cuando inicie la aplicacion?");
    sfText_setColor (recursosGraficosInicio->texto.textoGuardarInicioSesion, sfColor_fromRGB (40, 54, 54));

    //Texto auxiliar para guardar inicio de sesion
    sfText_setFont (recursosGraficosInicio->texto.auxGuardarInicioSesion, fuentes.fuente1);
    sfText_setString (recursosGraficosInicio->texto.auxGuardarInicioSesion, "X");
    sfText_setColor (recursosGraficosInicio->texto.auxGuardarInicioSesion, sfColor_fromRGB (209, 0, 31));

    //Texto boton ingresar usuario
    sfText_setFont (recursosGraficosInicio->texto.textoBotonIngresar, fuentes.fuente1);
    sfText_setString (recursosGraficosInicio->texto.textoBotonIngresar, "INGRESAR");
    sfText_setColor (recursosGraficosInicio->texto.textoBotonIngresar, sfColor_fromRGB (40, 54, 54));

    //Texto ingreso incorrecto
    sfText_setFont (recursosGraficosInicio->texto.textoIngresoIncorrecto, fuentes.fuente1);
    sfText_setFillColor (recursosGraficosInicio->texto.textoIngresoIncorrecto, sfColor_fromRGB (40, 54, 54));

    //Texto registrar usuario
    sfText_setFont (recursosGraficosInicio->texto.textoRegistrarUsuario, fuentes.fuente1);
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

    //Boton ingresar usuario
    sfRectangleShape_setFillColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (208, 208, 208));
    sfRectangleShape_setOutlineColor (recursosGraficosInicio->elementos.botonIngresar, sfColor_fromRGB (40, 54, 54));

    //Circulo de ingreso incorrecto
    sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto, sfColor_fromRGB (223, 231, 233));


    ///SETUP POS Y TAM
    tamYPosPantallaInicio (recursosGraficosInicio);
}

void tamYPosPantallaInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///SETUP POS Y TAM TEXTO
    //Texto iniciar sesion
    sfText_setPosition (recursosGraficosInicio->texto.iniciarSesion, (sfVector2f){190, 25});
    sfText_setCharacterSize (recursosGraficosInicio->texto.iniciarSesion, 36);

    //Texto ingresar nombre
    sfText_setPosition (recursosGraficosInicio->texto.ingresarNombre, (sfVector2f){55, 120});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarNombre, 28);

    //Texto auxiliar escribir nombre
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirNombre, (sfVector2f){64, 167});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirNombre, 24);

    //Texto ingresar contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.ingresarContrasenia, (sfVector2f){55, 215});
    sfText_setCharacterSize (recursosGraficosInicio->texto.ingresarContrasenia, 28);

    //Texto auxiliar escribir contrasenia
    sfText_setPosition (recursosGraficosInicio->texto.auxEscribirContrasenia, (sfVector2f){64, 262});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxEscribirContrasenia, 24);

    //Texto para guardar inicio de sesion
    sfText_setPosition (recursosGraficosInicio->texto.textoGuardarInicioSesion, (sfVector2f){55, 311});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoGuardarInicioSesion, 22);

    //Texto auxiliar guardar inicio de sesion
    sfText_setPosition (recursosGraficosInicio->texto.auxGuardarInicioSesion, (sfVector2f){415, 318});
    sfText_setCharacterSize (recursosGraficosInicio->texto.auxGuardarInicioSesion, 30);

    //Texto boton ingresar usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoBotonIngresar, (sfVector2f){227, 412});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoBotonIngresar, 28);

    //Texto ingreso incorrecto
    sfText_setPosition (recursosGraficosInicio->texto.textoIngresoIncorrecto, (sfVector2f){55, 384});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoIngresoIncorrecto, 24);

    //Texto registrar usuario
    sfText_setPosition (recursosGraficosInicio->texto.textoRegistrarUsuario, (sfVector2f){126, 490});
    sfText_setCharacterSize (recursosGraficosInicio->texto.textoRegistrarUsuario, 26);
    sfText_setLetterSpacing (recursosGraficosInicio->texto.textoRegistrarUsuario, 1.3);


    ///SETUP POS Y TAM ELEMENTOS
    //Subrayado para el titulo
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.subrayadoTitulo, (sfVector2f){175, 75});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.subrayadoTitulo, (sfVector2f){172, 2.5});

    //Barra ingresar nombre
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){55, 168});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarNombre, (sfVector2f){420, 30});

    //Barra ingresar contrasenia
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){55, 263});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.barraIngresarContrasenia, (sfVector2f){420, 30});

    //Cuadrado para guardar inicio de sesion
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion, (sfVector2f){406, 322});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion, (sfVector2f){30, 30});

    //Boton ingresar usuario
    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.botonIngresar, (sfVector2f){195, 413});
    sfRectangleShape_setSize (recursosGraficosInicio->elementos.botonIngresar, (sfVector2f){140, 35});
    sfRectangleShape_setOutlineThickness (recursosGraficosInicio->elementos.botonIngresar, 2);

    //Circulo de ingreso incorrecto
    sfCircleShape_setPosition (recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto, (sfVector2f){40, 397});
    sfCircleShape_setRadius (recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto, 4);
}

void accionInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfEvent evento;
    sfVector2f nuevoTamPantalla;
    char bufferSolicitud [MAX_BUFFER_SOLICITUD], bufferRespuesta [MAX_BUFFER_RESPUESTA];

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


            if (clickEnTexto (app->renderizado, recursosGraficosInicio->texto.textoRegistrarUsuario))
                app->interfaz = INTERFAZ_REGISTRO;

            if ((recursosGraficosInicio->habilitaciones.habilitarIngreso == HABILITAR_INGRESO) && (clickEnRectangulo (app->renderizado, recursosGraficosInicio->elementos.botonIngresar)))
            {
                sprintf (bufferSolicitud, "%c|%s|%s", INDICE_INICIO_SESION, recursosGraficosInicio->bufferEscribirNombre, recursosGraficosInicio->bufferEscribirContrasenia);
                enviarSolicitudUsuario (app->sock, bufferSolicitud, bufferRespuesta);
                puts (bufferRespuesta);

                //sscanf (bufferRespuestaSolicitud, "%d|%d", &estadoSolicitud, &id);
                /*
                if (estadoSolicitud == SOLICITUD_ACEPTADA)
                {
                    app->interfaz = INTERFAZ_AMIGOS;
                    app->usuario.id = id;
                    strcpy (app->usuario.nombre, recursosGraficosInicio->bufferEscribirNombre);
                    if (recursosGraficosInicio->habilitaciones.guardarInicioSesion == HABILITAR_GUARDAR_INICIO_SESION)
                        guardarDatosEnArchivo (recursosGraficosInicio->bufferEscribirNombre, recursosGraficosInicio->bufferEscribirContrasenia);
                }
                else
                {
                    sfRectangleShape_setPosition (recursosGraficosInicio->elementos.botonIngresar, (sfVector2f){195, 437});
                    sfText_setPosition (recursosGraficosInicio->texto.textoBotonIngresar, (sfVector2f){227, 436});
                    sfText_setString (recursosGraficosInicio->texto.textoIngresoIncorrecto, "Usuario o contraseña incorrectos.");
                    sfCircleShape_setFillColor (recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto, sfColor_fromRGB (40, 54, 54));
                }
                */
            }
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosInicio->bufferEscribirNombre, MAX_INGRESO_TECLADO_NOMBRE - 1, evento);
            sfText_setString (recursosGraficosInicio->texto.auxEscribirNombre, recursosGraficosInicio->bufferEscribirNombre);
        }

        if ((recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosInicio->bufferEscribirContrasenia, MAX_INGRESO_TECLADO_CONTRASENIA - 1, evento);
            sfText_setString (recursosGraficosInicio->texto.auxEscribirContrasenia, recursosGraficosInicio->bufferEscribirContrasenia);
        }
        break;

    case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosInicio->habilitaciones.habilitarIngreso == HABILITAR_INGRESO) &&
            ((recursosGraficosInicio->habilitaciones.habilitarEscrituraNombre == HABILITAR_ESCRITURA_NOMBRE) || (recursosGraficosInicio->habilitaciones.habilitarEscrituraContrasenia == HABILITAR_ESCRITURA_CONTRASENIA)))
        {
            printf ("Solo boton.\n");
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

    if ((largoBufferEscribirNombre > 0) && (largoBufferEscribirContrasenia > 0))
        recursosGraficosInicio->habilitaciones.habilitarIngreso = HABILITAR_INGRESO;
    else
        recursosGraficosInicio->habilitaciones.habilitarIngreso = DESHABILITAR_INGRESO;
}

void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.subrayadoTitulo, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.barraIngresarContrasenia, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosInicio->elementos.botonIngresar, NULL);
    sfRenderWindow_drawCircleShape (app->renderizado, recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.iniciarSesion, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.ingresarContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxEscribirContrasenia, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoGuardarInicioSesion, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.auxGuardarInicioSesion, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoBotonIngresar, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoIngresoIncorrecto, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosInicio->texto.textoRegistrarUsuario, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio)
{
    ///LIBERAR TEXTO
    sfText_destroy (recursosGraficosInicio->texto.iniciarSesion);
    sfText_destroy (recursosGraficosInicio->texto.ingresarNombre);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirNombre);
    sfText_destroy (recursosGraficosInicio->texto.ingresarContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.auxEscribirContrasenia);
    sfText_destroy (recursosGraficosInicio->texto.textoGuardarInicioSesion);
    sfText_destroy (recursosGraficosInicio->texto.auxGuardarInicioSesion);
    sfText_destroy (recursosGraficosInicio->texto.textoBotonIngresar);
    sfText_destroy (recursosGraficosInicio->texto.textoIngresoIncorrecto);
    sfText_destroy (recursosGraficosInicio->texto.textoRegistrarUsuario);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.subrayadoTitulo);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarNombre);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.barraIngresarContrasenia);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.cuadradoGuardarInicioSesion);
    sfRectangleShape_destroy (recursosGraficosInicio->elementos.botonIngresar);
    sfCircleShape_destroy (recursosGraficosInicio->elementos.circuloTextoIngresoIncorrecto);
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




































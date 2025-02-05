#include "interfazAmigos.h"


///FUNCIONES ESTRUCTURALES


int inicializarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///INICIALIZAR TEXTO
    recursosGraficosAmigos->texto.amigos = sfText_create ();
    if (!recursosGraficosAmigos->texto.amigos)
    {
        perror ("ERROR - Crear texto amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.salas = sfText_create ();
    if (!recursosGraficosAmigos->texto.salas)
    {
        perror ("ERROR - Crear texto salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.nombreUsuario = sfText_create ();
    if (!recursosGraficosAmigos->texto.nombreUsuario)
    {
        perror ("ERROR - Crear texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.auxEscribirMensaje = sfText_create ();
    if (!recursosGraficosAmigos->texto.auxEscribirMensaje)
    {
        perror ("ERROR - Crear texto auxiliar para escribir mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->texto.interfazConfig = sfText_create ();
    if (!recursosGraficosAmigos->texto.interfazConfig)
    {
        perror ("ERROR - Crear texto para cambiar a la interfaz de configuraciones.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosAmigos->elementos.rectanguloAmigos = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.rectanguloAmigos)
    {
        perror ("ERROR - Crear rectangulo de amigos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.rectanguloSalas = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.rectanguloSalas)
    {
        perror ("ERROR - Crear rectangulo de salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas)
    {
        perror ("ERROR - Crear cuadrado para relieve de rectangulo de salas.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraSeparacionUsuarios = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraSeparacionUsuarios)
    {
        perror ("ERROR - Crear barra de separacion de usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Crear barra de separacion de nombre de usuarios.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosAmigos->elementos.barraIngresarMensaje = sfRectangleShape_create ();
    if (!recursosGraficosAmigos->elementos.barraIngresarMensaje)
    {
        perror ("ERROR - Crear barra para ingresar mensaje.\n");
        return ERROR_INICIALIZACION;
    }


    return OK;
}

void setupAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///SETUP ESCRITURA
    recursosGraficosAmigos->habilitarEscritura = DESHABILITAR_ESCRITURA;
    *(recursosGraficosAmigos->bufferEscribirMensaje) = '\0';


    ///SETUP TEXTO
    //Texto amigos
    sfText_setFont (recursosGraficosAmigos->texto.amigos, app->mensajes.fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.amigos, "AMIGOS");
    sfText_setFillColor (recursosGraficosAmigos->texto.amigos, sfColor_fromRGB (34, 48, 48));

    //Texto salas
    sfText_setFont (recursosGraficosAmigos->texto.salas, app->mensajes.fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.salas, "SALAS");
    sfText_setFillColor (recursosGraficosAmigos->texto.salas, sfColor_fromRGB (34, 48, 48));
    sfText_rotate (recursosGraficosAmigos->texto.salas, -90);

    //Texto nombre de usuario
    sfText_setFont (recursosGraficosAmigos->texto.nombreUsuario, app->mensajes.fuentes.fuente1);
    sfText_setFillColor (recursosGraficosAmigos->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));

    //Texto auxiliar escribir mensaje
    sfText_setFont (recursosGraficosAmigos->texto.auxEscribirMensaje, app->mensajes.fuentes.fuente1);
    sfText_setFillColor (recursosGraficosAmigos->texto.auxEscribirMensaje, sfColor_fromRGB (40, 54, 54));

    //Texto para cambiar a la interfaz de config
    sfText_setFont (recursosGraficosAmigos->texto.interfazConfig, app->mensajes.fuentes.fuente1);
    sfText_setString (recursosGraficosAmigos->texto.interfazConfig, "C");
    sfText_setFillColor (recursosGraficosAmigos->texto.interfazConfig, sfColor_fromRGB (40, 54, 54));


    ///SETUP ELEMENTOS
    //Rectangulo de amigos
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.rectanguloAmigos, sfColor_fromRGB (232, 217, 205));

    //Rectangulo de salas
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.rectanguloSalas, sfColor_fromRGB (255, 229, 127));

    //Cuadrado para relieve de rectangulo de salas
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, sfColor_fromRGB (189, 139, 37));

    //Barra separacion usuarios activos
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));

    //Barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    //Barra de ingresar mensaje
    sfRectangleShape_setFillColor (recursosGraficosAmigos->elementos.barraIngresarMensaje, sfColor_fromRGB (208, 208, 208));
}

void tamYPosPantallaAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///SETUP POS Y TAM TEXTO
    //Texto amigos
    sfText_setPosition (recursosGraficosAmigos->texto.amigos, (sfVector2f){62 * app->ventana.escalaElementos.x, 45 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.amigos, 36 * app->ventana.escalaPixeles);

    //Texto salas
    sfText_setPosition (recursosGraficosAmigos->texto.salas, (sfVector2f){353 * app->ventana.escalaElementos.x, 574 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.salas, 46 * app->ventana.escalaPixeles);
    sfText_setLetterSpacing (recursosGraficosAmigos->texto.salas, 10 * app->ventana.escalaPixeles);

    //Texto nombre de usuario
    sfText_setPosition (recursosGraficosAmigos->texto.nombreUsuario, (sfVector2f){35 * app->ventana.escalaElementos.x, 925 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.nombreUsuario, 36 * app->ventana.escalaPixeles);

    //Texto auxiliar para escribir mensaje
    sfText_setPosition (recursosGraficosAmigos->texto.auxEscribirMensaje, (sfVector2f){510 * app->ventana.escalaElementos.x, 912 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.auxEscribirMensaje, 26 * app->ventana.escalaPixeles);

    //Texto para cambiar a la interfaz de config
    sfText_setPosition (recursosGraficosAmigos->texto.interfazConfig, (sfVector2f){305 * app->ventana.escalaElementos.x, 922 * app->ventana.escalaElementos.y});
    sfText_setCharacterSize (recursosGraficosAmigos->texto.interfazConfig, 46 * app->ventana.escalaPixeles);


    ///SETUP POS Y TAM ELEMENTOS
    //Rectangulo de amigos
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.rectanguloAmigos, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.rectanguloAmigos, (sfVector2f){350 * app->ventana.escalaElementos.x, 1009 * app->ventana.escalaElementos.y});

    //Rectangulo de salas
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.rectanguloSalas, (sfVector2f){350 * app->ventana.escalaElementos.x, 124 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.rectanguloSalas, (sfVector2f){60 * app->ventana.escalaElementos.x, 759 * app->ventana.escalaElementos.y});

    //Cuadrado para relieve de rectangulo de salas
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, (sfVector2f){350 * app->ventana.escalaElementos.x, 117 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, (sfVector2f){25 * app->ventana.escalaElementos.x, 20 * app->ventana.escalaElementos.y});

    //Barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraSeparacionUsuarios, (sfVector2f){24 * app->ventana.escalaElementos.x, 120 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraSeparacionUsuarios, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraSeparacionNombre, (sfVector2f){24 * app->ventana.escalaElementos.x, 888 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraSeparacionNombre, (sfVector2f){250 * app->ventana.escalaElementos.x, 3 * app->ventana.escalaElementos.y});

    //Barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosAmigos->elementos.barraIngresarMensaje, (sfVector2f){490 * app->ventana.escalaElementos.x, 909 * app->ventana.escalaElementos.y});
    sfRectangleShape_setSize (recursosGraficosAmigos->elementos.barraIngresarMensaje, (sfVector2f){1350 * app->ventana.escalaElementos.x, 42 * app->ventana.escalaElementos.y});
}

void accionAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
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
            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.barraIngresarMensaje))
                recursosGraficosAmigos->habilitarEscritura = HABILITAR_ESCRITURA;
            else
                recursosGraficosAmigos->habilitarEscritura = DESHABILITAR_ESCRITURA;


            if (clickEnRectangulo (app->renderizado, recursosGraficosAmigos->elementos.rectanguloSalas))
                app->interfaz = INTERFAZ_SALAS;

            if (clickEnTexto (app->renderizado, recursosGraficosAmigos->texto.interfazConfig))
                app->interfaz = INTERFAZ_CONFIG;
        }
        break;

    case sfEvtTextEntered:
        if ((recursosGraficosAmigos->habilitarEscritura == HABILITAR_ESCRITURA) && (evento.text.unicode < 128))
        {
            ingresoTexto (recursosGraficosAmigos->bufferEscribirMensaje, MAX_BUFFER_MENSAJE - 5, evento);
            sfText_setString (recursosGraficosAmigos->texto.auxEscribirMensaje, recursosGraficosAmigos->bufferEscribirMensaje);
        }
        break;

    case sfEvtKeyPressed:
        if ((evento.key.code == sfKeyEnter) &&
            (recursosGraficosAmigos->habilitarEscritura == HABILITAR_ESCRITURA) &&
            (strlen (recursosGraficosAmigos->bufferEscribirMensaje) > 0))
        {
            //Enviar paquete mensaje
        }
        break;

    default:
        break;
    }
}

void actualizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///RECIBIR MENSAJES DE OTROS USUARIOS
    int bytesRecibidos;
    char bufferPaquete [MAX_NOMBRE_USUARIO + MAX_BUFFER_MENSAJE];

    bytesRecibidos = recv (app->sock, bufferPaquete, sizeof (bufferPaquete), 0);
    if (bytesRecibidos > 0)
    {
        bufferPaquete [bytesRecibidos] = '\0';
        asignarMensaje (app, bufferPaquete, OTRO_USUARIO);
    }


    ///TEXTO AUXILIAR ESCRIBIR MENSAJE
    if ((recursosGraficosAmigos->habilitarEscritura == DESHABILITAR_ESCRITURA) && ((strlen (recursosGraficosAmigos->bufferEscribirMensaje) == 0)))
        sfText_setString (recursosGraficosAmigos->texto.auxEscribirMensaje, "Escribir mensaje...");
}

void renderizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (223, 231, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.rectanguloAmigos, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.rectanguloSalas, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraSeparacionUsuarios, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosAmigos->elementos.barraIngresarMensaje, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.amigos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.salas, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.nombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.auxEscribirMensaje, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosAmigos->texto.interfazConfig, NULL);


    ///RENDERIZAR LISTA DE MENSAJES
    mapListaCircularConComplemento (&(app->mensajes.listaMensajes), app->renderizado, renderizarListaMensajes);


    sfRenderWindow_display (app->renderizado);
}

void liberarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos)
{
    ///LIBERAR TEXTO
    sfText_destroy (recursosGraficosAmigos->texto.amigos);
    sfText_destroy (recursosGraficosAmigos->texto.salas);
    sfText_destroy (recursosGraficosAmigos->texto.nombreUsuario);
    sfText_destroy (recursosGraficosAmigos->texto.auxEscribirMensaje);
    sfText_destroy (recursosGraficosAmigos->texto.interfazConfig);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.rectanguloAmigos);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.rectanguloSalas);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.cuadradoRelieveRecSalas);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraSeparacionNombre);
    sfRectangleShape_destroy (recursosGraficosAmigos->elementos.barraIngresarMensaje);
}







































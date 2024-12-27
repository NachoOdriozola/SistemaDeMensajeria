#include "interfazMensajes.h"

int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///INICIALIZAR TEXTO
    recursosGraficosMensajes->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosMensajes->texto.fuente)
    {
        perror ("ERROR - Inicializar fuente.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.mensajeRecibido = sfText_create ();
    if (!recursosGraficosMensajes->texto.mensajeRecibido)
    {
        perror ("ERROR - Inicializar texto de mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.nombreUsuario = sfText_create ();
    if (!recursosGraficosMensajes->texto.nombreUsuario)
    {
        perror ("ERROR - Inicializar texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.auxUsuariosActivos = sfText_create ();
    if (!recursosGraficosMensajes->texto.auxUsuariosActivos)
    {
        perror ("ERROR - Inicializar texto auxiliar usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR ELEMENTOS
    recursosGraficosMensajes->elementos.recIzquierda = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.recIzquierda)
    {
        perror ("ERROR - Inicializar rectangulo de la izquierda.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraSeparacionUsuarios = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionUsuarios)
    {
        perror ("ERROR - Inicializar barra de separacion de usuarios activos.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Inicializar barra de separacion de nombre de usuarios.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->elementos.barraIngresarMensaje = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraIngresarMensaje)
    {
        perror ("ERROR - Inicializar barra de ingresar mensaje.\n");
        return ERROR_INICIALIZACION;
    }

    return CONTINUAR_APLICACION;
}

void setupMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///SETUP TEXTO
    //texto de mensajes recibidos
    sfText_setFont (recursosGraficosMensajes->texto.mensajeRecibido, recursosGraficosMensajes->texto.fuente);
    sfText_setColor (recursosGraficosMensajes->texto.mensajeRecibido, sfColor_fromRGB (0, 0, 0));

    //texto auxiliar usuarios activos
    sfText_setFont (recursosGraficosMensajes->texto.auxUsuariosActivos, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.auxUsuariosActivos, "Usuarios activos");
    sfText_setColor (recursosGraficosMensajes->texto.auxUsuariosActivos, sfColor_fromRGB (34, 48, 48));

    //texto nombre de usuario
    sfText_setFont (recursosGraficosMensajes->texto.nombreUsuario, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.nombreUsuario, "mi usuario");
    sfText_setColor (recursosGraficosMensajes->texto.nombreUsuario, sfColor_fromRGB (34, 48, 48));


    ///SETUP ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.recIzquierda, sfColor_fromRGB (232, 217, 205));

    //barra separacion usuarios activos
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));

    //barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));

    //barra de ingresar mensaje
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraIngresarMensaje, sfColor_fromRGB (208, 208, 208));
}

void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfEvent evento;
    char buffer [MAX_BUFFER];
    int habilitarEscritura;

    sfRenderWindow_pollEvent (app->renderizado, &evento);

    if (evento.type == sfEvtResized)
    {
        sfView *nuevaVistaPantalla = sfView_create ();
        sfVector2f nuevoTamPantalla = {evento.size.width, evento.size.height};
        sfView_setSize (nuevaVistaPantalla, nuevoTamPantalla);
        sfView_setCenter(nuevaVistaPantalla, (sfVector2f){nuevoTamPantalla.x / 2.0f, nuevoTamPantalla.y / 2.0f});
        sfRenderWindow_setView (app->renderizado, nuevaVistaPantalla);
        modificarTamPantalla (recursosGraficosMensajes, app->tamOriginalPantalla, nuevoTamPantalla);
        sfView_destroy (nuevaVistaPantalla);
    }
    if (evento.type == sfEvtClosed)
        app->estado = CERRAR_APLICACION;
    if (evento.type == sfEvtMouseButtonPressed)
    {
        if (clickEnEscribirMensaje (app, recursosGraficosMensajes, evento))
            habilitarEscritura = HABILITAR_ESCRITURA;
        else
            habilitarEscritura = DESHABILITAR_ESCRITURA;
    }
    if (evento.type == sfEvtTextEntered)
    {
        if (habilitarEscritura)
        {
            if ((evento.text.unicode == 'b') && (strlen (buffer) > 0))
            {
                send (sock->sock, buffer, strlen (buffer), 0);
            }
        }
    }

    if (_kbhit ())
    {
        fgets (buffer, MAX_BUFFER, stdin);
        send (sock->sock, buffer, strlen (buffer), 0);
    }
}

void actualizarMensajes (s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    char buffer [MAX_BUFFER];
    int bytesRecibidos;

    bytesRecibidos = recv (sock->sock, buffer, MAX_BUFFER - 1, 0);
    if (bytesRecibidos > 0)
    {
        buffer [bytesRecibidos] = '\0';
        printf ("Mensaje recibido: %s", buffer);
        sfText_setString (recursosGraficosMensajes->texto.mensajeRecibido, buffer);
    }
}

void renderizarMensajes (const s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));


    ///RENDERIZAR ELEMENTOS
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.recIzquierda, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionUsuarios, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraIngresarMensaje, NULL);


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.auxUsuariosActivos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.nombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.mensajeRecibido, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosMensajes->texto.fuente);
    sfText_destroy (recursosGraficosMensajes->texto.mensajeRecibido);
    sfText_destroy (recursosGraficosMensajes->texto.nombreUsuario);
    sfText_destroy (recursosGraficosMensajes->texto.auxUsuariosActivos);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.recIzquierda);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionNombre);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraIngresarMensaje);
}

void modificarTamPantalla (s_recursosGraficosMensajes *recursosGraficosMensajes, sfVector2u tamOriginalPantalla, sfVector2f nuevoTamPantalla)
{
    //TAM REAL 1920 1009
    sfVector2f centroPantalla;
    float escala;

    centroPantalla.x = nuevoTamPantalla.x / 2.0f;
    centroPantalla.y = nuevoTamPantalla.y / 2.0f;
    escala = sqrt ((nuevoTamPantalla.x * nuevoTamPantalla.y) / (tamOriginalPantalla.x * tamOriginalPantalla.y));


    ///MODIFICAR TAM TEXTO
    //texto de mensajes recibidos
    sfText_setPosition (recursosGraficosMensajes->texto.mensajeRecibido, centroPantalla);
    sfText_setCharacterSize (recursosGraficosMensajes->texto.mensajeRecibido, 44 * escala);

    //texto auxiliar usuarios activos
    sfText_setPosition (recursosGraficosMensajes->texto.auxUsuariosActivos, (sfVector2f){nuevoTamPantalla.x / 32, nuevoTamPantalla.y / 20.18});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.auxUsuariosActivos, 28 * escala);

    //texto nombre de usuario
    sfText_setPosition (recursosGraficosMensajes->texto.nombreUsuario, (sfVector2f){nuevoTamPantalla.x / 32, nuevoTamPantalla.y / 1.08});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.nombreUsuario, 28 * escala);


    ///MODIFICAR TAM ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){nuevoTamPantalla.x / 6.4, nuevoTamPantalla.y});

    //barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){nuevoTamPantalla.x / 80, nuevoTamPantalla.y / 8.4});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){nuevoTamPantalla.x / 7.68, nuevoTamPantalla.y / 336});

    //barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){nuevoTamPantalla.x / 80, nuevoTamPantalla.y / 1.13});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){nuevoTamPantalla.x / 7.68, nuevoTamPantalla.y / 336});

    //barra de ingresar mensaje
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){nuevoTamPantalla.x / 4, nuevoTamPantalla.y / 1.11});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraIngresarMensaje, (sfVector2f){nuevoTamPantalla.x / 1.6, nuevoTamPantalla.y / 24});
}

bool clickEnEscribirMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, sfEvent evento)
{
    sfVector2i posMouse;
    sfFloatRect limiteRectangulo;

    posMouse = sfMouse_getPositionRenderWindow (app->renderizado);
    limiteRectangulo = sfRectangleShape_getGlobalBounds (recursosGraficosMensajes->elementos.barraIngresarMensaje);

    return sfFloatRect_contains (&limiteRectangulo, posMouse.x, posMouse.y);
}











































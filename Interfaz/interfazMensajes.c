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

    recursosGraficosMensajes->texto.textoNombreUsuario = sfText_create ();
    if (!recursosGraficosMensajes->texto.textoNombreUsuario)
    {
        perror ("ERROR - Inicializar texto nombre de usuario.\n");
        return ERROR_INICIALIZACION;
    }

    recursosGraficosMensajes->texto.textoAuxUsuariosActivos = sfText_create ();
    if (!recursosGraficosMensajes->texto.textoAuxUsuariosActivos)
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


    ///INICIALIZAR PANTALLA
    recursosGraficosMensajes->pantalla = sfView_create ();
    if (!recursosGraficosMensajes->pantalla)
    {
        perror ("ERROR - Inicializar display de pantalla.\n");
        return ERROR_INICIALIZACION;
    }

    return CONTINUAR_APLICACION;
}

void setupMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    //TAM REAL 1920 1009

    ///SETUP TEXTO
    //texto de mensajes recibidos
    sfText_setPosition (recursosGraficosMensajes->texto.mensajeRecibido, (sfVector2f){960, 540});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.mensajeRecibido, 44);
    sfText_setFont (recursosGraficosMensajes->texto.mensajeRecibido, recursosGraficosMensajes->texto.fuente);
    sfText_setColor (recursosGraficosMensajes->texto.mensajeRecibido, sfColor_fromRGB (0, 0, 0));

    //texto nombre de usuario
    sfText_setPosition (recursosGraficosMensajes->texto.textoNombreUsuario, (sfVector2f){60, 1000});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.textoNombreUsuario, 22);
    sfText_setFont (recursosGraficosMensajes->texto.textoNombreUsuario, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.textoNombreUsuario, "mi usuario");
    sfText_setColor (recursosGraficosMensajes->texto.textoNombreUsuario, sfColor_fromRGB (34, 48, 48));

    //texto auxiliar usuarios activos
    sfText_setPosition (recursosGraficosMensajes->texto.textoAuxUsuariosActivos, (sfVector2f){60, 50});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.textoAuxUsuariosActivos, 28);
    sfText_setFont (recursosGraficosMensajes->texto.textoAuxUsuariosActivos, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->texto.textoAuxUsuariosActivos, "Usuarios activos");
    sfText_setColor (recursosGraficosMensajes->texto.textoAuxUsuariosActivos, sfColor_fromRGB (34, 48, 48));


    ///SETUP ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){300, 1080});
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.recIzquierda, sfColor_fromRGB (232, 217, 205));

    //barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){24, 120});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){250, 3});
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));

    //barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){24, 960});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){250, 3});
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));
}

void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfEvent evento;
    char buffer [MAX_BUFFER];

    sfRenderWindow_pollEvent (app->renderizado, &evento);

    if (evento.type == sfEvtResized)
    {
        sfVector2f nuevoTam = {evento.size.width, evento.size.height};
        sfView_setSize (recursosGraficosMensajes->pantalla, nuevoTam);
        sfView_setCenter(recursosGraficosMensajes->pantalla, (sfVector2f){nuevoTam.x / 2, nuevoTam.y / 2});
        sfRenderWindow_setView (app->renderizado, recursosGraficosMensajes->pantalla);
        modificarTamPantalla (recursosGraficosMensajes, nuevoTam);
        printf ("x: %.2f , y = %.2f\n", nuevoTam.x, nuevoTam.y);
    }
    if (evento.type == sfEvtClosed)
        app->estado = CERRAR_APLICACION;

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


    ///RENDERIZAR TEXTO
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.textoAuxUsuariosActivos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.textoNombreUsuario, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.mensajeRecibido, NULL);


    sfRenderWindow_display (app->renderizado);
}

void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///LIBERAR TEXTO
    sfFont_destroy (recursosGraficosMensajes->texto.fuente);
    sfText_destroy (recursosGraficosMensajes->texto.mensajeRecibido);
    sfText_destroy (recursosGraficosMensajes->texto.textoNombreUsuario);
    sfText_destroy (recursosGraficosMensajes->texto.textoAuxUsuariosActivos);


    ///LIBERAR ELEMENTOS
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.recIzquierda);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionNombre);


    ///LIBERAR PANTALLA
    sfView_destroy (recursosGraficosMensajes->pantalla);
}

void modificarTamPantalla (s_recursosGraficosMensajes *recursosGraficosMensajes, sfVector2f tamPantalla)
{
    sfVector2f centroPantalla;

    centroPantalla.x = tamPantalla.x / 2;
    centroPantalla.y = tamPantalla.y / 2;


    ///MODIFICAR TAM TEXTO
    //texto de mensajes recibidos
    sfText_setPosition (recursosGraficosMensajes->texto.mensajeRecibido, centroPantalla);
    sfText_setCharacterSize (recursosGraficosMensajes->texto.mensajeRecibido, 44);

    //texto nombre de usuario
    sfText_setPosition (recursosGraficosMensajes->texto.textoNombreUsuario, (sfVector2f){tamPantalla.x / 32, tamPantalla.y / 1.08});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.textoNombreUsuario, 22);

    //texto auxiliar usuarios activos
    sfText_setPosition (recursosGraficosMensajes->texto.textoAuxUsuariosActivos, (sfVector2f){tamPantalla.x / 32, tamPantalla.y / 21.6});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.textoAuxUsuariosActivos, 28);


    ///MODIFICAR TAM ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){0, 0});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){tamPantalla.x / 6.4, tamPantalla.y});

    //barra separacion usuarios activos
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){tamPantalla.x / 80, tamPantalla.y / 9});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){tamPantalla.x / 7.68, tamPantalla.y / 360});

    //barra separacion nombre de usuario
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){tamPantalla.x / 80, tamPantalla.y / 1.125});
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){tamPantalla.x / 7.68, tamPantalla.y / 360});
}












#include "funciones.h"

///INICIALIZACION
void inicializar (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock)
{
    ///INICIALIZAR APLICACION
    app->aplicacionEjecutandose = CONTINUAR_APLICACION;

    app->renderizado = sfRenderWindow_create ((sfVideoMode){1920, 1080}, "App", sfDefaultStyle, NULL);
    if (!app->renderizado)
    {
        perror ("ERROR - Inicializar renderizado.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }


    ///INICIALIZAR SOCKET
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &(sock->wsaData));
    if (resultado != 0)
    {
        printf ("ERROR - Inicializar Winsock: %d.\n", resultado);
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    sock->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock->sock == INVALID_SOCKET)
    {
        printf ("ERROR - Crear el socket: %d.\n", WSAGetLastError ());
        WSACleanup ();
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }


    ///INICIALIZAR recursosGraficos
    recursosGraficos->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficos->texto.fuente)
    {
        perror ("ERROR - Inicializar fuente.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    recursosGraficos->texto.texto = sfText_create ();
    if (!recursosGraficos->texto.texto)
    {
        perror ("ERROR - Inicializar texto.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    recursosGraficos->elementos.recIzquierda = sfRectangleShape_create ();
    if (!recursosGraficos->elementos.recIzquierda)
    {
        perror ("ERROR - Inicializar rectangulo de la izquierda.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    recursosGraficos->elementos.barraSeparacionUsuarios = sfRectangleShape_create ();
    if (!recursosGraficos->elementos.barraSeparacionUsuarios)
    {
        perror ("ERROR - Inicializar barra de separacion de usuarios activos.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    recursosGraficos->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficos->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Inicializar barra de separacion de nombre de usuarios.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    recursosGraficos->elementos.textoNombreUsuario = sfText_create ();
    if (!recursosGraficos->elementos.textoNombreUsuario)
    {
        perror ("ERROR - Inicializar texto nombre de usuario.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    recursosGraficos->elementos.textoAuxUsuariosActivos = sfText_create ();
    if (!recursosGraficos->elementos.textoAuxUsuariosActivos)
    {
        perror ("ERROR - Inicializar texto auxiliar usuarios activos.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
}

void setup (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock)
{
    ///SETUP APLICACION
    sfRenderWindow_setFramerateLimit (app->renderizado, 60);


    ///SETUP SOCKET
    ioctlsocket (sock->sock, FIONBIO, &(sock->modoSocket)); //Socket modo no bloqueante
    sock->direccionServidor.sin_family = AF_INET;
    sock->direccionServidor.sin_port = htons (PUERTO);
    sock->direccionServidor.sin_addr.s_addr = inet_addr ("127.0.0.1");
    if (connect (sock->sock, (struct sockaddr*)&(sock->direccionServidor), sizeof (sock->direccionServidor)) != SOCKET_ERROR)
    {
        printf ("ERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        closesocket (sock->sock);
        WSACleanup ();
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    else
        printf ("Conectado al servidor.\n");


    ///SETUP recursosGraficos
    ///TEXTO
    sfText_setFont (recursosGraficos->texto.texto, recursosGraficos->texto.fuente);
    sfText_setPosition (recursosGraficos->texto.texto, (sfVector2f){0, 0});
    sfText_setCharacterSize (recursosGraficos->texto.texto, 24);
    sfText_setColor (recursosGraficos->texto.texto, sfColor_fromRGB (255, 255, 255));

    ///ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setFillColor (recursosGraficos->elementos.recIzquierda, sfColor_fromRGB (232, 217, 205));
    sfRectangleShape_setSize (recursosGraficos->elementos.recIzquierda, (sfVector2f){300, 1080});
    sfRectangleShape_setPosition (recursosGraficos->elementos.recIzquierda, (sfVector2f){0, 0});

    //barra separacion usuarios activos
    sfRectangleShape_setFillColor (recursosGraficos->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));
    sfRectangleShape_setSize (recursosGraficos->elementos.barraSeparacionUsuarios, (sfVector2f){250, 3});
    sfRectangleShape_setPosition (recursosGraficos->elementos.barraSeparacionUsuarios, (sfVector2f){24, 120});

    //barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficos->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));
    sfRectangleShape_setSize (recursosGraficos->elementos.barraSeparacionNombre, (sfVector2f){250, 3});
    sfRectangleShape_setPosition (recursosGraficos->elementos.barraSeparacionNombre, (sfVector2f){24, 960});

    //texto nombre de usuario
    sfText_setFont (recursosGraficos->elementos.textoNombreUsuario, recursosGraficos->texto.fuente);
    sfText_setString (recursosGraficos->elementos.textoNombreUsuario, "mi usuario");
    sfText_setPosition (recursosGraficos->elementos.textoNombreUsuario, (sfVector2f){60, 1000});
    sfText_setColor (recursosGraficos->elementos.textoNombreUsuario, sfColor_fromRGB (34, 48, 48));
    sfText_setCharacterSize (recursosGraficos->elementos.textoNombreUsuario, 22);

    //texto auxiliar usuarios activos
    sfText_setFont (recursosGraficos->elementos.textoAuxUsuariosActivos, recursosGraficos->texto.fuente);
    sfText_setString (recursosGraficos->elementos.textoAuxUsuariosActivos, "Usuarios activos");
    sfText_setPosition (recursosGraficos->elementos.textoAuxUsuariosActivos, (sfVector2f){60, 50});
    sfText_setColor (recursosGraficos->elementos.textoAuxUsuariosActivos, sfColor_fromRGB (34, 48, 48));
    sfText_setCharacterSize (recursosGraficos->elementos.textoAuxUsuariosActivos, 28);
}



///INTERFAZ DE INICIO
void accionInicio ()
{

}

void actualizarInicio ()
{

}

void renderizarInicio ()
{

}

void liberarInicio ()
{

}



///INTERFAZ DE MENSAJES
void accionMensajes (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock)
{
    sfEvent evento;
    char buffer [MAX_BUFFER];

    sfRenderWindow_pollEvent (app->renderizado, &evento);

    if (evento.type == sfEvtClosed)
        app->aplicacionEjecutandose = CERRAR_APLICACION;

    if (_kbhit ())
    {
        fgets (buffer, MAX_BUFFER, stdin);
        send (sock->sock, buffer, strlen (buffer), 0);
    }
}

void actualizarMensajes (s_recursosGraficos *recursosGraficos, s_socket *sock)
{
    char buffer [MAX_BUFFER];
    int bytesRecibidos;

    bytesRecibidos = recv (sock->sock, buffer, MAX_BUFFER - 1, 0);
    if (bytesRecibidos > 0)
    {
        buffer [bytesRecibidos] = '\0';
        printf ("Mensaje recibido: %s", buffer);
        sfText_setString (recursosGraficos->texto.texto, buffer);
    }
}

void renderizarMensajes (const s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));

    sfRenderWindow_drawText (app->renderizado, recursosGraficos->texto.texto, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficos->elementos.recIzquierda, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficos->elementos.barraSeparacionUsuarios, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficos->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficos->elementos.textoAuxUsuariosActivos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficos->elementos.textoNombreUsuario, NULL);

    sfRenderWindow_display (app->renderizado);
}

void liberarMensajes (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock)
{
    ///LIBERAR APLICACION
    sfRenderWindow_destroy (app->renderizado);


    ///LIBERAR SOCKET
    closesocket (sock->sock);
    WSACleanup ();


    ///LIBERAR recursosGraficos
    sfFont_destroy (recursosGraficos->texto.fuente);
    sfText_destroy (recursosGraficos->texto.texto);
    sfRectangleShape_destroy (recursosGraficos->elementos.recIzquierda);
    sfRectangleShape_destroy (recursosGraficos->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficos->elementos.barraSeparacionNombre);
    sfText_destroy (recursosGraficos->elementos.textoNombreUsuario);
    sfText_destroy (recursosGraficos->elementos.textoAuxUsuariosActivos);
}



















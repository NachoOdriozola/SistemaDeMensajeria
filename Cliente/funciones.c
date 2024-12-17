#include "funciones.h"

void inicializar (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock)
{
    ///INICIALIZAR APLICACION
    app->aplicacionEjecutandose = CONTINUAR_APLICACION;

    app->renderizado = sfRenderWindow_create (sfVideoMode_getDesktopMode (), "App", sfDefaultStyle, NULL);
    if (!app->renderizado)
    {
        perror ("ERROR - Inicializar renderizado.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }


    ///INICIALIZAR RECURSOS
    recursos->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursos->texto.fuente)
    {
        perror ("ERROR - Inicializar fuente.\n");
        app->aplicacionEjecutandose = CERRAR_APLICACION;
    }
    recursos->texto.texto = sfText_create ();
    if (!recursos->texto.texto)
    {
        perror ("ERROR - Inicializar texto.\n");
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
}

void setup (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock)
{
    ///SETUP APLICACION
    sfRenderWindow_setFramerateLimit (app->renderizado, 60);


    ///SETUP RECURSOS
    sfText_setFont (recursos->texto.texto, recursos->texto.fuente);
    sfText_setPosition (recursos->texto.texto, (sfVector2f){0, 0});
    sfText_setCharacterSize (recursos->texto.texto, 24);
    sfText_setColor (recursos->texto.texto, sfColor_fromRGB (255, 255, 255));


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
}

void accion (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock)
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

void actualizar (s_recursos *recursos, s_socket *sock)
{
    char buffer [MAX_BUFFER];
    int bytesRecibidos;

    bytesRecibidos = recv (sock->sock, buffer, MAX_BUFFER - 1, 0);
    if (bytesRecibidos > 0)
    {
        buffer [bytesRecibidos] = '\0';
        printf ("Mensaje recibido: %s", buffer);
        sfText_setString (recursos->texto.texto, buffer);
    }
}

void renderizar (const s_estadoAplicacion *app, s_recursos *recursos)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (0, 0, 0));

    sfRenderWindow_drawText (app->renderizado, recursos->texto.texto, NULL);

    sfRenderWindow_display (app->renderizado);
}

void liberar (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock)
{
    ///LIBERAR APLICACION
    sfRenderWindow_destroy (app->renderizado);

    ///LIBERAR RECURSOS
    sfFont_destroy (recursos->texto.fuente);
    sfText_destroy (recursos->texto.texto);


    ///LIBERAR SOCKET
    closesocket (sock->sock);
    WSACleanup ();
}



















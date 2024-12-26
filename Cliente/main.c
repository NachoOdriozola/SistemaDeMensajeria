#include "main.h"

int main()
{
    int interfaz;

    s_aplicacion app;
    s_socket socket;
    s_usuario usuario;

    s_recursosGraficosInicio recursosGraficosInicio;
    s_recursosGraficosMensajes recursosGraficosMensajes;

    inicializar (&app, &socket, &recursosGraficosInicio, &recursosGraficosMensajes);
    if (app.estado == CONTINUAR_APLICACION)
        setup (&app, &socket, &recursosGraficosInicio, &recursosGraficosMensajes);
    else
    {
        perror ("ERROR - Inicializar recursos.\n");
        return ERROR_INICIALIZACION;
    }

    printf ("INICIALIZACION Y SETUP EXITOSOS.\n");
    interfaz = INTERFAZ_MENSAJES;
    while (app.estado)
    {
        switch (interfaz)
        {
        case INTERFAZ_INICIO:
            accionInicio ();
            actualizarInicio ();
            renderizarInicio ();
            if (usuario.estado == ACTIVO)
            {
                interfaz = INTERFAZ_MENSAJES;
                liberarInicio ();
            }
            break;
        case INTERFAZ_MENSAJES:
            accionMensajes (&app, &socket, &recursosGraficosMensajes);
            actualizarMensajes (&socket, &recursosGraficosMensajes);
            renderizarMensajes (&app, &recursosGraficosMensajes);
            break;
        }
    }

    liberar (&app, &socket, &recursosGraficosMensajes);
    system ("pause");

    return OK;
}

void inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    printf ("INICIALIZANDO RECURSOS.\n");


    ///INICIALIZAR APLICACION
    app->estado = CONTINUAR_APLICACION;

    sfVideoMode tamPantalla;
    tamPantalla = sfVideoMode_getDesktopMode ();
    app->renderizado = sfRenderWindow_create ((sfVideoMode){tamPantalla.width, tamPantalla.height - 20}, "App", sfDefaultStyle, NULL);
    if (!app->renderizado)
    {
        perror ("ERROR - Inicializar renderizado.\n");
        app->estado = CERRAR_APLICACION;
    }


    ///INICIALIZAR SOCKET
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &(sock->wsaData));
    if (resultado != 0)
    {
        printf ("ERROR - Inicializar Winsock: %d.\n", resultado);
        app->estado = CERRAR_APLICACION;
    }
    sock->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock->sock == INVALID_SOCKET)
    {
        printf ("ERROR - Crear el socket: %d.\n", WSAGetLastError ());
        WSACleanup ();
        app->estado = CERRAR_APLICACION;
    }


    ///INICIALIZAR RECURSOS GRAFICOS DE INTERFAZ DE INICIO
    app->estado = inicializarInicio (recursosGraficosInicio);


    ///INICIALIZAR RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    app->estado = inicializarMensajes (recursosGraficosMensajes);
}

void setup (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    printf ("SETUP DE RECURSOS.\n");


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
        app->estado = CERRAR_APLICACION;
    }
    else
        printf ("CONECTADO CON EL SERVIDOR.\n");


    ///SETUP RECURSOS GRAFICOS DE INTERFAZ DE INICIO
    setupInicio (recursosGraficosInicio);


    ///SETUP RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    setupMensajes (recursosGraficosMensajes);
}

void liberar (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///LIBERAR APLICACION
    sfRenderWindow_destroy (app->renderizado);


    ///LIBERAR SOCKET
    closesocket (sock->sock);
    WSACleanup ();


    ///LIBERAR RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    liberarMensajes (recursosGraficosMensajes);
}






















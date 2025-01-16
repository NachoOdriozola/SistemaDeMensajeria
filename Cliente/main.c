#include "main.h"

int main()
{
    unsigned short int interfaz;

    s_aplicacion app;
    s_socket socket;

    s_recursosGraficosInicio recursosGraficosInicio;
    s_recursosGraficosMensajes recursosGraficosMensajes;


    if (inicializar (&app, &socket, &recursosGraficosInicio, &recursosGraficosMensajes) == ERROR_INICIALIZACION)
    {
        perror ("ERROR - Inicializar recursos.\n");
        liberar (&app, &socket, &recursosGraficosMensajes);
        return ERROR_INICIALIZACION;
    }
    if (setup (&app, &socket, &recursosGraficosInicio, &recursosGraficosMensajes) == ERROR_INICIALIZACION)
    {
        perror ("ERROR - Setup de recursos.\n");
        liberar (&app, &socket, &recursosGraficosMensajes);
        return ERROR_INICIALIZACION;
    }

    printf ("INICIALIZACION Y SETUP EXITOSOS.\n");
    interfaz = INTERFAZ_MENSAJES;
    app.aplicacionEjecutandose = CONTINUAR_APLICACION;
    while (app.aplicacionEjecutandose)
    {
        switch (interfaz)
        {
        case INTERFAZ_INICIO:
            accionInicio ();
            actualizarInicio ();
            renderizarInicio ();
            interfaz = INTERFAZ_MENSAJES;
            liberarInicio ();
            break;

        case INTERFAZ_MENSAJES:
            accionMensajes (&app, &socket, &recursosGraficosMensajes);
            actualizarMensajes (&app, &socket, &recursosGraficosMensajes);
            renderizarMensajes (&app, &recursosGraficosMensajes);
            break;
        }
    }

    liberar (&app, &socket, &recursosGraficosMensajes);
    system ("pause");

    return OK;
}

int inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    printf ("INICIALIZANDO RECURSOS.\n");


    ///INICIALIZAR APLICACION
    HWND hwnd;
    sfVideoMode tamPantalla;

    tamPantalla = sfVideoMode_getDesktopMode ();
    app->renderizado = sfRenderWindow_create ((sfVideoMode){tamPantalla.width, tamPantalla.height - 1}, "App", sfDefaultStyle, NULL);
    if (!app->renderizado)
    {
        perror ("ERROR - Inicializar renderizado.\n");
        return ERROR_INICIALIZACION;
    }
    hwnd = sfRenderWindow_getSystemHandle (app->renderizado);
    ShowWindow (hwnd, SW_MAXIMIZE);


    ///INICIALIZAR SOCKET
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &(sock->wsaData));
    if (resultado != 0)
    {
        printf ("ERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }
    sock->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock->sock == INVALID_SOCKET)
    {
        printf ("ERROR - Crear el socket: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR RECURSOS GRAFICOS DE INTERFAZ DE INICIO
    if (inicializarInicio (recursosGraficosInicio) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    ///INICIALIZAR RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    if (inicializarMensajes (recursosGraficosMensajes) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return OK;
}

int setup (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    printf ("SETUP DE RECURSOS.\n");


    ///SETUP APLICACION
    sfRenderWindow_setFramerateLimit (app->renderizado, 60);
    app->primerMaximizado = PRIMER_MAXIMIZADO;


    ///SETUP SOCKET
    u_long modoSocket = 1; //Socket modo no bloqueante

    ioctlsocket (sock->sock, FIONBIO, &modoSocket);
    sock->direccionServidor.sin_family = AF_INET;
    sock->direccionServidor.sin_port = htons (PUERTO);
    sock->direccionServidor.sin_addr.s_addr = inet_addr ("127.0.0.1");
    if (connect (sock->sock, (struct sockaddr*)&(sock->direccionServidor), sizeof (sock->direccionServidor)) != SOCKET_ERROR)
    {
        printf ("ERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }
    else
        printf ("CONECTADO CON EL SERVIDOR.\n");


    ///SETUP RECURSOS GRAFICOS DE INTERFAZ DE INICIO
    setupInicio (recursosGraficosInicio);


    ///SETUP RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    setupMensajes (recursosGraficosMensajes);


    return OK;
}

void liberar (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///LIBERAR RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    liberarMensajes (recursosGraficosMensajes);


    ///LIBERAR SOCKET
    closesocket (sock->sock);
    WSACleanup ();


    ///LIBERAR APLICACION
    sfRenderWindow_destroy (app->renderizado);
}






















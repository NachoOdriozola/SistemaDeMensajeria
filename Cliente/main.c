#include "main.h"


int main()
{
    s_aplicacion app;
    s_socket socket;

    s_recursosGraficosInicio recursosGraficosInicio;
    s_recursosGraficosMensajes recursosGraficosMensajes;


    if (inicializar (&app, &socket, &recursosGraficosMensajes) == ERROR_INICIALIZACION)
    {
        perror ("ERROR - Inicializar recursos.\n");
        liberar (&app, &socket, &recursosGraficosMensajes);
        return ERROR_INICIALIZACION;
    }
    setup (&app, &socket, &recursosGraficosMensajes);

    if (verificarDatosGuardados(&app) == INICIO_SESION_AUTOMATICO)
    {
        app.interfaz = INTERFAZ_MENSAJES;
        maximizadoAutomaticoVentana (&app);
        TamYPosPantallaMensajes (&app, &recursosGraficosMensajes);
        sfText_setString (recursosGraficosMensajes.texto.nombreUsuario, app.usuario.nombreUsuario);
    }
    else
    {
        app.interfaz = INTERFAZ_INICIO;
        inicializarInicio (&recursosGraficosInicio);
        setupInicio (&recursosGraficosInicio);
    }


    printf ("INICIALIZACION Y SETUP EXITOSOS.\n");
    while (app.aplicacionEjecutandose == CONTINUAR_APLICACION)
    {
        switch (app.interfaz)
        {
        case INTERFAZ_INICIO:
            accionInicio (&app, &recursosGraficosInicio);
            actualizarInicio (&recursosGraficosInicio);
            renderizarInicio (&app, &recursosGraficosInicio);
            if (app.interfaz == INTERFAZ_MENSAJES)
            {
                maximizadoAutomaticoVentana (&app);
                TamYPosPantallaMensajes (&app, &recursosGraficosMensajes);
                sfText_setString (recursosGraficosMensajes.texto.nombreUsuario, app.usuario.nombreUsuario);
                liberarInicio (&recursosGraficosInicio);
            }
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

int inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    printf ("INICIALIZANDO RECURSOS.\n");


    ///INICIALIZAR APLICACION
    app->renderizado = sfRenderWindow_create ((sfVideoMode){540, 540}, "App", sfDefaultStyle, NULL);
    if (!app->renderizado)
    {
        perror ("ERROR - Crear renderizado.\n");
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR SOCKET
    int resultado;
    u_long modoSocket = 1; //Socket modo no bloqueante

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


    ///INICIALIZAR RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    if (inicializarMensajes (recursosGraficosMensajes) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return OK;
}

void setup (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    printf ("SETUP DE RECURSOS.\n");


    ///SETUP APLICACION
    sfRenderWindow_setFramerateLimit (app->renderizado, 60);
    app->aplicacionEjecutandose = CONTINUAR_APLICACION;
    app->usuario.actividadUsuario = ACTIVO;


    ///SETUP RECURSOS GRAFICOS DE INTERFAZ DE MENSAJES
    setupMensajes (app, recursosGraficosMensajes);
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





















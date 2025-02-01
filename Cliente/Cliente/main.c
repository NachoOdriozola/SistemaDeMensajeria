#include "main.h"


int main()
{
    s_aplicacion app;
    s_socket socket;
    s_recursosGraficos recursosGraficos;
    u_long modoSocket = 1; //Socket modo no bloqueante


    if (inicializar (&app, &socket, &recursosGraficos) == ERROR_INICIALIZACION)
    {
        perror ("ERROR - Inicializar recursos.\n");
        liberar (&app, &socket, &recursosGraficos);
        return ERROR_INICIALIZACION;
    }
    setup (&app, &socket, &recursosGraficos);


    inicializarRegistro (&(recursosGraficos.recursosGraficosRegistro));
    setupRegistro (&(recursosGraficos.recursosGraficosRegistro));


    if (verificarDatosGuardados (&app) == INICIO_SESION_AUTOMATICO)
    {
        app.interfaz = INTERFAZ_AMIGOS;
        maximizadoAutomaticoVentana (&app);
        TamYPosPantallaAmigos (&app, &(recursosGraficos.recursosGraficosAmigos));
        tamYPosPantallaSalas (&app, &(recursosGraficos.recursosGraficosSalas));
        sfText_setString (recursosGraficos.recursosGraficosAmigos.texto.nombreUsuario, app.usuario.nombreUsuario);
    }
    else //Inicio de sesion manual
    {
        app.interfaz = INTERFAZ_INICIO;
        inicializarInicio (&(recursosGraficos.recursosGraficosInicio));
        setupInicio (&(recursosGraficos.recursosGraficosInicio));
    }


    printf ("INICIALIZACION Y SETUP EXITOSOS.\n");
    while (app.aplicacionEjecutandose == CONTINUAR_APLICACION)
    {
        switch (app.interfaz)
        {
        case INTERFAZ_INICIO:
            accionInicio (&app, &socket, &(recursosGraficos.recursosGraficosInicio));
            actualizarInicio (&(recursosGraficos.recursosGraficosInicio));
            renderizarInicio (&app, &(recursosGraficos.recursosGraficosInicio));
            if (app.interfaz != INTERFAZ_INICIO)
            {
                if (app.interfaz == INTERFAZ_AMIGOS)
                {
                    maximizadoAutomaticoVentana (&app);
                    TamYPosPantallaAmigos (&app, &(recursosGraficos.recursosGraficosAmigos));
                    tamYPosPantallaSalas (&app, &(recursosGraficos.recursosGraficosSalas));
                    ioctlsocket (socket.sock, FIONBIO, &modoSocket);
                    sfText_setString (recursosGraficos.recursosGraficosAmigos.texto.nombreUsuario, app.usuario.nombreUsuario);
                    liberarInicio (&(recursosGraficos.recursosGraficosInicio));
                }

                if (app.interfaz == INTERFAZ_REGISTRO)
                {
                    //inicializarRegistro (&(recursosGraficos.recursosGraficosRegistro));
                    //setupRegistro (&(recursosGraficos.recursosGraficosRegistro));
                }
            }
            break;

        case INTERFAZ_REGISTRO:
            accionRegistro (&app, &socket, &(recursosGraficos.recursosGraficosRegistro));
            actualizarRegistro (&(recursosGraficos.recursosGraficosRegistro));
            renderizarRegistro (&app, &(recursosGraficos.recursosGraficosRegistro));
            if (app.interfaz != INTERFAZ_REGISTRO)
            {
                printf ("entro.\n");
                if (app.interfaz == INTERFAZ_INICIO)
                    liberarRegistro (&(recursosGraficos.recursosGraficosRegistro));

                if (app.interfaz == INTERFAZ_AMIGOS)
                {
                    liberarRegistro (&(recursosGraficos.recursosGraficosRegistro));
                    liberarInicio (&(recursosGraficos.recursosGraficosInicio));
                }
            }
            break;

        case INTERFAZ_AMIGOS:
            accionAmigos (&app, &socket, &(recursosGraficos.recursosGraficosAmigos));
            actualizarAmigos (&app, &socket, &(recursosGraficos.recursosGraficosAmigos));
            renderizarAmigos (&app, &(recursosGraficos.recursosGraficosAmigos));
            if (app.interfaz == INTERFAZ_CONFIG)
            {
                inicializarConfig (&(recursosGraficos.recursosGraficosConfig));
                setupConfig (&app, &(recursosGraficos.recursosGraficosConfig));
                app.usuario.ultimaInterfaz = INTERFAZ_AMIGOS;
            }
            break;

        case INTERFAZ_SALAS:
            accionSalas (&app, &socket, &(recursosGraficos.recursosGraficosSalas));
            actualizarSalas (&app, &socket, &(recursosGraficos.recursosGraficosSalas));
            renderizarSalas (&app, &(recursosGraficos.recursosGraficosSalas));
            if (app.interfaz == INTERFAZ_CONFIG)
            {
                inicializarConfig (&(recursosGraficos.recursosGraficosConfig));
                setupConfig (&app, &(recursosGraficos.recursosGraficosConfig));
                app.usuario.ultimaInterfaz = INTERFAZ_SALAS;
            }
            break;

        case INTERFAZ_CONFIG:
            accionConfig (&app, &(recursosGraficos.recursosGraficosConfig));
            actualizarConfig (&(recursosGraficos.recursosGraficosConfig));
            renderizarConfig (&app, &(recursosGraficos.recursosGraficosConfig));
            if (app.interfaz != INTERFAZ_CONFIG)
                liberarConfig (&(recursosGraficos.recursosGraficosConfig));
            break;
        }
    }

    liberar (&app, &socket, &recursosGraficos);
    system ("pause");

    return OK;
}

int inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficos *recursosGraficos)
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
    u_long modoSocket = 0; //Socket modo bloqueante

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
    if (connect (sock->sock, (struct sockaddr*)&(sock->direccionServidor), sizeof (sock->direccionServidor)) == SOCKET_ERROR)
    {
        printf ("ERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }
    else
        printf ("CONECTADO CON EL SERVIDOR.\n");


    ///INICIALIZAR RECURSOS GRAFICOS
    //Interfaz de amigos
    if (inicializarAmigos (&(recursosGraficos->recursosGraficosAmigos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //Interfaz de salas
    if (inicializarSalas (&(recursosGraficos->recursosGraficosSalas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    return OK;
}

void setup (s_aplicacion *app, s_socket *sock, s_recursosGraficos *recursosGraficos)
{
    printf ("SETUP DE RECURSOS.\n");


    ///SETUP APLICACION
    sfRenderWindow_setFramerateLimit (app->renderizado, 60);
    app->aplicacionEjecutandose = CONTINUAR_APLICACION;


    ///SETUP RECURSOS GRAFICOS
    //Interfaz de amigos
    setupAmigos (app, &(recursosGraficos->recursosGraficosAmigos));

    //Interfaz de salas
    setupSalas (app, &(recursosGraficos->recursosGraficosSalas));
}

void liberar (s_aplicacion *app, s_socket *sock, s_recursosGraficos *recursosGraficos)
{
    ///LIBERAR RECURSOS GRAFICOS
    //Interfaz de amigos
    liberarAmigos (&(recursosGraficos->recursosGraficosAmigos));

    //Interfaz de salas
    liberarSalas (&(recursosGraficos->recursosGraficosSalas));


    ///LIBERAR SOCKET
    closesocket (sock->sock);
    WSACleanup ();


    ///LIBERAR APLICACION
    sfRenderWindow_destroy (app->renderizado);
}





















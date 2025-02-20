#include "main.h"


///FUNCIONES ESTRUCTURALES


int main()
{
    s_aplicacion app;
    s_recursosGraficos recursosGraficos;


    ///INICIALIZAR WINSOCK
    WSADATA wsaData;
    int resultado;

    resultado = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (resultado != 0)
    {
        printf ("ERROR - Inicializar Winsock: %d.\n", resultado);
        return ERROR_INICIALIZACION;
    }


    ///INICIALIZAR Y SETUP APLICACION Y RECURSOS
    if (inicializar (&app, &recursosGraficos) == ERROR_INICIALIZACION)
    {
        perror ("ERROR - Inicializar recursos.\n");
        liberar (&app, &recursosGraficos);
        return ERROR_INICIALIZACION;
    }
    setup (&app, &recursosGraficos);

    if (verificarDatosGuardados (&app) == INICIO_SESION_AUTOMATICO)
        inicioMenuAplicacion (&app, &recursosGraficos);
    else
    {
        if (inicioSesionManual (&app, &recursosGraficos) == ERROR_INICIALIZACION)
        {
            perror ("ERROR - Inicializar recursos para inicio de sesion manual.\n");
            liberar (&app, &recursosGraficos);
            return ERROR_INICIALIZACION;
        }
    }


    printf ("INICIALIZACION Y SETUP EXITOSOS.\n");

    while (app.aplicacionEjecutandose == CONTINUAR_APLICACION)
    {
        switch (app.interfaz)
        {
        case INTERFAZ_INICIO:
            accionInicio (&app, &(recursosGraficos.recursosGraficosInicio));
            actualizarInicio (&(recursosGraficos.recursosGraficosInicio));
            renderizarInicio (&app, &(recursosGraficos.recursosGraficosInicio));
            if (app.interfaz == INTERFAZ_AMIGOS)
            {
                inicioMenuAplicacion (&app, &recursosGraficos);
                liberarInicio (&(recursosGraficos.recursosGraficosInicio));
                liberarRegistro (&(recursosGraficos.recursosGraficosRegistro));
            }
            break;

        case INTERFAZ_REGISTRO:
            accionRegistro (&app, &(recursosGraficos.recursosGraficosRegistro));
            actualizarRegistro (&(recursosGraficos.recursosGraficosRegistro));
            renderizarRegistro (&app, &(recursosGraficos.recursosGraficosRegistro));
            if (app.interfaz == INTERFAZ_AMIGOS)
            {
                inicioMenuAplicacion (&app, &recursosGraficos);
                liberarInicio (&(recursosGraficos.recursosGraficosInicio));
                liberarRegistro (&(recursosGraficos.recursosGraficosRegistro));
            }
            break;

        case INTERFAZ_AMIGOS:
            accionAmigos (&app, &(recursosGraficos.recursosGraficosAmigos));
            actualizarAmigos (&app, &(recursosGraficos.recursosGraficosAmigos));
            renderizarAmigos (&app, &(recursosGraficos.recursosGraficosAmigos));
            break;

        case INTERFAZ_SALAS:
            accionSalas (&app, &(recursosGraficos.recursosGraficosSalas));
            actualizarSalas (&app, &(recursosGraficos.recursosGraficosSalas));
            renderizarSalas (&app, &(recursosGraficos.recursosGraficosSalas));
            break;

        case INTERFAZ_CONFIG:
            accionConfig (&app, &(recursosGraficos.recursosGraficosConfig));
            actualizarConfig (&(recursosGraficos.recursosGraficosConfig));
            renderizarConfig (&app, &(recursosGraficos.recursosGraficosConfig));
            break;
        }
    }

    liberar (&app, &recursosGraficos);
    system ("pause");


    return OK;
}

int inicializar (s_aplicacion *app, s_recursosGraficos *recursosGraficos)
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
    struct sockaddr_in dirCliente;
    u_long modoSocket = 0; //Socket modo bloqueante

    app->sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (app->sock == INVALID_SOCKET)
    {
        printf ("ERROR - Crear el socket: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }

    dirCliente.sin_family = AF_INET;
    dirCliente.sin_port = htons (PUERTO);
    dirCliente.sin_addr.s_addr = inet_addr ("127.0.0.1");
    if (connect (app->sock, (struct sockaddr*)&(dirCliente), sizeof (dirCliente)) == SOCKET_ERROR)
    {
        printf ("ERROR - Conectarse con el servidor: %d.\n", WSAGetLastError ());
        return ERROR_INICIALIZACION;
    }
    ioctlsocket (app->sock, FIONBIO, &modoSocket);
    printf ("CONECTADO CON EL SERVIDOR.\n");


    ///INICIALIZAR RECURSOS GRAFICOS
    //Interfaz de amigos
    if (inicializarAmigos (&(recursosGraficos->recursosGraficosAmigos)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //Interfaz de salas
    if (inicializarSalas (&(recursosGraficos->recursosGraficosSalas)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //Interfaz configuraciones
    if (inicializarConfig (&(recursosGraficos->recursosGraficosConfig)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    ///INICIALIZAR FUENTES
    if (inicializarFuentes (&(app->mensajes.fuentes)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    ///INICIALIZAR LISTA DE MENSAJES
    unsigned short int i;
    s_mensaje mensajes [MAX_MENSAJES_EN_MEM], *ptrMensaje = mensajes;

    crearListaCircular (&(app->mensajes.listaMensajes));
    for (i = 0; i < MAX_MENSAJES_EN_MEM; i ++)
    {
        ptrMensaje->mensaje = sfText_create ();
        insertarSegundoCircular (&(app->mensajes.listaMensajes), ptrMensaje, sizeof (s_mensaje));
        ptrMensaje ++;
    }


    ///INICIALIZAR LISTA DE NOTIFICACIONES
    crearLista (&(app->listaNotificaciones));


    return OK;
}

void setup (s_aplicacion *app, s_recursosGraficos *recursosGraficos)
{
    printf ("SETUP DE RECURSOS.\n");


    ///SETUP APLICACION
    sfRenderWindow_setFramerateLimit (app->renderizado, 60);
    app->aplicacionEjecutandose = CONTINUAR_APLICACION;


    ///SETUP RECURSOS GRAFICOS
    //Interfaz de amigos
    setupAmigos (&(recursosGraficos->recursosGraficosAmigos), app->mensajes.fuentes);

    //Interfaz de salas
    setupSalas (app, &(recursosGraficos->recursosGraficosSalas));

    //Interfaz de configuraciones
    setupConfig (app, &(recursosGraficos->recursosGraficosConfig));


    ///SETUP LISTA DE MENSAJES
    mapListaCircularConComplemento (&(app->mensajes.listaMensajes), app->mensajes.fuentes.fuente1, setupListaMensajes);
    app->mensajes.siguienteMensaje = app->mensajes.listaMensajes;
}

void liberar (s_aplicacion *app, s_recursosGraficos *recursosGraficos)
{
    ///LIBERAR LISTA DE NOTIFICACIONES
    vaciarListaConAccion (&(app->listaNotificaciones), liberarMensaje);


    ///LIBERAR LISTA DE MENSAJES
    vaciarListaCircularConAccion (&(app->mensajes.listaMensajes), liberarMensaje);


    ///LIBERAR FUENTES
    liberarFuentes (&(app->mensajes.fuentes));


    ///LIBERAR RECURSOS GRAFICOS
    //Interfaz de amigos
    liberarAmigos (&(recursosGraficos->recursosGraficosAmigos));

    //Interfaz de salas
    liberarSalas (&(recursosGraficos->recursosGraficosSalas));

    //Interfaz de configuraciones
    liberarConfig (&(recursosGraficos->recursosGraficosConfig));


    ///LIBERAR SOCKET
    closesocket (app->sock);
    WSACleanup ();


    ///LIBERAR APLICACION
    sfRenderWindow_destroy (app->renderizado);
}


///FUNCIONES DE INICIO


void inicioMenuAplicacion (s_aplicacion *app, s_recursosGraficos *recursosGraficos)
{
    u_long modoSocket = 1; //Socket modo no bloqueante


    ///SELECCIONAR INTERFAZ
    app->interfaz = INTERFAZ_AMIGOS;


    ///SETUP APLICACION
    maximizadoAutomaticoVentana (app);
    ioctlsocket (app->sock, FIONBIO, &modoSocket);
    sfText_setString (recursosGraficos->recursosGraficosAmigos.texto.nombreUsuario, app->usuario.nombre);
    sfText_setString (recursosGraficos->recursosGraficosSalas.texto.nombreUsuario, app->usuario.nombre);


    ///SETUP RECURSOS GRAFICOS
    tamYPosPantallaAmigos (&(recursosGraficos->recursosGraficosAmigos), app->ventana);
    tamYPosPantallaSalas (app, &(recursosGraficos->recursosGraficosSalas));
    tamYPosPantallaConfig (app, &(recursosGraficos->recursosGraficosConfig));
    mapListaCircularConComplemento (&(app->mensajes.listaMensajes), &(app->ventana.escalaPixeles), tamListaMensajes);
}

int inicioSesionManual (s_aplicacion *app, s_recursosGraficos *recursosGraficos)
{
    ///SELECCIONAR INTERFAZ
    app->interfaz = INTERFAZ_INICIO;


    ///INICIALIZAR RECURSOS GRAFICOS
    //Interfaz de inicio
    if (inicializarInicio (&(recursosGraficos->recursosGraficosInicio)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;

    //Interfaz de registro
    if (inicializarRegistro (&(recursosGraficos->recursosGraficosRegistro)) == ERROR_INICIALIZACION)
        return ERROR_INICIALIZACION;


    ///SETUP RECURSOS GRAFICOS
    setupInicio (&(recursosGraficos->recursosGraficosInicio), app->mensajes.fuentes);
    setupRegistro (&(recursosGraficos->recursosGraficosRegistro), app->mensajes.fuentes);


    return OK;
}



















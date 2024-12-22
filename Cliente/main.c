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
    setup (&app, &socket, &recursosGraficosInicio, &recursosGraficosMensajes);

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
        default:
            break;
        }
    }

    liberarMensajes (&app, &socket, &recursosGraficosMensajes);
    system ("pause");

    return OK;
}

void inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///INICIALIZAR APLICACION
    app->estado = CONTINUAR_APLICACION;

    app->renderizado = sfRenderWindow_create ((sfVideoMode){1920, 1080}, "App", sfDefaultStyle, NULL);
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


    ///INICIALIZAR recursosGraficos
    recursosGraficosMensajes->texto.fuente = sfFont_createFromFile ("fuente.ttf");
    if (!recursosGraficosMensajes->texto.fuente)
    {
        perror ("ERROR - Inicializar fuente.\n");
        app->estado = CERRAR_APLICACION;
    }
    recursosGraficosMensajes->texto.texto = sfText_create ();
    if (!recursosGraficosMensajes->texto.texto)
    {
        perror ("ERROR - Inicializar texto.\n");
        app->estado = CERRAR_APLICACION;
    }
    recursosGraficosMensajes->elementos.recIzquierda = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.recIzquierda)
    {
        perror ("ERROR - Inicializar rectangulo de la izquierda.\n");
        app->estado = CERRAR_APLICACION;
    }
    recursosGraficosMensajes->elementos.barraSeparacionUsuarios = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionUsuarios)
    {
        perror ("ERROR - Inicializar barra de separacion de usuarios activos.\n");
        app->estado = CERRAR_APLICACION;
    }
    recursosGraficosMensajes->elementos.barraSeparacionNombre = sfRectangleShape_create ();
    if (!recursosGraficosMensajes->elementos.barraSeparacionNombre)
    {
        perror ("ERROR - Inicializar barra de separacion de nombre de usuarios.\n");
        app->estado = CERRAR_APLICACION;
    }
    recursosGraficosMensajes->elementos.textoNombreUsuario = sfText_create ();
    if (!recursosGraficosMensajes->elementos.textoNombreUsuario)
    {
        perror ("ERROR - Inicializar texto nombre de usuario.\n");
        app->estado = CERRAR_APLICACION;
    }
    recursosGraficosMensajes->elementos.textoAuxUsuariosActivos = sfText_create ();
    if (!recursosGraficosMensajes->elementos.textoAuxUsuariosActivos)
    {
        perror ("ERROR - Inicializar texto auxiliar usuarios activos.\n");
        app->estado = CERRAR_APLICACION;
    }
}

void setup (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes)
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
        app->estado = CERRAR_APLICACION;
    }
    else
        printf ("Conectado al servidor.\n");


    ///SETUP recursosGraficos
    ///TEXTO
    sfText_setFont (recursosGraficosMensajes->texto.texto, recursosGraficosMensajes->texto.fuente);
    sfText_setPosition (recursosGraficosMensajes->texto.texto, (sfVector2f){0, 0});
    sfText_setCharacterSize (recursosGraficosMensajes->texto.texto, 24);
    sfText_setColor (recursosGraficosMensajes->texto.texto, sfColor_fromRGB (255, 255, 255));

    ///ELEMENTOS
    //rectangulo de la izquierda
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.recIzquierda, sfColor_fromRGB (232, 217, 205));
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){300, 1080});
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.recIzquierda, (sfVector2f){0, 0});

    //barra separacion usuarios activos
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, sfColor_fromRGB (82, 61, 53));
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){250, 3});
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionUsuarios, (sfVector2f){24, 120});

    //barra separacion nombre de usuario
    sfRectangleShape_setFillColor (recursosGraficosMensajes->elementos.barraSeparacionNombre, sfColor_fromRGB (82, 61, 53));
    sfRectangleShape_setSize (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){250, 3});
    sfRectangleShape_setPosition (recursosGraficosMensajes->elementos.barraSeparacionNombre, (sfVector2f){24, 960});

    //texto nombre de usuario
    sfText_setFont (recursosGraficosMensajes->elementos.textoNombreUsuario, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->elementos.textoNombreUsuario, "mi usuario");
    sfText_setPosition (recursosGraficosMensajes->elementos.textoNombreUsuario, (sfVector2f){60, 1000});
    sfText_setColor (recursosGraficosMensajes->elementos.textoNombreUsuario, sfColor_fromRGB (34, 48, 48));
    sfText_setCharacterSize (recursosGraficosMensajes->elementos.textoNombreUsuario, 22);

    //texto auxiliar usuarios activos
    sfText_setFont (recursosGraficosMensajes->elementos.textoAuxUsuariosActivos, recursosGraficosMensajes->texto.fuente);
    sfText_setString (recursosGraficosMensajes->elementos.textoAuxUsuariosActivos, "Usuarios activos");
    sfText_setPosition (recursosGraficosMensajes->elementos.textoAuxUsuariosActivos, (sfVector2f){60, 50});
    sfText_setColor (recursosGraficosMensajes->elementos.textoAuxUsuariosActivos, sfColor_fromRGB (34, 48, 48));
    sfText_setCharacterSize (recursosGraficosMensajes->elementos.textoAuxUsuariosActivos, 28);
}


























#include "interfazMensajes.h"

void inicializarMensajes ()
{

}

void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfEvent evento;
    char buffer [MAX_BUFFER];

    sfRenderWindow_pollEvent (app->renderizado, &evento);

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
        sfText_setString (recursosGraficosMensajes->texto.texto, buffer);
    }
}

void renderizarMensajes (const s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    sfRenderWindow_clear (app->renderizado, sfColor_fromRGB (239, 239, 233));

    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->texto.texto, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.recIzquierda, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionUsuarios, NULL);
    sfRenderWindow_drawRectangleShape (app->renderizado, recursosGraficosMensajes->elementos.barraSeparacionNombre, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->elementos.textoAuxUsuariosActivos, NULL);
    sfRenderWindow_drawText (app->renderizado, recursosGraficosMensajes->elementos.textoNombreUsuario, NULL);

    sfRenderWindow_display (app->renderizado);
}

void liberarMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes)
{
    ///LIBERAR APLICACION
    sfRenderWindow_destroy (app->renderizado);


    ///LIBERAR SOCKET
    closesocket (sock->sock);
    WSACleanup ();


    ///LIBERAR recursosGraficos
    sfFont_destroy (recursosGraficosMensajes->texto.fuente);
    sfText_destroy (recursosGraficosMensajes->texto.texto);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.recIzquierda);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionUsuarios);
    sfRectangleShape_destroy (recursosGraficosMensajes->elementos.barraSeparacionNombre);
    sfText_destroy (recursosGraficosMensajes->elementos.textoNombreUsuario);
    sfText_destroy (recursosGraficosMensajes->elementos.textoAuxUsuariosActivos);
}

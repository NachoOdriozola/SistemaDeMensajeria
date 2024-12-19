#include "main.h"

int main()
{
    s_estadoAplicacion app;
    s_socket socket;
    s_usuario usuario;
    s_recursosGraficosMensajes recursosGraficosMensajes;
    int interfaz;

    inicializar (&app, &recursosGraficos, &socket);
    setup (&app, &recursosGraficos, &socket);

    interfaz = INTERFAZ_INICIO;
    while (app.aplicacionEjecutandose)
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
            accionMensajes (&app, &recursosGraficos, &socket);
            actualizarMensajes (&recursosGraficos, &socket);
            renderizarMensajes (&app, &recursosGraficos);
            break;
        default:
            break;
        }
        Sleep (1);
    }

    liberarMensajes (&app, &recursosGraficos, &socket);
    system ("pause");

    return OK;
}




























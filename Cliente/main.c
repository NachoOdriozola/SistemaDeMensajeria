#include "main.h"

int main()
{
    s_estadoAplicacion app;
    s_recursos recursos;
    s_socket socket;

    inicializar (&app, &recursos, &socket);
    setup (&app, &recursos, &socket);
    while (app.aplicacionEjecutandose)
    {
        accion (&app, &recursos, &socket);
        actualizar (&recursos, &socket);
        renderizar (&app, &recursos);
    }
    liberar (&app, &recursos, &socket);
    system ("pause");

    return OK;
}




























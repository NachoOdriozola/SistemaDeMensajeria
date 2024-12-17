#include "main.h"

int main ()
{
    s_servidor servidor;
    s_lista listaClientes;
    char ingresoTecla = '\0';
    char buffer [MAX_BUFFER];

    inicializar (&servidor);
    crearLista (&listaClientes);
    setup (&servidor);

    if (servidor.servidorEjecutandose == CERRAR_SERVIDOR)
        return ERROR_INICIALIZACION_SERVIDOR;
    printf ("SERVIDOR INICIADO.\n");
    printf ("Presione '%c' para apagar servidor.\n", TECLA_CERRAR_SERVIDOR);

    while ((ingresoTecla != TECLA_CERRAR_SERVIDOR) && (servidor.servidorEjecutandose == CONTINUAR_SERVIDOR))
    {
        aceptarCliente (&servidor, &listaClientes);
        if (recibirMensajes (&listaClientes, buffer))
        {
            enviarMensajes (&listaClientes, buffer);
            *buffer = '\0';
        }

        if (kbhit ())
        {
            ingresoTecla = getch ();
            ingresoTecla = toupper (ingresoTecla);
            if (ingresoTecla != TECLA_CERRAR_SERVIDOR)
                    printf ("Tecla incorrecta.\nPresione '%c' para apagar servidor.\n", TECLA_CERRAR_SERVIDOR);
        }

        Sleep (10);
    }

    liberar (&servidor, &listaClientes);

    system ("pause");

    return OK;
}















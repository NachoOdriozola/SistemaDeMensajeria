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

    if (servidor.estado == APAGAR_SERVIDOR)
        return ERROR_INICIALIZACION_SERVIDOR;
    printf ("SERVIDOR INICIADO.\n");
    printf ("Presione '%c' para apagar servidor.\n", TECLA_APAGAR_SERVIDOR);

    while ((ingresoTecla != TECLA_APAGAR_SERVIDOR) && (servidor.estado == CONTINUAR_SERVIDOR))
    {
        aceptarCliente (&servidor, &listaClientes);
        if (recibirMensajes (&listaClientes, buffer))
            enviarMensajes (&listaClientes, buffer);

        if (kbhit ())
        {
<<<<<<< HEAD
            buffer [bytesRecibidos - 1] = '\0';
            send (cliente2, buffer, strlen (buffer), 0);
        }
        bytesRecibidos = recv (cliente2, buffer, sizeof (buffer), 0);
        if (bytesRecibidos > 0)
        {
            buffer [bytesRecibidos - 1] = '\0';
            send (cliente1, buffer, strlen (buffer), 0);
        }
        Sleep (100);
=======
            ingresoTecla = getch ();
            ingresoTecla = toupper (ingresoTecla);
            if (ingresoTecla != TECLA_APAGAR_SERVIDOR)
                    printf ("Tecla incorrecta.\nPresione '%c' para apagar servidor.\n", TECLA_APAGAR_SERVIDOR);
        }
        Sleep (10);
>>>>>>> servidor
    }

    liberar (&servidor, &listaClientes);

    system ("pause");

    return OK;
}















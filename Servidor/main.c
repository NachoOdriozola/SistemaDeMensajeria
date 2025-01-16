#include "main.h"

int main ()
{
    s_servidor servidor;
    s_lista listaClientes;

    char ingresoTeclaApagar = '\0';
    char buffer [MAX_BUFFER];

    crearLista (&listaClientes);
    if (inicializar (&servidor) == ERROR_INICIALIZACION_SERVIDOR)
        return ERROR_INICIALIZACION_SERVIDOR;
    if (setup (&servidor) == ERROR_INICIALIZACION_SERVIDOR)
        return ERROR_INICIALIZACION_SERVIDOR;

    printf ("SERVIDOR INICIADO CORRECTAMENTE.\n\n");
    printf ("Presione '%c' para apagar servidor.\n", TECLA_APAGAR_SERVIDOR);

    while (ingresoTeclaApagar != TECLA_APAGAR_SERVIDOR)
    {
        aceptarCliente (&servidor, &listaClientes);
        if (recibirMensajes (&listaClientes, buffer))
            enviarMensajes (&listaClientes, buffer);

        if (kbhit ())
        {
            ingresoTeclaApagar = getch ();
            ingresoTeclaApagar = toupper (ingresoTeclaApagar);
            if (ingresoTeclaApagar != TECLA_APAGAR_SERVIDOR)
                    printf ("Tecla incorrecta.\nPresione '%c' para apagar servidor.\n", TECLA_APAGAR_SERVIDOR);
        }
        Sleep (10);
    }

    liberar (&servidor, &listaClientes);

    system ("pause");

    return OK;
}















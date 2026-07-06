#include "../include/main.h"


int main ()
{
    t_contextoServidor contextoServidor;

    if (inicializarServidor (&contextoServidor) == ERROR_INICIALIZACION)
    {
        liberarServidor (&contextoServidor);
        return ERROR_INICIALIZACION;
    }

    if (configurarServidor (&contextoServidor) == ERROR_CONFIGURACION)
    {
        liberarServidor (&contextoServidor);
        return ERROR_CONFIGURACION;
    }

    while (servidorActivo)
    {
        aceptarNuevosClientes (contextoServidor.sock, &(contextoServidor.clientesNoAutenticados));
        recibirSolicitudes (&contextoServidor);
        procesarSolicitudes (&contextoServidor);
        Sleep (5); // Pausa para evitar ciclos innecesarios.
    }

    liberarServidor (&contextoServidor);
    return EXITO;
}

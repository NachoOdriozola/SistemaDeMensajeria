#include "../include/main.h"


int main ()
{
    t_contextoServidor contextoServidor;
    t_nodoListaDoble *clienteAProcesar;
    char solicitud [MAX_BUFFER_SOLICITUD];

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
        if (recibiSolicitud (&(contextoServidor.clientes), &(contextoServidor.clientesNoAutenticados), &clienteAProcesar, solicitud))
            procesarSolicitud (&contextoServidor, clienteAProcesar, solicitud);
        Sleep (5); // Pausa para evitar ciclos innecesarios.
    }

    liberarServidor (&contextoServidor);
    return EXITO;
}




































#include "main.h"


int main ()
{
    ContextoServidor contextoServidor;

    if (servidor_inicializar (&contextoServidor) == ERROR_INICIALIZACION)
    {
        servidor_liberar (&contextoServidor);
        return ERROR_INICIALIZACION;
    }

    if (servidor_configurar (&contextoServidor) == ERROR_CONFIGURACION)
    {
        servidor_liberar (&contextoServidor);
        return ERROR_CONFIGURACION;
    }

    while (servidorActivo)
    {
        aceptar_nuevos_clientes (contextoServidor.sock, &(contextoServidor.clientesNoAutenticados));
        recibir_solicitudes (&contextoServidor);
        procesar_solicitudes (&contextoServidor);
        Sleep (5); // Pausa para evitar ciclos innecesarios.
    }

    servidor_liberar (&contextoServidor);
    return EXITO;
}

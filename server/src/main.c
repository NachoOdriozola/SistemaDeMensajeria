#include "servidor.h"

int main ()
{
    Servidor servidor;

    if (servidor_inicializar (&servidor) != EXITO)
        return ERROR_INICIALIZACION;
    servidor_ejecutar (&servidor);
    servidor_liberar (&servidor);

    return EXITO;
}

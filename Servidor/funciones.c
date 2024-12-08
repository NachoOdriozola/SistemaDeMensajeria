#include "funciones.h"

BOOL WINAPI manejadorDeConsola (DWORD senial)
{
    if (senial != CTRL_CLOSE_EVENT)
        return FALSE;

    //liberar recursos aca
    return TRUE;
}

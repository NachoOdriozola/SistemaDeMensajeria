#include "plataforma/signals.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static volatile LONG apagado = 0;

static BOOL WINAPI handler_consola (DWORD tipoEvento);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno signals_instalar_handler ()
{
    if (SetConsoleCtrlHandler (handler_consola, TRUE) == 0)
    {
        logs_escribir (LOG_ERROR, "signals", "Instalacion de handler de consola.");
        return ERROR_INICIALIZACION;
    }
    return EXITO;
}

bool signals_apagado_solicitado ()
{
    return apagado != 0;
}

void signals_sleep (unsigned ms)
{
    Sleep (ms);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static BOOL WINAPI handler_consola (DWORD tipoEvento)
{
    switch (tipoEvento)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        InterlockedExchange (&apagado, 1);
        return TRUE;

    default:
        return FALSE;
    }
}



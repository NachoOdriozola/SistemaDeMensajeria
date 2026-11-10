#include "logs.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


FILE *archLogs = NULL;

static void convertir_nivel_log (NivelLog nivelLog, char *returnNivelLog, size_t tamBuffer);
static void obtener_tiempo_actual (char *returnTiempo, size_t tamBuffer);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno logs_inicializar (const char *rutaArchivo)
{
    if (rutaArchivo == NULL)
        return ERROR_OPERACION_INVALIDA;

    archLogs = fopen (rutaArchivo, "wt");
    if (!archLogs)
        return ERROR_INICIALIZACION;
    return EXITO;
}

void logs_escribir (NivelLog nivelLog, const char *modulo, const char *formato, ...)
{
    char log [MAX_LOG];
    char fechaYHora [20];
    char nivel [8];
    va_list args;
    int desplazamiento;

    if (!archLogs)
        return;

    convertir_nivel_log (nivelLog, nivel, sizeof (nivel));
    obtener_tiempo_actual (fechaYHora, sizeof (fechaYHora));

    desplazamiento = sprintf (log, "%s [%s] [%s] ", fechaYHora, nivel , modulo);
    if ((desplazamiento < 0) || (desplazamiento >= MAX_LOG))
        return;

    va_start (args, formato);
    vsnprintf (log + desplazamiento, sizeof (log) - desplazamiento, formato, args);
    va_end (args);

    puts (log);
    fprintf (archLogs, "%s\n", log);
    fflush (archLogs);
}

void logs_liberar ()
{
    fclose (archLogs);
    archLogs = NULL;
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void convertir_nivel_log (NivelLog nivelLog, char *returnNivelLog, size_t tamBuffer)
{
    switch (nivelLog)
    {
        case LOG_ERROR:
            strncpy (returnNivelLog, "ERROR", tamBuffer);
            break;

        case LOG_AVISO:
            strncpy (returnNivelLog, "AVISO", tamBuffer);
            break;

        case LOG_INFO:
            strncpy (returnNivelLog, "INFO", tamBuffer);
            break;

        default:
            strncpy (returnNivelLog, "ERR_LOG", tamBuffer);
            break;
    }
}

static void obtener_tiempo_actual (char *returnTiempo, size_t tamBuffer)
{
    time_t tiempoActual;
    struct tm *infoTiempo;

    tiempoActual = time (NULL);
    if (tiempoActual == (time_t)-1)
        return;

    infoTiempo = localtime (&tiempoActual);
    if (infoTiempo == NULL)
        return;

    strftime (returnTiempo, tamBuffer, "%d/%m/%Y %H:%M:%S", infoTiempo);
}

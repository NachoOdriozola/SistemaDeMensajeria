#include "../../../include/interfacesGraficas/interfazContactos/interfazContactos_actualizaciones.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void procesarRecepcionMensaje (t_interfazContactos *interfazContactos, const char *respuesta);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


void _interfazContactos_procesarRespuesta (t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_tipoRespuesta tipoRespuesta = *respuesta;
    const char *respuesaSinTipoRespuesta = &(respuesta[2]);

    switch (tipoRespuesta)
        {
        case RESPUESTA_RECEPCION_MENSAJE:
            procesarRecepcionMensaje (interfazContactos, respuesaSinTipoRespuesta);
            break;

        default:
            break;
        }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void extraerDatosRecepcionMensaje (const char *respuesta, t_datosRecepcionMensaje *datosRecepcionMensaje)
{
    sscanf (respuesta, "%d|%[^\n]", &(datosRecepcionMensaje->idUsuarioEmisor), datosRecepcionMensaje->mensaje);
}

static bool elUsuarioDelChatSeleccionadoEsElEmisor (int idUsuarioEmisor, int idUsuarioDelChatSeleccionado)
{
    return (idUsuarioEmisor == idUsuarioDelChatSeleccionado);
}

static void procesarMensaje (t_interfazContactos *interfazContactos, t_datosRecepcionMensaje *datosRecepcionMensaje)
{
    if (elUsuarioDelChatSeleccionadoEsElEmisor (datosRecepcionMensaje->idUsuarioEmisor, interfazContactos->logica.idUsuarioDelChatSeleccionado))
        insertarMensaje (&(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes), datosRecepcionMensaje->mensaje, MENSAJE_REMOTO);
}

/*
 * Recibe los datos del mensaje de la siguiente manera:
 * id del emisor|texto del mensaje
*/
static void procesarRecepcionMensaje (t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRecepcionMensaje datosRecepcionMensaje;

    extraerDatosRecepcionMensaje (respuesta, &datosRecepcionMensaje);
    procesarMensaje (interfazContactos, &datosRecepcionMensaje);
}


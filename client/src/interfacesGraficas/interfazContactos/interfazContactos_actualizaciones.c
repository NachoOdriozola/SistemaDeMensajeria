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
    char headerTipoRespuesta;

    headerTipoRespuesta = *respuesta;
    switch (headerTipoRespuesta)
        {
        case RESPUESTA_RECEPCION_MENSAJE:
            procesarRecepcionMensaje (interfazContactos, respuesta);
            break;

        default:
            break;
        }
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static void extraerDatosRecepcionMensaje (const char *respuesta, t_datosRespuestaRecepcionMensaje *returnDatosRespuestaRecepcionMensaje)
{
    memcpy (returnDatosRespuestaRecepcionMensaje, respuesta, sizeof (t_datosRespuestaRecepcionMensaje));
}

static bool elUsuarioDelChatSeleccionadoEsElEmisor (int idUsuarioEmisor, int idUsuarioDelChatSeleccionado)
{
    return (idUsuarioEmisor == idUsuarioDelChatSeleccionado);
}

static void procesarMensaje (t_interfazContactos *interfazContactos, t_datosRespuestaRecepcionMensaje *datosRespuestaRecepcionMensaje)
{
    if (elUsuarioDelChatSeleccionadoEsElEmisor (datosRespuestaRecepcionMensaje->idEmisor, interfazContactos->logica.idUsuarioDelChatSeleccionado))
        recursosComunesContactosSalas_insertarMensajeAListaMensajes (&(interfazContactos->recursosComunesContactosSalas->logica.contextoMensajes), datosRespuestaRecepcionMensaje->texto, MENSAJE_REMOTO, &(interfazContactos->recursosComunesContactosSalas->fuentes));
}

/*
 * Recibe los datos del mensaje de la siguiente manera:
 * id del emisor|texto del mensaje
*/
static void procesarRecepcionMensaje (t_interfazContactos *interfazContactos, const char *respuesta)
{
    t_datosRespuestaRecepcionMensaje datosRespuestaRecepcionMensaje;

    extraerDatosRecepcionMensaje (respuesta, &datosRespuestaRecepcionMensaje);
    printf ("\nRespuesta recibida: %c|%d|%s\n", datosRespuestaRecepcionMensaje.headerTipoRespuesta, datosRespuestaRecepcionMensaje.idEmisor, datosRespuestaRecepcionMensaje.texto);
    procesarMensaje (interfazContactos, &datosRespuestaRecepcionMensaje);
}


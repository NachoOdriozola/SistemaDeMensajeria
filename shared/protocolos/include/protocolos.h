/**
 * \file   protocolos.h
 * \brief  Contiene el puerto de conexion, tamanios de buffers de comunicacion y codigos de comunicacion.
 */


#ifndef PROTOCOLO_H_INCLUDED
#define PROTOCOLO_H_INCLUDED


/* ============================================================================================================================================
   TAMANIOS DE BUFFERS DE COMUNICACION
   ============================================================================================================================================ */


/**
 * \def MAX_BUFFER_SOLICITUD
 * \brief Tamanio maximo del buffer para comunicar solicitudes entre el cliente y el servidor. Incluye el '0'.
 */
#define MAX_BUFFER_SOLICITUD 781

/**
 * \def MAX_BUFFER_RESPUESTA
 * \brief Tamanio maximo del buffer para comunicar respuestas entre el cliente y el servidor. Incluye el '0'.
 */
#define MAX_BUFFER_RESPUESTA 781


/* ============================================================================================================================================
   CONEXION
   ============================================================================================================================================ */


/**
 * \def PUERTO
 * \brief Puerto en el que se comunicaran los sockets.
 */
#define PUERTO 8080


/* ============================================================================================================================================
   ESTRUCTURAS DE COMUNICACION
   ============================================================================================================================================ */


/**
 * \enum t_tipoSolicitud
 * \brief Indice del tipo de solicitud, enviado por el cliente hacia el servidor.
 */
typedef enum
{
    SOLICITUD_AUTENTICACION = 'a',
    SOLICITUD_REGISTRO = 'b',
    SOLICITUD_ENVIO_MENSAJE = 'c',
    SOLICITUD_SELECCION_CHAT = 'd',
} t_tipoSolicitud;

/**
 * \enum t_estadoSolicitud
 * \brief Indice sobre el estado de la solicitud, enviado por el servidor hacia el cliente.
 */
typedef enum
{
    SOLICITUD_EXITO = 'a',
    SOLICITUD_ERROR_CREDENCIALES_INVALIDAS = 'b',
    SOLICITUD_ERROR_OPERACION_INVALIDA = 'c'
} t_estadoSolicitud;

/**
 * \enum t_tipoRespuesta
 * \brief Indice del tipo de respuesta, enviado por el servidor hacia el cliente.
 */
typedef enum
{
    RESPUESTA_RECEPCION_MENSAJE = 'A',
} t_tipoRespuesta;


#endif // PROTOCOLO_H_INCLUDED

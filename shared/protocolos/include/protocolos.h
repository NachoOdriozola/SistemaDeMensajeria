/**
 * \file   protocolos.h
 * \brief  C
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
 * \union t_buffersComunicacion
 * \brief  Contiene los buffers necesarios para establecer la comunicacion entre el cliente y el servidor.
 */
typedef union
{
    char solicitud [MAX_BUFFER_SOLICITUD];              /**< Buffer que almacena una solicitud un clientes. */
    char respuesta [MAX_BUFFER_RESPUESTA];              /**< Buffer que almacena una respuestas del servidor para enviar al cliente. */
} t_buffersComunicacion;

/**
 * \enum t_tipoSolicitud
 * \brief Indice del tipo de solicitud enviado por el usuario hacia el servidor.
 */
typedef enum
{
    SOLICITUD_AUTENTICACION = 'a',
    SOLICITUD_REGISTRO = 'b',
    SOLICITUD_MENSAJE = 'c',
    SOLICITUD_SELECCIONAR_CONTACTO = 'd',
} t_tipoSolicitud;

/**
 * \enum t_tipoRespuesta
 * \brief Indice del tipo de respuesta enviado por el servidor hacia el usuario.
 */
typedef enum
{
    RESPUESTA_MENSAJE = 'A',
} t_tipoRespuesta;

/**
 * \enum t_estadoRespuesta
 * \brief Indice de respuesta enviado por el servidor hacia el usuario sobre estado de la solicitud.
 */
typedef enum
{
    RESPUESTA_EXITO = 'a',

    RESPUESTA_ERROR_SERVIDOR = 'b',
    RESPUESTA_ERROR_CREDENCIALES_INVALIDAS = 'c',
    RESPUESTA_ERROR_USUARIO_NO_ENCONTRADO = 'd',
    RESPUESTA_ERROR_OPERACION_INVALIDA = 'e'
} t_estadoRespuesta;



#endif // PROTOCOLO_H_INCLUDED

















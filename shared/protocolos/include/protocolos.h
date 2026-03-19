/**
 * \file   protocolos.h
 * \brief  Contiene los protocolos de comunicacion entre el cliente y el servidor.
 */



#ifndef PROTOCOLO_H_INCLUDED
#define PROTOCOLO_H_INCLUDED



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
    SOLICITUD_AGENDAR_CONTACTO = 'e'
} t_tipoSolicitud;

/**
 * \enum t_tipoRespuesta
 * \brief Indice del tipo de respuesta enviado por el servidor hacia el usuario.
 */
typedef enum
{
    RESPUESTA_MENSAJE = 'A',
    RESPUESTA_AGENDAR_CONTACTO = 'B'
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

















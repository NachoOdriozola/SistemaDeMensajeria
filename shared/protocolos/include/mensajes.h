/**
 * \file   mensajes.h
 * \brief  
 */


#ifndef MENSAJES_H_INCLUDED
#define MENSAJES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "constantes.h"


/* ============================================================================================================================================
   ESTRUCTURAS DE ENVIO DE SOLICITUDES: cliente -> servidor
   ============================================================================================================================================ */


/**
 * \enum TipoSolicitud
 * \brief Indice del tipo de solicitud, enviado por el cliente hacia el servidor.
 */
typedef enum
{
    SOLICITUD_AUTENTICACION = 'a',
    SOLICITUD_REGISTRO = 'b',
    SOLICITUD_ENVIO_MENSAJE = 'c',
    SOLICITUD_SELECCION_CHAT = 'd',
} TipoSolicitud;


/**
 * \struct SolicitudAutenticacion
 * \brief Datos enviados por el cliente para realizar la solicitud.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    char contrasenia [MAX_CONTRASENIA];
} SolicitudAutenticacion;

/**
 * \struct SolicitudRegistro
 * \brief Datos enviados por el cliente para realizar la solicitud.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    char contrasenia [MAX_CONTRASENIA];
    char correoElectronico [MAX_CORREO_ELECTRONICO];
} SolicitudRegistro;

/**
 * \struct SolicitudEnvioMensaje
 * \brief Datos enviados por el cliente para realizar la solicitud.
 */
typedef struct
{
    int idEmisor, idReceptor;
    char texto [MAX_TEXTO];
} SolicitudEnvioMensaje;

/**
 * \struct SolicitudSeleccionChat
 * \brief Datos enviados por el cliente para realizar la solicitud.
 */
typedef struct
{
    char nombreUsuarioChatSeleccionado [MAX_NOMBRE_USUARIO];
} SolicitudSeleccionChat;


typedef union
{
    SolicitudAutenticacion solicitudAutenticacion;
    SolicitudRegistro solicitudRegistro;
    SolicitudEnvioMensaje solicitudEnvioMensaje;
    SolicitudSeleccionChat solicitudSeleccionChat;
} PayloadSolicitud;


/* ============================================================================================================================================
   ESTRUCTURAS DE RESPUESTAS DE SOLICITUDES: servidor -> cliente
   ============================================================================================================================================ */


/**
 * \enum TipoRespuesta
 * \brief Indice del tipo de respuesta, enviado por el servidor hacia el cliente.
 */
typedef enum
{
    RESPUESTA_AUTENTICACION = 'A',
    RESPUESTA_REGISTRO = 'B',
    RESPUESTA_ENVIO_MENSAJE = 'C',
    RESPUESTA_SELECCION_CHAT = 'D',
    RESPUESTA_RECEPCION_MENSAJE = 'E',
} TipoRespuesta;


/**
 * \enum EstadoSolicitud
 * \brief Indice sobre el EstadoSolicitud de la solicitud, enviado por el servidor hacia el cliente.
 */
typedef enum
{
    RESPUESTA_EXITO = 'a',
    RESPUESTA_ERROR_SERVIDOR = 'b',
    RESPUESTA_ERROR_CONEXION = 'c',
    RESPUESTA_ERROR_CREDENCIALES_INVALIDAS = 'd',
    RESPUESTA_ERROR_OPERACION_INVALIDA = 'e',
    RESPUESTA_ERROR_NOMBRE_YA_EXISTENTE = 'f',
    RESPUESTA_ERROR_CORREO_YA_EXISTENTE = 'g'
} EstadoRespuesta;


/**
 * \struct RespuestaAutenticacion
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    char estado;
    int idUsuario;
} RespuestaAutenticacion;

/**
 * \struct RespuestaRegistro
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    char estado;
    int idUsuario;
} RespuestaRegistro;

/**
 * \struct RespuestaEnvioMensaje
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    char estado;
} RespuestaEnvioMensaje;

/**
 * \struct RespuestaRegistro
 * \brief Datos de respuesta a enviar al cliente.
 */
typedef struct
{
    int idEmisor;
    char texto [MAX_TEXTO];
} RespuestaRecepcionMensaje;

/**
 * \struct RespuestaSeleccionChat
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    char estado;
    int idUsuarioChatSeleccionado;
} RespuestaSeleccionChat;


typedef union
{
    RespuestaAutenticacion respuestaAutenticacion;
    RespuestaRegistro respuestaRegistro;
    RespuestaEnvioMensaje respuestaEnvioMensaje;
    RespuestaRecepcionMensaje respuestaRecepcionMensaje;
    RespuestaSeleccionChat respuestaSeleccionChat;
} PayloadRespuesta;


#endif // MENSAJES_H_INCLUDED

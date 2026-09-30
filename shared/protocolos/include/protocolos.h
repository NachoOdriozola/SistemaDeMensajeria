/**
 * \file   protocolos.h
 * \brief  Contiene el puerto de conexion, tamanios de buffers de comunicacion, codigos y estructuras de comunicacion.
 */


#ifndef PROTOCOLOS_H_INCLUDED
#define PROTOCOLOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "constantes.h"


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
#define PUERTO 8070


/* ============================================================================================================================================
   ESTRUCTURAS DE COMUNICACION
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
 * \enum EstadoSolicitud
 * \brief Indice sobre el EstadoSolicitud de la solicitud, enviado por el servidor hacia el cliente.
 */
typedef enum
{
    SOLICITUD_EXITO = 'a',
    SOLICITUD_ERROR_SERVIDOR = 'b',
    SOLICITUD_ERROR_CONEXION = 'c',
    SOLICITUD_ERROR_CREDENCIALES_INVALIDAS = 'd',
    SOLICITUD_ERROR_OPERACION_INVALIDA = 'e',
    SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE = 'f',
    SOLICITUD_ERROR_CORREO_YA_EXISTENTE = 'g'
} EstadoSolicitud;

/**
 * \enum TipoRespuesta
 * \brief Indice del tipo de respuesta, enviado por el servidor hacia el cliente.
 */
typedef enum
{
    RESPUESTA_SOLICITUD_AUTENTICACION = 'A',
    RESPUESTA_SOLICITUD_REGISTRO = 'B',
    RESPUESTA_SOLICITUD_ENVIO_MENSAJE = 'C',
    RESPUESTA_SOLICITUD_SELECCION_CHAT = 'D',
    RESPUESTA_RECEPCION_MENSAJE = 'E',
} TipoRespuesta;


/**
 * \struct Header
 * \brief Header que contiene los datos del paquete a transmitir.
 */
typedef struct
{
    char tipoPaquete;
    short int bytesTransmitidos;
} Header;


/* ============================================================================================================================================
   ESTRUCTURAS DE DATOS DE ENVIO DE SOLICITUDES: cliente -> servidor
   ============================================================================================================================================ */


/**
 * \struct SolicitudAutenticacion
 * \brief Datos enviados por el cliente para realizar la solicitud.
 */
typedef struct
{
    Header header;
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    char contrasenia [MAX_CONTRASENIA];
} SolicitudAutenticacion;

/**
 * \struct SolicitudRegistro
 * \brief Datos enviados por el cliente para realizar la solicitud.
 */
typedef struct
{
    Header header;
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
    Header header;
    int idEmisor, idReceptor;
    char texto [MAX_MENSAJE];
} SolicitudEnvioMensaje;

/**
 * \struct SolicitudSeleccionChat
 * \brief Datos enviados por el cliente para realizar la solicitud.
 */
typedef struct
{
    Header header;
    char nombreUsuarioChatSeleccionado [MAX_NOMBRE_USUARIO];
} SolicitudSeleccionChat;


/* ============================================================================================================================================
   ESTRUCTURAS DE DATOS DE RESPUESTAS DE SOLICITUDES: servidor -> cliente
   ============================================================================================================================================ */


/**
 * \struct RespuestaAutenticacion
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    Header header;
    char estado;
    int idUsuario;
} RespuestaAutenticacion;

/**
 * \struct RespuestaRegistro
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    Header header;
    char estado;
    int idUsuario;
} RespuestaRegistro;

/**
 * \struct RespuestaEnvioMensaje
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    Header header;
    char estado;
} RespuestaEnvioMensaje;

/**
 * \struct RespuestaRegistro
 * \brief Datos de respuesta a enviar al cliente.
 */
typedef struct
{
    Header header;
    int idEmisor;
    char texto [MAX_MENSAJE];
} RespuestaRecepcionMensaje;

/**
 * \struct RespuestaSeleccionChat
 * \brief Datos de respuesta de la solicitud a enviar al cliente.
 */
typedef struct
{
    Header header;
    char estado;
    int idUsuarioChatSeleccionado;
} RespuestaSeleccionChat;


#endif // PROTOCOLOS_H_INCLUDED

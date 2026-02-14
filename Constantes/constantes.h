/**
 * \file   constantes.h
 * \brief  Contiene los valores constantes globales de codigos de retorno, tamanios de buffers, identificadores y estructuras.
 */



#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED



/* ============================
   CODIGOS DE RETORNO
   ============================ */



/**
 * \def EXITO
 * \brief Codigo de retorno para indicar que la funcion se ejecuto correctamente.
 */
#define EXITO 0

/**
 * \def ERROR_INICIALIZACION
 * \brief Codigo de retorno para fallos en la inicializacion.
 */
#define ERROR_INICIALIZACION -100

/**
 * \def ERROR_SIN_MEMORIA
 * \brief Codigo de retorno para fallos en la asignacion de memoria.
 */
#define ERROR_SIN_MEMORIA -101



/* ============================
   TAMANIOS DE BUFFERS
   ============================ */



/**
 * \def MAX_BUFFER_SOLICITUD
 * \brief Tamanio maximo del buffer para comunicar solicitudes entre el cliente y el servidor. Incluye el '0'.
 */
#define MAX_BUFFER_SOLICITUD 2048

/**
 * \def MAX_BUFFER_RESPUESTA
 * \brief Tamanio maximo del buffer para comunicar respuestas entre el cliente y el servidor. Incluye el '0'.
 */
#define MAX_BUFFER_RESPUESTA 2048


/**
 * \def MAX_BUFFER_MENSAJE
 * \brief Longitud maxima para el mensaje escrito por el usuario. Incluye el '0'.
 */
#define MAX_BUFFER_MENSAJE 2001

/**
 * \def MAX_NOMBRE_USUARIO
 * \brief Longitud maxima para el nombre del usuario. Incluye el '0'.
 */
#define MAX_NOMBRE_USUARIO 26

/**
 * \def MAX_CONTRASENIA_USUARIO
 * \brief Longitud maxima para la contrasenia del usuario. Incluye el '0'.
 */
#define MAX_CONTRASENIA_USUARIO 128

/**
 * \def MAX_CORREO_USUARIO
 * \brief Longitud maxima para el correo electronico del usuario. Incluye el '0'.
 */
#define MAX_CORREO_USUARIO 256



/* ============================
   IDENTIFICADORES
   ============================ */



/**
 * \def PUERTO
 * \brief Puerto en el que se comunicaran los sockets.
 */
#define PUERTO 8080



/* ============================
   ESTRUCTURAS
   ============================ */



/**
 * \enum t_tipoSolicitud
 * \brief Indice del tipo de solicitud enviado por el usuario hacia el servidor.
 */
typedef enum
{
    SOLICITUD_AUTENTICACION = '1',
    SOLICITUD_REGISTRO = '2',
    SOLICITUD_MENSAJE = '3',
    SOLICITUD_AGENDAR_CONTACTO = '4'
} t_tipoSolicitud;

/**
 * \enum t_tipoRespuesta
 * \brief Indice del tipo de respuesta enviado por el servidor hacia el usuario.
 */
typedef enum
{
    RESPUESTA_MENSAJE = 'a',
    RESPUESTA_AGENDAR_CONTACTO = 'b'
} t_tipoRespuesta;

/**
 * \enum t_estadoRespuesta
 * \brief Indice de respuesta enviado por el servidor hacia el usuario sobre estado de la solicitud.
 */
typedef enum
{
    RESPUESTA_EXITO = '0',
    RESPUESTA_ERROR_SERVIDOR = '1',
    RESPUESTA_ERROR_CREDENCIALES = '2'
} t_estadoRespuesta;



#endif // CONSTANTES_H_INCLUDED





































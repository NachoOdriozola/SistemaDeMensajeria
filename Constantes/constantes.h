/**
 * \file   constantes.h
 * \brief  Contiene los valores constantes globales de codigos de retorno, tamanios de buffers e identificadores.
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

/**
 * \def ERROR_CONFIGURACION
 * \brief Codigo de retorno para fallos en la configuracion.
 */
#define ERROR_CONFIGURACION -102


/**
 * \def ENCONTRO_CLAVE
 * \brief Codigo de retorno para indicar que se encontro la clave.
 */
#define ENCONTRO_CLAVE 1

/**
 * \def NO_ENCONTRO_CLAVE
 * \brief Codigo de retorno para indicar que no se encontro la clave.
 */
#define NO_ENCONTRO_CLAVE 0



/* ============================
   TAMANIOS DE BUFFERS
   ============================ */



/**
 * \def MAX_BUFFER_SOLICITUD
 * \brief Tamanio maximo del buffer para recibir solicitudes de los clientes.
 */
#define MAX_BUFFER_SOLICITUD 2048

/**
 * \def MAX_BUFFER_RESPUESTA
 * \brief Tamanio maximo del buffer para enviar respuestas a los clientes.
 */
#define MAX_BUFFER_RESPUESTA 2048

#define MAX_BUFFER_MENSAJE 2001


/**
 * \def MAX_NOMBRE_USUARIO
 * \brief Longitud maxima para el nombre del usuario.
 */
#define MAX_NOMBRE_USUARIO 26

/**
 * \def MAX_CONTRASENIA_USUARIO
 * \brief Longitud maxima para la contrasenia del usuario.
 */
#define MAX_CONTRASENIA_USUARIO 128

#define MAX_CORREO_ELECTRONICO_USUARIO 256



/* ============================
   IDENTIFICADORES
   ============================ */



/**
 * \def PUERTO
 * \brief Puerto en el que se comunicaran los sockets.
 */
#define PUERTO 8080


/**
 * \def INDICE_SOLICITUD_AUTENTICACION
 * \brief Identificador de solicitud para autenticacion
 */
#define INDICE_SOLICITUD_AUTENTICACION '1'

/**
 * \def INDICE_SOLICITUD_REGISTRO
 * \brief Identificador de solicitud para registro de usuario.
 */
#define INDICE_SOLICITUD_REGISTRO '2'

/**
 * \def INDICE_SOLICITUD_MENSAJE
 * \brief Identificador de solicitud para envio de mensaje.
 */
#define INDICE_SOLICITUD_MENSAJE '3'

/**
 * \def INDICE_SOLICITUD_AGENDAR_CONTACTO
 * \brief Identificador de solicitud para agendar un nuevo contacto.
 */
#define INDICE_SOLICITUD_AGENDAR_CONTACTO '4'


/**
 * \def INDICE_RESPUESTA_ACEPTADA
 * \brief Indice de respuesta al cliente que la solicitud fue aceptada.
 */
#define INDICE_RESPUESTA_EXITO '0'

/**
 * \def INDICE_RESPUESTA_SOLICITUD_RECHAZADA
 * \brief Indice de respuesta al cliente que la solicitud fue rechazada.
 */
#define INDICE_RESPUESTA_ERROR_SERVIDOR '1'

#define INDICE_RESPUESTA_ERROR_CREDENCIALES '2'

/**
 * \def INDICE_RESPUESTA_MENSAJE
 * \brief Indice de respuesta al cliente que le envias un mensaje.
 */
#define INDICE_RESPUESTA_MENSAJE 'a'

/**
 * \def INDICE_RESPUESTA_SOLICITUD_AMISTAD
 * \brief Indice de respuesta al cliente que le envias una solicitud de amistad.
 */
#define INDICE_RESPUESTA_AGENDAR_CONTACTO 'b'



#endif // CONSTANTES_H_INCLUDED





































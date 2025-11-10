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
 * \def ENCONTRO
 * \brief Codigo de retorno para indicar que se encontro la clave.
 */
#define ENCONTRO 1

/**
 * \def NO_ENCONTRO
 * \brief Codigo de retorno para indicar que no se encontro la clave.
 */
#define NO_ENCONTRO 0



/* ============================
   TAMANIOS DE BUFFERS
   ============================ */



/**
 * \def MAX_BUFFER_SOLICITUD
 * \brief Tamanio maximo del buffer para recibir solicitudes de los clientes.
 */
#define MAX_BUFFER_SOLICITUD 256

/**
 * \def MAX_BUFFER_RESPUESTA
 * \brief Tamanio maximo del buffer para enviar respuestas a los clientes.
 */
#define MAX_BUFFER_RESPUESTA 256


/**
 * \def MAX_NOMBRE_USUARIO
 * \brief Longitud maxima para el nombre del usuario.
 */
#define MAX_NOMBRE_USUARIO 26

/**
 * \def MAX_CONTRASENIA_USUARIO
 * \brief Longitud maxima para la contrasenia del usuario.
 */
#define MAX_CONTRASENIA_USUARIO 46



/* ============================
   IDENTIFICADORES
   ============================ */



/**
 * \def PUERTO
 * \brief Puerto en el que se comunicaran los sockets.
 */
#define PUERTO 8080


/**
 * \def INDICE_AUTENTICACION
 * \brief Identificador de solicitud para autenticacion
 */
#define INDICE_AUTENTICACION '1'

/**
 * \def INDICE_REGISTRO
 * \brief Identificador de solicitud para registro de usuario.
 */
#define INDICE_REGISTRO '2'

/**
 * \def INDICE_MENSAJE
 * \brief Identificador de solicitud para envio de mensaje.
 */
#define INDICE_MENSAJE '3'

/**
 * \def INDICE_AGENDARCONTACTO
 * \brief Identificador de solicitud para agendar un nuevo contacto.
 */
#define INDICE_AGENDARCONTACTO '4'


/**
 * \def INDICE_RESPUESTA_SOLICITUD_ACEPTADA
 * \brief Indice de respuesta al cliente que la solicitud fue aceptada.
 */
#define INDICE_RESPUESTA_SOLICITUD_ACEPTADA '1'

/**
 * \def INDICE_RESPUESTA_SOLICITUD_RECHAZADA
 * \brief Indice de respuesta al cliente que la solicitud fue rechazada.
 */
#define INDICE_RESPUESTA_SOLICITUD_RECHAZADA '0'

/**
 * \def INDICE_RESPUESTA_MENSAJE
 * \brief Indice de respuesta al cliente que le envias un mensaje.
 */
#define INDICE_RESPUESTA_MENSAJE 'a'

/**
 * \def INDICE_RESPUESTA_SOLICITUD_AMISTAD
 * \brief Indice de respuesta al cliente que le envias una solicitud de amistad.
 */
#define INDICE_RESPUESTA_SOLICITUD_AMISTAD 'b'



#endif // CONSTANTES_H_INCLUDED





































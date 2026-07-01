/**
 * \file   constantes.h
 * \brief  Contiene valores constantes globales de codigos de retorno, tamanios de datos e identificadores.
 */


#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED


/* ============================================================================================================================================
   CODIGOS DE RETORNO
   ============================================================================================================================================ */


/**
 * \struct t_codigoRetorno
 * \brief  Codigos de retorno segun el resultado de la ejecucion de la funcion.
 */
typedef  enum
{
   EXITO,
   ERROR_INICIALIZACION,
   ERROR_CONFIGURACION,
   ERROR_SIN_MEMORIA,
   ERROR_OPERACION
} t_codigoRetorno;


/* ============================================================================================================================================
   TAMANIOS DE DATOS
   ============================================================================================================================================ */


/**
 * \def MAX_MENSAJE
 * \brief Longitud maxima para el mensaje escrito por el usuario. Incluye el '0'.
 */
#define MAX_MENSAJE 751

/**
 * \def MAX_NOMBRE_USUARIO
 * \brief Longitud maxima para el nombre del usuario. Incluye el '0'.
 */
#define MAX_NOMBRE_USUARIO 26

/**
 * \def MAX_CONTRASENIA
 * \brief Longitud maxima para la contrasenia del usuario. Incluye el '0'.
 */
#define MAX_CONTRASENIA 65

/**
 * \def MAX_CORREO_ELECTRONICO
 * \brief Longitud maxima para el correo electronico del usuario. Incluye el '0'.
 */
#define MAX_CORREO_ELECTRONICO 129


/* ============================================================================================================================================
   IDENTIFICADORES
   ============================================================================================================================================ */


/**
 * \def ID_INVALIDO
 * \brief ID de usuario invalido.
 */
#define ID_INVALIDO -1


#endif // CONSTANTES_H_INCLUDED


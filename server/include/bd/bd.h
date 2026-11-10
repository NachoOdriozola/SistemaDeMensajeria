/**
 * \file   bd.h
 * \brief  Contiene funciones de la base de datos SQLite.
 */


#ifndef BD_H_INCLUDED
#define BD_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sqlite3.h"

#include "constantes.h"

#include "logs.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \struct ResultadoInicializacionBD
 * \brief  Codigos de retorno de la inicializacion de la base de datos.
 */
typedef enum
{
    BD_EXITO,
    BD_ENCONTRO,
    BD_NO_ENCONTRO,
    BD_ERROR_INICIALIZACION,
    BD_ERROR_EJECUCION
} ResultadoBd;


/**
 * \struct Sentencias
 * \brief  Cache de sentencias de consultas de base de datos.
 */
typedef struct
{
    sqlite3_stmt *buscarIdPorNombre;
    sqlite3_stmt *buscarIdYContraseniaPorNombre;
    sqlite3_stmt *buscarIdPorCorreo;
    sqlite3_stmt *insertarUsuario;
    sqlite3_stmt *insertarMensaje;
} Sentencias;

typedef struct
{
    sqlite3 *conexion;
    Sentencias sentencias;
} Bd;


/**
 * \struct ParametrosInsertarUsuario
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de insertarUsuario.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    char contrasenia [MAX_CONTRASENIA];
    char correoElectronico [MAX_CORREO_ELECTRONICO];
} ParametrosInsertarUsuario;

/**
 * \struct ParametrosInsertarMensaje
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de insertarMensaje.
 */
typedef struct
{
    int idEmisor;
    int idReceptor;
    char texto [MAX_TEXTO];
} ParametrosInsertarMensaje;


typedef struct
{
    int idUsuario;
    char contrasenia [MAX_CONTRASENIA];
} ResultadoConsultaIdYContrasenia;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar la base de datos. Intentar abrir si ya hay una existente, sino, crearla.
 *
 * Verificar si existen las tablas del disenio.
 * En caso de que existan, la base de datos existe y conserva sus datos.
 * En caso contrario, intenta abrir el archivo "schema.sql" que contiene las consultas SQLite de creacion de tablas, segun el disenio, para ejecutarlas.
 * Establece el journal en modo WAL para mejorar el rendimiento sin sacrificar confiabilidad.
 * No cierra la base de datos en caso de fallas.
 *
 * \param bd Direccion del puntero que contiene la base de datos del contexto del servidor.
 * \param sentenciasSqlite Puntero a la cache de sentencias de consultas de base de datos.
 *
 * \return Retorna EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al preparar consultas, abrir archivos y asignar memoria.
 *
 */
ResultadoBd bd_inicializar (Bd *bd);

/** \brief Cerrar la base de datos y liberar las sentencias de consultas de base de datos.
 *
 * \param bd Puntero que contiene la base de datos del contexto del servidor.
 * \param sentenciasSqlite Puntero a la cache de sentencias de consultas de base de datos.
 *
 */
void bd_liberar (Bd *bd);


/** \brief Buscar un usuario en la base de datos por su nombre, y retornar su ID correspondiente.
 * 
 * \param sentenciaBuscarIdPorNombre Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param ParametrosBuscarUsuarioPorNombre Puntero a la estructura que contiene los datos necesarios para realizar la consulta.
 * \param returnIdUsuario Puntero donde se retorna el resultado de la consulta. Si encontro un usuario retorna su ID correspondiente, sino retorna ID_INVALIDO. Enviar NULL si no se desea recuperar el ID.
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
ResultadoBd bd_buscar_id_usuario_por_nombre (Bd *bd, const char *nombre, int *returnId);

/** \brief Buscar un usuario en la base de datos por su nombre, y retornar su ID y contrasenia correspondiente.
 *
 * \param sentenciaBuscarIdYContraseniaPorNombre Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param parametrosBuscarUsuarioPorNombre Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * \param returnIdUsuario Puntero donde se retorna el resultado de la consulta. Si encontro un usuario retorna su ID correspondiente, sino retorna ID_INVALIDO.
 * \param returnContrasenia Puntero donde se retorna el resultado de la consulta. Si encontro un usuario retorna su contrasenia correspondiente, sino retorna NULL.
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
ResultadoBd bd_buscar_id_y_contrasenia_usuario_por_nombre (Bd *bd, const char *nombre, ResultadoConsultaIdYContrasenia *returnResultadoConsultaIdYContrasenia);

/** \brief Buscar un usuario en la base de datos por su correo electronico.
 *
 * \param sentenciaBuscarIdPorCorreo Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param parametrosBuscarUsuarioPorCorreo Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
ResultadoBd bd_buscar_id_usuario_por_correo (Bd *bd, const char *correo, int *returnId);

/** \brief Insertar un usuario en la base de datos.
 *
 * \param sentenciaInsertarUsuario Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param parametrosInsertarUsuario Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * 
 */
ResultadoBd bd_insertar_usuario (Bd *bd, const ParametrosInsertarUsuario *parametrosInsertarUsuario);

/** \brief Insertar un mensaje en la base de datos.
 *
 * \param sentenciaInsertarMensaje Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param parametrosInsertarMensaje Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * 
 */
ResultadoBd bd_insertar_mensaje (Bd *bd, const ParametrosInsertarMensaje *parametrosInsertarMensaje);


#endif // BD_H_INCLUDED
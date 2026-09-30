/**
 * \file   baseDeDatos.h
 * \brief  Contiene funciones de la base de datos SQLite.
 */


#ifndef BASEDEDATOS_H_INCLUDED
#define BASEDEDATOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sqlite3.h"

#include "constantes.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \struct ResultadoInicializacionBD
 * \brief  Codigos de retorno de la inicializacion de la base de datos.
 */
typedef enum
{
   TABLA_EXISTE,
   TABLA_NO_EXISTE,
   ERROR_PREPARACION_CONSULTA
} ResultadoInicializacionBD;


/**
 * \struct SentenciasSqlite
 * \brief  Cache de sentencias de consultas de base de datos.
 */
typedef struct
{
    sqlite3_stmt *buscarIdPorNombre;
    sqlite3_stmt *buscarIdYContraseniaPorNombre;
    sqlite3_stmt *buscarIdPorCorreo;
    sqlite3_stmt *insertarUsuario;
    sqlite3_stmt *insertarMensaje;
} SentenciasSqlite;


/**
 * \struct ParametrosBuscarUsuarioPorNombre
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de buscarUsuarioPorNombre.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
} ParametrosBuscarUsuarioPorNombre;

/**
 * \struct ParametrosBuscarUsuarioPorCorreo
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de buscarUsuarioPorCorreo.
 */
typedef struct
{
    char correoElectronico [MAX_CORREO_ELECTRONICO];
} ParametrosBuscarUsuarioPorCorreo;

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
    char texto [MAX_MENSAJE];
} ParametrosInsertarMensaje;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar la base de datos. Intentar abrir si ya hay una existente, sino, crearla.
 *
 * Verificar si existen las tablas del disenio.
 * En caso de que existan, la base de datos existe y conserva sus datos.
 * En caso contrario, intenta abrir el archivo "schema.sql" que contiene las consultas SQLite de creacion de tablas, segun el disenio, para ejecutarlas.
 * No cierra la base de datos en caso de fallas.
 *
 * \param bd Direccion del puntero que contiene la base de datos del contexto del servidor.
 * \param sentenciasSqlite Puntero a la cache de sentencias de consultas de base de datos.
 *
 * \return Retorna EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al preparar consultas, abrir archivos y asignar memoria.
 *
 */
CodigoRetorno bd_inicializar (sqlite3 **bd, SentenciasSqlite *sentenciasSqlite);

/** \brief Configurar la base de datos. Establece el journal en modo WAL para mejorar el rendimiento sin sacrificar confiabilidad.
 *
 * \param bd Puntero que contiene la base de datos del contexto del servidor.
 *
 */
void bd_configurar (sqlite3 *bd);

/** \brief Cerrar la base de datos y liberar las sentencias de consultas de base de datos.
 *
 * \param bd Puntero que contiene la base de datos del contexto del servidor.
 * \param sentenciasSqlite Puntero a la cache de sentencias de consultas de base de datos.
 *
 */
void bd_liberar (sqlite3 *bd, SentenciasSqlite *sentenciasSqlite);


/** \brief Buscar un usuario en la base de datos por su nombre, y retornar su ID correspondiente.
 * 
 * \param sentenciaBuscarIdPorNombre Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param ParametrosBuscarUsuarioPorNombre Puntero a la estructura que contiene los datos necesarios para realizar la consulta.
 * \param returnIdUsuario Puntero donde se retorna el resultado de la consulta. Si encontro un usuario retorna su ID correspondiente, sino retorna ID_INVALIDO. Enviar NULL si no se desea recuperar el ID.
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
bool bd_buscar_id_por_nombre (sqlite3_stmt *sentenciaBuscarIdPorNombre, const ParametrosBuscarUsuarioPorNombre *parametrosBuscarUsuarioPorNombre, int *returnIdUsuario);

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
bool bd_buscar_id_y_contrasenia_por_nombre (sqlite3_stmt *sentenciaBuscarIdYContraseniaPorNombre, const ParametrosBuscarUsuarioPorNombre *parametrosBuscarUsuarioPorNombre, int *returnIdUsuario, char *returnContrasenia);

/** \brief Buscar un usuario en la base de datos por su correo electronico.
 *
 * \param sentenciaBuscarIdPorCorreo Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param parametrosBuscarUsuarioPorCorreo Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
bool bd_existe_usuario_con_correo (sqlite3_stmt *sentenciaBuscarIdPorCorreo, const ParametrosBuscarUsuarioPorCorreo *parametrosBuscarUsuarioPorCorreo);

/** \brief Insertar un usuario en la base de datos.
 *
 * \param sentenciaInsertarUsuario Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param parametrosInsertarUsuario Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * 
 */
void bd_insertar_usuario (sqlite3_stmt *sentenciaInsertarUsuario, const ParametrosInsertarUsuario *parametrosInsertarUsuario);

/** \brief Insertar un mensaje en la base de datos.
 *
 * \param sentenciaInsertarMensaje Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param parametrosInsertarMensaje Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * 
 */
void bd_insertar_mensaje (sqlite3_stmt *sentenciaInsertarMensaje, const ParametrosInsertarMensaje *parametrosInsertarMensaje);


#endif // BASEDEDATOS_H_INCLUDED
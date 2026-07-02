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
#include <sqlite3.h>

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \struct t_respuestaInicializacionDB
 * \brief  Codigos de retorno de la inicializacion de la base de datos.
 */
typedef enum
{
   TABLA_EXISTE,
   TABLA_NO_EXISTE,
   ERROR_PREPARACION_CONSULTA
} t_respuestaInicializacionDB;


/**
 * \struct t_sentenciasSqlite
 * \brief  Cache de sentencias de consultas de base de datos.
 */
typedef struct
{
    sqlite3_stmt *buscarUsuarioPorNombre_recuperarId;
    sqlite3_stmt *buscarUsuarioPorNombre_recuperarIdYContrasenia;
    sqlite3_stmt *buscarUsuarioPorNombreYCorreo;
    sqlite3_stmt *insertarUsuario;
    sqlite3_stmt *insertarMensaje;
} t_sentenciasSqlite;


/**
 * \struct t_datosBuscarUsuarioPorNombre
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de buscarUsuarioPorNombre.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
} t_datosBuscarUsuarioPorNombre;

/**
 * \struct t_datosBuscarUsuarioPorNombreYCorreo
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de buscarUsuarioPorNombreYCorreo.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    char correoElectronico [MAX_CORREO_ELECTRONICO];
} t_datosBuscarUsuarioPorNombreYCorreo;

/**
 * \struct t_datosInsertarUsuario
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de insertarUsuario.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    char contrasenia [MAX_CONTRASENIA];
    char correoElectronico [MAX_CORREO_ELECTRONICO];
} t_datosInsertarUsuario;

/**
 * \struct t_datosInsertarMensaje
 * \brief  Estructura que contiene los datos necesarios para realizar la consulta de insertarMensaje.
 */
typedef struct
{
    int idEmisor;
    int idReceptor;
    char texto [MAX_MENSAJE];
} t_datosInsertarMensaje;


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
 * \param db Direccion del puntero que contiene la base de datos del contexto del servidor.
 * \param sentenciasSqlite Puntero a la cache de sentencias de consultas de base de datos.
 *
 * \return Retorna EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al preparar consultas, abrir archivos y asignar memoria.
 *
 */
t_codigoRetorno inicializarBaseDatos(sqlite3 **db, t_sentenciasSqlite *sentenciasSqlite);

/** \brief Configurar la base de datos. Establece el journal en modo WAL para mejorar el rendimiento sin sacrificar confiabilidad.
 *
 * \param db Puntero que contiene la base de datos del contexto del servidor.
 *
 */
void configurarBaseDeDatos (sqlite3 *db);

/** \brief Cerrar la base de datos y liberar las sentencias de consultas de base de datos.
 *
 * \param db Puntero que contiene la base de datos del contexto del servidor.
 * \param sentenciasSqlite Puntero a la cache de sentencias de consultas de base de datos.
 *
 */
void liberarBaseDeDatos (sqlite3 *db, t_sentenciasSqlite *sentenciasSqlite);


/** \brief Buscar un usuario en la base de datos por su nombre, y retornar su ID correspondiente.
 * 
 * \param sentenciaBuscarUsuarioPorNombre_recuperarId Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param t_datosBuscarUsuarioPorNombre Puntero a la estructura que contiene los datos necesarios para realizar la consulta.
 * \param returnIdUsuario Puntero donde se retorna el resultado de la consulta. Si encontro un usuario retorna su ID correspondiente, sino retorna ID_INVALIDO.
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
bool buscarUsuarioPorNombre_recuperarId (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarId, const t_datosBuscarUsuarioPorNombre *datosBuscarUsuarioPorNombre, int *returnIdUsuario);

/** \brief Buscar un usuario en la base de datos por su nombre, y retornar su ID y contrasenia correspondiente.
 *
 * \param sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param datosBuscarUsuarioPorNombre Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * \param returnIdUsuario Puntero donde se retorna el resultado de la consulta. Si encontro un usuario retorna su ID correspondiente, sino retorna ID_INVALIDO.
 * \param returnContrasenia Puntero donde se retorna el resultado de la consulta. Si encontro un usuario retorna su contrasenia correspondiente, sino retorna NULL.
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
bool buscarUsuarioPorNombre_recuperarIdYContrasenia (sqlite3_stmt *sentenciaBuscarUsuarioPorNombre_recuperarIdYContrasenia, const t_datosBuscarUsuarioPorNombre *datosBuscarUsuarioPorNombre, int *returnIdUsuario, char *returnContrasenia);

/** \brief Buscar un usuario en la base de datos por su nombre y correo electronico.
 *
 * \param sentenciaBuscarUsuarioPorNombreYCorreo Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param datosBuscarUsuarioPorNombreYCorreo Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 *
 * \return True en caso de que encontro un usuario, False en caso contrario.
 * 
 */
bool buscarUsuarioPorNombreYCorreo (sqlite3_stmt *sentenciaBuscarUsuarioPorNombreYCorreo, const t_datosBuscarUsuarioPorNombreYCorreo *datosBuscarUsuarioPorNombreYCorreo);

/** \brief Insertar un usuario en la base de datos.
 *
 * \param sentenciaInsertarUsuario Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param datosInsertarUsuario Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * 
 */
void insertarUsuario (sqlite3_stmt *sentenciaInsertarUsuario, const t_datosInsertarUsuario *datosInsertarUsuario);

/** \brief Insertar un mensaje en la base de datos.
 *
 * \param sentenciaInsertarMensaje Puntero que contiene la sentencia para realizar la consulta en la base de datos.
 * \param datosInsertarMensaje Puntero a la estructura que contiene los datos necesarios para realizar la consulta..
 * 
 */
void insertarMensaje (sqlite3_stmt *sentenciaInsertarMensaje, const t_datosInsertarMensaje *datosInsertarMensaje);


#endif // BASEDEDATOS_H_INCLUDED
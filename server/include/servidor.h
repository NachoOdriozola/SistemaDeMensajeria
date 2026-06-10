/**
 * \file   servidor.h
 * \brief  g
 */



#ifndef SERVIDOR_H_INCLUDED
#define SERVIDOR_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <sqlite3.h>

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/estructurasDeDatos/listaSimple/include/listaSimple.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "estructuras.h"
#include "utiles.h"



/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */



/**
 * \def ERROR_CONFIGURACION
 * \brief Codigo de retorno para fallos en la configuracion.
 */
#define ERROR_CONFIGURACION -200



/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */



/** \brief Inicializar la base de datos.
 *
 * Intentar abrir la base de datos "database.db".
 * Verificar si existen las tablas del disenio.
 * En caso de que existan, la base de datos existe y conserva sus datos.
 * En caso contrario, intenta abrir el archivo "schema.sql" que contiene las consultas SQLite de creacion de tablas, segun el disenio, para ejecutarlas.
 *
 * \param bd Doble puntero a la base de datos SQLite.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos, ERROR_SIN_MEMORIA en caso de no poder asignar memoria dinamica, y ERROR_OPERACION si el archivo "schema.sql" es invalido.
 *
 */
int inicializarBaseDatos(sqlite3 **bd);

/** \brief Inicializar los recursos del servidor.
 *
 * Iniciar la API de Winsock, inicializar la base de datos y crear el socket del servidor, la tabla hash de clientes y la lista simple de clientes
 * conectados pero no autenticados.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 *
 */
int inicializarServidor (t_contextoServidor *contextoServidor);

/** \brief Configurar los recursos del servidor.
 *
 * Configurar el socket del servidor para escuchar conexiones de cualquier direccion IP en el puerto asignado. Ademas, establecerlo como modo no bloqueante.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 * \return EXITO si se configuro correctamente, ERROR_CONFIGURACION en caso de error.
 *
 */
int configurarServidor (t_contextoServidor *contextoServidor);

/** \brief Liberar los recursos del servidor.
 *
 * Vaciar la lista simple de clientes conectados pero no autenticados, vaciar y eliminar la tabla hash de clientes y cerrar el socket del servidor,
 * la base de datos y la API de Winsock.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 */
void liberarServidor (t_contextoServidor *contextoServidor);



#endif // SERVIDOR_H_INCLUDED
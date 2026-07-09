/**
 * \file   servidor.h
 * \brief  Contiene las funciones estructurales del servidor.
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
#include <sqlite3.h>
#include "../../external/libsodium/include/sodium.h"

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/estructurasDeDatos/cola/include/cola.h"
#include "../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "../../shared/sockets/include/sockets.h"

#include "estructuras.h"
#include "utiles.h"
#include "baseDeDatos.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/*
* Variable para mantener activo o apagar el servidor. Es modificada en el manejador de la consola.
*/
extern BOOL servidorActivo;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar los recursos del servidor.
 *
 * Inicializar el socket del servidor, la base de datos, y crear la tabla hash de clientes, la lista doble de clientes no autenticados y la cola de solicitudes.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 *
 */
t_codigoRetorno inicializarServidor (t_contextoServidor *contextoServidor);

/** \brief Configurar los recursos del servidor.
 *
 * Configurar el manejador de cierre de la consola, el socket del del servidor para escuchar conexiones de cualquier direccion IP en el puerto asignado y establecerlo como modo no bloqueante,
 * y la base de datos.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 * \return EXITO si se configuro correctamente, ERROR_CONFIGURACION en caso de error.
 *
 */
t_codigoRetorno configurarServidor (t_contextoServidor *contextoServidor);

/** \brief Liberar los recursos del servidor.
 *
 * Vaciar la lista doble de clientes no autenticados y la tabla hash de clientes, y cerrar y finalizar el socket del servidor y la base de datos.
 * No vacia la cola de solicitudes debido a que no es necesario, siempre se encontraria vacia al ejecutar esta fucion.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 */
void liberarServidor (t_contextoServidor *contextoServidor);

/** \brief Manejar eventos de cierre de la consola.
 *
 * Al recibir un evento de cierre de consola o interrupcion, modifica el valor de la variable global servidorActivo a FALSE para
 * finalizar la ejecucion del servidor.
 * No libera recursos directamente.
 * Esta funcion es registrada en al configuracion del servidor y es invocada automaticamente por el sistema operativo.
 *
 * \param tipoEvento Tipo de evento de control recibido por la consola.
 * 
 * \return TRUE si el evento fue manejado, FALSE en caso contrario.
 *
 */
BOOL WINAPI manejadorConsola(DWORD tipoEvento);


#endif // SERVIDOR_H_INCLUDED
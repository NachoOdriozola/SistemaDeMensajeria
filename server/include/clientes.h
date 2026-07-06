/**
 * \file   clientes.h
 * \brief  Contiene funciones de gestion de clientes.
 */


#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/estructurasDeDatos/cola/include/cola.h"
#include "../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "estructuras.h"
#include "utiles.h"
#include "sockets.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Aceptar nuevas conexiones de clientes.
 *
 * Si hay una nueva conexion de un cliente, le establece el socket como no bloqueante, le asigna una ID invalida y lo inserta en la lista doble de clientes no autenticados.
 *
 * \param sock Socket del servidor.
 * \param clientesNoAutenticados Lista doble que contiene a los clientes conectados pero no autenticados.
 *
 */
void aceptarNuevosClientes (t_socket sockServidor, t_listaDoble *clientesNoAutenticados);

/** \brief Recibir solicitudes de los clientes y almacenarlas en la cola de solicitudes.
 *
 * Si un cliente de la lista doble de clientes conectados no autenticados o de la tabla hash de clientes autenticados envio una solicitud, se
 * almacena la direccion del cliente y su solicitud en la cola de solicitudes para luego ser procesada.
 * Si un cliente cerro o perdio la conexion, lo desconectara automaticamente.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 * 
 */
void recibirSolicitudes (t_contextoServidor *contextoServidor);


#endif // CLIENTES_H_INCLUDED
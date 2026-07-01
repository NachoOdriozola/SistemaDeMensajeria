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
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "estructuras.h"
#include "utiles.h"

   
/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def RECIBI_SOLICITUD
 * \brief Codigo de retorno que indica que se recibio una solicitud de un cliente.
 */
#define RECIBI_SOLICITUD 1

/**
 * \def NO_RECIBI_SOLICITUD
 * \brief Codigo de retorno que indica que no se recibio ninguna solicitud de un cliente.
 */
#define NO_RECIBI_SOLICITUD 0


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
void aceptarNuevosClientes (SOCKET sock, t_listaDoble *clientesNoAutenticados);

/** \brief Detectar si un cliente, autenticado o no, envio una solicitud.
 *
 * Si un cliente de la lista doble de clientes conectados no autenticados o de la tabla hash de clientes autenticados envio una solicitud, se
 * almacena y retorna la direccion del nodo del cliente y su solicitud para luego ser procesada.
 * Si un cliente cerro o perdio la conexion, lo desconectara automaticamente.
 *
 * \param clientes Tabla hash que contiene a los clientes conectados y autenticados.
 * \param clientesNoAutenticados Lista doble que contiene a los clientes conectados pero no autenticados.
 * \param clienteAProcesar Puntero donde se retornara la direccion del nodo del cliente que envio la solicitud y se debe procesar.
 * \param solicitud Puntero a donde se retornara la solicitud enviada por el cliente.
 *
 * \return RECIBI_SOLICITUD si se recibio una solicitud, NO_RECIBI SOLICITUD en caso contrario.
 * 
 */
bool recibiSolicitud (t_tablaHash *clientes, t_listaDoble *clientesNoAutenticados, t_nodoListaDoble**clienteAProcesar, char *solicitud);


#endif // CLIENTES_H_INCLUDED
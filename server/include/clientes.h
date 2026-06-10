/**
 * \file   clientes.h
 * \brief  g
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
#include "../../shared/estructurasDeDatos/listaSimple/include/listaSimple.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "estructuras.h"
#include "utiles.h"

   

/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */



/**
 * \def RECIBIO_SOLICITUD
 * \brief Codigo de retorno que indica que se recibio una solicitud de un cliente.
 */
#define RECIBIO_SOLICITUD 1

/**
 * \def NO_RECIBIO_SOLICITUD
 * \brief Codigo de retorno que indica que no se recibio ninguna solicitud.
 */
#define NO_RECIBIO_SOLICITUD 0



/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */



/** \brief Procesar a un nuevo cliente conectado e insertarlo en la lista simple de clientes conectados pero no autenticados.
 *
 * Establecer el socket del cliente como no bloqueante, asignarle una ID invalida e insertarlo en la lista simple de clientes conectados pero no autenticados.
 *
 * \param nuevoCliente Puntero al nuevo cliente conectado.
 * \param listaSimpleClientesNoAutenticados Puntero a la lista simple de clientes no autenticados.
 *
 */
void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaSimple *listaSimpleClientesNoAutenticados);

/** \brief Detectar si se recibio una solicitud de algun cliente en una lista simple.
 *
 * Recorrer la lista simple y preguntar a cada cliente si envio una solicitud.
 * Si un cliente envio una solicitud, se guarda su posicion y retorna.
 * Si un cliente perdio la conexion, lo desconectara automaticamente.
 *
 * \param listaSimple Puntero a la lista simple.
 * \param nodoDelCliente Direccion del doble puntero donde se guardara el nodo del cliente que envio la solicitud.
 * \param bufferSolicitud Buffer donde se almacenara la cadena de la solicitud enviada por el cliente.
 *
 * \return RECIBIO_SOLICITUD si se recibio una solicitud, NO_RECIBIO_SOLICITUD en caso contrario.
 *
 */
bool recibirSolicitudEnListaSimple (t_listaSimple *listaSimple, t_nodo ***nodoDelCliente, char *bufferSolicitud);

/** \brief Detectar si se recibio una solicitud de algun cliente en una tabla hash.
 *
 * Recorrer todas las listas simples de cada bucket y preguntar a cada cliente si envio una solicitud.
 * Si un cliente envio una solicitud, se guarda su posicion y retorna.
 * Si un cliente perdio la conexi�n, lo desconectara automaticamente.
 *
 * \param tablaHash Puntero a la tabla hash.
 * \param nodoDelCliente Direccion del doble puntero donde se guardara el nodo del cliente que envio la solicitud.
 * \param bufferSolicitud Buffer donde se almacenara la cadena de la solicitud enviada por el cliente.
 *
 * \return RECIBIO_SOLICITUD si se recibio una solicitud, NO_RECIBIO_SOLICITUD en caso contrario.
 *
 */
bool recibirSolicitudEnTablaHash (t_tablaHash *tablaHash, t_nodo ***nodoDelCliente, char *bufferSolicitud);




#endif // CLIENTES_H_INCLUDED
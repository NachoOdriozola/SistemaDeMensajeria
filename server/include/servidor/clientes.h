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

#include "constantes.h"
#include "protocolos.h"
#include "sockets.h"
#include "cola.h"
#include "listaSimple.h"
#include "listaDoble.h"
#include "tablaHash.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"


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
void aceptar_nuevos_clientes (Socket sockServidor, ListaDoble *clientesNoAutenticados);

/** \brief Recibir solicitudes de los clientes y almacenarlas en la cola de solicitudes.
 *
 * Si un cliente de la lista doble de clientes conectados no autenticados o de la tabla hash de clientes autenticados envio una solicitud, se
 * almacena la direccion del cliente y su solicitud en la cola de solicitudes para luego ser procesada.
 * Si un cliente cerro o perdio la conexion, lo desconectara automaticamente.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global del servidor.
 * 
 */
void recibir_solicitudes (ContextoServidor *contextoServidor);

/** \brief Enviar una respuesta al cliente. Iterar hasta enviar todos los datos al buffer del socket del cliente.
 *
 * En caso de que el socket del cliente tenga el buffer lleno, se inserta la respuesta en la lista simple de respuestas pendientes.
 * 
 * \param contextoServidor Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global del servidor.
 * \param respuestaCliente Puntero a la estructura que almacena al cliente a responder con la respuesta a darle.
 * 
 * \return ENVIO_COMPLETO si pudo enviar todos los datos correctamente, ENVIO_BUFFER_LLENO si el buffer del socket se encuentra agotado y no se pueden cargar mas datos, ENVIO_ERROR_CONEXION en caso de error de conexion.
 * 
 */
ResultadoEnvio enviar_respuesta_cliente (ContextoServidor *contextoServidor, RespuestaCliente *respuestaCliente);

/** \brief Volver a intentar enviar una respuesta pendiente al cliente. Iterar hasta enviar todos los datos al buffer del socket del cliente.
 *
 * \param respuestaPendienteCliente Puntero a la estructura que almacena al cliente a responder con la respuesta a darle.
 * 
 * \return ENVIO_COMPLETO si pudo enviar todos los datos correctamente, ENVIO_BUFFER_LLENO si el buffer del socket se encuentra agotado y no se pueden cargar mas datos, ENVIO_ERROR_CONEXION en caso de error de conexion.
 * 
 */
ResultadoEnvio intentar_enviar_respuesta_pendiente_cliente (RespuestaCliente *respuestaPendienteCliente);


#endif // CLIENTES_H_INCLUDED
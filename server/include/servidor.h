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

#include "constantes.h"

#include "logs.h"

#include "plataforma/signals.h"
#include "bd/bd.h"
#include "clientes/registro_clientes.h"
#include "red/comunicacion.h"
#include "servicios/servicios.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


typedef struct
{
   Bd bd;
   RegistroClientes registroClientes;
   Servicios servicios;
   Comunicacion comunicacion;
} Servidor;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar los recursos del servidor.
 *
 * Inicializar el socket del servidor, la base de datos, y crear la tabla hash de clientes, la lista doble de clientes no autenticados y la cola de solicitudes.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 *
 */
CodigoRetorno servidor_inicializar (Servidor *servidor);

void servidor_ejecutar (Servidor *servidor);

/** \brief Liberar los recursos del servidor.
 *
 * Vaciar la lista doble de clientes no autenticados y la tabla hash de clientes, y cerrar y finalizar el socket del servidor y la base de datos.
 * No vacia la cola de solicitudes debido a que no es necesario, siempre se encontraria vacia al ejecutar esta fucion.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global del servidor.
 *
 */
void servidor_liberar (Servidor *servidor);



#endif // SERVIDOR_H_INCLUDED
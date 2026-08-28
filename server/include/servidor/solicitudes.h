/**
 * \file   solicitudes.h
 * \brief  Contiene funciones que procesan las solicitudes de los clientes.
 */


#ifndef SOLICITUDES_H_INCLUDED
#define SOLICITUDES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>

#include "constantes.h"
#include "protocolos.h"
#include "sockets.h"
#include "cola.h"
#include "listaSimple.h"
#include "listaDoble.h"
#include "tablaHash.h"

#include "sodium.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "baseDeDatos/baseDeDatos.h"

#include "servidor/clientes.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Procesar las solicitudes enviada por los cliente y enviarles una respuesta. Procesa toda la cola de solicitudes y finalmente las elimina.
 * 
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 */
void procesarSolicitudes (t_contextoServidor *contextoServidor);



#endif // SOLICITUDES_H_INCLUDED
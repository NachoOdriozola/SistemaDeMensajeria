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
#include "../../external/libsodium/include/sodium.h"

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/estructurasDeDatos/cola/include/cola.h"
#include "../../shared/estructurasDeDatos/listaSimple/include/listaSimple.h"
#include "../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "../../shared/sockets/include/sockets.h"

#include "estructuras.h"
#include "utiles.h"
#include "baseDeDatos.h"
#include "clientes.h"


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
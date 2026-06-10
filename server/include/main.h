/**
 * \file   main.h
 * \brief  g
 */



#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "estructuras.h"
#include "servidor.h"
#include "clientes.h"
#include "solicitudes.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def CARACTER_APAGAR_SERVIDOR
 * \brief Caracter que el usuario debe escribir en consola para apagar el servidor.
 */
#define CARACTER_APAGAR_SERVIDOR 'S'



#endif // SERVIDOR_H_INCLUDED
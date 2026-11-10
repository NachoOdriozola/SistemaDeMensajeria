/**
 * \file   signals.h
 * \brief 
 */


#ifndef SIGNALS_H_INCLUDED
#define SIGNALS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdbool.h>

#include "constantes.h"

#include "logs.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
#else
    //LINUX
#endif


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */

   
CodigoRetorno signals_instalar_handler ();
bool signals_apagado_solicitado ();

void signals_sleep (unsigned ms);


#endif // SIGNALS_H_INCLUDED
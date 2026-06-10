/**
 * \file   main.h
 * \brief  Une las interfaces graficas y contiene las funciones estructurales base de ejecucion principal.
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
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "../../external/csfml/include/SFML/System.h"
#include "../../external/csfml/include/SFML/Window.h"
#include "../../external/csfml/include/SFML/Graphics.h"

#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/constantes/include/constantes.h"
#include "estructuras.h"

#include "recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"
#include "recursosGraficosComunes/recursosComunesContactosSalas.h"

#include "interfaces/interfazAutenticacion.h"
#include "interfaces/interfazConfig.h"
#include "interfaces/interfazContactos.h"
#include "interfaces/interfazRegistro.h"
#include "interfaces/interfazSalas.h"



/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */



/** \struct t_interfaces
 * \brief Une todas las interfaces graficas y los recursos graficos comunes.
 */
typedef struct
{
    t_interfazAutenticacion autenticacion;
    t_interfazConfig config;
    t_interfazContactos contactos;
    t_interfazRegistro registro;
    t_interfazSalas salas;
    t_recursosComunesAutenticacionRegistro recursosComunesAutenticacionRegistro;
    t_recursosComunesContactosSalas recursosComunesContactosSalas;
} t_interfaces;



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES BASE
   ============================================================================================================================================ */



/** \brief Inicializar los valores de los recursos de la aplicacion en NULL.
 *
 * Inicializar en NULL: un estado de la API de Winsock, el renderizado de la ventana, el socket del usuario, los recursos graficos comunes y las interfaces graficas.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void inicializarValoresNulosAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces);

/** \brief Inicializar los recursos de la aplicacion.
 *
 * Crear: la API de Winsock, el renderizado de la ventana, el socket del usuario y conectarlo con el servidor, los recursos graficos comunes y las interfaces graficas.
 * Antes de crear cada recurso, los inicializa en NULL.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int inicializarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces);

/** \brief Configurar los recursos de la aplicacion.
 *
 * Configurar: la aplicacion, los recursos graficos comunes y las interfaces graficas.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void configurarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces);

/** \brief Liberar los recursos de la aplicacion.
 *
 * Liberar: la API de Winsock, el renderizado de la ventana, el socket del usuario, los recursos graficos comunes y las interfaces graficas.
 * Antes de liberar, pregunta si el recurso fue creado o no.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void liberarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfaces *interfaces);



#endif // MAIN_H_INCLUDED


















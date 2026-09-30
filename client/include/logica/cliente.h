/**
 * \file   cliente.h
 * \brief  Contiene las funciones estructurales del cliente y une las interfaces graficas.
 */


#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "protocolos.h"
#include "constantes.h"

#include "logica/estructuras.h"

#include "interfacesGraficas/interfazAutenticacion/interfazAutenticacion.h"
#include "interfacesGraficas/interfazContactos/interfazContactos.h"
#include "interfacesGraficas/interfazRegistro/interfazRegistro.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def APLICACION_ESTA_EJECUTANDOSE
 * \brief Valor booleano para saber si la ventana de renderizado esta abierta.
 */
#define APLICACION_ESTA_EJECUTANDOSE(x) (sfRenderWindow_isOpen (x))


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct InterfacesGraficas
 * \brief Une todas las interfaces graficas y los recursos comunes.
 */
typedef struct
{
   UiAcceso uiAcceso;
   UiAutenticacion uiAutenticacion;
   UiRegistro uiRegistro;
   UiContactos uiContactos;
} InterfacesGraficas;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar los recursos de la aplicacion.
 *
 * Inicializar el Winsock API y crear: el renderizado de la ventana, los recursos graficos comunes y las interfaces graficas.
 * Antes de crear cada recurso, los inicializa en NULL para facilitar la liberacion de los mismos en caso de errores.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
CodigoRetorno aplicacion_inicializar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas);

/** \brief Configurar los recursos de la aplicacion, los recursos comunes, las interfaces graficas.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 * 
 * \return EXITO si se inicializo correctamente, ERROR_CONFIGURACION en caso de error.
 *
 */
void aplicacion_configurar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas);

/** \brief Ejecutar la interfaz correspondiente en la que se encuentra situado el usuario actualmente.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void aplicacion_ejecutar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas);

/** \brief Liberar los recursos de la aplicacion.
 *
 * Liberar: la API de Winsock, el renderizado de la ventana, el socket del usuario, los recursos graficos comunes y las interfaces graficas.
 * Antes de liberar, pregunta si el recurso fue creado o no.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void aplicacion_liberar (ContextoAplicacion *contextoAplicacion, InterfacesGraficas *interfacesGraficas);


#endif // CLIENTE_H_INCLUDED
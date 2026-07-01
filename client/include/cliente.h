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
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "../../external/csfml/include/SFML/System.h"
#include "../../external/csfml/include/SFML/Window.h"
#include "../../external/csfml/include/SFML/Graphics.h"

#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/constantes/include/constantes.h"
#include "estructuras.h"

#include "interfacesGraficas/recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"

#include "interfacesGraficas/interfazAutenticacion/interfazAutenticacion.h"
#include "interfacesGraficas/interfazConfig/interfazConfig.h"
#include "interfacesGraficas/interfazContactos/interfazContactos.h"
#include "interfacesGraficas/interfazRegistro/interfazRegistro.h"
#include "interfacesGraficas/interfazSalas/interfazSalas.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


#define APLICACION_ESTA_EJECUTANDOSE(x) (sfRenderWindow_isOpen (x))
#define MAXIMIZAR_VENTANA(x, y) (ShowWindow(x, y))


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_interfacesGraficas
 * \brief Une todas las interfaces graficas y los recursos comunes.
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
} t_interfacesGraficas;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar los recursos de la aplicacion.
 *
 * Crear: la API de Winsock, el renderizado de la ventana, el socket del usuario y conectarlo con el servidor, los recursos graficos comunes y las interfaces graficas.
 * Antes de crear cada recurso, los inicializa en NULL para facilitar la liberacion de los mismos en caso de errores.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
t_codigoRetorno inicializarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);

/** \brief Configurar los recursos de la aplicacion, los recursos comunes, y las interfaces graficas.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void configurarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);

/** \brief Ejecutar la interfaz correspondiente en la que se encuentra situado el usuario actualmente.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void ejecutarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);

/** \brief Liberar los recursos de la aplicacion.
 *
 * Liberar: la API de Winsock, el renderizado de la ventana, el socket del usuario, los recursos graficos comunes y las interfaces graficas.
 * Antes de liberar, pregunta si el recurso fue creado o no.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfacesGraficas Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void liberarAplicacion (t_contextoAplicacion *contextoAplicacion, t_interfacesGraficas *interfacesGraficas);


#endif // CLIENTE_H_INCLUDED
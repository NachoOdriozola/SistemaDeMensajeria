/**
 * \file   interfazContactos.h
 * \brief  Contiene funciones estructurales de interfaz.
 */


#ifndef INTERFAZCONTACTOS_H_INCLUDED
#define INTERFAZCONTACTOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"
#include "logica/estructuras.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/recursos.h"
#include "interfacesGraficas/interfazContactos/controladores.h"
#include "interfacesGraficas/interfazContactos/accion.h"
#include "interfacesGraficas/interfazContactos/actualizar.h"
#include "interfacesGraficas/interfazContactos/renderizar.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def MAXIMIZAR_VENTANA
 * \brief Macro para maximizar la ventana a los valores recibidos por parametros.
 */
#define MAXIMIZAR_VENTANA(x, y) (ShowWindow(x, y))


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void interfazContactos_inicializarValoresNulos (t_interfazContactos *interfazContactos);

/** \brief Inicializar los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazContactos_inicializar (t_interfazContactos *interfazContactos);

/** \brief Configurar los recursos graficos y logica de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void interfazContactos_configurar (t_interfazContactos *interfazContactos);

/** \brief Preparar la interfaz de contactos para su ejecucion.
 * 
 * Se realiza una distincion entre las funciones de inicializar y configurar ya que realiza ciertas operaciones que en un inicio no se deben realizar y necesita ciertos datos que en un inicio no se conocen.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void interfazContactos_prepararInterfaz (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

/** \brief Ejecutar la interfaz de contactos.
 *
 * Realizar los procesos de:
 * 1) Accion: Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * 2) Actualizacion: Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes, notificaciones, etc).
 * 3) Renderizado: Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de contactos en la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void interfazContactos_ejecutar (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void interfazContactos_liberar (t_interfazContactos *interfazContactos);


#endif // INTERFAZCONTACTOS_H_INCLUDED


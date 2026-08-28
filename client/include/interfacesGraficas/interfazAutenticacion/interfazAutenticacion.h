/**
 * \file   interfazAutenticacion.h
 * \brief  Contiene funciones estructurales de interfaz.
 */


#ifndef INTERFAZAUTENTICACION_H_INCLUDED
#define INTERFAZAUTENTICACION_H_INCLUDED


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

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"
#include "interfacesGraficas/interfazAutenticacion/recursos.h"
#include "interfacesGraficas/interfazAutenticacion/controladores.h"
#include "interfacesGraficas/interfazAutenticacion/accion.h"
#include "interfacesGraficas/interfazAutenticacion/actualizar.h"
#include "interfacesGraficas/interfazAutenticacion/renderizar.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_inicializarValoresNulos (t_interfazAutenticacion *interfazAutenticacion);

/** \brief Inicializar los recursos graficos de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazAutenticacion_inicializar (t_interfazAutenticacion *interfazAutenticacion);

/** \brief Configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazAutenticacion_configurar (t_interfazAutenticacion *interfazAutenticacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Ejecutar la interfaz de autenticacion.
 *
 * Realizar los procesos de:
 * 1) Accion: Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * 2) Actualizacion: Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
 * 3) Renderizado: Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de contactos en la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_ejecutar (t_contextoAplicacion *contextoAplicacion, t_interfazAutenticacion *interfazAutenticacion);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos y logica de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_liberar (t_interfazAutenticacion *interfazAutenticacion);


#endif // INTERFAZAUTENTICACION_H_INCLUDED


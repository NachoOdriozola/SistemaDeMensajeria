/**
 * \file   interfazConfig.h
 * \brief  Contiene funciones estructurales de interfaz.
 */


#ifndef INTERFAZCONFIG_H_INCLUDED
#define INTERFAZCONFIG_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../utiles.h"
#include "../../estructuras.h"

#include "interfazConfig_estructuras.h"
#include "interfazConfig_recursos.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar los recursos graficos de la interfaz de configuraciones.
 *
 * Establecer todas las variables graficas en NULL y luego crear cada recurso.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos y logica de la interfaz de configuraciones.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
t_codigoRetorno interfazConfig_inicializar (t_interfazConfig *interfazConfig);

/** \brief Configurar y establecer el tamanio y la posicion sobre la ventana de los recursos graficos de la interfaz de configuraciones.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecerle un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos y logica de la interfaz de configuraciones.
 *
 */
void interfazConfig_configurar (t_interfazConfig *interfazConfig);

/** \brief Ejecutar la interfaz de configuraciones.
 *
 * Realizar los procesos de:
 * 1) Accion: Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * 2) Actualizacion: Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
 * 3) Renderizado: Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de contactos en la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazConfig Puntero a la estructura base de los recursos graficos y logica de la interfaz de configuraciones.
 *
 */
void ejecutarInterfazConfig (t_contextoAplicacion *contextoAplicacion, t_interfazConfig *interfazConfig);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de configuraciones.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos y logica de la interfaz de configuraciones.
 *
 */
void interfazConfig_liberar (t_interfazConfig *interfazConfig);


#endif // INTERFAZCONFIG_H_INCLUDED

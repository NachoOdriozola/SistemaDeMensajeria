/**
 * \file   interfazConfig.h
 * \brief  Define las estructuras y contiene funciones estructurales y logicas relacionadas a la interfaz de configuraciones.
 */



#ifndef INTERFAZCONFIG_H_INCLUDED
#define INTERFAZCONFIG_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../../Constantes/constantes.h"
#include "../utiles.h"
#include "../estructuras.h"
#include "../logicaAplicacion.h"



/* ============================
   DEFINES
   ============================ */





/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_interfazConfigTextos
 * \brief Contiene todos los textos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    sfText *textoConfig;
} t_interfazConfigTextos;

/** \struct t_interfazConfigElementos
 * \brief Contiene todos los elementos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    sfRectangleShape *rectanguloVolver;
} t_interfazConfigElementos;

/** \struct t_interfazConfigHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de configuraciones.
 */
typedef struct
{

} t_interfazConfigHabilitaciones;

/** \struct t_interfazConfig
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    t_interfazConfigTextos textos;
    t_interfazConfigElementos elementos;
    t_interfazConfigHabilitaciones habilitaciones;
} t_interfazConfig;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de configuraciones.
 *
 * Establecer todas las variables graficas en NULL y luego crear cada recurso.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazConfig_inicializar (t_interfazConfig *interfazConfig);

/** \brief Configurar y establecer el tamanio y la posicion sobre la ventana de los recursos graficos de la interfaz de configuraciones.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecerle un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazConfig_configurar (t_interfazConfig *interfazConfig, const t_fuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de configuraciones.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 */
void interfazConfig_accion (t_aplicacion *aplicacion, const t_interfazConfig *interfazConfig);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de configuraciones.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 */
void interfazConfig_actualizar (t_interfazConfig *interfazConfig);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de configuraciones sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de configuraciones en la ventana.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 *
 */
void interfazConfig_renderizar (sfRenderWindow *renderizado, const t_interfazConfig *interfazConfig);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de configuraciones.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 */
void interfazConfig_liberar (t_interfazConfig *interfazConfig);



#endif // INTERFAZCONFIG_H_INCLUDED




























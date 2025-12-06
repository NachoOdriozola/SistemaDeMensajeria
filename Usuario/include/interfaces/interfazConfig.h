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
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"

#include "../../../Constantes/constantes.h"
#include "../logicaUsuario.h"



/* ============================
   DEFINES
   ============================ */





/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct s_interfazConfigTextos
 * \brief Contiene todos los textos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    sfText *textoConfig;
} s_interfazConfigTextos;

/** \struct s_interfazConfigElementos
 * \brief Contiene todos los elementos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    sfRectangleShape *rectanguloVolver;
} s_interfazConfigElementos;

/** \struct s_interfazConfigHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de configuraciones.
 */
typedef struct
{

} s_interfazConfigHabilitaciones;

/** \struct s_interfazConfig
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    s_interfazConfigTextos textos;
    s_interfazConfigElementos elementos;
    s_interfazConfigHabilitaciones habilitaciones;
} s_interfazConfig;



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
int interfazConfig_inicializar (s_interfazConfig *interfazConfig);

/** \brief Configurar y establecer el tamanio y la posicion sobre la ventana de los recursos graficos de la interfaz de configuraciones.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL, configurar cada recurso y establecerle un tamanio y una posicion sobre la ventana.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
void interfazConfig_configurar (s_interfazConfig *interfazConfig, const s_fuentes *fuentes, const s_ventana *ventana);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de configuraciones.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 */
void interfazConfig_accion (s_aplicacion *aplicacion, const s_interfazConfig *interfazConfig);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de configuraciones.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 */
void interfazConfig_actualizar (s_interfazConfig *interfazConfig);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de configuraciones sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de configuraciones en la ventana.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 *
 */
void interfazConfig_renderizar (sfRenderWindow *renderizado, const s_interfazConfig *interfazConfig);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de configuraciones.
 *
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 */
void interfazConfig_liberar (s_interfazConfig *interfazConfig);



#endif // INTERFAZCONFIG_H_INCLUDED




























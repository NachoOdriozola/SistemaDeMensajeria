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



/* ============================
   DEFINES
   ============================ */





/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_interfazConfigFuentes
 * \brief Contiene las fuentes graficas de la interfaz de configuraciones.
 */
typedef struct
{
    sfFont *ui;                      /**< Fuente utilizada en textos de la interfaz grafica. */
} t_interfazConfigFuentes;

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

/** \enum t_interfazConfigFoco
 * \brief Contiene todos los estados de foco de la interfaz de configuraciones.
 */
typedef enum
{
    ICF_NINGUNO
} t_interfazConfigFoco;

/** \struct t_interfazConfig
 * \brief Estructura base que contiene los buffers, focos y une los recursos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    t_interfazConfigFuentes fuentes;
    t_interfazConfigTextos textos;
    t_interfazConfigElementos elementos;
    t_interfazConfigFoco estadoFoco;
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
void interfazConfig_configurar (t_interfazConfig *interfazConfig);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de configuraciones.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
 *
 */
void interfazConfig_accion (t_contextoAplicacion *contextoAplicacion, t_interfazConfig *interfazConfig);

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
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param interfazConfig Puntero a la estructura base de los recursos graficos de la interfaz de configuraciones.
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




























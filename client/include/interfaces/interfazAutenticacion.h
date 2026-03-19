/**
 * \file   interfazAutenticacion.h
 * \brief  Define las estructuras y contiene funciones estructurales y logicas relacionadas a la interfaz de autenticacion.
 */



#ifndef INTERFAZAUTENTICACION_H_INCLUDED
#define INTERFAZAUTENTICACION_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../external/csfml/include/SFML/System.h"
#include "../../external/csfml/include/SFML/Window.h"
#include "../../external/csfml/include/SFML/Graphics.h"

#include "../../shared/constantes/include/constantes.h"
#include "../../../shared/protocolos/include/protocolos.h"
#include "../utiles.h"
#include "../estructuras.h"
#include "../recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"



/* ============================
   DEFINES
   ============================ */




/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_interfazAutenticacionTextos
 * \brief Contiene todos los textos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   sfText *aux;
} t_interfazAutenticacionTextos;

/** \struct t_interfazAutenticacionElementos
 * \brief Contiene todos los elementos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   sfRectangleShape *aux;
} t_interfazAutenticacionElementos;

/** \enum t_interfazAutenticacionFoco
 * \brief Contiene todos los estados de foco de la interfaz de autenticacion.
 */
typedef enum
{
    IA_NINGUNO                  /**< Ningun foco establecido. */
} t_interfazAutenticacionFoco;

/** \struct t_interfazAutenticacion
 * \brief Estructura base que contiene los buffers, focos y une los recursos graficos de la interfaz de autenticacion.
 */
typedef struct
{
    t_interfazAutenticacionTextos textos;
    t_interfazAutenticacionElementos elementos;
    t_interfazAutenticacionFoco estadoFoco;
} t_interfazAutenticacion;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_inicializarValoresNulos (t_interfazAutenticacion *interfazAutenticacion);

/** \brief Inicializar los recursos graficos de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazAutenticacion_inicializar (t_interfazAutenticacion *interfazAutenticacion);

/** \brief Configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico de la interfaz de autenticacion.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecerle un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficas de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazAutenticacion_configurar (t_interfazAutenticacion *interfazAutenticacion, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de autenticacion.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de autenticacion.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_actualizar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de autenticacion sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de autenticacion en la ventana.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_renderizar (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const t_interfazAutenticacion *interfazAutenticacion);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_liberar (t_interfazAutenticacion *interfazAutenticacion);



#endif // INTERFAZAUTENTICACION_H_INCLUDED


















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
#include "../recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"



/* ============================
   DEFINES
   ============================ */




/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct s_interfazAutenticacionTexto
 * \brief Contiene todos los textos graficos de la interfaz de autenticacion.
 */
typedef struct
{
    sfText *textoRegistrarUsuario;  /**< Texto interrogativo para registrar usuario. */
} s_interfazAutenticacionTexto;

/** \struct s_interfazAutenticacionElementos
 * \brief Contiene todos los elementos graficos de la interfaz de autenticacion.
 */
typedef struct
{

} s_interfazAutenticacionElementos;

/** \struct s_interfazAutenticacionHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de autenticacion.
 */
typedef struct
{

} s_interfazAutenticacionHabilitaciones;

/** \struct s_interfazAutenticacion
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de autenticacion.
 */
typedef struct
{
    s_interfazAutenticacionTexto texto;
    s_interfazAutenticacionElementos elementos;
    s_interfazAutenticacionHabilitaciones habilitaciones;
} s_interfazAutenticacion;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de autenticacion.
 *
 * Establecer todas las variables graficas en NULL y luego invocar a las funciones
 * interfazAutenticacion_inicializarTexto e interfazAutenticacion_inicializarElementos para crear cada recurso.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazAutenticacion_inicializar (s_interfazAutenticacion *interfazAutenticacion);

/** \brief Configurar y establecer el tamanio y la posicion sobre la ventana de los recursos graficos de la interfaz de autenticacion.
 *
 * Invocar a las funciones interfazAutenticacion_configurarTexto e interfazAutenticacion_configurarElementos para configurar cada recurso y luego invocar a las funciones
 * interfazAutenticacion_tamYPosVentanaTexto e interfazAutenticacion_tamYPosVentanaElementos para establecer a todos los recursos graficos un tamanio y posicion sobre la ventana.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazAutenticacion_configurar (s_interfazAutenticacion *interfazAutenticacion, const s_fuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de autenticacion.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazAutenticacion_accion (s_aplicacion *aplicacion, const s_interfazAutenticacion *interfazAutenticacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de autenticacion.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazAutenticacion_actualizar (s_interfazAutenticacion *interfazAutenticacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de autenticacion sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de autenticacion en la ventana.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazAutenticacion_renderizar (sfRenderWindow *renderizado, const s_interfazAutenticacion *interfazAutenticacion, const s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Liberar todos los recursos graficos creados de la interfaz de autenticacion.
 *
 * Liberar, de manera segura, todos los recursos graficos creados de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_liberar (s_interfazAutenticacion *interfazAutenticacion);



/* ============================
   FUNCIONES LOGICAS
   ============================ */



void intentarIngreso (s_aplicacion *aplicacion, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



#endif // INTERFAZAUTENTICACION_H_INCLUDED


















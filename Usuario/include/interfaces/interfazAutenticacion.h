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



/** \struct t_interfazAutenticacionTextos
 * \brief Contiene todos los textos graficos de la interfaz de autenticacion.
 */
typedef struct
{

} t_interfazAutenticacionTextos;

/** \struct t_interfazAutenticacionElementos
 * \brief Contiene todos los elementos graficos de la interfaz de autenticacion.
 */
typedef struct
{

} t_interfazAutenticacionElementos;

/** \struct t_interfazAutenticacionHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de autenticacion.
 */
typedef struct
{

} t_interfazAutenticacionHabilitaciones;

/** \struct t_interfazAutenticacion
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de autenticacion.
 */
typedef struct
{
    t_interfazAutenticacionTextos textos;
    t_interfazAutenticacionElementos elementos;
    t_interfazAutenticacionHabilitaciones habilitaciones;
} t_interfazAutenticacion;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de autenticacion.
 *
 * Establecer todas las variables graficas en NULL y luego crear cada recurso.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazAutenticacion_inicializar (t_interfazAutenticacion *interfazAutenticacion);

/** \brief Configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico de la interfaz de autenticacion.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecerle un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazAutenticacion_configurar (t_interfazAutenticacion *interfazAutenticacion, const t_fuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de autenticacion.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_accion (t_aplicacion *aplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de autenticacion.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_actualizar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazAutenticacion *interfazAutenticacion);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de autenticacion sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de autenticacion en la ventana.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_renderizar (sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const t_interfazAutenticacion *interfazAutenticacion);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de autenticacion.
 *
 * \param interfazAutenticacion Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de autenticacion.
 *
 */
void interfazAutenticacion_liberar (t_interfazAutenticacion *interfazAutenticacion);



#endif // INTERFAZAUTENTICACION_H_INCLUDED


















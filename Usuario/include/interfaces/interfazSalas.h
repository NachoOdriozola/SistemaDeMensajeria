/**
 * \file   interfazSalas.h
 * \brief  Define las estructuras y contiene funciones estructurales y logicas relacionadas a la interfaz de salas.
 */



#ifndef INTERFAZSALAS_H_INCLUDED
#define INTERFAZSALAS_H_INCLUDED



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
#include "../../../EstructurasDeDatos/include/listaCircular.h"
#include "../logicaUsuario.h"
#include "../recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================
   DEFINES
   ============================ */






/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct s_interfazSalasTexto
 * \brief Contiene todos los textos graficos de la interfaz de salas.
 */
typedef struct
{

} s_interfazSalasTexto;

/** \struct s_interfazSalasElementos
 * \brief Contiene todos los elementos graficos de la interfaz de salas.
 */
typedef struct
{

} s_interfazSalasElementos;

/** \struct s_interfazSalasHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de salas.
 */
typedef struct
{

} s_interfazSalasHabilitaciones;

/** \struct s_interfazSalas
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de salas.
 */
typedef struct
{
    s_interfazSalasTexto texto;
    s_interfazSalasElementos elementos;
    s_interfazSalasHabilitaciones habilitaciones;
} s_interfazSalas;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de salas.
 *
 * Establecer todas las variables graficas en NULL y luego invocar a las funciones
 * interfazSalas_inicializarTexto e interfazSalas_inicializarElementos para crear cada recurso.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazSalas_inicializar (s_interfazSalas *interfazSalas);

/** \brief Configurar los recursos graficos, habilitaciones y buffers de la interfaz de salas.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y luego invocar a las funciones interfazSalas_configurarTexto e
 * interfazSalas_configurarElementos para configurar cada recurso.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazSalas_configurar (s_interfazSalas *interfazSalas, const s_fuentes *fuentes);

/** \brief Establecer el tamanio y la posicion sobre la ventana de cada recurso grafico de la interfaz de salas.
 *
 * Invocar a las funciones interfazSalas_tamYPosPantallaTexto e interfazSalas_tamYPosPantallaElementos para establecer a todos los recursos
 * graficos un tamanio y posicion sobre la ventana.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
void interfazSalas_tamYPosVentana (s_interfazSalas *interfazSalas, const s_ventana *ventana);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de salas.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y manejar la respuesta correspondientes segun el evento detectado.
 * Cada evento se desarrolla en una funcion particular manejadora de eventos, y se encuentran ordenados descendentemente (arbitrario) a la concurrencia que los utiliza el usuario.
 *
 * \param app Puntero a la estructura base de la aplicacion.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazSalas_accion (s_aplicacion *app, s_interfazSalas *interfazSalas, s_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de salas.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param app Puntero a la estructura base de la aplicacion.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazSalas_actualizar (s_aplicacion *app, s_interfazSalas *interfazSalas, s_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de salas sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de salas en la ventana.
 *
 * \param app Puntero a la estructura base de la aplicacion.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazSalas_renderizar (s_aplicacion *app, const s_interfazSalas *interfazSalas, const s_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Liberar todos los recursos graficos creados de la interfaz de salas.
 *
 * Liberar, de manera segura, todos los recursos graficos creados de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 */
void interfazSalas_liberar (s_interfazSalas *interfazSalas);



#endif // INTERFAZSALAS_H_INCLUDED



















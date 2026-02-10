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

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../../Constantes/constantes.h"
#include "../../../EstructurasDeDatos/include/listaSimple.h"
#include "../../../EstructurasDeDatos/include/listaCircular.h"
#include "../utiles.h"
#include "../estructuras.h"
#include "../logicaAplicacion.h"
#include "../recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================
   DEFINES
   ============================ */






/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_interfazSalasTextos
 * \brief Contiene todos los textos graficos de la interfaz de salas.
 */
typedef struct
{
    sfText *textoEnDesarrollo;              /**< Texto que indica que la funcionalidad se encuentra en desarrollo. */
} t_interfazSalasTextos;

/** \struct t_interfazSalasElementos
 * \brief Contiene todos los elementos graficos de la interfaz de salas.
 */
typedef struct
{
    sfRectangleShape *taparBarraEscribirMensaje;    /**< Tapar visualmente la barra para escribir mensajes. */
} t_interfazSalasElementos;

/** \struct t_interfazSalasHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de salas.
 */
typedef struct
{

} t_interfazSalasHabilitaciones;

/** \struct t_interfazSalas
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de salas.
 */
typedef struct
{
    t_interfazSalasTextos textos;
    t_interfazSalasElementos elementos;
    t_interfazSalasHabilitaciones habilitaciones;
} t_interfazSalas;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de salas.
 *
 * Establecer todas las variables graficas en NULL y luego crear cada recurso.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazSalas_inicializar (t_interfazSalas *interfazSalas);

/** \brief Configurar los recursos graficos, habilitaciones y buffers de la interfaz de salas.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y luego configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazSalas_configurar (t_interfazSalas *interfazSalas, const t_fuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de salas.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y manejar la respuesta correspondientes segun el evento detectado.
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 */
void interfazSalas_accion (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de salas.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 */
void interfazSalas_actualizar (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de salas sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de salas en la ventana.
 * Primero renderiza las vistas moviles y luego la vista de UI.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 */
void interfazSalas_renderizar (t_aplicacion *aplicacion, const t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de salas.
 *
 */
void interfazSalas_liberar (t_interfazSalas *interfazSalas);



#endif // INTERFAZSALAS_H_INCLUDED



















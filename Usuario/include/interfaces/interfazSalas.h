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

/** \enum t_interfazSalasFoco
 * \brief Contiene los estados de foco de la interfaz de salas.
 */
typedef enum
{
    IS_NINGUNO                   /**< Ningun foco establecido. */
} t_interfazSalasFoco;

/** \struct t_interfazSalas
 * \brief Estructura base que contiene los buffers, focos y une los recursos graficos de la interfaz de salas.
 */
typedef struct
{
    t_interfazSalasTextos textos;
    t_interfazSalasElementos elementos;
    t_interfazSalasFoco estadoFoco;
} t_interfazSalas;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
void interfazSalas_inicializarValoresNulos (t_interfazSalas *interfazSalas);

/** \brief Inicializar los recursos graficos de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazSalas_inicializar (t_interfazSalas *interfazSalas);

/** \brief Configurar los recursos graficos, focos y buffers de la interfaz de salas.
 *
 * Deshabilitar el estado de foco, apuntar los buffers a NULL y luego configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void interfazSalas_configurar (t_interfazSalas *interfazSalas, const t_recursosComunesContactosSalasFuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de salas.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y manejar la respuesta correspondientes segun el evento detectado.
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 */
void interfazSalas_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de salas.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 */
void interfazSalas_actualizar (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazSalas *interfazSalas);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de salas sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de salas en la ventana.
 * Primero renderiza las vistas moviles y luego la vista de UI.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 */
void interfazSalas_renderizar (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazSalas *interfazSalas);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de salas.
 *
 */
void interfazSalas_liberar (t_interfazSalas *interfazSalas);



#endif // INTERFAZSALAS_H_INCLUDED



















/**
 * \file   interfazContactos.h
 * \brief  Define las estructuras y contiene funciones estructurales y logicas relacionadas a la interfaz de contactos.
 */



#ifndef INTERFAZCONTACTOS_H_INCLUDED
#define INTERFAZCONTACTOS_H_INCLUDED



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
#include "../../../shared/estructurasDeDatos/listaCircular/include/listaCircular.h"
#include "../utiles.h"
#include "../estructuras.h"
#include "../recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================
   DEFINES
   ============================ */



/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_interfazContactosTextos
 * \brief Contiene todos los textos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfText *agendarContacto;             /**< Boton para abrir la ventana emergente de agendar contacto. */
    sfText *auxAgendarContacto;          /**< Muestra el nombre del contacto que escribe el usuario. */
    sfText *auxContactoSeleccionado;     /**< Nombre del contacto que el usuario selecciono para comunicar. */
} t_interfazContactosTextos;

/** \struct t_interfazContactosElementos
 * \brief Contiene todos los elementos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfRectangleShape *areaContactoSeleccionado;         /**< Area que encierra el nombre del contacto que el usuario selecciono para comunicar. */
    sfRectangleShape *barraEscribirAgendarContacto;     /**< Barra donde el usuario escribe el nombre del contacto. */
} t_interfazContactosElementos;

/** \enum t_interfazContactosFoco
 * \brief Contiene los estados de foco de la interfaz de contactos.
 */
typedef enum
{
    AGENDAR_CONTACTO,                     /**< Abrir/cerrar la ventana emergente de agendar contacto. */
    ESCRIBIR_AGENDAR_CONTACTO,            /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir el nombre del contacto */
    ICT_NINGUNO                           /**< Ningun foco establecido. */
} t_interfazContactosFoco;

/** \struct t_interfazContactos
 * \brief Estructura base que contiene los buffers, focos y une los recursos graficos de la interfaz de contactos.
 */
typedef struct
{
    t_interfazContactosTextos textos;
    t_interfazContactosElementos elementos;
    t_interfazContactosFoco estadoFoco;
    int idContactoSeleccionado;                     /**< ID del contacto seleccionado para comunicarse. */
} t_interfazContactos;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 */
void interfazContactos_inicializarValoresNulos (t_interfazContactos *interfazContactos);

/** \brief Inicializar los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazContactos_inicializar (t_interfazContactos *interfazContactos);

/** \brief Configurar los recursos graficos, focos y buffers de la interfaz de contactos.
 *
 * Deshabilitar el estado de foco, apuntar los buffers a NULL y configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void interfazContactos_configurar (t_interfazContactos *interfazContactos, const t_recursosComunesContactosSalasFuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de contactos.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y manejar la respuesta correspondientes segun el evento detectado.
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 */
void interfazContactos_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de contactos.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 */
void interfazContactos_actualizar (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, t_interfazContactos *interfazContactos);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de contactos sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de contactos en la ventana.
 * Primero renderiza las vistas moviles y luego la vista de UI.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 */
void interfazContactos_renderizar (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_interfazContactos *interfazContactos);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de contactos.
 *
 */
void interfazContactos_liberar (t_interfazContactos *interfazContactos);



#endif // INTERFAZCONTACTOS_H_INCLUDED




















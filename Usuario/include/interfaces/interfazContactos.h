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
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../../Constantes/constantes.h"
#include "../../../EstructurasDeDatos/include/listaCircular.h"
#include "../../../EstructurasDeDatos/include/listaSimple.h"
#include "../logicaUsuario.h"
#include "../recursosGraficosComunes/recursosComunesContactosSalas.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def HABILITAR_AGENDAR_CONTACTO
 * \brief Codigo para abrir la ventana emergente de agendar contacto.
 */
#define HABILITAR_AGENDAR_CONTACTO 1

/**
 * \def DESHABILITAR_AGENDAR_CONTACTO
 * \brief Codigo para cerrar la ventana emergente de agendar contacto.
 */
#define DESHABILITAR_AGENDAR_CONTACTO 0


/**
 * \def HABILITAR_ESCRIBIR_AGENDAR_CONTACTO
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para agendar un contacto esta habilitado.
 */
#define HABILITAR_ESCRIBIR_AGENDAR_CONTACTO 1

/**
 * \def DESHABILITAR_ESCRIBIR_AGENDAR_CONTACTO
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para agendar un contacto esta deshabilitado.
 */
#define DESHABILITAR_ESCRIBIR_AGENDAR_CONTACTO 0



/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct s_interfazContactosTexto
 * \brief Contiene todos los textos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfText *agendarContacto;        /**< Boton para abrir la ventana emergente de agendar contacto. */
    sfText *auxAgendarContacto;     /**< Muestra el nombre del contacto que escribe el usuario. */
} s_interfazContactosTexto;

/** \struct s_interfazContactosElementos
 * \brief Contiene todos los elementos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfRectangleShape *barraEscribirAgendarContacto; /**< Barra donde el usuario escribe el nombre del contacto. */
} s_interfazContactosElementos;

/** \struct s_interfazContactosHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de contactos.
 */
typedef struct
{
    bool agendarContacto;               /**< Abrir/cerrar la ventana emergente de agendar contacto. */
    bool escribirAgendarContacto;       /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir el nombre del contacto */
} s_interfazContactosHabilitaciones;

/** \struct s_interfazContactos
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de contactos.
 */
typedef struct
{
    s_interfazContactosTexto texto;
    s_interfazContactosElementos elementos;
    s_interfazContactosHabilitaciones habilitaciones;
    char bufferAgendarContacto [MAX_NOMBRE_USUARIO];    /**< Buffer donde se guarda el nombre del contacto que escribe el usuario. */
} s_interfazContactos;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de contactos.
 *
 * Establecer todas las variables graficas en NULL y luego invocar a las funciones
 * interfazContactos_inicializarTexto e interfazContactos_inicializarElementos para crear cada recurso.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazContactos_inicializar (s_interfazContactos *interfazContactos);

/** \brief Configurar los recursos graficos, habilitaciones y buffers de la interfaz de contactos.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y luego invocar a las funciones interfazContactos_configurarTexto e
 * interfazContactos_configurarElementos para configurar cada recurso.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazContactos_configurar (s_interfazContactos *interfazContactos, const s_fuentes *fuentes);

/** \brief Establecer el tamanio y la posicion sobre la ventana de cada recurso grafico de la interfaz de contactos.
 *
 * Invocar a las funciones interfazContactos_tamYPosPantallaTexto e interfazContactos_tamYPosPantallaElementos para establecer a todos los recursos
 * graficos un tamanio y posicion sobre la ventana.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
void interfazContactos_tamYPosVentana (s_interfazContactos *interfazContactos, const s_ventana *ventana);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de contactos.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y manejar la respuesta correspondientes segun el evento detectado.
 * Cada evento se desarrolla en una funcion particular manejadora de eventos, y se encuentran ordenados descendentemente (arbitrario) a la concurrencia en la que los utiliza el usuario.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazContactos_accion (s_aplicacion *aplicacion, s_interfazContactos *interfazContactos, s_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de contactos.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazContactos_actualizar (s_aplicacion *aplicacion, s_interfazContactos *interfazContactos, s_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de contactos sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de contactos en la ventana.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazContactos_renderizar (s_aplicacion *aplicacion, const s_interfazContactos *interfazContactos, const s_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Liberar todos los recursos graficos creados de la interfaz de contactos.
 *
 * Liberar, de manera segura, todos los recursos graficos creados de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 */
void interfazContactos_liberar (s_interfazContactos *interfazContactos);



/* ============================
   FUNCIONES LOGICAS
   ============================ */



void intentarSolicitudAmistad (s_aplicacion *aplicacion, s_interfazContactos *interfazContactos);



#endif // INTERFAZCONTACTOS_H_INCLUDED




















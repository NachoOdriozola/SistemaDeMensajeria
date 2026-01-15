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



/** \struct t_interfazContactosTextos
 * \brief Contiene todos los textos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfText *agendarContacto;        /**< Boton para abrir la ventana emergente de agendar contacto. */
    sfText *auxAgendarContacto;     /**< Muestra el nombre del contacto que escribe el usuario. */
} t_interfazContactosTextos;

/** \struct t_interfazContactosElementos
 * \brief Contiene todos los elementos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfRectangleShape *barraEscribirAgendarContacto; /**< Barra donde el usuario escribe el nombre del contacto. */
} t_interfazContactosElementos;

/** \struct t_interfazContactosHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de contactos.
 */
typedef struct
{
    bool agendarContacto;               /**< Abrir/cerrar la ventana emergente de agendar contacto. */
    bool escribirAgendarContacto;       /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir el nombre del contacto */
} t_interfazContactosHabilitaciones;

/** \struct t_interfazContactos
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de contactos.
 */
typedef struct
{
    t_interfazContactosTextos textos;
    t_interfazContactosElementos elementos;
    t_interfazContactosHabilitaciones habilitaciones;
    char bufferAgendarContacto [MAX_NOMBRE_USUARIO];    /**< Buffer donde se guarda el nombre del contacto que escribe el usuario. */
} t_interfazContactos;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de contactos.
 *
 * Establecer todas las variables graficas en NULL y luego crear cada recurso.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazContactos_inicializar (t_interfazContactos *interfazContactos);

/** \brief Configurar los recursos graficos, habilitaciones y buffers de la interfaz de contactos.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazContactos_configurar (t_interfazContactos *interfazContactos, const t_fuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de contactos.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y manejar la respuesta correspondientes segun el evento detectado.
 * Cada evento se desarrolla en una funcion particular manejadora de eventos.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazContactos_accion (t_aplicacion *aplicacion, t_interfazContactos *interfazContactos, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

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
void interfazContactos_actualizar (t_aplicacion *aplicacion, t_interfazContactos *interfazContactos, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de contactos sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de contactos en la ventana.
 * Primero renderiza las vistas moviles y luego la vista de UI.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void interfazContactos_renderizar (t_aplicacion *aplicacion, const t_interfazContactos *interfazContactos, const t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de contactos.
 *
 */
void interfazContactos_liberar (t_interfazContactos *interfazContactos);



/* ============================
   FUNCIONES LOGICAS
   ============================ */



void intentarSolicitudAmistad (t_aplicacion *aplicacion, t_interfazContactos *interfazContactos);



#endif // INTERFAZCONTACTOS_H_INCLUDED




















/**
 * \file  recursosComunesContactosSalas.h
 * \brief Declaracion de funciones y estructuras para recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */



#ifndef RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED



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



/* ============================
   DEFINES
   ============================ */



/**
 * \def HABILITAR_ESCRIBIR_MENSAJE
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir un mensaje esta habilitado.
 */
#define HABILITAR_ESCRIBIR_MENSAJE 1

/**
 * \def DESHABILITAR_ESCRIBIR_MENSAJE
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir un mensaje esta deshabilitado.
 */
#define DESHABILITAR_ESCRIBIR_MENSAJE 0


/**
 * \def HABILITAR_NOTIFICACIONES
 * \brief Codigo para abrir la ventana emergente de notificaciones.
 */
#define HABILITAR_NOTIFICACIONES 1

/**
 * \def DESHABILITAR_NOTIFICACIONES
 * \brief Codigo para cerrar la ventana emergente de notificaciones.
 */
#define DESHABILITAR_NOTIFICACIONES 0



/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct s_recursosComunesContactosSalasTexto
 * \brief Contiene todos los textos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfText *alertaNotificaciones;       /**< Signo de alerta cuando se recibe una nueva notificacion no leida. */
    sfText *auxEscribirMensaje;         /**< Muestra el mensaje que escribe el usuario. */
    sfText *cerrarVentanaEmergente;     /**< Cruz para cerrar la ventana emergente. */
    sfText *configuraciones;            /**< Boton para dirigirse a la interfaz de configuraciones. */
    sfText *nombreCambiarInterfaz;      /**< Muestra el nombre de la interfaz disponible para cambiar, esta ubicado sobre la solapaCambiarInterfaz. */
    sfText *nombreUsuario;              /**< Muestra el nombre del usuario. */
    sfText *notificaciones;             /**< Boton para abrir la ventana emergente de notificaciones. */
    sfText *tituloInterfaz;             /**< Titulo de la interfaz sobre la que se encuentra ubicado el usuario. */
    sfText *tituloVentanaEmergente;     /**< Titulo de la ventana emergente. */
} s_recursosComunesContactosSalasTexto;

/** \struct s_recursosComunesContactosSalasElementos
 * \brief Contiene todos los elementos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfRectangleShape *barraEscribirMensaje;     /**< Barra donde el usuario escribe el mensaje. */
    sfRectangleShape *barraSeparacionNombre;    /**< Barra decorativa que separa el panel del nombre de usuario. */
    sfRectangleShape *barraSeparacionTitulo;    /**< Barra decorativa que separa el panel del titulo de la interfaz. */
    sfRectangleShape *panelInterfaz;            /**< Panel principal de la interfaz ubicado a la izquierda de la ventana. */
    sfRectangleShape *puntoInsercion;           /**< Punto de insercion para escritura de texto. */
    sfRectangleShape *solapaCambiarInterfaz;    /**< Solapa para cambiar de interfaz encontrada en el panel. */
    sfRectangleShape *ventanaEmergente;         /**< Rectangulo de la ventana emergente. */
} s_recursosComunesContactosSalasElementos;

/** \struct s_recursosComunesContactosSalasHabilitaciones
 * \brief Contiene todas las habilitaciones comunes (compartidas) entre las interfaces de contactos y salas.
 */
typedef struct
{
    bool escribirMensaje;                       /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir un mensaje. */
    bool notificaciones;                        /**< Abrir/cerrar la ventana emergente de notificaciones. */
    bool puntoInsercion;                        /**< Activar/desactivar el punto de insercion. */
    unsigned short int contadorPuntoInsercion;  /**< Contador para determinar el tiempo en el que se activa/desactiva el punto de insercion. */
} s_recursosComunesContactosSalasHabilitaciones;

/** \struct s_recursosComunesContactosSalas
 * \brief Estructura base que contiene los buffers, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    s_recursosComunesContactosSalasTexto texto;
    s_recursosComunesContactosSalasElementos elementos;
    s_recursosComunesContactosSalasHabilitaciones habilitaciones;
    char bufferMensaje [MAX_BUFFER_MENSAJE];                /**< Buffer donde se guarda el mensaje que escribe el usuario. */
} s_recursosComunesContactosSalas;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Establecer todas las variables graficas en NULL y luego invocar a las funciones
 * recursosComunesContactosSalas_inicializarTexto e recursosComunesContactosSalas_inicializarElementos para crear cada recurso.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int recursosComunesContactosSalas_inicializar (s_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Configurar los recursos graficos, habilitaciones y buffers comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y luego invocar a las funciones recursosComunesContactosSalas_configurarTexto e
 * recursosComunesContactosSalas_configurarElementos para configurar cada recurso.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void recursosComunesContactosSalas_configurar (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_fuentes *fuentes);

/** \brief Establecer el tamanio y la posicion sobre la ventana de cada recurso grafico comun (compartido) entre las interfaces de contactos y salas
 *
 * Invocar a las funciones recursosComunesContactosSalas_tamYPosVentanaTexto e recursosComunesContactosSalas_tamYPosVentanaElementos para establecer a todos los recursos
 * graficos un tamanio y posicion sobre la ventana.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos, buffers y habilitaciones graficos comunes entre las interfaces de contactos y salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 *
 */
void recursosComunesContactosSalas_tamYPosVentana (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana);

/** \brief Renderizar los recursos graficos de texto comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalasTexto Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarTexto (sfRenderWindow *renderizado, const s_recursosComunesContactosSalasTexto *recursosComunesContactosSalasTexto);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesContactosSalasElementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const s_recursosComunesContactosSalasElementos *recursosComunesContactosSalasElementos);

/** \brief Liberar todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Liberar, de manera segura, todos los recursos graficos comunes entre las interfaces de contactos y salas creados.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_liberar (s_recursosComunesContactosSalas *recursosComunesContactosSalas);



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de escribir mensaje.
 *
 * Si se encuentra habilitado el escribir mensaje, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param ventana Puntero a la estructura que contiene los valores del tamanio de la ventana sobre la que se esta ejecutando la aplicacion.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarEscribirMensaje (s_recursosComunesContactosSalas *recursosComunesContactosSalas, const s_ventana *ventana, sfEvent eventoChar);

/** \brief Manejar el evento de enviar mensaje.
 *
 * Asignar el mensaje a la lista circular de mensajes, reestablecer el buffer de escribir mensaje al inicio y se envia el mensaje al destinatario.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarEnterEnviarMensaje (s_recursosComunesContactosSalas *recursosComunesContactosSalas, s_aplicacion *aplicacion);



#endif // RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED
























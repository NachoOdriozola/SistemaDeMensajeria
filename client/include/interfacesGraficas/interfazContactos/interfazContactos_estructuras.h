/**
 * \file   interfazContactos_estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZCONTACTOS_ESTRUCTURAS_H_INCLUDED
#define INTERFAZCONTACTOS_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../../../shared/constantes/include/constantes.h"

#include "../../utiles.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_interfazContactosVistas
 * \brief Contiene las vistas de la interfaz de contactos.
 */
typedef struct
{
    sfView *ui;                                                     /**< Vista fija que muestra la interfaz del usuario. */
    sfView *mensajes;                                         /**< Vista movil que navega sobre el historial de mensajes. */
} t_interfazContactosVistas;

/**
 * \struct t_interfazContactosFuentes
 * \brief  Contiene las fuentes graficas de textos de la interfaz de contactos.
 */
typedef struct
{
    sfFont *ui;                                                         /**< Fuente utilizada en textos de la interfaz grafica. */
    sfFont *cuerpo;                                                /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
} t_interfazContactosFuentes;

/** \struct t_interfazContactosTextos
 * \brief Contiene todos los textos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfText *auxContactoSeleccionado;                     /**< Nombre del contacto que el usuario selecciono para comunicar. */
    sfText *auxEscribirMensaje;                                /**< Muestra el mensaje que escribe el usuario. */
    sfText *botonEnviar;                                         /**< Texto encontrado dentro del boton para enviar mensaje. */
    sfText *feedbackUsuario;                                  /**< Texto que muestra informacion util sobre el estado de los procedimientos que se encuentra realizando la aplicacion. */
    sfText *informacionSeleccionChat;                   /**< Texto informativo que le indica al usuario que debe seleccionar un chat con un usuario. */
    sfText *nombreUsuario;                                     /**< Muestra el nombre del usuario. */
    sfText *tituloContactos;                                     /**< Titulo que muestra los contactos del usuario. */
} t_interfazContactosTextos;

/** \struct t_interfazContactosElementos
 * \brief Contiene todos los elementos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfRectangleShape *areaContactoSeleccionado;         /**< Area que encierra el nombre del contacto que el usuario selecciono para comunicar. */
    sfRectangleShape *areaMensajes;                             /**< Area donde se muestran los mensajes enviados y recibidos. */
    sfRectangleShape *barraEscribirMensaje;                 /**< Barra donde el usuario escribe el mensaje. */
    sfRectangleShape *botonEnviar;                               /**< Boton para enviar mensaje. */
    sfRectangleShape *carpetaDecorativaFondo1;         /**< Carpeta decorativa ubicada al fondo. */
    sfRectangleShape *carpetaDecorativaFondo2;         /**< Carpeta decorativa ubicada al fondo.*/
    sfRectangleShape *carpetaDecorativaFondo3;         /**< Carpeta decorativa ubicada al fondo.*/
    sfRectangleShape *separacionNombre;                   /**< Barra decorativa que separa el panel del nombre de usuario. */
    sfRectangleShape *separacionTitulo;                       /**< Barra decorativa que separa el panel del titulo de contactos. */
    sfRectangleShape *panelInterfaz;                            /**< Panel principal de la interfaz ubicado a la izquierda de la ventana. */
    sfRectangleShape *puntoInsercion;                         /**< Punto de insercion para escritura de texto. */
} t_interfazContactosElementos;

/** \enum t_interfazContactosFoco
 * \brief Contiene los estados de foco de la interfaz de contactos.
 */
typedef enum
{
    AREA_MENSAJES,                      /**< Indicar si el area de mensajes fue seleccionado/deseleccionado por el usuario. */
    ESCRIBIR_MENSAJE,                  /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir un mensaje. */
    ICT_NINGUNO                           /**< Ningun foco establecido. */
} t_interfazContactosFoco;

/**
 * \enum t_origenMensaje
 * \brief Indica el origen de un mensaje dentro de la aplicacion.
 */
typedef enum
{
    MENSAJE_PROPIO,                 /**< Mensaje enviado por el usuario local. */
    MENSAJE_REMOTO                /**< Mensaje recibido por otro usuario. */
} t_origenMensaje;

/**
 * \struct t_contextoMensajes
 * \brief Contexto sobre el manejo y el estado de los mensajes.
 */
typedef struct
{
    t_listaDoble mensajes;                                   /**< Lista doble que contiene los mensajes sfText. */
    char mensaje [MAX_MENSAJE];                    /**< Cadena donde se guarda el mensaje escrito por el usuario. */
    t_nodoListaDoble *ultimoMensaje;               /**< Puntero que apunta al ultimo mensaje de la lista */
} t_contextoMensajes;

/** \enum t_interfazContactosLogica
 * \brief Contiene la logica de la interfaz de contactos.
 */
typedef struct
{
    t_contextoMensajes contextoMensajes;
    t_puntoInsercion puntoInsercion;
    int idUsuarioDelChatSeleccionado;                                                               /**< ID del usuario del chat seleccionado para comunicarse. */
    char nombreUsuarioDelChatSeleccionado [MAX_NOMBRE_USUARIO];      /**< Nombre del usuario del chat seleccionado para comunicarse. */
} t_interfazContactosLogica;

/** \struct t_interfazContactos
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de contactos.
 */
typedef struct
{
    t_interfazContactosFuentes fuentes;
    t_interfazContactosTextos textos;
    t_interfazContactosElementos elementos;
    t_interfazContactosVistas vistas;
    t_interfazContactosFoco estadoFoco;
    t_interfazContactosLogica logica;
} t_interfazContactos;


#endif // INTERFAZCONTACTOS_ESTRUCTURAS_H_INCLUDED
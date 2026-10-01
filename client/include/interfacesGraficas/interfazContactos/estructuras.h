/**
 * \file   estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZCONTACTOS_ESTRUCTURAS_H_INCLUDED
#define INTERFAZCONTACTOS_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "lista_doble.h"
#include "constantes.h"

#include "logica/utiles.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct UiContactosVistas
 * \brief Contiene las vistas de la interfaz de contactos.
 */
typedef struct
{
    sfView *ui;                                                     /**< Vista fija que muestra la interfaz del usuario. */
    sfView *mensajes;                                         /**< Vista movil que navega sobre el historial de mensajes. */
} UiContactosVistas;

/**
 * \struct UiContactosFuentes
 * \brief  Contiene las fuentes graficas de textos de la interfaz de contactos.
 */
typedef struct
{
    sfFont *ui;                                                         /**< Fuente utilizada en textos de la interfaz grafica. */
    sfFont *cuerpo;                                                /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
} UiContactosFuentes;

/** \struct UiContactosTextos
 * \brief Contiene todos los textos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfText *auxContactoSeleccionado;                     /**< Nombre del contacto que el usuario selecciono para comunicar. */
    sfText *auxEscribirMensaje;                               /**< Muestra el mensaje que escribe el usuario. */
    sfText *botonEnviar;                                          /**< Texto encontrado dentro del boton para enviar mensaje. */
    sfText *feedbackUsuario;                                  /**< Texto que muestra informacion util sobre el EstadoSolicitud de los procedimientos que se encuentra realizando la aplicacion. */
    sfText *informacionSeleccionChat;                   /**< Texto informativo que le indica al usuario que debe seleccionar un chat con un usuario. */
    sfText *nombreUsuario;                                     /**< Muestra el nombre del usuario. */
    sfText *tituloContactos;                                     /**< Titulo que muestra los contactos del usuario. */
} UiContactosTextos;

/** \struct UiContactosElementos
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
} UiContactosElementos;

/** \enum UiContactosFoco
 * \brief Contiene los EstadoSolicituds de foco de la interfaz de contactos.
 */
typedef enum
{
    AREA_MENSAJES,                      /**< Indicar si el area de mensajes fue seleccionado/deseleccionado por el usuario. */
    ESCRIBIR_MENSAJE,                  /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir un mensaje. */
    UI_CONTACTOS_NINGUNO                           /**< Ningun foco establecido. */
} UiContactosFoco;

/**
 * \enum OrigenMensaje
 * \brief Indica el origen de un mensaje dentro de la aplicacion.
 */
typedef enum
{
    MENSAJE_PROPIO,                 /**< Mensaje enviado por el usuario local. */
    MENSAJE_REMOTO                /**< Mensaje recibido por otro usuario. */
} OrigenMensaje;

/**
 * \struct ContextoMensajes
 * \brief Contexto sobre el manejo y el EstadoSolicitud de los mensajes.
 */
typedef struct
{
    ListaDoble mensajes;                                   /**< Lista doble que contiene los mensajes sfText. */
    char mensaje [MAX_MENSAJE];                    /**< Cadena donde se guarda el mensaje escrito por el usuario. */
    NodoListaDoble *ultimoMensaje;               /**< Puntero que apunta al ultimo mensaje de la lista */
} ContextoMensajes;

/** \enum UiContactosLogica
 * \brief Contiene la logica de la interfaz de contactos.
 */
typedef struct
{
    ContextoMensajes contextoMensajes;
    PuntoInsercion puntoInsercion;
    int idUsuarioChatSeleccionado;                                                               /**< ID del usuario del chat seleccionado para comunicarse. */
    char nombreUsuarioDelChatSeleccionado [MAX_NOMBRE_USUARIO];      /**< Nombre del usuario del chat seleccionado para comunicarse. */
    TextoDeCarga textoDeCarga;
} UiContactosLogica;

/** \struct UiContactos
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de contactos.
 */
typedef struct
{
    UiContactosFuentes fuentes;
    UiContactosTextos textos;
    UiContactosElementos elementos;
    UiContactosVistas vistas;
    UiContactosFoco foco;
    UiContactosLogica logica;
} UiContactos;


#endif // INTERFAZCONTACTOS_ESTRUCTURAS_H_INCLUDED
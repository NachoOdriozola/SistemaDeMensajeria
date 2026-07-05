/**
 * \file  recursosComunesContactosSalas_estructuras.h
 * \brief Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef RECURSOSCOMUNESCONTACTOSSALAS_ESTRUCTURAS_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../../shared/constantes/include/constantes.h"
#include "../../../../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../../utiles.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


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
 * \struct t_recursosComunesContactosSalasFuentes
 * \brief  Contiene las fuentes graficas de textos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfFont *ui;                                                         /**< Fuente utilizada en textos de la interfaz grafica. */
    sfFont *cuerpo;                                                /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
} t_recursosComunesContactosSalasFuentes;

/** \struct t_recursosComunesContactosSalasTextos
 * \brief Contiene todos los textos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfText *auxEscribirMensaje;                             /**< Muestra el mensaje que escribe el usuario. */
    sfText *proximaInterfaz;                                  /**< Muestra el nombre de la interfaz disponible para cambiar, esta ubicado sobre la solapaCambiarInterfaz. */
    sfText *nombreUsuario;                                  /**< Muestra el nombre del usuario. */
    sfText *textoBotonEnviar;                               /**< Texto encontrado dentro del boton para enviar mensaje. */
    sfText *tituloInterfaz;                                      /**< Titulo de la interfaz sobre la que se encuentra ubicado el usuario. */
} t_recursosComunesContactosSalasTextos;

/** \struct t_recursosComunesContactosSalasElementos
 * \brief Contiene todos los elementos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfRectangleShape *areaMensajes;                             /**< Area donde se muestran los mensajes enviados y recibidos. */
    sfRectangleShape *barraEscribirMensaje;                 /**< Barra donde el usuario escribe el mensaje. */
    sfRectangleShape *botonEnviar;                               /**< Boton para enviar mensaje. */
    sfRectangleShape *carpetaDecorativaFondo1;         /**< Carpeta decorativa ubicada al fondo.*/
    sfRectangleShape *carpetaDecorativaFondo2;         /**< Carpeta decorativa ubicada al fondo.*/
    sfCircleShape *ojalilloArriba;                                     /**< Ojalillo decorativo superior. */
    sfCircleShape *ojalilloAbajo;                                     /**< Ojalillo decorativo inferior. */
    sfCircleShape *ojalilloSelecInterfaz;                          /**< Ojalillo decorativo situado en la carpeta para cambiar de interfaz. */
    sfRectangleShape *separacionNombre;                   /**< Barra decorativa que separa el panel del nombre de usuario. */
    sfRectangleShape *separacionTitulo;                       /**< Barra decorativa que separa el panel del titulo de la interfaz. */
    sfRectangleShape *panelInterfaz;                            /**< Panel principal de la interfaz ubicado a la izquierda de la ventana. */
    sfRectangleShape *puntoInsercion;                         /**< Punto de insercion para escritura de texto. */
    sfRectangleShape *solapaCambiarInterfaz;             /**< Solapa para cambiar de interfaz encontrada en el panel. */
} t_recursosComunesContactosSalasElementos;

/** \struct t_recursosComunesContactosSalasVistas
 * \brief Contiene todas las vistas comunes (compartidas) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfView *ui;                                                     /**< Vista fija que muestra la interfaz del usuario. */
    sfView *mensajes;                                         /**< Vista movil que navega sobre el historial de mensajes. */
} t_recursosComunesContactosSalasVistas;

/** \enum t_recursosComunesContactosSalasFoco
 * \brief Contiene los estados de foco comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef enum
{
    AREA_MENSAJES,                                      /**< Indicar si el area de mensajes fue seleccionado/deseleccionado por el usuario. */
    ESCRIBIR_MENSAJE,                                  /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir un mensaje. */
    RCCS_NINGUNO                                       /**< Ningun foco establecido. */
} t_recursosComunesContactosSalasFoco;

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

/**
 * \struct t_recursosComunesContactosSalasLogica
 * \brief Contiene la logica comun (compartida) entre las interfaces de contactos y salas.
 */
typedef struct
{
    t_contextoMensajes contextoMensajes;
    t_puntoInsercion puntoInsercion;
} t_recursosComunesContactosSalasLogica;

/** \struct t_recursosComunesContactosSalas
 * \brief Estructura base que contiene la logica y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    t_recursosComunesContactosSalasFuentes fuentes;
    t_recursosComunesContactosSalasTextos textos;
    t_recursosComunesContactosSalasElementos elementos;
    t_recursosComunesContactosSalasVistas vistas;
    t_recursosComunesContactosSalasFoco estadoFoco;
    t_recursosComunesContactosSalasLogica logica;
} t_recursosComunesContactosSalas;


#endif // RECURSOSCOMUNESCONTACTOSSALAS_ESTRUCTURAS_H_INCLUDED
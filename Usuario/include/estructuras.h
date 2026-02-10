/**
 * \file   estructuras.h
 * \brief  Define las estructuras principales de la aplicacion.
 */



#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../Constantes/constantes.h"
#include "../../EstructurasDeDatos/include/listaSimple.h"
#include "../../EstructurasDeDatos/include/listaCircular.h"



/* ============================
   ESTRUCTURAS
   ============================ */



/**
 * \struct t_usuario
 * \brief  Representa un usuario.
 */
typedef struct
{
    int id;                                     /**< Identificador correspondiente del usuario. */
    char nombre [MAX_NOMBRE_USUARIO];           /**< Nombre correspondiente del usuario. */
    unsigned short int interfazActual;          /**< Interfaz sobre la cual se encuentra ubicado actualmente. */
} t_usuario;

/**
 * \struct t_fuentes
 * \brief  Estructura que contiene las fuentes graficas para los textos.
 */
typedef struct
{
    sfFont *ui;             /**< Fuente utilizada en textos de la interfaz grafica. */
    sfFont *cuerpo;         /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
} t_fuentes;

/**
 * \struct t_mensajes
 * \brief
 */
typedef struct
{
    t_listaCircular listaMensajes;      /**< Lista circular de mensajes. */
    t_nodo *primerMensaje;              /**< Puntero al primer mensaje de la lista circular de mensajes. */
    t_nodo *ultimoMensaje;              /**< Puntero al ultimo mensaje de la lista circular de mensajes. */
    t_fuentes fuentes;
} t_mensajes;

/**
 * \struct t_aplicacion
 * \brief  Estructura base de la aplicacion
 */
typedef struct
{
    sfRenderWindow *renderizado;        /**< Renderizado de la ventana. */
    SOCKET sock;                        /**< Socket del usuario. */
    t_usuario usuario;
    t_mensajes mensajes;
    t_listaSimple listaNotificaciones;  /**< Lista simple de notificaciones. */
} t_aplicacion;

/**
 * \struct t_notificacion
 * \brief  Estructura que contiene los elementos de una notificacion.
 * \note Estructura NO ACTIVA en el Incremento 1.
 */
typedef struct
{
    sfRectangleShape *recuadro;
    sfRectangleShape *botonAceptar;
    sfRectangleShape *botonRechazar;
    sfText *textoNotificacion;
    sfText *textoBotonAceptar;
    sfText *textoBotonRechazar;
} t_notificacion;

typedef enum
{
    MENSAJE_PROPIO,
    MENSAJE_REMOTO
} t_origenMensaje;



#endif // ESTRUCTURAS_H_INCLUDED


























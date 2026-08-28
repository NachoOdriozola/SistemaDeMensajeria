/**
 * \file   estructuras.h
 * \brief  Define las estructuras fundamentales de la aplicacion.
 */


#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdbool.h>

#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "constantes.h"
#include "sockets.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \enum t_interfaz
 * \brief Indica las interfaces graficas de la aplicacion.
 */
typedef enum
{
    INTERFAZ_AUTENTICACION,
    INTERFAZ_REGISTRO,
    INTERFAZ_CONTACTOS,
    INTERFAZ_SALAS,
    INTERFAZ_CONFIG
} t_interfaz;

/**
 * \struct t_usuario
 * \brief Representa un usuario.
 */
typedef struct
{
    int id;                                                                     /**< Identificador correspondiente del usuario. */
    char nombre [MAX_NOMBRE_USUARIO];            /**< Nombre correspondiente del usuario. */
} t_usuario;

/**
 * \struct t_contextoAplicacion
 * \brief Contexto (estados y recursos) global de la aplicacion.
 */
typedef struct
{
    sfRenderWindow *renderizado;         /**< Renderizado de la ventana. */
    t_socket sock;                                     /**< Socket del usuario. */
    t_usuario usuario;
    t_interfaz interfazActual;                                      /**< Interfaz sobre la cual se encuentra posicionado actualmente. */
    bool solicitudEnCurso;                       /**< Informar si hay una solicitud enviada en curso para no enviar otra. */
} t_contextoAplicacion;


#endif // ESTRUCTURAS_H_INCLUDED

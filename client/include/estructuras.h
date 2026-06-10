/**
 * \file   estructuras.h
 * \brief  Define las estructuras principales de la aplicacion.
 */



#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */



#include <stdlib.h>
#include <stdbool.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "../../external/csfml/include/SFML/System.h"
#include "../../external/csfml/include/SFML/Window.h"
#include "../../external/csfml/include/SFML/Graphics.h"

#include "../../shared/constantes/include/constantes.h"



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
    int id;                                     /**< Identificador correspondiente del usuario. */
    char nombre [MAX_NOMBRE_USUARIO];           /**< Nombre correspondiente del usuario. */
    t_interfaz interfazActual;                  /**< Interfaz sobre la cual se encuentra ubicado actualmente. */
} t_usuario;

/**
 * \struct t_contextoAplicacion
 * \brief Contexto (estados y recursos) global de la aplicacion.
 */
typedef struct
{
    bool estadoWinsock;                 /**< Estado de Winsock API */
    sfRenderWindow *renderizado;        /**< Renderizado de la ventana. */
    SOCKET sock;                        /**< Socket del usuario. */
    t_usuario usuario;
} t_contextoAplicacion;



#endif // ESTRUCTURAS_H_INCLUDED


























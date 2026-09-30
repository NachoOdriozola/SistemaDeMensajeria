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

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"
#include "sockets.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \enum IdInterfaz
 * \brief Identifica cada interfaz grafica de la aplicacion.
 */
typedef enum
{
    INTERFAZ_AUTENTICACION,
    INTERFAZ_REGISTRO,
    INTERFAZ_CONTACTOS
} IdInterfaz;

/**
 * \struct Usuario
 * \brief Representa un usuario.
 */
typedef struct
{
    int id;                                                                     /**< Identificador correspondiente del usuario. */
    char nombre [MAX_NOMBRE_USUARIO];            /**< Nombre correspondiente del usuario. */
} Usuario;

/**
 * \struct ContextoAplicacion
 * \brief Contexto (EstadoSolicituds y recursos) global de la aplicacion.
 */
typedef struct
{
    sfRenderWindow *renderizado;         /**< Renderizado de la ventana. */
    Socket sock;                                     /**< Socket del usuario. */
    Usuario usuario;
    IdInterfaz interfazActual;                     /**< Interfaz sobre la cual se encuentra posicionado actualmente. */
    bool solicitudEnCurso;                       /**< Informar si hay una solicitud enviada en curso para no enviar otra. */
} ContextoAplicacion;


#endif // ESTRUCTURAS_H_INCLUDED

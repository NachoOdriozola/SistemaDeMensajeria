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

#include "../recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_interfazContactosTextos
 * \brief Contiene todos los textos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfText *auxContactoSeleccionado;            /**< Nombre del contacto que el usuario selecciono para comunicar. */
} t_interfazContactosTextos;

/** \struct t_interfazContactosElementos
 * \brief Contiene todos los elementos graficos de la interfaz de contactos.
 */
typedef struct
{
    sfRectangleShape *areaContactoSeleccionado;         /**< Area que encierra el nombre del contacto que el usuario selecciono para comunicar. */
} t_interfazContactosElementos;

/** \enum t_interfazContactosFoco
 * \brief Contiene los estados de foco de la interfaz de contactos.
 */
typedef enum
{
    ICT_NINGUNO                           /**< Ningun foco establecido. */
} t_interfazContactosFoco;

/** \enum t_interfazContactosLogica
 * \brief Contiene la logica de la interfaz de contactos.
 */
typedef struct
{
    int idUsuarioDelChatSeleccionado;                                                               /**< ID del usuario del chat seleccionado para comunicarse. */
    char nombreUsuarioDelChatSeleccionado [MAX_NOMBRE_USUARIO];      /**< Nombre del usuario del chat seleccionado para comunicarse. */
} t_interfazContactosLogica;

/** \struct t_interfazContactos
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de contactos.
 */
typedef struct
{
    t_interfazContactosTextos textos;
    t_interfazContactosElementos elementos;
    t_interfazContactosFoco estadoFoco;
    t_interfazContactosLogica logica;
    t_recursosComunesContactosSalas *recursosComunesContactosSalas;
} t_interfazContactos;


#endif // INTERFAZCONTACTOS_ESTRUCTURAS_H_INCLUDED
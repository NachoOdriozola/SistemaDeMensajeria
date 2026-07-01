/**
 * \file   interfazSalas_estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZSALAS_ESTRUCTURAS_H_INCLUDED
#define INTERFAZSALAS_ESTRUCTURAS_H_INCLUDED


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


/** \struct t_interfazSalasTextos
 * \brief Contiene todos los textos graficos de la interfaz de salas.
 */
typedef struct
{
    sfText *textoEnDesarrollo;              /**< Texto que indica que la funcionalidad se encuentra en desarrollo. */
} t_interfazSalasTextos;

/** \struct t_interfazSalasElementos
 * \brief Contiene todos los elementos graficos de la interfaz de salas.
 */
typedef struct
{
    sfRectangleShape *taparBarraEscribirMensaje;            /**< Tapar visualmente la barra para escribir mensajes. */
} t_interfazSalasElementos;

/** \enum t_interfazSalasFoco
 * \brief Contiene los estados de foco de la interfaz de salas.
 */
typedef enum
{
    IS_NINGUNO                   /**< Ningun foco establecido. */
} t_interfazSalasFoco;

/** \struct t_interfazSalas
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de salas.
 */
typedef struct
{
    t_interfazSalasTextos textos;
    t_interfazSalasElementos elementos;
    t_interfazSalasFoco estadoFoco;
    t_recursosComunesContactosSalas *recursosComunesContactosSalas;
} t_interfazSalas;


#endif // INTERFAZSALAS_ESTRUCTURAS_H_INCLUDED
/**
 * \file   interfazConfig_estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZCONFIG_ESTRUCTURAS_H_INCLUDED
#define INTERFAZCONFIG_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_interfazConfigFuentes
 * \brief Contiene las fuentes graficas de la interfaz de configuraciones.
 */
typedef struct
{
    sfFont *ui;                         /**< Fuente utilizada en textos de la interfaz grafica. */
} t_interfazConfigFuentes;

/** \struct t_interfazConfigTextos
 * \brief Contiene todos los textos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    sfText *textoConfig;
} t_interfazConfigTextos;

/** \struct t_interfazConfigElementos
 * \brief Contiene todos los elementos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    sfRectangleShape *rectanguloVolver;
} t_interfazConfigElementos;

/** \enum t_interfazConfigFoco
 * \brief Contiene todos los estados de foco de la interfaz de configuraciones.
 */
typedef enum
{
    ICF_NINGUNO
} t_interfazConfigFoco;

/** \struct t_interfazConfig
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de configuraciones.
 */
typedef struct
{
    t_interfazConfigFuentes fuentes;
    t_interfazConfigTextos textos;
    t_interfazConfigElementos elementos;
    t_interfazConfigFoco estadoFoco;
} t_interfazConfig;


#endif // INTERFAZCONFIG_ESTRUCTURAS_H_INCLUDED
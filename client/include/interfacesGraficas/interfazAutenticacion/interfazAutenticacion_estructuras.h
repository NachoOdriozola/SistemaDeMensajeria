/**
 * \file   interfazAutenticacion_estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZAUTENTICACION_ESTRUCTURAS_H_INCLUDED
#define INTERFAZAUTENTICACION_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */

   
/** \struct t_interfazAutenticacionTextos
 * \brief Contiene todos los textos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   sfText *aux;
} t_interfazAutenticacionTextos;

/** \struct t_interfazAutenticacionElementos
 * \brief Contiene todos los elementos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   sfRectangleShape *aux;
} t_interfazAutenticacionElementos;

/** \enum t_interfazAutenticacionFoco
 * \brief Contiene todos los estados de foco de la interfaz de autenticacion.
 */
typedef enum
{
   IA_NINGUNO                                /**< Ningun foco establecido. */
} t_interfazAutenticacionFoco;

/** \struct t_interfazAutenticacion
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   t_interfazAutenticacionTextos textos;
   t_interfazAutenticacionElementos elementos;
   t_interfazAutenticacionFoco estadoFoco;
   t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro;
} t_interfazAutenticacion;


#endif // INTERFAZAUTENTICACION_ESTRUCTURAS_H_INCLUDED


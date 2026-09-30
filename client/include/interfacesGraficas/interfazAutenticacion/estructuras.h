/**
 * \file   estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZAUTENTICACION_ESTRUCTURAS_H_INCLUDED
#define INTERFAZAUTENTICACION_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct UiAutenticacionTextos
 * \brief Contiene todos los textos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   sfText *aux;                                 /**< Declaracion de variable unicamente para que sea posible la creacion de la estructura. */
} UiAutenticacionTextos;

/** \struct UiAutenticacionElementos
 * \brief Contiene todos los elementos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   sfRectangleShape *aux;                     /**< Declaracion de variable unicamente para que sea posible la creacion de la estructura. */
} UiAutenticacionElementos;

/** \enum UiAutenticacionFoco
 * \brief Contiene todos los EstadoSolicituds de foco de la interfaz de autenticacion.
 */
typedef enum
{
   UI_AUTENTICACION_NINGUNO                                /**< Ningun foco establecido. */
} UiAutenticacionFoco;

/** \struct UiAutenticacion
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de autenticacion.
 */
typedef struct
{
   UiAutenticacionTextos textos;
   UiAutenticacionElementos elementos;
   UiAutenticacionFoco foco;
   UiAcceso *uiAcceso;
} UiAutenticacion;


#endif // INTERFAZAUTENTICACION_ESTRUCTURAS_H_INCLUDED


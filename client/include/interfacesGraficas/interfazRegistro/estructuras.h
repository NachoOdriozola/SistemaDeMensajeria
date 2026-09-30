/**
 * \file   estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZREGISTRO_ESTRUCTURAS_H_INCLUDED
#define INTERFAZREGISTRO_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct UiRegistroTextos
 * \brief Contiene todos los textos graficos de la interfaz de registro.
 */
typedef struct
{
    sfText *auxEscribirCorreo;                          /**< Muestra el correo electronico que escribe el usuario. */
    sfText *ingresarCorreo;                              /**< Indica al usuario donde escribir su correo electronico. */
    sfText *informacionContrasenia;               /**< Texto informativo sobre la contrasenia. */
    sfText *informacionNombre;                    /**< Texto informativo sobre el nombre. */
} UiRegistroTextos;

/** \struct UiRegistroElementos
 * \brief Contiene todos los elementos graficos de la interfaz de registro.
 */
typedef struct
{
    sfRectangleShape *barraEscribirCorreo;          /**< Barra donde el usuario escribe su correo electronico. */
} UiRegistroElementos;

/** \enum UiRegistroFoco
 * \brief Contiene todos los EstadoSolicituds de foco de la interfaz de registro.
 */
typedef enum
{
    ESCRIBIR_CORREO,                /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su correo electronico. */
    UI_REGISTRO_NINGUNO                         /**< Ningun foco establecido. */
} UiRegistroFoco;

/** \enum UiRegistroLogica
 * \brief Contiene la logica de la interfaz de registro.
 */
typedef struct
{
    char correoElectronico [MAX_CORREO_ELECTRONICO];         /**< Cadena donde se guarda el correo electronico que escribe el usuario. */
} UiRegistroLogica;

/** \struct UiRegistro
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de registro.
 */
typedef struct
{
    UiRegistroTextos textos;
    UiRegistroElementos elementos;
    UiRegistroFoco foco;
    UiRegistroLogica logica;
    UiAcceso *uiAcceso;
} UiRegistro;


#endif // INTERFAZREGISTRO_ESTRUCTURAS_H_INCLUDED
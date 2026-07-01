/**
 * \file   interfazRegistro_estructuras.h
 * \brief  Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef INTERFAZREGISTRO_ESTRUCTURAS_H_INCLUDED
#define INTERFAZREGISTRO_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/constantes/include/constantes.h"

#include "../recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_interfazRegistroTextos
 * \brief Contiene todos los textos graficos de la interfaz de registro.
 */
typedef struct
{
    sfText *auxEscribirCorreo;                          /**< Muestra el correo electronico que escribe el usuario. */
    sfText *ingresarCorreo;                              /**< Indica al usuario donde escribir su correo electronico. */
    sfText *textoInformativoContrasenia;        /**< Texto informativo sobre la contrasenia. */
    sfText *textoInformativoNombre;             /**< Texto informativo sobre el nombre. */
} t_interfazRegistroTextos;

/** \struct t_interfazRegistroElementos
 * \brief Contiene todos los elementos graficos de la interfaz de registro.
 */
typedef struct
{
    sfRectangleShape *barraEscribirCorreo;          /**< Barra donde el usuario escribe su correo electronico. */
} t_interfazRegistroElementos;

/** \enum t_interfazRegistroFoco
 * \brief Contiene todos los estados de foco de la interfaz de registro.
 */
typedef enum
{
    ESCRIBIR_CORREO,                /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su correo electronico. */
    IR_NINGUNO                         /**< Ningun foco establecido. */
} t_interfazRegistroFoco;

/** \enum t_interfazRegistroLogica
 * \brief Contiene la logica de la interfaz de registro.
 */
typedef struct
{
    char correoElectronico [MAX_CORREO_ELECTRONICO];         /**< Cadena donde se guarda el correo electronico que escribe el usuario. */
} t_interfazRegistroLogica;

/** \struct t_interfazRegistro
 * \brief Estructura base que contiene la logica y une los recursos graficos de la interfaz de registro.
 */
typedef struct
{
    t_interfazRegistroTextos textos;
    t_interfazRegistroElementos elementos;
    t_interfazRegistroFoco estadoFoco;
    t_interfazRegistroLogica logica;
    t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro;
} t_interfazRegistro;


#endif // INTERFAZREGISTRO_ESTRUCTURAS_H_INCLUDED
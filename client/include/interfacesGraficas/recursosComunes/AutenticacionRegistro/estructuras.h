/**
 * \file   estructuras.h
 * \brief Define las estructuras de los recursos graficos y logicos de la interfaz.
 */


#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_ESTRUCTURAS_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_ESTRUCTURAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \struct t_recursosComunesAutenticacionRegistroFuentes
 * \brief  Contiene las fuentes graficas de textos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfFont *cuerpo;                                                           /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
    sfFont *ui;                                                                   /**< Fuente utilizada en textos de la interfaz grafica. */
} t_recursosComunesAutenticacionRegistroFuentes;

/** \struct t_recursosComunesAutenticacionRegistroTextos
 * \brief Contiene todos los textos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfText *auxEscribirContrasenia;                                /**< Muestra la contrasenia que escribe el usuario. */
    sfText *auxEscribirNombre;                                      /**< Muestra el nombre que escribe el usuario. */
    sfText *botonIngresar;                                            /**< Texto encontrado dentro del boton para ingresar usuario. */
    sfText *cambiarInterfaz;                                          /**< Texto interrogativo para cambiar de interfaz. */
    sfText *feedbackUsuario;                                        /**< Texto que muestra informacion util sobre el estado de los procedimientos que se encuentra realizando la aplicacion. */
    sfText *ingresarContrasenia;                                    /**< Indica al usuario donde escribir su contrasenia. */
    sfText *ingresarNombre;                                         /**< Indica al usuario donde escribir su nombre. */
    sfText *tituloInterfaz;                                              /**< Titulo de la interfaz sobre la que se encuentra ubicado el usuario. */
} t_recursosComunesAutenticacionRegistroTextos;

/** \struct t_recursosComunesAutenticacionRegistroElementos
 * \brief Contiene todos los elementos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfRectangleShape *barraEscribirContrasenia;                  /**< Barra donde el usuario escribe su contrasenia. */
    sfRectangleShape *barraEscribirNombre;                        /**< Barra donde el usuario escribe su nombre. */
    sfRectangleShape *botonIngresar;                                  /**< Boton para ingresar usuario. */
    sfRectangleShape *puntoInsercion;                                /**< Punto de insercion para escritura de texto. */
    sfRectangleShape *subrayadoTitulo;                               /**< Barra decorativa para subrayar el titulo de la interfaz. */
} t_recursosComunesAutenticacionRegistroElementos;

/** \struct t_recursosComunesAutenticacionRegistroVistas
 * \brief Contiene todas las vistas comunes (compartidas) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfView *ui;                                                                     /**< Vista fija que muestra la interfaz del usuario. */
} t_recursosComunesAutenticacionRegistroVistas;

/** \enum t_recursosComunesAutenticacionRegistroFoco
 * \brief Contiene todos los estados de foco comunes (compartidas) entre las interfaces de autenticacion y registro.
 */
typedef enum
{
    ESCRIBIR_CONTRASENIA,                                           /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su contrasenia. */
    ESCRIBIR_NOMBRE,                                                    /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su nombre. */
    RCAR_NINGUNO                                                        /**< Ningun foco establecido. */
} t_recursosComunesAutenticacionRegistroFoco;

/** \enum t_recursosComunesAutenticacionRegistroLogica
 * \brief Contiene la logica comun (compartida) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];               /**< Cadena donde se guarda el nombre que escribe el usuario. */
    char contrasenia [MAX_CONTRASENIA];                             /**< Cadena donde se guarda la contrasenia que escribe el usuario. */
    t_puntoInsercion puntoInsercion;
} t_recursosComunesAutenticacionRegistroLogica;

/** \struct t_recursosComunesAutenticacionRegistro
 * \brief Estructura base que contiene la logica y une todos los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    t_recursosComunesAutenticacionRegistroFuentes fuentes;
    t_recursosComunesAutenticacionRegistroTextos textos;
    t_recursosComunesAutenticacionRegistroElementos elementos;
    t_recursosComunesAutenticacionRegistroVistas vistas;
    t_recursosComunesAutenticacionRegistroFoco estadoFoco;
    t_recursosComunesAutenticacionRegistroLogica logica;
} t_recursosComunesAutenticacionRegistro;


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_ESTRUCTURAS_H_INCLUDED
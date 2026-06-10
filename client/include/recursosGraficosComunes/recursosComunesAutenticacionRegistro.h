/**
 * \file   recursosComunesAutenticacionRegistro.h
 * \brief Declaracion de funciones y estructuras para recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */



#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../external/csfml/include/SFML/System.h"
#include "../../external/csfml/include/SFML/Window.h"
#include "../../external/csfml/include/SFML/Graphics.h"

#include "../../shared/constantes/include/constantes.h"
#include "../utiles.h"



/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */



/**
 * \def INPUT_VALIDO
 * \brief Indicador que el input es valido.
 */
#define INPUT_VALIDO 0

/**
 * \def INPUT_INVALIDO
 * \brief Indicador que el input es invalido.
 */
#define INPUT_INVALIDO 1



/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */



/**
 * \struct t_recursosComunesAutenticacionRegistroFuentes
 * \brief  Contiene las fuentes graficas de textos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfFont *cuerpo;         /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
    sfFont *ui;             /**< Fuente utilizada en textos de la interfaz grafica. */
} t_recursosComunesAutenticacionRegistroFuentes;

/** \struct t_inputContrasenia
 * \brief Contexto sobre el input de la contrasenia del usuario.
 */
typedef struct
{
    sfText *auxEscribirContrasenia;     /**< Muestra la contrasenia que escribe el usuario. */
    bool validez;                       /**< Indicar si el ingreso es valido o invalido. */
} t_inputContrasenia;

/** \struct t_inputNombre
 * \brief Contexto sobre el input del nombre de usuario.
 */
typedef struct
{
    sfText *auxEscribirNombre;          /**< Muestra el nombre que escribe el usuario. */
    t_habilitacion validez;             /**< Indicar si el ingreso es valido o invalido. */
} t_inputNombre;

/** \struct t_recursosComunesAutenticacionRegistroTextos
 * \brief Contiene todos los textos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    t_inputContrasenia inputContrasenia;
    t_inputNombre inputNombre;
    sfText *ingresarContrasenia;        /**< Indica al usuario donde escribir su contrasenia. */
    sfText *ingresarNombre;             /**< Indica al usuario donde escribir su nombre. */
    sfText *ingresoIncorrecto;          /**< Mensaje de error al ingresar incorrectamente el usuario. */
    sfText *textoBotonIngresar;         /**< Texto encontrado dentro del boton para ingresar usuario. */
    sfText *textoCambiarInterfaz;       /**< Texto interrogativo para cambiar de interfaz. */
    sfText *tituloInterfaz;             /**< Titulo de la interfaz sobre la que se encuentra ubicado el usuario. */
} t_recursosComunesAutenticacionRegistroTextos;

/** \struct t_recursosComunesAutenticacionRegistroElementos
 * \brief Contiene todos los elementos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfRectangleShape *barraEscribirContrasenia;         /**< Barra donde el usuario escribe su contrasenia. */
    sfRectangleShape *barraEscribirNombre;              /**< Barra donde el usuario escribe su nombre. */
    sfRectangleShape *botonIngresar;                    /**< Boton para ingresar usuario. */
    sfRectangleShape *puntoInsercion;                   /**< Punto de insercion para escritura de texto. */
    sfRectangleShape *subrayadoTitulo;                  /**< Barra decorativa para subrayar el titulo de la interfaz. */
} t_recursosComunesAutenticacionRegistroElementos;

/** \enum t_recursosComunesAutenticacionRegistroFoco
 * \brief Contiene todos los estados de foco comunes (compartidas) entre las interfaces de autenticacion y registro.
 */
typedef enum
{
    ESCRIBIR_CONTRASENIA,                  /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su contrasenia. */
    ESCRIBIR_NOMBRE,                       /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su nombre. */
    RCAR_NINGUNO                           /**< Ningun foco establecido. */
} t_recursosComunesAutenticacionRegistroFoco;

/** \struct t_recursosComunesAutenticacionRegistro
 * \brief Estructura base que contiene los buffers, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    t_recursosComunesAutenticacionRegistroFuentes fuentes;
    t_recursosComunesAutenticacionRegistroTextos textos;
    t_recursosComunesAutenticacionRegistroElementos elementos;
    t_recursosComunesAutenticacionRegistroFoco estadoFoco;
    t_habilitacion ingreso;                                                                         /**< Habilitar/deshabilitar la posibilidad de ingreso de usuario. */
    char bufferNombre [MAX_NOMBRE_USUARIO];                                 /**< Buffer donde se guarda el nombre que escribe el usuario. */
    char bufferContrasenia [MAX_CONTRASENIA_USUARIO];                  /**< Buffer donde se guarda la contrasenia que escribe el usuario. */
    t_puntoInsercion puntoInsercion;
} t_recursosComunesAutenticacionRegistro;



/* ============================================================================================================================================
   FUNCIONES ESTRUCTURALES
   ============================================================================================================================================ */



/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_inicializarValoresNulos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Inicializar los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int recursosComunesAutenticacionRegistro_inicializar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico comun (compartido) entre las interfaces de autenticacion y registro.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_configurar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Renderizar los recursos graficos de texto comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroTextos *textos);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroElementos *elementos);

/** \brief Liberar, de manera segura, todos los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_liberar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================================================================================================================================
   FUNCIONES LOGICAS
   ============================================================================================================================================ */



/** \brief Activar la interfaz de autenticacion.
 *
 * Modificar los estados de foco, los buffers, resetear el punto de insercion y los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de autenticacion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 */
void activarInterfazAutenticacion (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Activar la interfaz de registro.
 *
 * Modificar los estados de foco, los buffers, resetear el punto de insercion y los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 *
 */
void activarInterfazRegistro (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED
































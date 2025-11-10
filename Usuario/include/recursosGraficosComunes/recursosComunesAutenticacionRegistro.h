/**
 * \file   recursosComunesAutenticacionRegistro.h
 * \brief Declaracion de funciones y estructuras para recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */



#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"

#include "../../../Constantes/constantes.h"
#include "../logicaUsuario.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def MAX_INGRESO_NOMBRE
 * \brief Cantidad maxima de caracteres que puede ingresar el usuario para escribir su nombre.
 */
#define MAX_INGRESO_NOMBRE 31

/**
 * \def MAX_INGRESO_CONTRASENIA
 * \brief Cantidad maxima de caracteres que puede ingresar el usuario para escribir su contrasenia.
 */
#define MAX_INGRESO_CONTRASENIA 36


/**
 * \def HABILITAR_ESCRIBIR_NOMBRE
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir su nombre esta habilitado.
 */
#define HABILITAR_ESCRIBIR_NOMBRE 1

/**
 * \def DESHABILITAR_ESCRIBIR_NOMBRE
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir su nombre esta deshabilitado.
 */
#define DESHABILITAR_ESCRIBIR_NOMBRE 0

/**
 * \def HABILITAR_ESCRIBIR_CONTRASENIA
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir su contrasenia esta habilitado.
 */
#define HABILITAR_ESCRIBIR_CONTRASENIA 1

/**
 * \def DESHABILITAR_ESCRIBIR_CONTRASENIA
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir su contrasenia esta deshabilitado.
 */
#define DESHABILITAR_ESCRIBIR_CONTRASENIA 0


/**
 * \def HABILITAR_GUARDAR_AUTENTICACION
 * \brief Codigo para indicar que el guardado de datos del usuario para la autenticacion automatica esta habilitado.
 */
#define HABILITAR_GUARDAR_AUTENTICACION 1

/**
 * \def DESHABILITAR_GUARDAR_AUTENTICACION
 * \brief Codigo para indicar que el guardado de datos del usuario para la autenticacion automatica esta deshabilitado.
 */
#define DESHABILITAR_GUARDAR_AUTENTICACION 0


/**
 * \def HABILITAR_INGRESAR
 * \brief Codigo para indicar que el ingreso de usuario esta habilitado.
 */
#define HABILITAR_INGRESAR 1

/**
 * \def DESHABILITAR_INGRESAR
 * \brief Codigo para indicar que el ingreso de usuario esta deshabilitado.
 */
#define DESHABILITAR_INGRESAR 0



/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct s_recursosComunesAutenticacionRegistroTexto
 * \brief Contiene todos los textos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfText *auxEscribirContrasenia;     /**< Muestra la contrasenia que escribe el usuario. */
    sfText *auxEscribirNombre;          /**< Muestra el nombre que escribe el usuario. */
    sfText *auxGuardarAutenticacion;    /**< Salida (tilde/cruz) que muestra el estado del guardado de datos del usuario para la autenticacion automatica. */
    sfText *guardarAutenticacion;       /**< Texto interrogativo para guardar los datos del usuario para la autenticacion automatica. */
    sfText *ingresarContrasenia;        /**< Indica al usuario donde escribir su contrasenia. */
    sfText *ingresarNombre;             /**< Indica al usuario donde escribir su nombre. */
    sfText *ingresoIncorrecto;
    sfText *textoBotonIngresar;         /**< Texto encontrado dentro del boton para ingresar usuario. */
    sfText *tituloInterfaz;             /**< Titulo de la interfaz sobre la que se encuentra ubicado el usuario. */
} s_recursosComunesAutenticacionRegistroTexto;

/** \struct s_recursosComunesAutenticacionRegistroElementos
 * \brief Contiene todos los elementos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    sfRectangleShape *barraEscribirContrasenia;         /**< Barra donde el usuario escribe su contrasenia. */
    sfRectangleShape *barraEscribirNombre;              /**< Barra donde el usuario escribe su nombre. */
    sfRectangleShape *botonGuardarAutenticacion;        /**< Boton para modificar el estado del guardado de datos del usuario para la autenticacion automatica. */
    sfRectangleShape *botonIngresar;                    /**< Boton para ingresar usuario. */
    sfRectangleShape *puntoInsercion;                   /**< Punto de insercion para escritura de texto. */
    sfRectangleShape *subrayadoTitulo;                  /**< Barra decorativa para subrayar el titulo de la interfaz. */
} s_recursosComunesAutenticacionRegistroElementos;

/** \struct s_recursosComunesAutenticacionRegistroHabilitaciones
 * \brief Contiene todas las habilitaciones comunes (compartidas) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    bool escribirContrasenia;                   /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su contrasenia. */
    bool escribirNombre;                        /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su nombre. */
    bool guardarAutenticacion;                  /**< Habilitar/deshabilitar el guardado de datos del usuario para la autenticacion automatica. */
    bool ingresar;                              /**< Habilitar/deshabilitar el ingreso de usuario. */
    bool puntoInsercion;                        /**< Activar/desactivar el punto de insercion. */
    unsigned short int contadorPuntoInsercion;  /**< Contador para determinar el tiempo en el que se activa/desactiva el punto de insercion. */
} s_recursosComunesAutenticacionRegistroHabilitaciones;

/** \struct s_recursosComunesAutenticacionRegistro
 * \brief Estructura base que contiene los buffers, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 */
typedef struct
{
    s_recursosComunesAutenticacionRegistroTexto texto;
    s_recursosComunesAutenticacionRegistroElementos elementos;
    s_recursosComunesAutenticacionRegistroHabilitaciones habilitaciones;
    char bufferNombre [MAX_INGRESO_NOMBRE];             /**< Buffer donde se guarda el nombre que escribe el usuario. */
    char bufferContrasenia [MAX_INGRESO_CONTRASENIA];    /**< Buffer donde se guarda la contrasenia que escribe el usuario. */
} s_recursosComunesAutenticacionRegistro;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Establecer todas las variables graficas en NULL y luego invocar a las funciones
 * recursosComunesAutenticacionRegistro_inicializarTexto e recursosComunesAutenticacionRegistro_inicializarElementos para crear cada recurso.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int recursosComunesAutenticacionRegistro_inicializar (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Configurar los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Invocar a las funciones recursosComunesAutenticacionRegistro_configurarTexto e recursosComunesAutenticacionRegistro_configurarElementos para configurar cada recurso y luego invocar a las funciones
 * recursosComunesAutenticacionRegistro_tamYPosVentanaTexto e recursosComunesAutenticacionRegistro_tamYPosVentanaElementos para establecer a todos los recursos graficos un tamanio y posicion sobre la ventana.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void recursosComunesAutenticacionRegistro_configurar (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const s_fuentes *fuentes);

/** \brief Renderizar los recursos graficos de texto comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistroTexto Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_renderizarTexto (sfRenderWindow *renderizado, const s_recursosComunesAutenticacionRegistroTexto *recursosComunesAutenticacionRegistroTexto);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro
 *
 * No se limpia ni muestra la pantalla, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistroElementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_renderizarElementos (sfRenderWindow *renderizado, const s_recursosComunesAutenticacionRegistroElementos *recursosComunesAutenticacionRegistroElementos);

/** \brief Liberar todos los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * Liberar, de manera segura, todos los recursos graficos comunes entre las interfaces de autenticacion y registro creados.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_liberar (s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de click en el boton para guardar los datos de autenticacion.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param botonGuardarAutenticacion Puntero al elemento del boton para guardar los datos de autenticacion.
 * \param auxGuardarAutenticacion Puntero al texto auxiliar para guardar los datos de autenticacion.
 * \param habilitaciones Puntero a la estructura que contiene todos las habilitaciones comunes (compartidas) entre las interfaces de autenticacion y registro.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarClickGuardarAutenticacion (const sfRenderWindow *renderizado, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);



#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED
































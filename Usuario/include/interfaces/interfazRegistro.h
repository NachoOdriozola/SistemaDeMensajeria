/**
 * \file   interfazRegistro.h
 * \brief  Define las estructuras y contiene funciones estructurales y logicas relacionadas a la interfaz de registro.
 */



#ifndef INTERFAZREGISTRO_H_INCLUDED
#define INTERFAZREGISTRO_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../../Constantes/constantes.h"
#include "../utiles.h"
#include "../estructuras.h"
#include "../recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"



/* ============================
   DEFINES
   ============================ */


#define INGRESO_VALIDO 0
#define INGRESO_INVALIDO 1


/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_inputCorreo
 * \brief Contexto sobre el input del correo electronico del usuario.
 */
typedef struct
{
    sfText *auxEscribirCorreo;              /**< Muestra el correo electronico que escribe el usuario. */
    bool validez;                           /**< Indicar si el ingreso es valido o invalido. */
} t_inputCorreo;

/** \struct t_interfazRegistroTextos
 * \brief Contiene todos los textos graficos de la interfaz de registro.
 */
typedef struct
{
    t_inputCorreo inputCorreo;
    sfText *ingresarCorreo;                 /**< Indica al usuario donde escribir su correo electronico. */
    sfText *textoInformativoContrasenia;    /**< Texto informativo sobre la contrasenia. */
    sfText *textoInformativoNombre;         /**< Texto informativo sobre el nombre. */
} t_interfazRegistroTextos;

/** \struct t_interfazRegistroElementos
 * \brief Contiene todos los elementos graficos de la interfaz de registro.
 */
typedef struct
{
    sfRectangleShape *barraEscribirCorreo;   /**< Barra donde el usuario escribe su correo electronico. */
} t_interfazRegistroElementos;

/** \enum t_interfazRegistroFoco
 * \brief Contiene todos los estados de foco de la interfaz de registro.
 */
typedef enum
{
    ESCRIBIR_CORREO,        /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir su correo electronico. */
    IR_NINGUNO              /**< Ningun foco establecido. */
} t_interfazRegistroFoco;

/** \struct t_interfazRegistro
 * \brief Estructura base que contiene los buffers, focos y une los recursos graficos de la interfaz de registro.
 */
typedef struct
{
    t_interfazRegistroTextos textos;
    t_interfazRegistroElementos elementos;
    t_interfazRegistroFoco estadoFoco;
    char bufferCorreo [MAX_CORREO_USUARIO];
} t_interfazRegistro;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de registro.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 *
 */
void interfazRegistro_inicializarValoresNulos (t_interfazRegistro *interfazRegistro);

/** \brief Inicializar los recursos graficos de la interfaz de registro.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazRegistro_inicializar (t_interfazRegistro *interfazRegistro);

/** \brief Configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico de la interfaz de registro.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 * \param fuentes Puntero a la estructura que contiene las variables de las fuentes graficas de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazRegistro_configurar (t_interfazRegistro *interfazRegistro, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de registro.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 *
 */
void interfazRegistro_accion (t_contextoAplicacion *contextoAplicacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de registro.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 *
 */
void interfazRegistro_actualizar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, t_interfazRegistro *interfazRegistro);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de registro sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de registro en la ventana.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y focos comunes entre las interfaces de autenticacion y registro.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 *
 */
void interfazRegistro_renderizar (sfRenderWindow *renderizado, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro, const t_interfazRegistro *interfazRegistro);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de registro.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y focos de la interfaz de registro.
 *
 */
void interfazRegistro_liberar (t_interfazRegistro *interfazRegistro);



#endif // INTERFAZREGISTRO_H_INCLUDED




















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
#include "../recursosGraficosComunes/recursosComunesAutenticacionRegistro.h"



/* ============================
   DEFINES
   ============================ */








/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct s_interfazRegistroTextos
 * \brief Contiene todos los textos graficos de la interfaz de registro.
 */
typedef struct
{
    sfText *textoInformativoContrasenia;    /**< Texto informativo sobre la contrasenia. */
    sfText *textoInformativoNombre;         /**< Texto informativo sobre el nombre. */
} s_interfazRegistroTextos;

/** \struct s_interfazRegistroElementos
 * \brief Contiene todos los elementos graficos de la interfaz de registro.
 */
typedef struct
{
    sfRectangleShape *flechaVolverBarra;
    sfRectangleShape *flechaVolverTriangulo1;
    sfRectangleShape *flechaVolverTriangulo2;
} s_interfazRegistroElementos;

/** \struct s_interfazRegistroHabilitaciones
 * \brief Contiene todas las habilitaciones de la interfaz de registro.
 */
typedef struct
{

} s_interfazRegistroHabilitaciones;

/** \struct s_interfazRegistro
 * \brief Estructura base que contiene los buffers, habilitaciones y une los recursos graficos de la interfaz de registro.
 */
typedef struct
{
    s_interfazRegistroTextos textos;
    s_interfazRegistroElementos elementos;
    s_interfazRegistroHabilitaciones habilitaciones;
} s_interfazRegistro;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos de la interfaz de registro.
 *
 * Establecer todas las variables graficas en NULL y luego crear cada recursos.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazRegistro_inicializar (s_interfazRegistro *interfazRegistro);

/** \brief Configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico de la interfaz de registro.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL, configurar cada recurso y establecerle un tamanio y una posicion sobre la ventana.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void interfazRegistro_configurar (s_interfazRegistro *interfazRegistro, const s_fuentes *fuentes);

/** \brief Manejar las acciones que realiza el usuario sobre la interfaz de registro.
 *
 * Capturar los eventos generados por el usuario (clicks, teclado, redimensionado, etc.) y realizar o invocar las funciones correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazRegistro_accion (s_aplicacion *aplicacion, const s_interfazRegistro *interfazRegistro, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Manejar las acciones que ocurren sin intervencion directa del usuario en la interfaz de registro.
 *
 * Capturar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc.) y realizar o invocar las funciones
 * correspondientes segun el evento detectado.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazRegistro_actualizar (s_interfazRegistro *interfazRegistro, s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Mostrar los recursos graficos actualizados de la interfaz de registro sobre la ventana.
 *
 * Limpiar la ventana anterior y mostrar los elementos graficos actualizados de la interfaz de registro en la ventana.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de autenticacion y registro.
 *
 */
void interfazRegistro_renderizar (sfRenderWindow *renderizado, const s_interfazRegistro *interfazRegistro, const s_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de registro.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos, buffers y habilitaciones de la interfaz de registro.
 *
 */
void interfazRegistro_liberar (s_interfazRegistro *interfazRegistro);



/* ============================
   FUNCIONES LOGICAS
   ============================ */




#endif // INTERFAZREGISTRO_H_INCLUDED




















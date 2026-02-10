/**
 * \file   utiles.h
 * \brief  Contiene funciones utiles logicas.
 */



#ifndef UTILES_H_INCLUDED
#define UTILES_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def RECIBIO_RESPUESTA
 * \brief Codigo de retorno para indicar que se recibio una respuesta del servidor.
 */
#define RECIBIO_RESPUESTA 1

/**
 * \def NO_RECIBIO_RESPUESTA
 * \brief Codigo de retorno para indicar que no se recibio una respuesta del servidor.
 */
#define NO_RECIBIO_RESPUESTA 0


/**
 * \def HABILITAR_PUNTO_INSERCION
 * \brief Codigo para activar el punto de insercion.
 */
#define HABILITAR_PUNTO_INSERCION 1

/**
 * \def DESHABILITAR_PUNTO_INSERCION
 * \brief Codigo para desactivar el punto de insercion.
 */
#define DESHABILITAR_PUNTO_INSERCION 0

/**
 * \def VELOCIDAD_PARPADEO_PUNTO_INSERCION
 * \brief Constante que determina la velocidad de parpadeo del punto de insercion.
 */
#define VELOCIDAD_PARPADEO_PUNTO_INSERCION 22

/**
 * \def REINICIAR_CONTADOR_PUNTO_INSERCION
 * \brief Constante para reiniciar el contador del punto de insercion.
 */
#define REINICIAR_CONTADOR_PUNTO_INSERCION 0



/* ============================
   FUNCIONES DE SOCKETS
   ============================ */



/** \brief Recibir una respuesta del servidor a traves del socket.
 *
 * Intentar leer datos disponibles en el socket especificado.
 * Si se recibe una respuesta, asegura terminar el bufferRespuesta con caracter nulo para que sea una cadena valida.
 * No bloquea el socket.
 *
 * \param sock Socket del usuario desde el cual se recibe la respuesta.
 * \param bufferRespuesta Buffer donde se almacenara la respuesta recibida.
 * \param tamMaxBufferRespuesta Tamanio maximo del buffer que recibe la respuesta.
 *
 * \return RECIBIO_RESPUESTA en caso de que haya recibido respuesta, NO_RECIBIO_RESPUESTA en caso contrario.
 *
 */
bool recibirRespuesta (SOCKET sock, char *bufferRespuesta, int tamMaxBufferRespuesta);

/** \brief Enviar una solicitud al servidor y esperar a recibir su respuesta.
 *
 * Envia una solicitud almacenada en el bufferSolicitud y recibe una respuesta que se almacenara en el bufferRespuesa. Todo el proceso se comunica mediante el socket especificado.
 * Asegura terminar el bufferRespuesta con caracter nulo para que sea una cadena valida.
 * Cambiar temporalmente el modo del socket a bloqueante para asegurar que el envio y la recepcion se completen antes de continuar. Una vez realizado el proceso, se desbloquea.
 *
 * \param sock Socket del usuario desde el cual se realizara la comunicacion (envio y recepcion).
 * \param bufferSolicitud Buffer que contiene la solicitud a enviar.
 * \param bufferRespuesta Buffer donde se almacenara la respuesta recibida.
 * \param tamMaxBufferRespuesta Tamanio maximo del buffer que recibe la respuesta.
 *
 */
void enviarSolicitudYRecibirRespuesta (SOCKET sock, const char *bufferSolicitud, char *bufferRespuesta, int tamMaxBufferRespuesta);



/* ============================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================ */



/** \brief Verificar si el usuario clickeo un rectangulo grafico en pantalla.
 *
 * Obtiene la posicion del mouse en pantalla y los limites del rectangulo para saber si el usuario lo clickeo.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param rectangulo Puntero al rectangulo grafico.
 *
 * \return True en caso de que el usuario lo clickeo, False en caso contrario.
 *
 */
bool clickEnRectangulo (const sfRenderWindow *renderizado, const sfRectangleShape *rectangulo);

/** \brief Verificar si el usuario clickeo un texto grafico en pantalla.
 *
 * Obtiene la posicion del mouse en pantalla y los limites del texto para saber si el usuario lo clickeo.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param texto Puntero al texto grafico.
 *
 * \return True en caso de que el usuario lo clickeo, False en caso contrario.
 *
 */
bool clickEnTexto (const sfRenderWindow *renderizado, const sfText *texto);

/** \brief Centrar un texto dentro de una area.
 *
 * \param texto Puntero al texto sfText a centrar.
 * \param posXInicial Posicion en X donde comienza el area.
 * \param posYInicial Posicion en Y donde comienza el area.
 * \param anchoArea Ancho (x) del area.
 * \param altoArea Alto (y) del area.
 *
 */
void centrarTextoEnArea (sfText *texto, float posXInicial, float posYInicial, float anchoArea, float altoArea);

/** \brief Limitar la visualizacion de texto ingresado por el usuario sobre la barra de escritura.
 *
 * \param texto Puntero al texto sfText ingresado por el usuario.
 * \param bufferTexto Puntero al buffer que contiene el texto a mostrar.
 * \param anchoBarra Ancho de la barra de escritura.
 */
void limitarVisualizarTextoSobreBarra (sfText *texto, const char *bufferTexto, float anchoBarra);



/* ============================
   FUNCIONES DE ESCRITURA
   ============================ */



/** \brief Ingresar un caracter almacenado en un evento a un buffer.
 *
 * Procesar el caracter y colocarlo en la posicion que corresponda dentro del buffer.
 * Acepta el caracter "Backspace" para borrado de texto.
 * Si la tecla es "Enter" retorna.
 *
 * \param buffer Puntero al buffer donde se almacenara el caracter.
 * \param tamMaxBuffer Tamanio maximo del buffer. Es por como esta definido, ej: char buffer [5], el tamanio maximo es '5'.
 * \param eventoChar Variable de evento que contiene el caracter.
 *
 */
void ingresarCaracterABuffer (char *buffer, int tamMaxBuffer, sfEvent eventoChar);



/* ============================
   FUNCIONES DE PUNTO DE INSERCION
   ============================ */



/** \brief Actualizar el punto de insercion segun su estado.
 *
 * Avanzar el contador del punto de insercion. Si el punto de insercion alcanza la velocidad (constante) establecida, se reinicia el contador y se actualiza (activa/desactiva) segun su estado:
 * si el punto de insercion esta deshabilitado, se habilita.
 * si el punto de insercion esta habilitado, se deshabilita.
 *
 * \param puntoInsercion Habilitacion para activar/desactivar (mostrar o no) el punto de insercion.
 * \param contadorPuntoInsercion Contador para activar/desactivar determinado tiempo el punto de insercion.
 *
 */
void actualizarPuntoInsercion (bool *puntoInsercion, unsigned short int *contadorPuntoInsercion);

/** \brief Reiniciar el punto de insercion.
 *
 * Deshabilitar (desactivar) el parpadeo del punto de insercion y reiniciar su contador.
 *
 * \param puntoInsercion Habilitacion para activar/desactivar (mostrar o no) el punto de insercion.
 * \param contadorPuntoInsercion Contador para activar/desactivar determinado tiempo el punto de insercion.
 *
 */
void reiniciarPuntoInsercion (bool *puntoInsercion, unsigned short int *contadorPuntoInsercion);



#endif // UTILES_H_INCLUDED




























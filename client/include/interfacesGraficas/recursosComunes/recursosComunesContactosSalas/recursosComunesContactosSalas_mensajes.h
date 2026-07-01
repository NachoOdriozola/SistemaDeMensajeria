/**
 * \file  recursosComunesContactosSalas.h
 * \brief Declaracion de funciones y estructuras para recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */


#ifndef RECURSOSCOMUNESCONTACTOSSALAS_MENSAJES_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_MENSAJES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDE
   ============================================================================================================================================ */

#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../utiles.h"
#include "../../../estructuras.h"
#include "../../../../../shared/estructurasDeDatos/listaCircular/include/listaCircular.h"

#include "recursosComunesContactosSalas_estructuras.h"

/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _recursosComunesContactosSalas_configurarContextoMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Configurar un mensaje.
 *
 * Establecerle un color y la fuente enviada como parametro.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param fuente Puntero a fuente sfFont.
 *
 */
void configurarMensaje (void *mensaje, void *fuente);

/** \brief Establecer un tamanio a un mensaje. Ademas, agrega un espaciado de linea.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void tamMensaje (void *mensaje);

/** \brief Renderizar un mensaje.
 *
 * No se limpia ni muestra la ventana, solo lo renderiza.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 *
 */
void renderizarMensaje (void *mensaje, void *renderizado);

/** \brief Vaciar (resetear) un mensaje sfText. Setear su string a "".
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void vaciarMensaje (void *mensaje);

/** \brief Liberar un mensaje sfText.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void liberarMensaje (void *mensaje);

/** \brief Modificar la posicion de un mensaje.
 *
 * Unicamente modifica la posicion en Y del mensaje.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param desplazamientoY Puntero a la cantidad de desplazamiento en Y que se desea modificar.
 *
 */
void modificarPosMensaje (void *mensaje, void *desplazamientoY);

/** \brief Establecer los saltos de linea necesarios a un mensaje sfText.
 *
 * Establecer una cadena valida al texto sfText, con saltos de linea incorporados, que las lineas no sobrepasen el ancho maximo enviado como parametro.
 *
 * \param texto Puntero al mensaje sfText.
 * \param bufferMensaje Buffer que almacena el mensaje completo (sin saltos de linea).
 * \param anchoMax Ancho maximo que no debe sobrepasar los limites del mensaje.
 *
 */
void establecerSaltoDeLineaMensaje (sfText *texto, const char *bufferMensaje, float anchoMax);

/** \brief Insertar un mensaje a la lista circular de mensajes.
 *
 * Trabaja sobre el puntero al nodo del primer mensaje de la lista circular.
 * Establecer los saltos de linea necesarios para que el mensaje no sobrepase los limites establecidos.
 * Desplazar en Y a toda la lista circular de mensajes. El desplazamiento depende del alto del mensaje a insertar.
 * Dependiendo del origen del mensaje, se establece una posicion u otra al mismo.
 * Actualizar correspondientemente los punteros a nodo del primer y ultimo mensaje de la lista circular de mensajes.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param bufferMensaje Buffer que almacena el mensaje completo.
 * \param origen Origen de quien envio mensaje.
 *
 */
void insertarMensaje (t_contextoMensajes *contextoMensajes, const char *bufferMensaje, t_origenMensaje origen);

void renderizarVistaMensajes (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);


#endif // RECURSOSCOMUNESCONTACTOSSALAS_MENSAJES_H_INCLUDED
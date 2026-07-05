/**
 * \file  recursosComunesContactosSalas_mensajes.h
 * \brief Contiene funciones que manejan el comportamiento de la lista de mensajes.
 */


#ifndef RECURSOSCOMUNESCONTACTOSSALAS_MENSAJES_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_MENSAJES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDE
   ============================================================================================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../../shared/constantes/include/constantes.h"
#include "../../../../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../../utiles.h"

#include "recursosComunesContactosSalas_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Crear la lista doble de mensajes que contiene los mensajes sfText*.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 *
 */
void _recursosComunesContactosSalas_crearListaMensajes (t_contextoMensajes *contextoMensajes);

/** \brief Insertar un nuevo mensaje a la lista de mensajes.
 *
 * Crea el mensaje sfText*, lo configura, le establece el texto del mensaje con saltos de linea, desplaza hacia arriba a todos los mensajes que hay en la lista de mensajes
 * para hacer espacio para el nuevo mensaje entrante, le establece su posicion y lo inserta a la lista de mensajes.
 * En caso de que sea el primer mensaje insertado a la lista, almacena su referencia en el contexto de mensajes.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param mensaje Cadena que contiene el mensaje. Si bien la estructura contextoMensajes contiene la cadena del mensaje que escribe el usuario, este parametro es necesario para mensajes recibidos por otros usuarios.
 * \param origenMensaje Origen de quien envio mensaje.
 * \param fuentes Puntero a la estructura que contiene las fuentes de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 * 
 * \return EXITO en caso de que todo se ejecuto correctamente, ERROR_SIN_MEMORIA en caso de que no se pueda crear el mensaje.
 *
 */
t_codigoRetorno recursosComunesContactosSalas_insertarMensajeAListaMensajes (t_contextoMensajes *contextoMensajes, char *mensaje, t_origenMensaje origenMensaje, t_recursosComunesContactosSalasFuentes *fuentes);

/** \brief Setear la vista de mensajes y renderizar la lista de mensajes.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_setearVistaMensajesYRenderizarListaMensajes (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Vaciar la lista de mensajes, liberando los sfText* creados.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 *
 */
void recursosComunesContactosSalas_vaciarListaMensajes (t_contextoMensajes *contextoMensajes);


#endif // RECURSOSCOMUNESCONTACTOSSALAS_MENSAJES_H_INCLUDED
/**
 * \file   controladores.h
 * \brief  Contiene funciones que hacen de puente entre la logica y la interfaz grafica.
 */


#ifndef INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
#define INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "external/csfml/include/SFML/System.h"
#include "external/csfml/include/SFML/Window.h"
#include "external/csfml/include/SFML/Graphics.h"

#include "shared/estructurasDeDatos/listaDoble/include/listaDoble.h"

#include "logica/estructuras.h"
#include "logica/utiles.h"

#include "comunicacion/comunicacion.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/recursos.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Preguntar si el mensaje es un comando.
 *
 * \param mensaje Cadena que contiene el mensaje.
 *
 * \return True si el mensaje es un comando, False en caso contrario.
 * 
 */
bool _interfazContactos_esUnComando (const char *mensaje);

/** \brief Verificar que los datos de seleccion de chat sean validos. En caso de que lo sean, envia la solicitud de seleccion de chat.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void _interfazContactos_realizarSeleccionChat (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos);

/** \brief Verificar que los datos de envio de mensaje sean validos. En caso de que lo sean, envia la solicitud de envio de mensaje.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void _interfazContactos_realizarEnvioMensaje (t_contextoAplicacion *contextoAplicacion, const t_interfazContactos *interfazContactos);


/** \brief Realizar el procedimiento en caso de error de conexion con el servidor.
 * 
 * Resetear la interfaz de contactos, cerrar el socket del usuario y seleccionar la interfaz de autenticacion para utilizar.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void _interfazContactos_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


/** \brief Preparar la interfaz para establecer un nuevo chat con un contacto seleccionado, tanto logicamente como graficamente.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 * \param datosRespuestaSolicitudSeleccionChat Puntero a la estructura que contiene los datos de respuesta de la solicitud a enviar al cliente.
 *
 */
void _interfazContactos_setearNuevoChatSeleccionado (t_interfazContactos *interfazContactos, const t_datosRespuestaSolicitudSeleccionChat *datosRespuestaSolicitudSeleccionChat);


/** \brief Crear la lista doble de mensajes que contiene los mensajes sfText*.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 *
 */
void _interfazContactos_listaMensajes_crear (t_contextoMensajes *contextoMensajes);

/** \brief Insertar un nuevo mensaje a la lista doble de mensajes.
 *
 * Crea el mensaje sfText*, lo configura, le establece el texto del mensaje con saltos de linea, desplaza hacia arriba a todos los mensajes que hay en la lista de mensajes
 * para hacer espacio para el nuevo mensaje entrante, le establece su posicion y lo inserta a la lista de mensajes.
 * En caso de que sea el primer mensaje insertado a la lista, almacena su referencia en el contexto de mensajes.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param mensaje Cadena que contiene el mensaje. Si bien la estructura contextoMensajes contiene la cadena del mensaje que escribe el usuario, este parametro es necesario para mensajes recibidos por otros usuarios.
 * \param origenMensaje Origen de quien envio mensaje.
 * \param fuentes Puntero a la estructura que contiene las fuentes de los textos graficos de la interfaz de contactos.
 * 
 * \return EXITO en caso de que todo se ejecuto correctamente, ERROR_SIN_MEMORIA en caso de que no se pueda crear el mensaje.
 *
 */
t_codigoRetorno _interfazContactos_listaMensajes_insertarMensaje (t_contextoMensajes *contextoMensajes, const char *mensaje, t_origenMensaje origenMensaje, const t_interfazContactosFuentes *fuentes);

/** \brief Vaciar la lista doble de mensajes, liberando los sfText* creados.
 *
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 *
 */
void _interfazContactos_listaMensajes_vaciar (t_contextoMensajes *contextoMensajes);


#endif // INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
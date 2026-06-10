/**
 * \file   solicitudes.h
 * \brief  g
 */



#ifndef SOLICITUDES_H_INCLUDED
#define SOLICITUDES_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <sqlite3.h>

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/estructurasDeDatos/listaSimple/include/listaSimple.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "estructuras.h"
#include "utiles.h"


   
/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */




/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */



/** \brief Verifica y procesa la solicitud de autenticacion.
 *
 * Parsea la cadena enviada en el buffer de solicitud compuesta de la siguiente manera:
 * SOLICITUD_AUTENTICACION|nombre de usuario|contrasenia del usuario
 * Consulta en la base de datos si las credenciales del usuario existen y son validas.
 * Si lo son, recupera su ID, lo guarda en el nodo del cliente y lo mueve de la lista simple de clientes no autenticados a la tabla hash.
 * Si no lo son, responde al cliente con RESPUESTA_ERROR_CREDENCIALES_INVALIDAS y un ID invalido.
 * Si la operacion se ejecuta con exito, responde al cliente con RESPUESTA_EXITO y el ID del cliente.
 *
 * Genera una cadena valida para responder al cliente en el buffer de respuesta compuesta de la siguiente manera:
 * t_estadoRespuesta|ID del usuario
 * En caso de que el servidor falle, responde con RESPUESTA_ERROR_SERVIDOR y un ID invalido.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 * \param clienteAProcesar Referencia al nodo del cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return EXITO si se proceso correctamente, ERROR_INICIALIZACION en caso de falla al preparar la consulta SQLite.
 *
 */
int manejarSolicitudAutenticacion (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);

/** \brief Verifica y procesa la solicitud de registro.
 *
 * Parsea la cadena enviada en el buffer de solicitud compuesta de la siguiente manera:
 * SOLICITUD_REGISTRO|nombre de usuario|contrasenia del usuario|correo electronico del usuario
 * Consulta en la base de datos si el nombre de usuario y/o el correo electronico ya existen.
 * Si ya existen, responde al cliente con RESPUESTA_ERROR_CREDENCIALES_INVALIDAS y un ID invalido.
 * Inserta el usuario en la base de datos, recupera su ID, lo guarda en el nodo del cliente y lo mueve de la lista simple de clientes no autenticados a la tabla hash.
 * Si la operacion se ejecuta con exito, responde al cliente con RESPUESTA_EXITO y el ID del cliente.
 *
 * Genera una cadena valida para responder al cliente en el buffer de respuesta compuesta de la siguiente manera:
 * t_estadoRespuesta|ID del usuario
 * En caso de que el servidor falle, le responde al cliente "INDICE_RESPUESTA_ERROR_SERVIDOR".
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return EXITO si se proceso correctamente, ERROR_INICIALIZACION en caso de falla al preparar la consulta SQLite.
 *
 */
int manejarSolicitudRegistro (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);

/** \brief Verifica y procesa la solicitud de envio de mensaje.
 *
 * Parsea la cadena enviada en el buffer de solicitud compuesta de la siguiente manera:
 * SOLICITUD_MENSAJE|ID del emisor|ID del receptor|texto
 * Si el ID del emisor es igual al ID del receptor (se envia un mensaje a si mismo), responde al cliente con RESPUESTA_ERROR_OPERACION_INVALIDA.
 * Inserta el mensaje en la base de datos.
 *
 * Genera una cadena valida para responder al cliente en el buffer de respuesta compuesta de la siguiente manera:
 * t_estadoRespuesta
 *
 * Si la operacion se ejecuta con exito, responde al cliente con RESPUESTA_EXITO.
 * Busca el ID del receptor en la tabla hash de clientes para saber si el usuario receptor esta conectado.
 * En caso de que este conectado, genera una cadena valida para enviar el mensaje al usuario receptor en el buffer de respuesta compuesta de la siguiente manera:
 * RESPUESTA_MENSAJE|ID del emisor|texto
 *
 * En caso de que el servidor falle, responde con RESPUESTA_ERROR_SERVIDOR.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return EXITO si se proceso correctamente, ERROR_INICIALIZACION en caso de falla al preparar la consulta SQLite, ERROR_OPERACION en caso de fallas en la logica de operacion de la funcion.
 *
 */
int manejarSolicitudEnvioMensaje (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);

/** \brief Verifica y procesa la solicitud de seleccionar contacto.
 *
 * Parsea la cadena enviada en el buffer de solicitud compuesta de la siguiente manera:
 * SOLICITUD_SELECCIONAR_CONTACTO|nombre del contacto
 * Consulta en la base de datos si el nombre de usuario del contacto existe.
 * Si existe, recupera su ID y pregunta si el ID del emisor es igual al ID del receptor (mismo cliente).
 * Si el ID es el mismo, responde al cliente con RESPUESTA_ERROR_OPERACION_INVALIDA y un ID invalido.
 * Si el ID no es el mismo, responde al cliente con RESPUESTA_EXITO y el ID correspondiente del receptor.
 * Si no existe, responde al cliente con RESPUESTA_ERROR_USUARIO_NO_ENCONTRADO y un ID invalido.
 *
 * Genera una cadena valida para responder al cliente en el buffer de respuesta compuesta de la siguiente manera:
 * t_estadoRespuesta|ID del receptor
 * En caso de que el servidor falle, responde con RESPUESTA_ERROR_SERVIDOR y un ID invalido.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return EXITO si se proceso correctamente, ERROR_INICIALIZACION en caso de falla al preparar la consulta SQLite, ERROR_OPERACION en caso de fallas en la logica de operacion de la funcion.
 *
 */
int manejarSolicitudSeleccionContacto (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);



#endif // SOLICITUDES_H_INCLUDED
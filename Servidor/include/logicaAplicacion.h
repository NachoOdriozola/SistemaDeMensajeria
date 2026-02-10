/**
 * \file   logicaServidor.h
 * \brief  Contiene funciones logicas, defines y macros globales de la aplicacion.
 */



#ifndef LOGICASERVIDOR_H_INCLUDED
#define LOGICASERVIDOR_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <sqlite3.h>

#include "../../Constantes/constantes.h"
#include "../../EstructurasDeDatos/include/listaSimple.h"
#include "../../EstructurasDeDatos/include/tablaHash.h"
#include "estructuras.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def CARACTER_APAGAR_SERVIDOR
 * \brief Caracter que el usuario debe escribir en consola para apagar el servidor.
 */
#define CARACTER_APAGAR_SERVIDOR 'S'


/**
 * \def CANT_BUCKETS_TABLA_HASH
 * \brief Cantidad de buckets que tiene la tabla hash.
 */
#define CANT_BUCKETS_TABLA_HASH 1000

/**
 * \def MAX_BUFFER_CONSULTA_SQLITE
 * \brief Tamanio maximo del buffer para almacenar consultas SQLite.
 */
#define MAX_BUFFER_CONSULTA_SQLITE 128


/**
 * \def RECIBIO_SOLICITUD
 * \brief Codigo de retorno que indica que se recibio una solicitud de un cliente.
 */
#define RECIBIO_SOLICITUD 1

/**
 * \def NO_RECIBIO_SOLICITUD
 * \brief Codigo de retorno que indica que no se recibio ninguna solicitud.
 */
#define NO_RECIBIO_SOLICITUD 0



/* ============================
   FUNCIONES ESTRUCTURALES BASE
   ============================ */



/** \brief Inicializar los recursos del servidor.
 *
 * Iniciar la API de Winsock, abrir la base de datos y crear el socket del servidor, la tabla hash de clientes y la lista simple de clientes
 * conectados pero no autenticados.
 *
 * \param servidor Puntero a la estructura base del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int inicializarServidor (t_servidor *servidor);

/** \brief Configurar los recursos del servidor.
 *
 * Configurar el socket del servidor para escuchar conexiones de cualquier direccion IP en el puerto asignado. Ademas, establecerlo como modo no bloqueante.
 *
 * \param servidor Puntero a la estructura base del servidor.
 *
 * \return EXITO si se configuro correctamente, ERROR_CONFIGURACION en caso de error.
 *
 */
int configurarServidor (t_servidor *servidor);

/** \brief Liberar los recursos del servidor.
 *
 * Vaciar la lista simple de clientes conectados pero no autenticados, vaciar y eliminar la tabla hash de clientes y cerrar el socket del servidor,
 * la base de datos y la API de Winsock.
 *
 * \param servidor Puntero a la estructura base del servidor.
 *
 */
void liberarServidor (t_servidor *servidor);



/* ============================
   FUNCIONES DE GESTION DE CLIENTES
   ============================ */



/** \brief Procesar a un nuevo cliente conectado e insertarlo en la lista simple de clientes conectados pero no autenticados.
 *
 * Establecer el socket del cliente como no bloqueante, asignarle una ID invalida e insertarlo en la lista simple de clientes conectados pero no autenticados.
 *
 * \param nuevoCliente Puntero al nuevo cliente conectado.
 * \param listaSimpleClientesNoAutenticados Puntero a la lista simple de clientes no autenticados.
 *
 */
void procesarNuevoCliente (t_cliente *nuevoCliente, t_listaSimple *listaSimpleClientesNoAutenticados);

/** \brief Detectar si se recibio una solicitud de algun cliente en una lista simple.
 *
 * Recorrer la lista simple y preguntar a cada cliente si envio una solicitud.
 * Si un cliente envio una solicitud, se guarda su posicion y retorna.
 * Si un cliente perdio la conexion, lo desconectara automaticamente.
 *
 * \param listaSimple Puntero a la lista simple.
 * \param nodoDelCliente Direccion del doble puntero donde se guardara el nodo del cliente que envio la solicitud.
 * \param bufferSolicitud Buffer donde se almacenara la cadena de la solicitud enviada por el cliente.
 *
 * \return RECIBIO_SOLICITUD si se recibio una solicitud, NO_RECIBIO_SOLICITUD en caso contrario.
 *
 */
bool recibirSolicitudEnListaSimple (t_listaSimple *listaSimple, t_nodo ***nodoDelCliente, char *bufferSolicitud);

/** \brief Detectar si se recibio una solicitud de algun cliente en una tabla hash.
 *
 * Recorrer todas las listas simples de cada bucket y preguntar a cada cliente si envio una solicitud.
 * Si un cliente envio una solicitud, se guarda su posicion y retorna.
 * Si un cliente perdio la conexión, lo desconectara automaticamente.
 *
 * \param tablaHash Puntero a la tabla hash.
 * \param nodoDelCliente Direccion del doble puntero donde se guardara el nodo del cliente que envio la solicitud.
 * \param bufferSolicitud Buffer donde se almacenara la cadena de la solicitud enviada por el cliente.
 *
 * \return RECIBIO_SOLICITUD si se recibio una solicitud, NO_RECIBIO_SOLICITUD en caso contrario.
 *
 */
bool recibirSolicitudEnTablaHash (t_tablaHash *tablaHash, t_nodo ***nodoDelCliente, char *bufferSolicitud);



/* ============================
   FUNCIONES DE PROCESAMIENTO DE SOLICITUDES
   ============================ */



/** \brief Verifica y procesa la solicitud de autenticacion.
 *
 * Parsea la cadena del buffer de solicitud.
 * Consulta en la base de datos si las credenciales que envio el usuario existen y son validas.
 * Si lo son, recupera su ID, la guarda en la estructura del cliente y lo mueve de la lista simple de clientes no autenticados a la tabla hash, y
 * le responde al cliente "INDICE_RESPUESTA_EXITO" y su ID.
 * Si no lo son, no realiza ninguna accion y le responde al cliente "INDICE_RESPUESTA_ERROR_CREDENCIALES".
 * En caso de que el servidor falle, le responde al cliente "INDICE_RESPUESTA_ERROR_SERVIDOR".
 *
 * \param servidor Puntero a la estructura base del servidor.
 * \param clienteAProcesar Referencia al nodo del cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return EXITO si se proceso correctamente, ERROR_INICIALIZACION en caso contrario.
 *
 */
int manejarSolicitudAutenticacion (t_servidor *servidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);

/** \brief Verifica y procesa la solicitud de registro.
 *
 * Parsea la cadena del buffer de solicitud.
 * Consulta en la base de datos si el nombre de usuario y/o el correo electronico ya existen.
 * Si ya existen, no realiza ninguna accion y le responde al cliente "INDICE_RESPUESTA_ERROR_CREDENCIALES".
 * Si no existen, lo inserta en la base de datos, recupera su ID, la guarda en la estructura del cliente y lo mueve de la lista simple de clientes
 * no autenticados a la tabla hash, y le responde al cliente "INDICE_RESPUESTA_EXITO" y su ID.
 * En caso de que el servidor falle, le responde al cliente "INDICE_RESPUESTA_ERROR_SERVIDOR".
 *
 * \param servidor Puntero a la estructura base del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return EXITO si se proceso correctamente, ERROR_INICIALIZACION en caso contrario.
 *
 */
int manejarSolicitudRegistro (t_servidor *servidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);

/** \brief Verifica y procesa la solicitud de envio de mensaje.
 *
 * Parsea la cadena del buffer de solicitud.
 * Verifica si el ID del emisor es igual al ID del receptor, en tal caso no realiza ninguna accion y le responde al cliente "INDICE_RESPUESTA_ERROR_CREDENCIALES".
 * Inserta el mensaje a la base de datos y le responde al cliente "INDICE_RESPUESTA_EXITO".
 * Busca el ID del receptor en la tabla hash, si se encuentra conectado, le envia el mensaje en tiempo real.
 * En caso de que el servidor falle, le responde al cliente "INDICE_RESPUESTA_ERROR_SERVIDOR".
 *
 * \param servidor Puntero a la estructura base del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return EXITO si se proceso correctamente, ERROR_INICIALIZACION en caso contrario.
 *
 */
int manejarEnvioMensaje (t_servidor *servidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);

/** \brief Verifica y procesa la solicitud de solicitud de contacto
 *
 * Consulta en la base de datos si existe el usuario receptor.
 * Si existe, inserta en la base de datos la solicitud de amistad.
 * Le responde al cliente el resultado del proceso y, si el usuario receptor esta conectado, le envia la solicitud de amistad.
 *
 * \param servidor Puntero a la estructura base del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return OK si se proceso correctamente, ERROR_SIN_MEMORIA si no se pudo asignar memoria dinamica o ERROR_INICIALIZACION si no se pudo realizar una consulta SQLite.
 *
 */
int manejarSolicitudContacto (t_servidor *servidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);



#endif // LOGICASERVIDOR_H_INCLUDED



























/**
 * \file   logicaServidor.h
 * \brief  Contiene las funciones estructurales base, las de gestion de clientes y las de procesamiento de solicitudes del servidor.
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
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdbool.h>
#include <sqlite3.h>

#include "../../Constantes/constantes.h"
#include "../../EstructurasDeDatos/include/listaSimple.h"
#include "../../EstructurasDeDatos/include/tablaHash.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def CARACTER_APAGAR_SERVIDOR
 * \brief Caracter que el usuario debera escribir en consola para apagar el servidor.
 */
#define CARACTER_APAGAR_SERVIDOR 'S'


/**
 * \def TAM_TABLA_HASH
 * \brief Cantidad de buckets que tendra la tabla hash.
 */
#define TAM_TABLA_HASH 10

/**
 * \def MAX_BUFFER_CONSULTA_SQLITE
 * \brief Tamanio maximo del buffer para almacenar consultas de SQLite.
 */
#define MAX_BUFFER_CONSULTA_SQLITE 101


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
   ESTRUCTURAS
   ============================ */



/**
 * \struct s_cliente
 * \brief  Representa un cliente.
 */
typedef struct
{
    SOCKET sock; /**< Socket del cliente. */
    int id;      /**< Identificador correspondiente del usuario. */
} s_cliente;


/**
 * \struct s_servidor
 * \brief  Estructura base del servidor.
 */
typedef struct
{
    SOCKET sock;                                     /**< Socket del servidor. */
    sqlite3 *baseDeDatos;                            /**< Puntero a la base de datos. */
    s_listaSimple listaSimpleClientesNoAutenticados; /**< Lista simple de clientes conectados pero no autenticados. */
    s_tablaHash tablaHashClientes;                   /**< Tabla hash de clientes conectados y autenticados. */
} s_servidor;



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
int inicializarServidor (s_servidor *servidor);

/** \brief Configurar los recursos del servidor.
 *
 * Configurar el socket del servidor para escuchar conexiones de cualquier direccion IP en el puerto asignado. Ademas, establecerlo como modo no bloqueante.
 *
 * \param servidor Puntero a la estructura base del servidor.
 *
 * \return EXITO si se configuro correctamente, ERROR_CONFIGURACION en caso de error.
 *
 */
int configurarServidor (s_servidor *servidor);

/** \brief Liberar los recursos del servidor.
 *
 * Vaciar la lista simple de clientes conectados pero no autenticados, vaciar y eliminar la tabla hash de clientes y cerrar el socket del servidor,
 * la base de datos y la API de Winsock.
 *
 * \param servidor Puntero a la estructura base del servidor.
 *
 */
void liberarServidor (s_servidor *servidor);



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
void procesarNuevoCliente (s_cliente *nuevoCliente, s_listaSimple *listaSimpleClientesNoAutenticados);

/** \brief Detectar si se recibio una solicitud de algun cliente en una lista simple.
 *
 * Recorrer la lista simple y preguntar a cada cliente si envio una solicitud.
 * Si un cliente envio una solicitud, se guarda su posicion y retorna.
 * Si un cliente perdio la conexion, lo desconectara automaticamente.
 *
 * \param listaSimple Puntero a la lista simple.
 * \param nodoDelCliente Triple puntero donde se guardara el nodo del cliente que envio la solicitud.
 * \param bufferSolicitud Buffer donde se almacenara la cadena de la solicitud enviada por el cliente.
 *
 * \return RECIBIO_SOLICITUD si se recibio una solicitud, NO_RECIBIO_SOLICITUD en caso contrario.
 *
 */
bool recibirSolicitudEnListaSimple (s_listaSimple *listaSimple, s_nodo ***nodoDelCliente, char *bufferSolicitud);

/** \brief Detectar si se recibio una solicitud de algun cliente en una tabla hash.
 *
 * Recorrer todas las listas simples de cada bucket y preguntar a cada cliente si envio una solicitud.
 * Si un cliente envio una solicitud, se guarda su posicion y retorna.
 * Si un cliente perdio la conexión, lo desconectara automaticamente.
 *
 * \param tablaHash Puntero a la tabla hash.
 * \param nodoDelCliente Triple puntero donde se guardara el nodo del cliente que envio la solicitud.
 * \param bufferSolicitud Buffer donde se almacenara la cadena de la solicitud enviada por el cliente.
 *
 * \return RECIBIO_SOLICITUD si se recibio una solicitud, NO_RECIBIO_SOLICITUD en caso contrario.
 *
 */
bool recibirSolicitudEnTablaHash (s_tablaHash *tablaHash, s_nodo ***nodoDelCliente, char *bufferSolicitud);



/* ============================
   FUNCIONES DE PROCESAMIENTO DE SOLICITUDES
   ============================ */



/** \brief Verifica y procesa la solicitud de inicio de sesion.
 *
 * Consulta en la base de datos si el nombre y la contrasenia del usuario son validos.
 * Si lo son, recupera su ID, la guarda en la estructura del cliente y lo mueve de la lista simple de no autenticados a la tabla hash.
 * Le responde al cliente el resultado del proceso.
 *
 * \param servidor Puntero a la estructura base del servidor.
 * \param clienteAProcesar Referencia al nodo del cliente que envio la solicitud y se debe procesar.
 * \param bufferSolicitud Buffer que almacena la cadena de la solicitud enviada por el cliente.
 *
 * \return EXITO si se proceso correctamente, ERROR_SIN_MEMORIA si no se pudo asignar memoria dinamica o ERROR_INICIALIZACION si no se pudo realizar una consulta SQLite.
 *
 */
int procesarInicioSesion (s_servidor *servidor, s_nodo **clienteAProcesar, const char *bufferSolicitud);

/** \brief Verifica y procesa la solicitud de registro.
 *
 * Consulta en la base de datos si el nombre de usuario ya existe.
 * Si no existe, lo inserta en la base de datos, recupera su ID, la guarda en la estructura del cliente y lo mueve de la lista simple de no autenticados a la tabla hash.
 * Le responde al cliente el resultado del proceso.
 *
 * \param servidor Puntero a la estructura base del servidor.
 * \param clienteAProcesar Referencia al cliente que envió la solicitud y se debe procesar.
 * \param bufferSolicitud Buffer que contiene la cadena de la solicitud enviada por el cliente.
 *
 * \return EXITO si se proceso correctamente, ERROR_SIN_MEMORIA si no se pudo asignar memoria dinamica o ERROR_INICIALIZACION si no se pudo realizar una consulta SQLite.
 *
 */
int procesarRegistro (s_servidor *servidor, s_nodo **clienteAProcesar, const char *bufferSolicitud);

/** \brief Verifica y procesa la solicitud de solicitud de amistad.
 *
 * Consulta en la base de datos si existe el usuario receptor.
 * Si existe, inserta en la base de datos la solicitud de amistad.
 * Le responde al cliente el resultado del proceso y, si el usuario receptor esta conectado, le envia la solicitud de amistad.
 *
 * \param servidor Puntero a la estructura base del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param bufferSolicitud Buffer que contiene la cadena de la solicitud enviada por el cliente.
 *
 * \return OK si se proceso correctamente, ERROR_SIN_MEMORIA si no se pudo asignar memoria dinamica o ERROR_INICIALIZACION si no se pudo realizar una consulta SQLite.
 *
 */
int procesarSolicitudAmistad (s_servidor *servidor, s_nodo **clienteAProcesar, const char *bufferSolicitud);



#endif // LOGICASERVIDOR_H_INCLUDED



























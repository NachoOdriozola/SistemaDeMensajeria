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

#include "../../shared/constantes/include/constantes.h"
#include "../../shared/protocolos/include/protocolos.h"
#include "../../shared/estructurasDeDatos/listaSimple/include/listaSimple.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "estructuras.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def ERROR_CONFIGURACION
 * \brief Codigo de retorno para fallos en la configuracion.
 */
#define ERROR_CONFIGURACION -200


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



/** \brief Inicializar la base de datos.
 *
 * Intentar abrir la base de datos "database.db".
 * Verificar si existen las tablas del disenio.
 * En caso de que existan, la base de datos existe y conserva sus datos.
 * En caso contrario, intenta abrir el archivo "schema.sql" que contiene las consultas SQLite de creacion de tablas, segun el disenio, para ejecutarlas.
 *
 * \param bd Doble puntero a la base de datos SQLite.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos, ERROR_SIN_MEMORIA en caso de no poder asignar memoria dinamica, y ERROR_OPERACION si el archivo "schema.sql" es invalido.
 *
 */
int inicializarBaseDatos(sqlite3 **bd);

/** \brief Inicializar los recursos del servidor.
 *
 * Iniciar la API de Winsock, inicializar la base de datos y crear el socket del servidor, la tabla hash de clientes y la lista simple de clientes
 * conectados pero no autenticados.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de fallas al inicializar recursos.
 *
 */
int inicializarServidor (t_contextoServidor *contextoServidor);

/** \brief Configurar los recursos del servidor.
 *
 * Configurar el socket del servidor para escuchar conexiones de cualquier direccion IP en el puerto asignado. Ademas, establecerlo como modo no bloqueante.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 * \return EXITO si se configuro correctamente, ERROR_CONFIGURACION en caso de error.
 *
 */
int configurarServidor (t_contextoServidor *contextoServidor);

/** \brief Liberar los recursos del servidor.
 *
 * Vaciar la lista simple de clientes conectados pero no autenticados, vaciar y eliminar la tabla hash de clientes y cerrar el socket del servidor,
 * la base de datos y la API de Winsock.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 *
 */
void liberarServidor (t_contextoServidor *contextoServidor);



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

/** \brief Verifica y procesa la solicitud de solicitud de contacto
 *
 * Consulta en la base de datos si existe el usuario receptor.
 * Si existe, inserta en la base de datos la solicitud de amistad.
 * Le responde al cliente el resultado del proceso y, si el usuario receptor esta conectado, le envia la solicitud de amistad.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 * \param clienteAProcesar Referencia al cliente que envio la solicitud y se debe procesar.
 * \param buffersComunicacion Puntero a la estructura que contiene los buffers necesarios para la comunicacion entre el cliente y el servidor.
 *
 * \return OK si se proceso correctamente, ERROR_SIN_MEMORIA si no se pudo asignar memoria dinamica o ERROR_INICIALIZACION si no se pudo realizar una consulta SQLite.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
//int manejarSolicitudContacto (t_contextoServidor *contextoServidor, t_nodo **clienteAProcesar, t_buffersComunicacion *buffersComunicacion);



#endif // LOGICASERVIDOR_H_INCLUDED



























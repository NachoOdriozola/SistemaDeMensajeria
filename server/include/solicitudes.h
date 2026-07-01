/**
 * \file   solicitudes.h
 * \brief  Contiene funciones que procesan las solicitudes de los clientes.
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
#include "../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"
#include "../../shared/estructurasDeDatos/tablaHash/include/tablaHash.h"
#include "estructuras.h"
#include "utiles.h"
#include "baseDeDatos.h"


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/**
 * \struct t_datosAutenticacionUsuario
 * \brief  Almacena los datos recibidos de autenticacion del usuario.
 */
typedef struct 
{
   char nombreUsuario [MAX_NOMBRE_USUARIO];
   char contrasenia [MAX_CONTRASENIA];
} t_datosAutenticacionUsuario;

/**
 * \struct t_datosRegistroUsuario
 * \brief  Almacena los datos recibidos de registro del usuario.
 */
typedef struct
{
   char nombreUsuario [MAX_NOMBRE_USUARIO];
   char contrasenia [MAX_CONTRASENIA];
   char correoElectronico [MAX_CORREO_ELECTRONICO];
} t_datosRegistroUsuario;

/**
 * \struct t_datosEnvioMensaje
 * \brief  Almacena los datos recibidos de envio de mensaje del usuario.
 */
typedef struct
{
   int idEmisor;
   int idReceptor;
   char texto [MAX_MENSAJE];
} t_datosEnvioMensaje;

/**
 * \struct t_datosSeleccionChat
 * \brief  Almacena los datos recibidos de seleccion de chat del usuario.
 */
typedef struct
{
   char nombreReceptor [MAX_NOMBRE_USUARIO];
} t_datosSeleccionChat;


/**
 * \struct t_respuestaSeleccionChat
 * \brief  Almacena los datos a responder de seleccion de chat del usuario.
 */
typedef struct
{
   t_estadoSolicitud estadoSolicitud;
   int idUsuarioDelChatSeleccionado;
} t_respuestaSeleccionChat;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Procesar la solicitud enviada por el cliente y enviarle una respuesta.
 *
 * \param contextoServidor Puntero a la estructura que provee contexto (estados y recursos) global del servidor.
 * \param clienteAProcesar Direccion del nodo del cliente que envio la solicitud y se debe procesar.
 * \param solicitud Contiene la solicitud a procesar enviada por el cliente.
 *
 */
void procesarSolicitud (t_contextoServidor *contextoServidor, t_nodoListaDoble *clienteAProcesar, const char *solicitud);



#endif // SOLICITUDES_H_INCLUDED
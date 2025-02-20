#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


///INCLUDES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdbool.h>
#include <sqlite3.h>

#include "../../EstructurasDeDatos/ListaSimple/listaSimple.h"
#include "../Servidor/estructuras.h"


///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_SERVIDOR 1
#define APAGAR_SERVIDOR 0

#define MAX_BUFFER_SOLICITUD 256
#define MAX_BUFFER_RESPUESTA 256
#define MAX_BUFFER_CONSULTA 101

#define NO_ACEPTO_CLIENTE 1

#define SOLICITUD_RECIBIDA 1
#define SOLICITUD_NO_RECIBIDA 0


///FUNCIONES LOGICAS

int aceptarCliente (s_servidor *servidor);
int recibirSolicitud (s_servidor *servidor, char *bufferSolicitud, char *solicitud);
void procesarInicioSesion (s_servidor *servidor, sqlite3 *db, char *bufferSolicitud);
void procesarRegistro (s_servidor *servidor, sqlite3 *db, char *bufferSolicitud);
void procesarSolicitudAmistad (s_servidor *servidor, sqlite3 *db, char *bufferSolicitud);
void procesarNotificaciones (s_servidor *servidor, sqlite3 *db, char *bufferSolicitud);
void liberarCliente (void *cliente);


#endif // FUNCIONES_H_INCLUDED



























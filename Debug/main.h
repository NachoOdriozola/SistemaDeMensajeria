#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>


#define PUERTO 8080

#define OK 0
#define ERROR_INICIALIZACION -1

#define INDICE_INICIO_SESION '1'
#define INDICE_REGISTRO '2'
#define INDICE_MENSAJE '3'
#define INDICE_SOLICITUD_AMISTAD '4'
#define INDICE_NOTIFICACIONES '5'

#define SOLICITUD_ACEPTADA '1'
#define SOLICITUD_RECHAZADA '0'

#define MAX_BUFFER_SOLICITUD 256
#define MAX_BUFFER_RESPUESTA 256

#define MAX_NOMBRE_USUARIO 26
#define MAX_CONTRASENIA_USUARIO 46


void enviarYRecibirSolicitud (SOCKET sock, char *bufferSolicitud, char *bufferRespuesta);


#endif // MAIN_H_INCLUDED

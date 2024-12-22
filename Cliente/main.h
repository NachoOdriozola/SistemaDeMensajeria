#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "interfazInicio.h"
#include "interfazMensajes.h"

#define INTERFAZ_INICIO 1
#define INTERFAZ_MENSAJES 2

typedef struct
{
    sfRenderWindow *renderizado;
    bool estado;
} s_aplicacion;

typedef struct
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;
    u_long modoSocket;
} s_socket;

typedef struct
{
    char nombreUsuario [21];
    bool estado;
} s_usuario;

void inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes);
void setup (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes);

#endif // MAIN_H_INCLUDED

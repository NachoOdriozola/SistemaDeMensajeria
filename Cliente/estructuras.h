#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"
#include "SFML/Network.h"

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

#endif // ESTRUCTURAS_H_INCLUDED

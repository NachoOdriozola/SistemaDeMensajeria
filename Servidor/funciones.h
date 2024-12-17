#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "../ListaSimple/listaSimple.h"

#define PUERTO 8080
#define MAX_BUFFER 512

typedef struct
{
    SOCKET sock;
    struct sockaddr_in direccion;
    int tamCliente;
} t_cliente;

BOOL WINAPI manejadorDeConsola (DWORD senial);

#endif // FUNCIONES_H_INCLUDED

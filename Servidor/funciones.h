#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
<<<<<<< HEAD

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
=======
#include <stdbool.h>

#include "../ListaSimple/listaSimple.h"

#define OK 0
#define SIN_MEMORIA -1

#define MAX_BUFFER 512

#define PUERTO 8080
#define ERROR_ACEPTAR_CLIENTE 1
#define MENSAJE_RECIBIDO 1
#define NO_RECIBIO_MENSAJE 0

#define CONTINUAR_SERVIDOR 1
#define APAGAR_SERVIDOR 0

typedef struct
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;
    bool estado;
} s_servidor;

typedef struct
{
    SOCKET sock;
    struct sockaddr_in direccionCliente;
} s_cliente;

void inicializar (s_servidor *servidor);
void setup (s_servidor *servidor);
int aceptarCliente (s_servidor *servidor, s_lista *listaClientes);
int recibirMensajes (s_lista *listaClientes, char *buffer);
void enviarMensajes (s_lista *listaClientes, char *buffer);
void liberarCliente (void *cliente);
void liberar (s_servidor *servidor, s_lista *listaClientes);

#endif // FUNCIONES_H_INCLUDED



























>>>>>>> servidor

#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "../ListaSimple/listaSimple.h"


#define OK 0
#define ERROR_INICIALIZACION_SERVIDOR -1

#define CONTINUAR_SERVIDOR 1
#define APAGAR_SERVIDOR 0

#define NO_ACEPTO_CLIENTE 1

#define MENSAJE_RECIBIDO 1
#define NO_RECIBIO_MENSAJE 0

#define ENVIO_MENSAJE 1
#define NO_ENVIO_MENSAJE 0

#define MAX_BUFFER 512
#define PUERTO 8080


typedef struct
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;
} s_servidor;

typedef struct
{
    SOCKET sock;
    struct sockaddr_in direccionCliente;
    bool envioMensaje;
} s_cliente;


int inicializar (s_servidor *servidor);
int setup (s_servidor *servidor);
int aceptarCliente (s_servidor *servidor, s_lista *listaClientes);
int recibirMensajes (s_lista *listaClientes, char *buffer);
void enviarMensajes (s_lista *listaClientes, char *buffer);
void liberarCliente (void *cliente);
void liberar (s_servidor *servidor, s_lista *listaClientes);


#endif // FUNCIONES_H_INCLUDED



























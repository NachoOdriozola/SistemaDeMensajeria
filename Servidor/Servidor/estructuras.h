#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED


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

#include "../ListaSimple/listaSimple.h"

///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define SOLICITUD_ACEPTADA 1
#define SOLICITUD_RECHAZADA 0

#define INDICE_INICIO_SESION '1'
#define INDICE_REGISTRO '2'
#define INDICE_MENSAJE '3'

#define MAX_BUFFER_NOMBRE 26


///ESTRUCTURAS

typedef struct
{
    SOCKET sockServidor;
    s_lista listaClientes;
    s_nodo *clienteAProcesar;
} s_servidor;

typedef struct
{
    SOCKET sock;
    int id;
    char nombre [MAX_BUFFER_NOMBRE];
} s_cliente;


#endif // ESTRUCTURAS_H_INCLUDED














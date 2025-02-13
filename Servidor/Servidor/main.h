#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


///INCLUDES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <sqlite3.h>

#include "estructuras.h"
#include "../../EstructurasDeDatos/ListaSimple/listaSimple.h"
#include "../FuncionesServidor/funcionesServidor.h"


///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define TECLA_APAGAR_SERVIDOR 'Q'

#define MAX_BUFFER_SOLICITUD 256

#define PUERTO 8080


///FUNCIONES ESTRUCTURALES

int inicializar (s_servidor *servidor, sqlite3 **db);
int setup (s_servidor *servidor);
void liberar (s_servidor *servidor, sqlite3 *db);


#endif // MAIN_H_INCLUDED














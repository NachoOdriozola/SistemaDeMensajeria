#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "estructuras.h"
#include "../Interfaz/interfazInicio.h"
#include "../Interfaz/interfazMensajes.h"


#define INTERFAZ_INICIO 1
#define INTERFAZ_MENSAJES 2

#define OK 0
#define ERROR_INICIALIZACION -1
#define CERRAR_APLICACION 0


void inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes);
void setup (s_aplicacion *app, s_socket *sock, s_recursosGraficosInicio *recursosGraficosInicio, s_recursosGraficosMensajes *recursosGraficosMensajes);
void liberar (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);


#endif // MAIN_H_INCLUDED

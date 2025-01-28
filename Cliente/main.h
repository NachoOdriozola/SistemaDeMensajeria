#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


///INCLUDES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "estructuras.h"
#include "../FuncionesEspecificas/especificas.h"
#include "../Interfaces/interfazInicio.h"
#include "../Interfaces/interfazRegistro.h"
#include "../Interfaces/interfazAmigos.h"
#include "../Interfaces/interfazSalas.h"
#include "../Interfaces/interfazConfig.h"


///DEFINES

#define PUERTO 8080

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define ACTIVO 1
#define AUSENTE 0


///ESTRUCTURAS

typedef struct
{
    s_recursosGraficosInicio recursosGraficosInicio;
    s_recursosGraficosRegistro recursosGraficosRegistro;
    s_recursosGraficosAmigos recursosGraficosAmigos;
    s_recursosGraficosSalas recursosGraficosSalas;
    s_recursosGraficosConfig recursosGraficosConfig;
} s_recursosGraficos;


///FUNCIONES ESTRUCTURALES

int inicializar (s_aplicacion *app, s_socket *sock, s_recursosGraficos *recursosGraficos);
void setup (s_aplicacion *app, s_socket *sock, s_recursosGraficos *recursosGraficos);
void liberar (s_aplicacion *app, s_socket *sock, s_recursosGraficos *recursosGraficos);


#endif // MAIN_H_INCLUDED


















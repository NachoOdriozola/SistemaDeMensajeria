#ifndef INTERFAZCONFIG_H_INCLUDED
#define INTERFAZCONFIG_H_INCLUDED


///INCLUDES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"

#include "../Cliente/estructuras.h"
#include "../FuncionesUtiles/utiles.h"


///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0


///ESTRUCTURAS

typedef struct
{
    sfText *textoConfig;
} s_textoConfig;

typedef struct
{
    sfRectangleShape *rectanguloVolver;
} s_elementosConfig;

typedef struct
{
    s_textoConfig texto;
    s_elementosConfig elementos;
} s_recursosGraficosConfig;


///FUNCIONES ESTRUCTURALES

int inicializarConfig (s_recursosGraficosConfig *recursosGraficosConfig);
void setupConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig);
void tamYPosPantallaConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig);
void accionConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig);
void actualizarConfig (s_recursosGraficosConfig *recursosGraficosConfig);
void renderizarConfig (s_aplicacion *app, s_recursosGraficosConfig *recursosGraficosConfig);
void liberarConfig (s_recursosGraficosConfig *recursosGraficosConfig);


#endif // INTERFAZCONFIG_H_INCLUDED




























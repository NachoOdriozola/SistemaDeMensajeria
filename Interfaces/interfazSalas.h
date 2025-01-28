#ifndef INTERFAZSALAS_H_INCLUDED
#define INTERFAZSALAS_H_INCLUDED


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
#include "../ListaCircular/listaCircular.h"


///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0


///ESTRUCTURAS

typedef struct
{
    sfFont *fuente;
    sfText *salas;
} s_textoSalas;

typedef struct
{
    sfRectangleShape *rectanguloAmigos;
    sfRectangleShape *rectanguloConfig;
} s_elementosSalas;

typedef struct
{
    s_textoSalas texto;
    s_elementosSalas elementos;
} s_recursosGraficosSalas;


///FUNCIONES ESTRUCTURALES

int inicializarSalas (s_recursosGraficosSalas *recursosGraficosSalas);
void setupSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void tamYPosPantallaSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void accionSalas (s_aplicacion *app, s_socket *sock, s_recursosGraficosSalas *recursosGraficosSalas);
void actualizarSalas (s_aplicacion *app, s_socket *sock, s_recursosGraficosSalas *recursosGraficosSalas);
void renderizarSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void liberarSalas (s_recursosGraficosSalas *recursosGraficosSalas);


#endif // INTERFAZSALAS_H_INCLUDED



















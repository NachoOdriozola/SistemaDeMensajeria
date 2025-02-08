#ifndef INTERFAZAMIGOS_H_INCLUDED
#define INTERFAZAMIGOS_H_INCLUDED


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

#define HABILITAR_ESCRITURA 1
#define DESHABILITAR_ESCRITURA 0

#define MI_USUARIO 1
#define OTRO_USUARIO 0

#define MAX_BUFFER_MENSAJE 256


///ESTRUCTURAS

typedef struct
{
    sfText *amigos;
    sfText *salas;
    sfText *nombreUsuario;
    sfText *interfazConfig;
    sfText *auxEscribirMensaje;
} s_textoAmigos;

typedef struct
{
    sfRectangleShape *rectanguloAmigos;
    sfRectangleShape *rectanguloSalas;
    sfRectangleShape *cuadradoRelieveRecSalas;
    sfRectangleShape *barraSeparacionAmigos;
    sfRectangleShape *barraSeparacionNombre;
    sfRectangleShape *barraIngresarMensaje;
} s_elementosAmigos;

typedef struct
{
    s_textoAmigos texto;
    s_elementosAmigos elementos;
    bool habilitarEscritura;
    char bufferEscribirMensaje [MAX_BUFFER_MENSAJE];
} s_recursosGraficosAmigos;


///FUNCIONES ESTRUCTURALES

int inicializarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos);
void setupAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void tamYPosPantallaAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void accionAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void actualizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void renderizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void liberarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos);


#endif // INTERFAZAmigos_H_INCLUDED




















#ifndef INTERFAZREGISTRO_H_INCLUDED
#define INTERFAZREGISTRO_H_INCLUDED

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
    sfFont *fuente;
    sfText *registrarse;
} s_textoRegistro;

typedef struct
{
    sfRectangleShape *rectanguloInvisibleVolver;
} s_elementosRegistro;

typedef struct
{
    s_textoRegistro texto;
    s_elementosRegistro elementos;
} s_recursosGraficosRegistro;


///FUNCIONES ESTRUCTURALES

int inicializarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void setupRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void tamYPosPantallaRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void accionRegistro (s_aplicacion *app, s_recursosGraficosRegistro *recursosGraficosRegistro);
void actualizarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void renderizarRegistro (s_aplicacion *app, s_recursosGraficosRegistro *recursosGraficosRegistro);
void liberarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);


#endif // INTERFAZREGISTRO_H_INCLUDED




















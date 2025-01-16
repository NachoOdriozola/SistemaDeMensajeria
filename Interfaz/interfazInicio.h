#ifndef INTERFAZINICIO_H_INCLUDED
#define INTERFAZINICIO_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "../Cliente/estructuras.h"

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"


#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define ACTIVO 1
#define AUSENTE 0

#define PUERTO 8080
#define MAX_BUFFER 512


typedef struct
{

} s_textoInicio;

typedef struct
{
    sfRectangleShape *rectanguloCentral;
} s_elementosInicio;

typedef struct
{
    s_textoInicio texto;
    s_elementosInicio elementos;
} s_recursosGraficosInicio;


///FUNCIONES ESTRUCTURALES
int inicializarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void setupInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void accionInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void actualizarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio);

///FUNCIONES LOGICAS
void modificarTamPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio, sfVector2f nuevoTamPantalla);


#endif // INTERFAZINICIO_H_INCLUDED


















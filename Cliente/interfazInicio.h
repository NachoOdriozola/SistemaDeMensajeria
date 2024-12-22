#ifndef INTERFAZINICIO_H_INCLUDED
#define INTERFAZINICIO_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"
#include "SFML/Network.h"

#define OK 0
#define ERROR_INICIALIZACION -1
#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define ACTIVO 1
#define AUSENTE 0

#define PUERTO 8080

#define MAX_BUFFER 512

#include "main.h"

typedef struct
{

} s_recursosGraficosInicio;

void inicializarInicio ();
void accionInicio ();
void actualizarInicio ();
void renderizarInicio ();
void liberarInicio ();

#endif // INTERFAZINICIO_H_INCLUDED

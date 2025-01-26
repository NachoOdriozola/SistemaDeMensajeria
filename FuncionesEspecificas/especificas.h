#ifndef ESPECIFICAS_H_INCLUDED
#define ESPECIFICAS_H_INCLUDED


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


///FUNCIONES DE INICIALIZACION ESPECIFICAS
void crearEscalaElementos (s_aplicacion *app);
void crearEscalaPixeles (s_aplicacion *app);
void eventoMaximizadoAutomatico (s_aplicacion *app);
void maximizadoAutomaticoVentana (s_aplicacion *app);


#endif // ESPECIFICAS_H_INCLUDED












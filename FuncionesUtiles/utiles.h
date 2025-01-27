#ifndef FUNCIONESGENERALES_H_INCLUDED
#define FUNCIONESGENERALES_H_INCLUDED


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


#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0


///FUNCIONES UTILES
void ajustarVista (s_aplicacion *app, sfVector2f nuevoTamPantalla);
bool clickEnRectangulo (sfRenderWindow *renderizado, sfRectangleShape *rectangulo);
void ingresoTexto (char *buffer, int maxIngreso, sfEvent evento);



#endif // FUNCIONESGENERALES_H_INCLUDED

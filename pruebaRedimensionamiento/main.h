#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

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

sfRenderWindow *renderizado;
sfRectangleShape *rectangulo;
sfText *texto;
sfFont *fuente;
sfVector2f tamOriginalVentana;
bool cerrar;

void inicializar ();
void setup ();
void accion ();
void actualizar ();
void renderizar ();
void liberar ();
void ajustarVista (sfVector2f nuevoTamPantalla);

#endif // MAIN_H_INCLUDED

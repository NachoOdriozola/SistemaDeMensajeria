#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

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


typedef struct
{
    sfVector2f tamOriginalPantalla;
    sfVector2f tamActualPantalla;
    float escala;
} s_ventana;

typedef struct
{
    sfRenderWindow *renderizado;
    s_ventana ventana;
    bool primerMaximizado;
    bool aplicacionEjecutandose;
} s_aplicacion;

typedef struct
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;
} s_socket;


#endif // ESTRUCTURAS_H_INCLUDED





















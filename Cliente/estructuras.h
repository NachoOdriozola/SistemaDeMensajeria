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

#define MAX_BUFFER_MENSAJE 50

#define MAX_NOMBRE_USUARIO 21
#define MAX_CONTRASENIA_USUARIO 21

#define RESOLUCION_BASE_MAXIMIZADO_X 1920
#define RESOLUCION_BASE_MAXIMIZADO_Y 1009

#define INTERFAZ_INICIO 1
#define INTERFAZ_MENSAJES 2


typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    bool actividadUsuario;
} s_usuario;

typedef struct
{
    sfVector2f tamOriginalPantalla;
    sfVector2f tamActualPantalla;
    sfVector2f escalaElementos;
    float escalaPixeles;
} s_ventana;

typedef struct
{
    sfRenderWindow *renderizado;
    s_usuario usuario;
    s_ventana ventana;
    unsigned short int interfaz;
    bool aplicacionEjecutandose;
} s_aplicacion;

typedef struct
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;
} s_socket;

typedef struct
{
    char nombreUsuario [MAX_NOMBRE_USUARIO];
    char bufferMensaje [MAX_BUFFER_MENSAJE];
} s_paqueteMensaje;


#endif // ESTRUCTURAS_H_INCLUDED





















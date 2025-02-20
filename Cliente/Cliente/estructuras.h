#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED


///INCLUDES

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

#include "../../EstructurasDeDatos/ListaCircular/listaCircular.h"
#include "../../EstructurasDeDatos/ListaSimple/listaSimple.h"


///DEFINES

#define INDICE_INICIO_SESION '1'
#define INDICE_REGISTRO '2'
#define INDICE_MENSAJE '3'
#define INDICE_SOLICITUD_AMISTAD '4'
#define INDICE_NOTIFICACIONES '5'

#define SOLICITUD_ACEPTADA '1'
#define SOLICITUD_RECHAZADA '0'

#define MAX_NOMBRE_USUARIO 26
#define MAX_CONTRASENIA_USUARIO 46

#define MAX_BUFFER_SOLICITUD 256
#define MAX_BUFFER_RESPUESTA 256

#define RESOLUCION_BASE_MAXIMIZADO_X 1920
#define RESOLUCION_BASE_MAXIMIZADO_Y 1009

#define INTERFAZ_INICIO 1
#define INTERFAZ_REGISTRO 2
#define INTERFAZ_AMIGOS 3
#define INTERFAZ_SALAS 4
#define INTERFAZ_CONFIG 5


///ESTRUCTURAS

typedef struct
{
    int id;
    char nombre [MAX_NOMBRE_USUARIO];
    unsigned short int ultimaInterfaz;
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
    sfFont *fuente1;
} s_fuentes;

typedef struct
{
    s_listaCircular listaMensajes;
    s_nodo *siguienteMensaje;
    s_fuentes fuentes;
} s_mensajes;

typedef struct
{
    sfRenderWindow *renderizado;
    SOCKET sock;
    s_usuario usuario;
    s_ventana ventana;
    s_mensajes mensajes;
    s_lista listaNotificaciones;
    unsigned short int interfaz;
    bool aplicacionEjecutandose;
} s_aplicacion;

typedef struct
{
    sfText *mensaje;
    sfVector2f posMensaje;
} s_mensaje; //Eliminar esta estructura

typedef struct
{
    int id;
    char nombre [MAX_NOMBRE_USUARIO];
} s_datosGuardados;


#endif // ESTRUCTURAS_H_INCLUDED





















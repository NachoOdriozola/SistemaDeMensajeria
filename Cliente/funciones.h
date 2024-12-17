#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

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

#define PUERTO 8080

#define MAX_BUFFER 201

typedef struct
{
    sfRenderWindow *renderizado;
    bool aplicacionEjecutandose;
} s_estadoAplicacion;

typedef struct
{
    sfFont *fuente;
    sfText *texto;
} s_texto;

typedef struct
{
    s_texto texto;
} s_recursos;

typedef struct
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;
    u_long modoSocket;
} s_socket;

void inicializar (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock);
void setup (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock);
//En accion se utiliza logica que cambie el estado de la aplicacion pero que SI este relacionada con la interaccion del usuario.
void accion (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock);
//En actualizar se utiliza logica que cambie el estado de la aplicacion pero que NO este relacionada con la interaccion del usuario.
void actualizar (s_recursos *recursos, s_socket *sock);
void renderizar (const s_estadoAplicacion *app, s_recursos *recursos);
void liberar (s_estadoAplicacion *app, s_recursos *recursos, s_socket *sock);

#endif // FUNCIONES_H_INCLUDED















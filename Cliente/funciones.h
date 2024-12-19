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

#define ACTIVO 1
#define AUSENTE 0

#define PUERTO 8080

#define MAX_BUFFER 201


typedef struct
{
    sfRenderWindow *renderizado;
    bool aplicacionEjecutandose;
} s_estadoAplicacion;

typedef struct
{
    char nombreUsuario [21];
    bool estado;
} s_usuario;

typedef struct
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in direccionServidor;
    u_long modoSocket;
} s_socket;

typedef struct
{
    sfFont *fuente;
    sfText *texto;
} s_texto;

typedef struct
{
    sfRectangleShape *recIzquierda;
    sfRectangleShape *barraSeparacionUsuarios;
    sfRectangleShape *barraSeparacionNombre;
    sfText *textoAuxUsuariosActivos;
    sfText *textoNombreUsuario;
} s_elementos;
//pasar sftext de s_elementos a s_texto
typedef struct
{
    s_texto texto;
    s_elementos elementos;
} s_recursosGraficos;

typedef struct


///INICIALIZACION
void inicializar (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock);
void setup (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock);

///INTERFAZ DE INICIO
void accionInicio ();
void actualizarInicio ();
void renderizarInicio ();
void liberarInicio ();

///INTERFAZ DE MENSAJES
void accionMensajes (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock);
void actualizarMensajes (s_recursosGraficos *recursosGraficos, s_socket *sock);
void renderizarMensajes (const s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos);
void liberarMensajes (s_estadoAplicacion *app, s_recursosGraficos *recursosGraficos, s_socket *sock);

#endif // FUNCIONES_H_INCLUDED















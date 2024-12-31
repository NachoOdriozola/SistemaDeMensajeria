#ifndef INTERFAZMENSAJES_H_INCLUDED
#define INTERFAZMENSAJES_H_INCLUDED

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
#include "SFML/Network.h"

#include "../Cliente/estructuras.h"

#define OK 0
#define ERROR_INICIALIZACION -1
#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define ACTIVO 1
#define AUSENTE 0
#define HABILITAR_ESCRITURA 1
#define DESHABILITAR_ESCRITURA 0

#define PUERTO 8080

#define MAX_BUFFER 512

typedef struct
{
    sfFont *fuente;
    sfText *mensajeRecibido;
    sfText *mensajeEnviado;
    sfText *auxUsuariosActivos;
    sfText *nombreUsuario;
    sfText *auxEscribirMensaje;
} s_texto;

typedef struct
{
    sfRectangleShape *recIzquierda;
    sfRectangleShape *barraSeparacionUsuarios;
    sfRectangleShape *barraSeparacionNombre;
    sfRectangleShape *barraIngresarMensaje;
} s_elementos;

typedef struct
{
    char bufferMensaje [MAX_BUFFER];
    bool habilitarEscritura;
    s_texto texto;
    s_elementos elementos;
} s_recursosGraficosMensajes;

int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);
void setupMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);
void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void actualizarMensajes (s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void renderizarMensajes (const s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);
void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);

void modificarTamPantalla (s_recursosGraficosMensajes *recursosGraficosMensajes, sfVector2u tamOriginalPantalla, sfVector2f nuevoTamPantalla);
bool clickEnEscribirMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);

#endif // INTERFAZMENSAJES_H_INCLUDED




















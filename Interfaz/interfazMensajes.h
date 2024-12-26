#ifndef INTERFAZMENSAJES_H_INCLUDED
#define INTERFAZMENSAJES_H_INCLUDED

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

#include "../Cliente/estructuras.h"

#define OK 0
#define ERROR_INICIALIZACION -1
#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define ACTIVO 1
#define AUSENTE 0

#define PUERTO 8080

#define MAX_BUFFER 512

typedef struct
{
    sfFont *fuente;
    sfText *mensajeRecibido;
    sfText *textoAuxUsuariosActivos;
    sfText *textoNombreUsuario;
} s_texto;

typedef struct
{
    sfRectangleShape *recIzquierda;
    sfRectangleShape *barraSeparacionUsuarios;
    sfRectangleShape *barraSeparacionNombre;
} s_elementos;

typedef struct
{
    s_texto texto;
    s_elementos elementos;
    sfView *pantalla;
} s_recursosGraficosMensajes;

int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);
void setupMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);
void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void actualizarMensajes (s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void renderizarMensajes (const s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);
void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);

void modificarTamPantalla (s_recursosGraficosMensajes *recursosGraficosMensajes, sfVector2f tamPantalla);

#endif // INTERFAZMENSAJES_H_INCLUDED




















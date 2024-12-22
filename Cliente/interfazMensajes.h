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

#define OK 0
#define ERROR_INICIALIZACION -1
#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define ACTIVO 1
#define AUSENTE 0

#define PUERTO 8080

#define MAX_BUFFER 512

#include "main.h"

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
} s_recursosGraficosMensajes;

void inicializarMensajes ();
void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void actualizarMensajes (s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void renderizarMensajes (const s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);
void liberarMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);

#endif // INTERFAZMENSAJES_H_INCLUDED

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

#include "../Cliente/estructuras.h"
#include "../ListaCircular/listaCircular.h"

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define HABILITAR_ESCRITURA 1
#define DESHABILITAR_ESCRITURA 0

#define MI_USUARIO 1
#define OTRO_USUARIO 0

#define PRIMER_MAXIMIZADO 1
#define NO_PRIMER_MAXIMIZADO 0

#define MAX_BUFFER 512
#define MAX_MENSAJES_EN_MEM 5


typedef struct
{
    sfFont *fuente;
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
    sfText *mensaje;
    bool enviadoPor;
    sfVector2f posicionMensaje;
} s_mensaje;

typedef struct
{
    s_texto texto;
    s_elementos elementos;
    bool habilitarEscritura;
    char bufferEscribirMensaje [MAX_BUFFER];
    s_nodo *siguienteMensaje;
    s_listaCircular listaMensajes;
} s_recursosGraficosMensajes;


///FUNCIONES ESTRUCTURALES
int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);
void setupMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);
void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void actualizarMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void renderizarMensajes (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);
void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);

///FUNCIONES LOGICAS
void asignarMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, const char *bufferMensaje, bool enviadoPor);
void modificarTamPantalla (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, sfVector2f nuevoTamPantalla);
bool clickEnEscribirMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);

///FUNCIONES COMPLEMENTARIAS
void renderizarListaMensajes (void *mensaje, void *renderizado);
void modificarPosicionMensajes (void *mensaje, void *escala);
void modificarTamYPosMensajes (void *mensaje, void *nuevoTamPantalla, void *app);
void setupListaMensaje (void *mensaje, void *recursosGraficosMensajes);
void liberarMensaje (void *mensaje);


#endif // INTERFAZMENSAJES_H_INCLUDED




















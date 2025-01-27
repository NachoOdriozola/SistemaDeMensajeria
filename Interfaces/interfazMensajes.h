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
#include "../FuncionesUtiles/utiles.h"
#include "../ListaCircular/listaCircular.h"


#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define HABILITAR_ESCRITURA 1
#define DESHABILITAR_ESCRITURA 0

#define MI_USUARIO 1
#define OTRO_USUARIO 0

#define MAX_BUFFER_MENSAJE 256
#define MAX_MENSAJES_EN_MEM 5


typedef struct
{
    sfFont *fuente;
    sfText *textoUsuariosActivos;
    sfText *nombreUsuario;
    sfText *auxEscribirMensaje;
} s_textoMensajes;

typedef struct
{
    sfRectangleShape *recIzquierda;
    sfRectangleShape *barraSeparacionUsuarios;
    sfRectangleShape *barraSeparacionNombre;
    sfRectangleShape *barraIngresarMensaje;
} s_elementosMensajes;

typedef struct
{
    s_textoMensajes texto;
    s_elementosMensajes elementos;
    bool habilitarEscritura;
    char bufferEscribirMensaje [MAX_BUFFER_MENSAJE];
    s_nodo *siguienteMensaje;
    s_listaCircular listaMensajes;
} s_recursosGraficosMensajes;

typedef struct
{
    sfText *mensaje;
    sfVector2f posicionMensaje;
} s_mensaje;

void ajustarMensajeDerecha(char* mensaje, sfText* texto, float anchoMaximo);
///FUNCIONES ESTRUCTURALES
int inicializarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);
void setupMensajes (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);
void TamYPosPantallaMensajes (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);
void accionMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void actualizarMensajes (s_aplicacion *app, s_socket *sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void renderizarMensajes (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes);
void liberarMensajes (s_recursosGraficosMensajes *recursosGraficosMensajes);


///FUNCIONES LOGICAS
void enviarPaqueteMensaje (s_aplicacion *app, SOCKET sock, s_recursosGraficosMensajes *recursosGraficosMensajes);
void asignarMensaje (s_aplicacion *app, s_recursosGraficosMensajes *recursosGraficosMensajes, const char *bufferMensaje, bool enviadoPor);


///FUNCIONES COMPLEMENTARIAS
void setupListaMensajes (void *mensaje, void *recursosGraficosMensajes);
void tamListaMensajes (void *mensaje, void *escalaPixeles);
void modificarPosicionListaMensajes (void *mensaje, void *escalaPixeles);
void renderizarListaMensajes (void *mensaje, void *renderizado);
void liberarMensaje (void *mensaje);


#endif // INTERFAZMENSAJES_H_INCLUDED




















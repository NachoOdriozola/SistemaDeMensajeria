#ifndef INTERFAZAMIGOS_H_INCLUDED
#define INTERFAZAMIGOS_H_INCLUDED


///INCLUDES

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
#include "../../EstructurasDeDatos/ListaCircular/listaCircular.h"


///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define HABILITAR_AGREGAR_AMIGOS 1
#define DESHABILITAR_AGREGAR_AMIGOS 0

#define HABILITAR_ESCRITURA_MENSAJES 1
#define DESHABILITAR_ESCRITURA_MENSAJES 0

#define HABILITAR_ESCRITURA_AGREGAR_AMIGOS 1
#define DESHABILITAR_ESCRITURA_AGREGAR_AMIGOS 0

#define MI_USUARIO 1
#define OTRO_USUARIO 0

#define MAX_BUFFER_MENSAJE 256


///ESTRUCTURAS

typedef struct
{
    sfText *amigos;
    sfText *agregarAmigos;
    sfText *salas;
    sfText *nombreUsuario;
    sfText *interfazConfig;
    sfText *auxEscribirMensaje;
    sfText *tituloAgregarAmigos;
    sfText *cerrarAgregarAmigos;
    sfText *auxAgregarAmigos;
} s_textoAmigos;

typedef struct
{
    sfRectangleShape *rectanguloAmigos;
    sfRectangleShape *rectanguloSalas;
    sfRectangleShape *cuadradoRelieveRecSalas;
    sfRectangleShape *barraSeparacionAmigos;
    sfRectangleShape *barraSeparacionNombre;
    sfRectangleShape *barraIngresarMensaje;
    sfRectangleShape *recBaseAgregarAmigos;
    sfRectangleShape *barraAgregarAmigos;
} s_elementosAmigos;

typedef struct
{
    bool agregarAmigos;
    bool habilitarEscrituraMensajes;
    bool habilitarEscrituraAgregarAmigos;
} s_habilitacionesAmigos;

typedef struct
{
    s_textoAmigos texto;
    s_elementosAmigos elementos;
    s_habilitacionesAmigos habilitaciones;
    char bufferEscribirMensaje [MAX_BUFFER_MENSAJE];
    char bufferAgregarAmigos [MAX_NOMBRE_USUARIO];
} s_recursosGraficosAmigos;


///FUNCIONES ESTRUCTURALES

int inicializarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos);
void setupAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos, s_fuentes fuentes);
void tamYPosPantallaAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos, s_ventana ventana);
void accionAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void actualizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void renderizarAmigos (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);
void liberarAmigos (s_recursosGraficosAmigos *recursosGraficosAmigos);


///FUNCIONES LOGICAS

void intentarSolicitudAmistad (s_aplicacion *app, s_recursosGraficosAmigos *recursosGraficosAmigos);


#endif // INTERFAZAmigos_H_INCLUDED




















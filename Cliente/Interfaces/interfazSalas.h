#ifndef INTERFAZSALAS_H_INCLUDED
#define INTERFAZSALAS_H_INCLUDED


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

#define HABILITAR_ESCRITURA 1
#define DESHABILITAR_ESCRITURA 0

#define HABILITAR_BARRA_ESCRIBIENDO_MENSAJE 1
#define DESHABILITAR_BARRA_ESCRIBIENDO_MENSAJE 0

#define MI_USUARIO 1
#define OTRO_USUARIO 0

#define MAX_BUFFER_MENSAJE 256
#define MAX_MENSAJES_EN_MEM 5


///ESTRUCTURAS

typedef struct
{
    sfText *salas;
    sfText *amigos;
    sfText *nombreUsuario;
    sfText *interfazConfig;
    sfText *auxEscribirMensaje;
} s_textoSalas;

typedef struct
{
    sfRectangleShape *rectanguloSalas;
    sfRectangleShape *rectanguloAmigos;
    sfRectangleShape *cuadradoRelieveRecAmigos;
    sfRectangleShape *barraSeparacionSalas;
    sfRectangleShape *barraSeparacionNombre;
    sfRectangleShape *barraIngresarMensaje;
    sfRectangleShape *barraEscribiendoMensaje;
} s_elementosSalas;

typedef struct
{
    bool habilitarEscritura;
    bool habilitarBarraEscribiendoMensaje;
    unsigned short int tempHabilitarBarra;
} s_habilitacionesSalas;

typedef struct
{
    s_textoSalas texto;
    s_elementosSalas elementos;
    s_habilitacionesSalas habilitaciones;
    char bufferEscribirMensaje [MAX_BUFFER_MENSAJE];
} s_recursosGraficosSalas;


///FUNCIONES ESTRUCTURALES

int inicializarSalas (s_recursosGraficosSalas *recursosGraficosSalas);
void setupSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void tamYPosPantallaSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void accionSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void actualizarSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void renderizarSalas (s_aplicacion *app, s_recursosGraficosSalas *recursosGraficosSalas);
void liberarSalas (s_recursosGraficosSalas *recursosGraficosSalas);


#endif // INTERFAZSALAS_H_INCLUDED



















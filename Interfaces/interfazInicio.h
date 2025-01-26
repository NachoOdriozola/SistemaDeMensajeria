#ifndef INTERFAZINICIO_H_INCLUDED
#define INTERFAZINICIO_H_INCLUDED


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "../FuncionesUtiles/utiles.h"
#include "../Cliente/estructuras.h"

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"


#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define HABILITAR_ESCRITURA_NOMBRE 1
#define DESHABILITAR_ESCRITURA_NOMBRE 0

#define HABILITAR_ESCRITURA_CONTRASENIA 1
#define DESHABILITAR_ESCRITURA_CONTRASENIA 0

#define HABILITAR_INGRESO 1
#define DESHABILITAR_INGRESO 0

#define MAX_INGRESO_TECLADO 26


typedef struct
{
    sfFont *fuente;
    sfText *ingresarUsuario;
    sfText *textoInformativoTam;
    sfText *ingresarNombre;
    sfText *auxEscribirNombre;
    sfText *ingresarContrasenia;
    sfText *auxEscribirContrasenia;
    sfText *textoRegistrarUsuario;
    sfText *textoBotonIngresar;
} s_textoInicio;

typedef struct
{
    sfRectangleShape *subrayadoTitulo;
    sfCircleShape *circuloTextoInformativoTam;
    sfRectangleShape *barraIngresarNombre;
    sfRectangleShape *barraIngresarContrasenia;
    sfRectangleShape *botonIngresar;
    sfRectangleShape *rectanguloInvisibleRegistrar;
} s_elementosInicio;

typedef struct
{
    s_textoInicio texto;
    s_elementosInicio elementos;
    bool habilitarEscrituraNombre;
    bool habilitarEscrituraContrasenia;
    bool habilitarIngreso;
    char bufferEscribirNombre [MAX_INGRESO_TECLADO];
    char bufferEscribirContrasenia [MAX_INGRESO_TECLADO];
} s_recursosGraficosInicio;


///FUNCIONES ESTRUCTURALES
int inicializarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void setupInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void tamYPosPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void accionInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void actualizarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio);


///FUNCIONES LOGICAS
void ingresoTexto (char *buffer, sfEvent evento);


#endif // INTERFAZINICIO_H_INCLUDED


















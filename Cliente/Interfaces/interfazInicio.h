#ifndef INTERFAZINICIO_H_INCLUDED
#define INTERFAZINICIO_H_INCLUDED


///INCLUDES

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


///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define MAX_INGRESO_TECLADO_NOMBRE 31
#define MAX_INGRESO_TECLADO_CONTRASENIA 51

#define HABILITAR_ESCRITURA_NOMBRE 1
#define DESHABILITAR_ESCRITURA_NOMBRE 0

#define HABILITAR_ESCRITURA_CONTRASENIA 1
#define DESHABILITAR_ESCRITURA_CONTRASENIA 0

#define HABILITAR_GUARDAR_INICIO_SESION 1
#define DESHABILITAR_GUARDAR_INICIO_SESION 0

#define HABILITAR_INGRESO 1
#define DESHABILITAR_INGRESO 0


///ESTRUCTURAS

typedef struct
{
    sfText *iniciarSesion;
    sfText *ingresarNombre;
    sfText *auxEscribirNombre;
    sfText *ingresarContrasenia;
    sfText *auxEscribirContrasenia;
    sfText *textoGuardarInicioSesion;
    sfText *auxGuardarInicioSesion;
    sfText *textoBotonIngresar;
    sfText *textoIngresoIncorrecto;
    sfText *textoRegistrarUsuario;
} s_textoInicio;

typedef struct
{
    sfRectangleShape *subrayadoTitulo;
    sfRectangleShape *barraIngresarNombre;
    sfRectangleShape *barraIngresarContrasenia;
    sfRectangleShape *cuadradoGuardarInicioSesion;
    sfRectangleShape *botonIngresar;
    sfCircleShape *circuloTextoIngresoIncorrecto;
} s_elementosInicio;

typedef struct
{
    bool habilitarEscrituraNombre;
    bool habilitarEscrituraContrasenia;
    bool guardarInicioSesion;
    bool habilitarIngreso;
} s_habilitacionesInicio;

typedef struct
{
    s_textoInicio texto;
    s_elementosInicio elementos;
    s_habilitacionesInicio habilitaciones;
    char bufferEscribirNombre [MAX_INGRESO_TECLADO_NOMBRE];
    char bufferEscribirContrasenia [MAX_INGRESO_TECLADO_CONTRASENIA];
} s_recursosGraficosInicio;


///FUNCIONES ESTRUCTURALES

int inicializarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void setupInicio (s_recursosGraficosInicio *recursosGraficosInicio, s_fuentes fuentes);
void tamYPosPantallaInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void accionInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void actualizarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio);


///FUNCIONES LOGICAS

int guardarDatosEnArchivo (const char *bufferNombre, const char *bufferContrasenia);


#endif // INTERFAZINICIO_H_INCLUDED


















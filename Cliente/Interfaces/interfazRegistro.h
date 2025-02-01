#ifndef INTERFAZREGISTRO_H_INCLUDED
#define INTERFAZREGISTRO_H_INCLUDED

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

#define HABILITAR_REGISTRO 1
#define DESHABILITAR_REGISTRO 0


///ESTRUCTURAS

typedef struct
{
    sfFont *fuente;
    sfText *registrarse;
    sfText *ingresarNombre;
    sfText *textoInformativoNombre;
    sfText *auxEscribirNombre;
    sfText *ingresarContrasenia;
    sfText *textoInformativoContrasenia;
    sfText *auxEscribirContrasenia;
    sfText *textoBotonRegistrar;
    sfText *textoErrorRegistro;
} s_textoRegistro;

typedef struct
{
    sfRectangleShape *subrayadoTitulo;
    sfRectangleShape *flechaVolverBarra;
    sfRectangleShape *flechaVolverTriangulo1;
    sfRectangleShape *flechaVolverTriangulo2;
    sfRectangleShape *rectanguloInvisibleVolver;
    sfRectangleShape *barraIngresarNombre;
    sfRectangleShape *barraIngresarContrasenia;
    sfRectangleShape *botonRegistrar;
} s_elementosRegistro;

typedef struct
{
    bool habilitarEscrituraNombre;
    bool habilitarEscrituraContrasenia;
    bool habilitarRegistro;
} s_habilitacionesRegistro;

typedef struct
{
    s_textoRegistro texto;
    s_elementosRegistro elementos;
    s_habilitacionesRegistro habilitaciones;
    char bufferEscribirNombre [MAX_INGRESO_TECLADO_NOMBRE];
    char bufferEscribirContrasenia [MAX_INGRESO_TECLADO_CONTRASENIA];
} s_recursosGraficosRegistro;


///FUNCIONES ESTRUCTURALES

int inicializarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void setupRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void tamYPosPantallaRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void accionRegistro (s_aplicacion *app, s_socket *sock, s_recursosGraficosRegistro *recursosGraficosRegistro);
void actualizarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);
void renderizarRegistro (s_aplicacion *app, s_recursosGraficosRegistro *recursosGraficosRegistro);
void liberarRegistro (s_recursosGraficosRegistro *recursosGraficosRegistro);


#endif // INTERFAZREGISTRO_H_INCLUDED




















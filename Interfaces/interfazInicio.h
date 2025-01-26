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

#define HABILITAR_ESCRITURA 1
#define DESHABILITAR_ESCRITURA 0

#define ACTIVO 1
#define AUSENTE 0


typedef struct
{
    sfFont *fuente;
    sfText *ingresarUsuario;
    sfText *ingresarNombre;
    sfText *auxEscribirNombre;
    sfText *ingresarContrasenia;
    sfText *auxEscribirContrasenia;
    sfText *textoRegistrarUsuario;
    sfText *textoBotonAceptar;
    sfText *textoInformativoTam;
} s_textoInicio;

typedef struct
{
    sfRectangleShape *barraIngresarNombre;
    sfRectangleShape *barraIngresarContrasenia;
    sfRectangleShape *botonAceptar;
    sfCircleShape *circuloTextoInformativoTam;
} s_elementosInicio;

typedef struct
{
    s_textoInicio texto;
    s_elementosInicio elementos;
    bool habilitarEscritura;
    char bufferEscribirNombre [MAX_NOMBRE_USUARIO];
} s_recursosGraficosInicio;


///FUNCIONES ESTRUCTURALES
int inicializarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void setupInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void tamYPosPantallaInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void accionInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void actualizarInicio (s_recursosGraficosInicio *recursosGraficosInicio);
void renderizarInicio (s_aplicacion *app, s_recursosGraficosInicio *recursosGraficosInicio);
void liberarInicio (s_recursosGraficosInicio *recursosGraficosInicio);


#endif // INTERFAZINICIO_H_INCLUDED


















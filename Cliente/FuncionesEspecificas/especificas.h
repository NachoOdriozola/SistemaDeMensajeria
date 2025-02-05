#ifndef ESPECIFICAS_H_INCLUDED
#define ESPECIFICAS_H_INCLUDED


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

#define INICIO_SESION_AUTOMATICO 1
#define INICIO_SESION_MANUAL 0


///FUNCIONES DE INICIALIZACION ESPECIFICAS

//Verificar inicio de sesion automatico
int verificarDatosGuardados (s_aplicacion *app);

//Funciones de fuentes
int inicializarFuentes (s_fuentes *fuentes);
void liberarFuentes (s_fuentes *fuentes);

//Crear escalas para la posicion y tamanio de los elementos
void crearEscalaElementos (s_aplicacion *app);
void crearEscalaPixeles (s_aplicacion *app);

//Maximizado automatico luego de inicio de sesion o registro
void eventoMaximizadoAutomatico (s_aplicacion *app);
void maximizadoAutomaticoVentana (s_aplicacion *app);

//Funciones complementarias de la lista circular de mensajes
void setupListaMensajes (void *mensaje, void *recursosGraficosAmigos);
void tamListaMensajes (void *mensaje, void *escalaPixeles);
void liberarMensaje (void *mensaje);


#endif // ESPECIFICAS_H_INCLUDED












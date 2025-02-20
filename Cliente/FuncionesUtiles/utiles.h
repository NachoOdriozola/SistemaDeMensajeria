#ifndef FUNCIONESGENERALES_H_INCLUDED
#define FUNCIONESGENERALES_H_INCLUDED


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


///DEFINES

#define OK 0
#define ERROR_INICIALIZACION -1

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define MI_USUARIO 1
#define OTRO_USUARIO 0


///FUNCIONES UTILES

//Manejar vista al redimensionar
void ajustarVista (s_aplicacion *app, sfVector2f nuevoTamPantalla);

//Manejar eventos de click
bool clickEnRectangulo (sfRenderWindow *renderizado, sfRectangleShape *rectangulo);
bool clickEnTexto (sfRenderWindow *renderizado, sfText *texto);

//Verificar ingreso correcto de texto
void ingresoTexto (char *buffer, int maxIngreso, sfEvent evento);

//Enviar y recibir solicitud al servidor
void enviarYRecibirSolicitud (SOCKET sock, char *bufferSolicitud, char *bufferRespuesta);

//Guardar datos para inicio de sesion automatico
int guardarDatosEnArchivo (int id, const char *bufferContrasenia);

//Asignar mensaje a la lista circular de mensajes
void asignarMensaje (s_aplicacion *app, const char *bufferMensaje, bool enviadoPor);

//Agregar notificacion a la lista
void agregarNotificacion (s_lista *listaNotificaciones, s_ventana ventana, s_fuentes fuentes, char *bufferNotificacion);

//Funciones complementarias de la lista circular de mensajes
void modificarPosListaMensajes (void *mensaje, void *escalaPixeles);
void renderizarListaMensajes (void *mensaje, void *renderizado);


#endif // FUNCIONESGENERALES_H_INCLUDED














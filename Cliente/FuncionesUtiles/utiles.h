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

#define CONTINUAR_APLICACION 1
#define CERRAR_APLICACION 0

#define MAX_BUFFER_SOLICITUD 101
#define MAX_BUFFER_RESPUESTA 101

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

//Enviar solicitud al servidor
void enviarSolicitudUsuario (SOCKET sock, char *bufferSolicitud, char *bufferRespuesta);

//Asignar mensaje a la lista circular de mensajes
void asignarMensaje (s_aplicacion *app, const char *bufferMensaje, bool enviadoPor);

//Funciones complementarias de la lista circular de mensajes
void modificarPosListaMensajes (void *mensaje, void *escalaPixeles);
void renderizarListaMensajes (void *mensaje, void *renderizado);


#endif // FUNCIONESGENERALES_H_INCLUDED














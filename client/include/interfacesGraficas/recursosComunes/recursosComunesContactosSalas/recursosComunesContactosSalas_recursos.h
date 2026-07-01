/**
 * \file  recursosComunesContactosSalas_recursos.h
 * \brief Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef RECURSOSCOMUNESCONTACTOSSALAS_RECURSOS_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../../shared/constantes/include/constantes.h"
#include "../../../utiles.h"

#include "recursosComunesContactosSalas_estructuras.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def ANCHO_LOGICO_VENTANA
 * \brief Ancho/tamanio en x, logico de la ventana.
 */
#define ANCHO_LOGICO_VENTANA 1920

/**
 * \def ALTO_LOGICO_VENTANA
 * \brief Alto/tamanio en y, logico de la ventana.
 */
#define ALTO_LOGICO_VENTANA 1009


/**
 * \def ANCHO_MINIMO_VENTANA
 * \brief Ancho/tamanio en x, minimo que puede tomar la ventana.
 */
#define ANCHO_MINIMO_VENTANA 800

/**
 * \def ALTO_MINIMO_VENTANA
 * \brief Alto/tamanio en y, minimo que puede tomar la ventana.
 */
#define ALTO_MINIMO_VENTANA 600


/**
 * \def VELOCIDAD_SCROLL
 * \brief Constante que determina que tan rapido se mueve el scroll.
 */
#define VELOCIDAD_SCROLL 35.0f


/**
 * \def MAX_MENSAJES_MEMORIA
 * \brief Cantidad maxima de mensajes que se guardan en memoria en la lista circular de mensajes.
 */
#define MAX_MENSAJES_MEMORIA 25


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _recursosComunesContactosSalas_inicializarValoresNulosFuentes (t_recursosComunesContactosSalasFuentes *fuentes);
void _recursosComunesContactosSalas_inicializarValoresNulosTextos (t_recursosComunesContactosSalasTextos *textos);
void _recursosComunesContactosSalas_inicializarValoresNulosElementos (t_recursosComunesContactosSalasElementos *elementos);
void _recursosComunesContactosSalas_inicializarValoresNulosVistas (t_recursosComunesContactosSalasVistas *vistas);

t_codigoRetorno _recursosComunesContactosSalas_inicializarFuentes (t_recursosComunesContactosSalasFuentes *fuentes);
t_codigoRetorno _recursosComunesContactosSalas_inicializarTextos (t_recursosComunesContactosSalasTextos *textos);
t_codigoRetorno _recursosComunesContactosSalas_inicializarElementos (t_recursosComunesContactosSalasElementos *elementos);
t_codigoRetorno _recursosComunesContactosSalas_inicializarVistas (t_recursosComunesContactosSalasVistas *vistas);
t_codigoRetorno _recursosComunesContactosSalas_inicializarListaMensajes (t_contextoMensajes *contextoMensajes);

void _recursosComunesContactosSalas_configurarInterfaz (t_recursosComunesContactosSalas *recursosComunesContactosSalas);
void _recursosComunesContactosSalas_configurarTextos (t_recursosComunesContactosSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
void _recursosComunesContactosSalas_configurarElementos (t_recursosComunesContactosSalasElementos *elementos);

void _recursosComunesContactosSalas_tamYPosVentanaTextos (t_recursosComunesContactosSalasTextos *textos);
void _recursosComunesContactosSalas_tamYPosVentanaElementos (t_recursosComunesContactosSalasElementos *elementos);
void _recursosComunesContactosSalas_tamVistas (t_recursosComunesContactosSalasVistas *vistas);

void _recursosComunesContactosSalas_liberarFuentes (t_recursosComunesContactosSalasFuentes *fuentes);
void _recursosComunesContactosSalas_liberarTextos (t_recursosComunesContactosSalasTextos *textos);
void _recursosComunesContactosSalas_liberarElementos (t_recursosComunesContactosSalasElementos *elementos);
void _recursosComunesContactosSalas_liberarVistas (t_recursosComunesContactosSalasVistas *vistas);


#endif // RECURSOSCOMUNESCONTACTOSSALAS_RECURSOS_H_INCLUDED
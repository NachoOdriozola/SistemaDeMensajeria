/**
 * \file   recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZCONTACTOS_RECURSOS_H_INCLUDED
#define INTERFAZCONTACTOS_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"


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


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazContactos_inicializarValoresNulosFuentes (t_interfazContactosFuentes *fuentes);
void _interfazContactos_inicializarValoresNulosTextos (t_interfazContactosTextos *textos);
void _interfazContactos_inicializarValoresNulosElementos (t_interfazContactosElementos *elementos);
void _interfazContactos_inicializarValoresNulosVistas (t_interfazContactosVistas *vistas);

t_codigoRetorno _interfazContactos_inicializarFuentes (t_interfazContactosFuentes *fuentes);
t_codigoRetorno _interfazContactos_inicializarTextos (t_interfazContactosTextos *textos, const t_interfazContactosFuentes *fuentes);
t_codigoRetorno _interfazContactos_inicializarElementos (t_interfazContactosElementos *elementos);
t_codigoRetorno _interfazContactos_inicializarVistas (t_interfazContactosVistas *vistas);

void _interfazContactos_configurarInterfaz (t_interfazContactos *interfazContactos);
void _interfazContactos_configurarTextos (t_interfazContactosTextos *textos);
void _interfazContactos_configurarElementos (t_interfazContactosElementos *elementos);

void _interfazContactos_tamYPosVentanaTextos (t_interfazContactosTextos *textos);
void _interfazContactos_tamYPosVentanaElementos (t_interfazContactosElementos *elementos);
void _interfazContactos_tamVistas (t_interfazContactosVistas *vistas);

void _interfazContactos_liberarFuentes (t_interfazContactosFuentes *fuentes);
void _interfazContactos_liberarTextos (t_interfazContactosTextos *textos);
void _interfazContactos_liberarElementos (t_interfazContactosElementos *elementos);
void _interfazContactos_liberarVistas (t_interfazContactosVistas *vistas);


#endif // INTERFAZCONTACTOS_RECURSOS_H_INCLUDED
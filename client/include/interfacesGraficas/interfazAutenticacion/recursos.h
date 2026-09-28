/**
 * \file   recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED
#define INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazAutenticacion_inicializarValoresNulosTextos (t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_inicializarValoresNulosElementos (t_interfazAutenticacionElementos *elementos);

t_codigoRetorno _interfazAutenticacion_inicializarTextos (t_interfazAutenticacionTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
t_codigoRetorno _interfazAutenticacion_inicializarElementos (t_interfazAutenticacionElementos *elementos);

void _interfazAutenticacion_configurarInterfaz (t_interfazAutenticacion *interfazAutenticacion);
void _interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_configurarElementos (t_interfazAutenticacionElementos *elementos);

void _interfazAutenticacion_tamYPosVentanaTextos (t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_tamYPosVentanaElementos (t_interfazAutenticacionElementos *elementos);

void _interfazAutenticacion_liberarTextos (t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_liberarElementos (t_interfazAutenticacionElementos *elementos);


#endif // INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED
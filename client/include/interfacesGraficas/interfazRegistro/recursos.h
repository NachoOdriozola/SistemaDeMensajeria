/**
 * \file   recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZREGISTRO_RECURSOS_H_INCLUDED
#define INTERFAZREGISTRO_RECURSOS_H_INCLUDED


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
#include "interfacesGraficas/interfazRegistro/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazRegistro_inicializarValoresNulosTextos (t_interfazRegistroTextos *textos);
void _interfazRegistro_inicializarValoresNulosElementos (t_interfazRegistroElementos *elementos);

t_codigoRetorno _interfazRegistro_inicializarTextos (t_interfazRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
t_codigoRetorno _interfazRegistro_inicializarElementos (t_interfazRegistroElementos *elementos);

void _interfazRegistro_configurarInterfaz (t_interfazRegistro *interfazRegistro);
void _interfazRegistro_configurarTextos (t_interfazRegistroTextos *textos);
void _interfazRegistro_configurarElementos (t_interfazRegistroElementos *elementos);

void _interfazRegistro_tamYPosVentanaTextos (t_interfazRegistroTextos *textos);
void _interfazRegistro_tamYPosVentanaElementos (t_interfazRegistroElementos *elementos);

void _interfazRegistro_liberarTextos (t_interfazRegistroTextos *textos);
void _interfazRegistro_liberarElementos (t_interfazRegistroElementos *elementos);


#endif // INTERFAZREGISTRO_RECURSOS_H_INCLUDED
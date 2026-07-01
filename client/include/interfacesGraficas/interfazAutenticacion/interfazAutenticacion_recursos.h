/**
 * \file   interfazAutenticacion_recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED
#define INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/constantes/include/constantes.h"
#include "../../utiles.h"

#include "../recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfazAutenticacion_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazAutenticacion_inicializarValoresNulosTextos (t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_inicializarValoresNulosElementos (t_interfazAutenticacionElementos *elementos);

t_codigoRetorno _interfazAutenticacion_inicializarTextos (t_interfazAutenticacionTextos *textos);
t_codigoRetorno _interfazAutenticacion_inicializarElementos (t_interfazAutenticacionElementos *elementos);

void _interfazAutenticacion_configurarInterfaz (t_interfazAutenticacion *interfazAutenticacion, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
void _interfazAutenticacion_configurarTextos (t_interfazAutenticacionTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
void _interfazAutenticacion_configurarElementos (t_interfazAutenticacionElementos *elementos);

void _interfazAutenticacion_tamYPosVentanaTextos (t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_tamYPosVentanaElementos (t_interfazAutenticacionElementos *elementos);

void _interfazAutenticacion_renderizarTextos (sfRenderWindow *renderizado, const t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_renderizarElementos (sfRenderWindow *renderizado, const t_interfazAutenticacionElementos *elementos);

void _interfazAutenticacion_liberarTextos (t_interfazAutenticacionTextos *textos);
void _interfazAutenticacion_liberarElementos (t_interfazAutenticacionElementos *elementos);


#endif // INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED
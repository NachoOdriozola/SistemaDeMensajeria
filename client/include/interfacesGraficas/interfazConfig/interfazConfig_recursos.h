/**
 * \file   interfazConfig_recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZCONFIG_RECURSOS_H_INCLUDED
#define INTERFAZCONFIG_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/constantes/include/constantes.h"
#include "../../utiles.h"

#include "interfazConfig_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazConfig_inicializarValoresNulosFuentes (t_interfazConfigFuentes *fuentes);
void _interfazConfig_inicializarValoresNulosTextos (t_interfazConfigTextos *textos);
void _interfazConfig_inicializarValoresNulosElementos (t_interfazConfigElementos *elementos);

t_codigoRetorno _interfazConfig_inicializarFuentes (t_interfazConfigFuentes *fuentes);
t_codigoRetorno _interfazConfig_inicializarTextos (t_interfazConfigTextos *textos);
t_codigoRetorno _interfazConfig_inicializarElementos (t_interfazConfigElementos *elementos);

void _interfazConfig_configurarInterfaz (t_interfazConfig *interfazConfig);
void _interfazConfig_configurarTextos (t_interfazConfigTextos *textos, const t_interfazConfigFuentes *fuentes);
void _interfazConfig_configurarElementos (t_interfazConfigElementos *elementos);

void _interfazConfig_tamYPosVentanaTextos (t_interfazConfigTextos *textos);
void _interfazConfig_tamYPosVentanaElementos (t_interfazConfigElementos *elementos);

void _interfazConfig_renderizarTextos (sfRenderWindow *renderizado, const t_interfazConfigTextos *textos);
void _interfazConfig_renderizarElementos (sfRenderWindow *renderizado, const t_interfazConfigElementos *elementos);

void _interfazConfig_liberarFuentes (t_interfazConfigFuentes *fuentes);
void _interfazConfig_liberarTextos (t_interfazConfigTextos *textos);
void _interfazConfig_liberarElementos (t_interfazConfigElementos *elementos);


#endif // INTERFAZCONFIG_RECURSOS_H_INCLUDED
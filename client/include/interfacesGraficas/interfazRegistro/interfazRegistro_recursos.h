/**
 * \file   interfazRegistro_recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZREGISTRO_RECURSOS_H_INCLUDED
#define INTERFAZREGISTRO_RECURSOS_H_INCLUDED


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
#include "interfazRegistro_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazRegistro_inicializarValoresNulosTextos (t_interfazRegistroTextos *textos);
void _interfazRegistro_inicializarValoresNulosElementos (t_interfazRegistroElementos *elementos);

t_codigoRetorno _interfazRegistro_inicializarTextos (t_interfazRegistroTextos *textos);
t_codigoRetorno _interfazRegistro_inicializarElementos (t_interfazRegistroElementos *elementos);

void _interfazRegistro_configurarInterfaz (t_interfazRegistro *interfazRegistro, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
void _interfazRegistro_configurarTextos (t_interfazRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
void _interfazRegistro_configurarElementos (t_interfazRegistroElementos *elementos);

void _interfazRegistro_tamYPosVentanaTextos (t_interfazRegistroTextos *textos);
void _interfazRegistro_tamYPosVentanaElementos (t_interfazRegistroElementos *elementos);

void _interfazRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_interfazRegistroTextos *textos);
void _interfazRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_interfazRegistroElementos *elementos);

void _interfazRegistro_liberarTextos (t_interfazRegistroTextos *textos);
void _interfazRegistro_liberarElementos (t_interfazRegistroElementos *elementos);


#endif // INTERFAZREGISTRO_RECURSOS_H_INCLUDED
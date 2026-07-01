/**
 * \file   interfazSalas_recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZSALAS_RECURSOS_H_INCLUDED
#define INTERFAZSALAS_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/constantes/include/constantes.h"
#include "../../utiles.h"

#include "../recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"
#include "interfazSalas_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazSalas_inicializarValoresNulosTextos (t_interfazSalasTextos *textos);
void _interfazSalas_inicializarValoresNulosElementos (t_interfazSalasElementos *elementos);

t_codigoRetorno _interfazSalas_inicializarTextos (t_interfazSalasTextos *textos);
t_codigoRetorno _interfazSalas_inicializarElementos (t_interfazSalasElementos *elementos);

void _interfazSalas_configurarInterfaz (t_interfazSalas *interfazSalas, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
void _interfazSalas_configurarTextos (t_interfazSalasTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
void _interfazSalas_configurarElementos (t_interfazSalasElementos *elementos);

void _interfazSalas_tamYPosVentanaTextos (t_interfazSalasTextos *textos);
void _interfazSalas_tamYPosVentanaElementos (t_interfazSalasElementos *elementos);

void _interfazSalas_renderizarTextos (sfRenderWindow *renderizado, const t_interfazSalasTextos *textos);
void _interfazSalas_renderizarElementos (sfRenderWindow *renderizado, const t_interfazSalasElementos *elementos);

void _interfazSalas_liberarTextos (t_interfazSalasTextos *textos);
void _interfazSalas_liberarElementos (t_interfazSalasElementos *elementos);


#endif // INTERFAZSALAS_RECURSOS_H_INCLUDED

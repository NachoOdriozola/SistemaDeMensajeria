/**
 * \file   interfazContactos_recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZCONTACTOS_RECURSOS_H_INCLUDED
#define INTERFAZCONTACTOS_RECURSOS_H_INCLUDED


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
#include "interfazContactos_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazContactos_inicializarValoresNulosTextos (t_interfazContactosTextos *textos);
void _interfazContactos_inicializarValoresNulosElementos (t_interfazContactosElementos *elementos);

t_codigoRetorno _interfazContactos_inicializarTextos (t_interfazContactosTextos *textos);
t_codigoRetorno _interfazContactos_inicializarElementos (t_interfazContactosElementos *elementos);

void _interfazContactos_configurarInterfaz (t_interfazContactos *interfazContactos, t_recursosComunesContactosSalas *recursosComunesContactosSalas);
void _interfazContactos_configurarTextos (t_interfazContactosTextos *textos, const t_recursosComunesContactosSalasFuentes *fuentes);
void _interfazContactos_configurarElementos (t_interfazContactosElementos *elementos);

void _interfazContactos_tamYPosVentanaTextos (t_interfazContactosTextos *textos);
void _interfazContactos_tamYPosVentanaElementos (t_interfazContactosElementos *elementos);

void _interfazContactos_renderizarTextos (sfRenderWindow *renderizado, const t_interfazContactosTextos *textos);
void _interfazContactos_renderizarElementos (sfRenderWindow *renderizado, const t_interfazContactosElementos *elementos);

void _interfazContactos_liberarTextos (t_interfazContactosTextos *textos);
void _interfazContactos_liberarElementos (t_interfazContactosElementos *elementos);


#endif // INTERFAZCONTACTOS_RECURSOS_H_INCLUDED
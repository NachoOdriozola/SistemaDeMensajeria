/**
 * \file   recursosComunesAutenticacionRegistro_recursos.h
 * \brief Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_RECURSOS_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../../shared/constantes/include/constantes.h"
#include "../../../utiles.h"

#include "recursosComunesAutenticacionRegistro_estructuras.h"


/* ============================================================================================================================================
   FUNCIONES 
   ============================================================================================================================================ */


void _recursosComunesAutenticacionRegistro_inicializarValoresNulosFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes);
void _recursosComunesAutenticacionRegistro_inicializarValoresNulosTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
void _recursosComunesAutenticacionRegistro_inicializarValoresNulosElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

t_codigoRetorno _recursosComunesAutenticacionRegistro_inicializarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes);
t_codigoRetorno _recursosComunesAutenticacionRegistro_inicializarTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
t_codigoRetorno _recursosComunesAutenticacionRegistro_inicializarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

void _recursosComunesAutenticacionRegistro_configurarInterfaz (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);
void _recursosComunesAutenticacionRegistro_configurarTextos (t_recursosComunesAutenticacionRegistroTextos *textos, const t_recursosComunesAutenticacionRegistroFuentes *fuentes);
void _recursosComunesAutenticacionRegistro_configurarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

void _recursosComunesAutenticacionRegistro_tamYPosVentanaTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
void _recursosComunesAutenticacionRegistro_tamYPosVentanaElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);

void _recursosComunesAutenticacionRegistro_liberarFuentes (t_recursosComunesAutenticacionRegistroFuentes *fuentes);
void _recursosComunesAutenticacionRegistro_liberarTextos (t_recursosComunesAutenticacionRegistroTextos *textos);
void _recursosComunesAutenticacionRegistro_liberarElementos (t_recursosComunesAutenticacionRegistroElementos *elementos);


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_RECURSOS_H_INCLUDED
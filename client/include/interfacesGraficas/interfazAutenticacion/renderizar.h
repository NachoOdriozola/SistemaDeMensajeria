/**
 * \file   renderizar.h
 * \brief  Contiene funciones de renderizado.
 */


#ifndef INTERFAZAUTENTICACION_RENDERIZAR_H_INCLUDED
#define INTERFAZAUTENTICACION_RENDERIZAR_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "external/csfml/include/SFML/System.h"
#include "external/csfml/include/SFML/Window.h"
#include "external/csfml/include/SFML/Graphics.h"

#include "logica/utiles.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * 1) Limpia la ventana anterior.
 * 2) Setea las vista de UI y luego la renderiza.
 * 3) Muestra la ventana actualizada.
 * Procura el orden de los objetos graficos renderizados para que no se superpongan.
*/
void _interfazAutenticacion_renderizar (sfRenderWindow *renderizado, const t_interfazAutenticacion *interfazAutenticacion);


#endif // INTERFAZAUTENTICACION_RENDERIZAR_H_INCLUDED
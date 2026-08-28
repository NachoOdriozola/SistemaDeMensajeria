/**
 * \file   renderizar.h
 * \brief  Contiene funciones de renderizado.
 */


#ifndef INTERFAZREGISTRO_RENDERIZAR_H_INCLUDED
#define INTERFAZREGISTRO_RENDERIZAR_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "logica/utiles.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazRegistro/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * 1) Limpia la ventana anterior.
 * 2) Setea las vista de UI y luego la renderiza.
 * 3) Muestra la ventana actualizada.
 * Procura el orden de los objetos graficos renderizados para que no se superpongan.
*/
void _interfazRegistro_renderizar (sfRenderWindow *renderizado, const t_interfazRegistro *interfazRegistro);


#endif // INTERFAZREGISTRO_RENDERIZAR_H_INCLUDED
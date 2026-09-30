/**
 * \file   renderizar.h
 * \brief  Contiene funciones de renderizado.
 */


#ifndef INTERFAZREGISTRO_RENDERIZAR_H_INCLUDED
#define INTERFAZREGISTRO_RENDERIZAR_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

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
void _ui_registro_renderizar (sfRenderWindow *renderizado, const UiRegistro *uiRegistro);


#endif // INTERFAZREGISTRO_RENDERIZAR_H_INCLUDED
/**
 * \file   renderizar.h
 * \brief  Contiene funciones de renderizado.
 */


#ifndef INTERFAZCONTACTOS_RENDERIZAR_H_INCLUDED
#define INTERFAZCONTACTOS_RENDERIZAR_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "logica/utiles.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"
#include "interfacesGraficas/interfazContactos/recursos.h"
#include "interfacesGraficas/interfazContactos/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * 1) Limpia la ventana anterior.
 * 2) Primero setea las vistas y renderiza los elementos de las vistas moviles y luego de la vista inmovil.
 * 3) Muestra la ventana actualizada.
 * Procura el orden de los objetos graficos renderizados para que no se superpongan.
*/
void _interfazContactos_renderizar (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);


#endif // INTERFAZCONTACTOS_RENDERIZAR_H_INCLUDED
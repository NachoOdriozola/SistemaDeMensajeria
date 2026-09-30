/**
 * \file   recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED
#define INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazAutenticacion/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _ui_autenticacion_inicializar_textos (UiAutenticacionTextos *textos);
void _ui_autenticacion_inicializar_elementos (UiAutenticacionElementos *elementos);

CodigoRetorno _ui_autenticacion_crear_textos (UiAutenticacionTextos *textos, const UiAccesoFuentes *fuentes);
CodigoRetorno _ui_autenticacion_crear_elementos (UiAutenticacionElementos *elementos);

void _ui_autenticacion_configurar_interfaz (UiAutenticacion *uiAutenticacion);
void _ui_autenticacion_configurar_textos (UiAutenticacionTextos *textos);
void _ui_autenticacion_configurar_elementos (UiAutenticacionElementos *elementos);

void _ui_autenticacion_establecer_tam_y_pos_ventana_textos (UiAutenticacionTextos *textos);
void _ui_autenticacion_establecer_tam_y_pos_ventana_elementos (UiAutenticacionElementos *elementos);

void _ui_autenticacion_liberar_textos (UiAutenticacionTextos *textos);
void _ui_autenticacion_liberar_elementos (UiAutenticacionElementos *elementos);


#endif // INTERFAZAUTENTICACION_RECURSOS_H_INCLUDED
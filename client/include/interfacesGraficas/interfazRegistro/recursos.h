/**
 * \file   recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZREGISTRO_RECURSOS_H_INCLUDED
#define INTERFAZREGISTRO_RECURSOS_H_INCLUDED


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
#include "interfacesGraficas/interfazRegistro/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _ui_registro_inicializar_textos (UiRegistroTextos *textos);
void _ui_registro_inicializar_elementos (UiRegistroElementos *elementos);

CodigoRetorno _ui_registro_crear_textos (UiRegistroTextos *textos, const UiAccesoFuentes *fuentes);
CodigoRetorno _ui_registro_crear_elementos (UiRegistroElementos *elementos);

void _ui_registro_configurar_interfaz (UiRegistro *uiRegistro);
void _ui_registro_configurar_textos (UiRegistroTextos *textos);
void _ui_registro_configurar_elementos (UiRegistroElementos *elementos);

void _ui_registro_establecer_tam_y_pos_ventana_textos (UiRegistroTextos *textos);
void _ui_registro_establecer_tam_y_pos_ventana_elementos (UiRegistroElementos *elementos);

void _ui_registro_liberar_textos (UiRegistroTextos *textos);
void _ui_registro_liberar_elementos (UiRegistroElementos *elementos);


#endif // INTERFAZREGISTRO_RECURSOS_H_INCLUDED
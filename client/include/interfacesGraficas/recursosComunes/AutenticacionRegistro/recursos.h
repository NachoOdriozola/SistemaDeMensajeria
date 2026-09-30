/**
 * \file   recursos.h
 * \brief Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_RECURSOS_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES 
   ============================================================================================================================================ */


void _ui_acceso_inicializar_fuentes (UiAccesoFuentes *fuentes);
void _ui_acceso_inicializar_textos (UiAccesoTextos *textos);
void _ui_acceso_inicializar_elementos (UiAccesoElementos *elementos);
void _ui_acceso_inicializar_vistas (UiAccesoVistas *vistas);

CodigoRetorno _ui_acceso_crear_fuentes (UiAccesoFuentes *fuentes);
CodigoRetorno _ui_acceso_crear_textos (UiAccesoTextos *textos, const UiAccesoFuentes *fuentes);
CodigoRetorno _ui_acceso_crear_elementos (UiAccesoElementos *elementos);
CodigoRetorno _ui_acceso_crear_vistas (UiAccesoVistas *vistas);

void _ui_acceso_configurar_interfaz (UiAcceso *uiAcceso);
void _ui_acceso_configurar_textos (UiAccesoTextos *textos);
void _ui_acceso_configurar_elementos (UiAccesoElementos *elementos);

void _ui_acceso_establecer_tam_y_pos_ventana_textos (UiAccesoTextos *textos);
void _ui_acceso_establecer_tam_y_pos_ventana_elementos (UiAccesoElementos *elementos);
void _ui_acceso_establecer_tam_vistas (UiAccesoVistas *vistas);

void _ui_acceso_liberar_fuentes (UiAccesoFuentes *fuentes);
void _ui_acceso_liberar_textos (UiAccesoTextos *textos);
void _ui_acceso_liberar_elementos (UiAccesoElementos *elementos);
void _ui_acceso_liberar_vistas (UiAccesoVistas *vistas);


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_RECURSOS_H_INCLUDED
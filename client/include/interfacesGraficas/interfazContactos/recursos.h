/**
 * \file   recursos.h
 * \brief  Contiene funciones auxiliares privadas sobre la creacion, configuracion, renderizacion y liberacion de los recursos graficos.
 */


#ifndef INTERFAZCONTACTOS_RECURSOS_H_INCLUDED
#define INTERFAZCONTACTOS_RECURSOS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"

#include "interfacesGraficas/interfazContactos/estructuras.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def ANCHO_LOGICO_VENTANA
 * \brief Ancho/tamanio en x, logico de la ventana.
 */
#define ANCHO_LOGICO_VENTANA 1920

/**
 * \def ALTO_LOGICO_VENTANA
 * \brief Alto/tamanio en y, logico de la ventana.
 */
#define ALTO_LOGICO_VENTANA 1009


/**
 * \def ANCHO_MINIMO_VENTANA
 * \brief Ancho/tamanio en x, minimo que puede tomar la ventana.
 */
#define ANCHO_MINIMO_VENTANA 800

/**
 * \def ALTO_MINIMO_VENTANA
 * \brief Alto/tamanio en y, minimo que puede tomar la ventana.
 */
#define ALTO_MINIMO_VENTANA 600


/**
 * \def VELOCIDAD_SCROLL
 * \brief Constante que determina que tan rapido se mueve el scroll.
 */
#define VELOCIDAD_SCROLL 35.0f


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _ui_contactos_inicializar_fuentes (UiContactosFuentes *fuentes);
void _ui_contactos_inicializar_textos (UiContactosTextos *textos);
void _ui_contactos_inicializar_elementos (UiContactosElementos *elementos);
void _ui_contactos_inicializar_vistas (UiContactosVistas *vistas);

CodigoRetorno _ui_contactos_crear_fuentes (UiContactosFuentes *fuentes);
CodigoRetorno _ui_contactos_crear_textos (UiContactosTextos *textos, const UiContactosFuentes *fuentes);
CodigoRetorno _ui_contactos_crear_elementos (UiContactosElementos *elementos);
CodigoRetorno _ui_contactos_crear_vistas (UiContactosVistas *vistas);

void _ui_contactos_configurar_interfaz (UiContactos *uiContactos);
void _ui_contactos_configurar_textos (UiContactosTextos *textos);
void _ui_contactos_configurar_elementos (UiContactosElementos *elementos);

void _ui_contactos_establecer_tam_y_pos_ventana_textos (UiContactosTextos *textos);
void _ui_contactos_establecer_tam_y_pos_ventana_elementos (UiContactosElementos *elementos);
void _ui_contactos_establecer_tam_vistas (UiContactosVistas *vistas);

void _ui_contactos_liberar_fuentes (UiContactosFuentes *fuentes);
void _ui_contactos_liberar_textos (UiContactosTextos *textos);
void _ui_contactos_liberar_elementos (UiContactosElementos *elementos);
void _ui_contactos_liberar_vistas (UiContactosVistas *vistas);


#endif // INTERFAZCONTACTOS_RECURSOS_H_INCLUDED
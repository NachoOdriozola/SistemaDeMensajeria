/**
 * \file   controladores.h
 * \brief Contiene funciones que hacen de puente entre la logica y la interfaz grafica.
 */


#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_CONTROLADORES_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_CONTROLADORES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Activar la interfaz de autenticacion.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de autenticacion.
 *
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void _ui_acceso_activar_interfaz_autenticacion (UiAcceso *uiAcceso);

/** \brief Activar la interfaz de registro.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de registro.
 *
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void _ui_acceso_activar_interfaz_registro (UiAcceso *uiAcceso);


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_CONTROLADORES_H_INCLUDED
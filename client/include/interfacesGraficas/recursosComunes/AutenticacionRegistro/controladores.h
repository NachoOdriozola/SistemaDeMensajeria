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

#include "SFML/System.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/estructuras.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Activar la interfaz de autenticacion.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de autenticacion.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void _recursosComunesAutenticacionRegistro_activarInterfazAutenticacion (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Activar la interfaz de registro.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void _recursosComunesAutenticacionRegistro_activarInterfazRegistro (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_CONTROLADORES_H_INCLUDED
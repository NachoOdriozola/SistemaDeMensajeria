/**
 * \file   recursosComunesAutenticacionRegistro_controladores.h
 * \brief Contiene funciones controladoras.
 */


#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_CONTROLADORES_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_CONTROLADORES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "recursosComunesAutenticacionRegistro_estructuras.h"
#include "recursosComunesAutenticacionRegistro_recursos.h"


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
void recursosComunesAutenticacionRegistro_activarInterfazAutenticacion (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Activar la interfaz de registro.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_activarInterfazRegistro (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_CONTROLADORES_H_INCLUDED
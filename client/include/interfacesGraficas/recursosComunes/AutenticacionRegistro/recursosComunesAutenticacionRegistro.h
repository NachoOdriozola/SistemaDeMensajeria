/**
 * \file   recursosComunesAutenticacionRegistro.h
 * \brief Contiene funciones estructurales de interfaz.
 */


#ifndef RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED
#define RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CSFML/System.h"
#include "CSFML/Window.h"
#include "CSFML/Graphics.h"

#include "constantes.h"

#include "logica/utiles.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/estructuras.h"
#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursos.h"
#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_inicializarValoresNulos (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Inicializar los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
t_codigoRetorno recursosComunesAutenticacionRegistro_inicializar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Configurar los recursos graficos comunes, establecerles un tamanio y posicion en ventana, y la logica (compartido) entre las interfaces de autenticacion y registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_configurar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

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

/** \brief Renderizar los recursos graficos de texto comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 * Procurar el orden de los renderizados para que no se superpongan.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroTextos *textos);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 * Procurar el orden de los renderizados para que no se superpongan.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesAutenticacionRegistroElementos *elementos);

/** \brief Liberar, de manera segura, todos los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void recursosComunesAutenticacionRegistro_liberar (t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED

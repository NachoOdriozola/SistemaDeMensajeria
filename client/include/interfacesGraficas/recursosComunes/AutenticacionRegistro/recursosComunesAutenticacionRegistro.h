/**
 * \file   uiAcceso.h
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
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void ui_acceso_inicializar (UiAcceso *uiAcceso);

/** \brief Inicializar los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
CodigoRetorno ui_acceso_crear (UiAcceso *uiAcceso);

/** \brief Configurar los recursos graficos comunes, establecerles un tamanio y posicion en ventana, y la logica (compartido) entre las interfaces de autenticacion y registro.
 *
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void ui_acceso_configurar (UiAcceso *uiAcceso);

/** \brief Activar la interfaz de autenticacion.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de autenticacion.
 *
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void ui_acceso_activar_interfaz_autenticacion (UiAcceso *uiAcceso);

/** \brief Activar la interfaz de registro.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de registro.
 *
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void ui_acceso_activar_interfaz_registro (UiAcceso *uiAcceso);

/** \brief Renderizar los recursos graficos de texto comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 * Procurar el orden de los renderizados para que no se superpongan.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void ui_acceso_renderizar_textos (sfRenderWindow *renderizado, const UiAccesoTextos *textos);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de autenticacion y registro
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 * Procurar el orden de los renderizados para que no se superpongan.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de autenticacion y registro.
 *
 */
void ui_acceso_renderizar_Elementos (sfRenderWindow *renderizado, const UiAccesoElementos *elementos);

/** \brief Liberar, de manera segura, todos los recursos graficos comunes (compartidos) entre las interfaces de autenticacion y registro.
 *
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 */
void ui_acceso_liberar (UiAcceso *uiAcceso);


#endif // RECURSOSCOMUNESAUTENTICACIONREGISTRO_H_INCLUDED

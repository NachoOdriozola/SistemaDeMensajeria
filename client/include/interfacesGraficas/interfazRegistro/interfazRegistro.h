/**
 * \file   interfazRegistro.h
 * \brief  Contiene funciones estructurales de interfaz.
 */


#ifndef INTERFAZREGISTRO_H_INCLUDED
#define INTERFAZREGISTRO_H_INCLUDED


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
#include "logica/estructuras.h"

#include "interfacesGraficas/recursosComunes/AutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfacesGraficas/interfazRegistro/estructuras.h"
#include "interfacesGraficas/interfazRegistro/recursos.h"
#include "interfacesGraficas/interfazRegistro/controladores.h"
#include "interfacesGraficas/interfazRegistro/accion.h"
#include "interfacesGraficas/interfazRegistro/actualizar.h"
#include "interfacesGraficas/interfazRegistro/renderizar.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de registro.
 *
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void ui_registro_inicializar (UiRegistro *uiRegistro);

/** \brief Inicializar los recursos graficos de la interfaz de registro. Ademas, asigna los recursos comunes.
 *
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 * \param uiAcceso Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
CodigoRetorno ui_registro_crear (UiRegistro *uiRegistro, UiAcceso *uiAcceso);

/** \brief Configurar los recursos graficos y logica de la interfaz de registro.
 *
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 * 
 */
void ui_registro_configurar (UiRegistro *uiRegistro);

/** \brief Ejecutar la interfaz de registro.
 *
 * Realizar los procesos de:
 * 1) Accion: Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * 2) Actualizacion: Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
 * 3) Renderizado: Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de registro en la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (EstadoSolicituds y recursos) global de la aplicacion.
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void ui_registro_ejecutar (ContextoAplicacion *contextoAplicacion, UiRegistro *uiRegistro);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de registro.
 *
 * \param uiRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void ui_registro_liberar (UiRegistro *uiRegistro);


#endif // INTERFAZREGISTRO_H_INCLUDED


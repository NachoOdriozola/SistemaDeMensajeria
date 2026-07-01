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

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../shared/constantes/include/constantes.h"
#include "../../utiles.h"
#include "../../estructuras.h"

#include "../recursosComunes/recursosComunesAutenticacionRegistro/recursosComunesAutenticacionRegistro.h"
#include "interfazRegistro_estructuras.h"
#include "interfazRegistro_recursos.h"
#include "interfazRegistro_controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de registro.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void interfazRegistro_inicializarValoresNulos (t_interfazRegistro *interfazRegistro);

/** \brief Inicializar los recursos graficos de la interfaz de registro.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
t_codigoRetorno interfazRegistro_inicializar (t_interfazRegistro *interfazRegistro);

/** \brief Configurar los recursos graficos y logica de la interfaz de registro. Ademas, asigna los recursos comunes.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 * \param recursosComunesAutenticacionRegistro Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de autenticacion y registro.
 * 
 */
void interfazRegistro_configurar (t_interfazRegistro *interfazRegistro, t_recursosComunesAutenticacionRegistro *recursosComunesAutenticacionRegistro);

/** \brief Ejecutar la interfaz de registro.
 *
 * Realizar los procesos de:
 * 1) Accion: Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * 2) Actualizacion: Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
 * 3) Renderizado: Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de registro en la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void ejecutarInterfazRegistro (t_contextoAplicacion *contextoAplicacion, t_interfazRegistro *interfazRegistro);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de registro.
 *
 * \param interfazRegistro Puntero a la estructura base de los recursos graficos y logica de la interfaz de registro.
 *
 */
void interfazRegistro_liberar (t_interfazRegistro *interfazRegistro);


#endif // INTERFAZREGISTRO_H_INCLUDED


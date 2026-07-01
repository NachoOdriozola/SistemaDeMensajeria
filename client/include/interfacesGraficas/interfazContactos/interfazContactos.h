/**
 * \file   interfazContactos.h
 * \brief  Contiene funciones estructurales de interfaz.
 */


#ifndef INTERFAZCONTACTOS_H_INCLUDED
#define INTERFAZCONTACTOS_H_INCLUDED


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

#include "../recursosComunes/recursosComunesContactosSalas/recursosComunesContactosSalas.h"
#include "interfazContactos_estructuras.h"
#include "interfazContactos_recursos.h"
#include "interfazContactos_controladores.h"
#include "interfazContactos_actualizaciones.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void interfazContactos_inicializarValoresNulos (t_interfazContactos *interfazContactos);

/** \brief Inicializar los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int interfazContactos_inicializar (t_interfazContactos *interfazContactos);

/** \brief Configurar los recursos graficos y logica de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 */
void interfazContactos_configurar (t_interfazContactos *interfazContactos, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Ejecutar la interfaz de contactos.
 *
 * Realizar los procesos de:
 * 1) Accion: Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * 2) Actualizacion: Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
 * 3) Renderizado: Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de contactos en la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void ejecutarInterfazContactos (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de contactos.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void interfazContactos_liberar (t_interfazContactos *interfazContactos);


#endif // INTERFAZCONTACTOS_H_INCLUDED


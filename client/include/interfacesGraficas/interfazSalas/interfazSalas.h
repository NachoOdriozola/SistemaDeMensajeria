/**
 * \file   interfazSalas.h
 * \brief  Contiene funciones estructurales de interfaz.
 */


#ifndef INTERFAZSALAS_H_INCLUDED
#define INTERFAZSALAS_H_INCLUDED


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
#include "interfazSalas_estructuras.h"
#include "interfazSalas_recursos.h"
#include "interfazSalas_controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL de los recursos graficos de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos y logica de la interfaz de salas.
 *
 */
void interfazSalas_inicializarValoresNulos (t_interfazSalas *interfazSalas);

/** \brief Inicializar los recursos graficos de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos y logica de la interfaz de salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
t_codigoRetorno interfazSalas_inicializar (t_interfazSalas *interfazSalas);

/** \brief Configurar los recursos graficos y la logica de la interfaz de salas. Ademas, asigna los recursos comunes.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos y logica de la interfaz de salas.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 */
void interfazSalas_configurar (t_interfazSalas *interfazSalas, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Ejecutar la interfaz de salas.
 *
 * Realizar los procesos de:
 * 1) Accion: Capturar y manejar los eventos generados por el usuario directamente (clicks, teclado, redimensionado, etc).
 * 2) Actualizacion: Capturar y manejar los eventos no generados por el usuario directamente (recepcion de mensajes o notificaciones, etc).
 * 3) Renderizado: Limpiar la ventana anterior y mostrar los recursos graficos actualizados de la interfaz de salas en la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param interfazSalas Puntero a la estructura base de los recursos graficos y logica de la interfaz de salas.
 *
 */
void ejecutarInterfazSalas (t_contextoAplicacion *contextoAplicacion, t_interfazSalas *interfazSalas);

/** \brief Liberar, de manera segura, todos los recursos graficos de la interfaz de salas.
 *
 * \param interfazSalas Puntero a la estructura base de los recursos graficos y logica de la interfaz de salas.
 *
 */
void interfazSalas_liberar (t_interfazSalas *interfazSalas);


#endif // INTERFAZSALAS_H_INCLUDED

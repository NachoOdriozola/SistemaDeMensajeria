/**
 * \file  recursosComunesContactosSalas.h
 * \brief Contiene funciones estructurales de interfaz.
 */


#ifndef RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "../../../../../shared/constantes/include/constantes.h"
#include "../../../utiles.h"
#include "../../../../../shared/estructurasDeDatos/listaDoble/include/listaDoble.h"

#include "recursosComunesContactosSalas_estructuras.h"
#include "recursosComunesContactosSalas_recursos.h"
#include "recursosComunesContactosSalas_mensajes.h"
#include "recursosComunesContactosSalas_controladores.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Inicializar todas las variables graficas en NULL y crear la lista de mensajes de los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 * 
 */
void recursosComunesContactosSalas_inicializarValoresNulos (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Inicializar los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 * 
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
t_codigoRetorno recursosComunesContactosSalas_inicializar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Configurar los recursos graficos comunes y la logica (compartidos) entre las interfaces de contactos y salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 * 
 */
void recursosComunesContactosSalas_configurar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Renderizar los recursos graficos de textos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 * Procurar el orden de los renderizados para que no se superpongan.
 *
 * \param renderizado renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasTextos *textos);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 * Procurar el orden de los renderizados para que no se superpongan.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasElementos *elementos);

/** \brief Liberar, de manera segura, todos los recursos graficos y vistas comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 * 
 */
void recursosComunesContactosSalas_liberar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);


#endif // RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED


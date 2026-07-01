/**
 * \file  recursosComunesContactosSalas_controladores.h
 * \brief Contiene funciones controladoras.
 */


#ifndef RECURSOSCOMUNESCONTACTOSSALAS_CONTROLADORES_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_CONTROLADORES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../../../../external/csfml/include/SFML/System.h"
#include "../../../../../external/csfml/include/SFML/Window.h"
#include "../../../../../external/csfml/include/SFML/Graphics.h"

#include "recursosComunesContactosSalas_estructuras.h"
#include "recursosComunesContactosSalas_recursos.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Manejar el evento de redimensionamiento de la ventana.
 *
 * Verificar que el nuevo tamanio de la ventana no exceda los valores de ancho y alto minimos, establecer los valores que correspondan a la ventana de renderizado,
 * y fijar los valores logicos de la vista UI.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param Vistas Puntero a la estructura que contiene las vistas comunes de las interfaces de contactos y salas.
 * \param eventoRedimensionamiento Variable de evento que contiene los nuevos valores de la ventana redimensionada.
 *
 */
void recursosComunesContactosSalas_manejarRedimensionamientoVentana (sfRenderWindow *renderizado, t_recursosComunesContactosSalasVistas *vistas, sfEvent eventoRedimensionamiento);


/** \brief Activar la interfaz de contactos.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de contactos.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_activarInterfazContactos (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Activar la interfaz de salas.
 *
 * Resetear la interfaz en uso y modificar los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_activarInterfazSalas (t_recursosComunesContactosSalas *recursosComunesContactosSalas);


/** \brief Establecer el nombre de usuario en un texto grafico.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 * \param nombreUsuario Puntero al nombre de usuario.
 *
 */
void recursosComunesContactosSalas_establecerNombreUsuario (t_recursosComunesContactosSalas *recursosComunesContactosSalas, const char *nombreUsuario);

/** \brief Posicionar el nombre de usuario sobre la interfaz.
 *
 * Si el nombre de usuario no entra dentro del area establecida, se achica el tamanio del texto hasta que quede centrado.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_posicionarNombreUsuario (t_recursosComunesContactosSalas *recursosComunesContactosSalas);


/** \brief Manejar el evento de click en la barra de escritura para escribir mensaje.
 *
 * Establece el foco en escribir mensaje y osiciona el punto de insercion.
 * 
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool recursosComunesContactosSalas_manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de click en el area de mensajes.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool recursosComunesContactosSalas_manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);


/** \brief Manejar el evento de escribir mensaje.
 *
 * Si se encuentra el foco en escribir mensaje, verifica que el caracter ingresado es valido.
 * En caso de exito, actualiza visualmente el caracter ingresado en la barra de escritura y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool recursosComunesContactosSalas_manejarEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoChar);


/** \brief Manejar el evento de pegar desde el portapapeles al buffer de escribir mensaje.
 *
 * Si se encuentra el foco en escribir mensaje, intenta pegar el texto desde el portapapeles al mensaje.
 * En caso de exito, actualiza visualmente el caracter ingresado en la barra de escritura y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool recursosComunesContactosSalas_manejarPegarTextoDesdePortapapelesAEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas);


/** \brief Manejar el evento de desplazar arriba el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia arriba por la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool recursosComunesContactosSalas_manejarDesplazarArribaAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de desplazar abajo el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia abajo por la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool recursosComunesContactosSalas_manejarDesplazarAbajoAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas);


/** \brief Manejar el evento de scroll en el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes segun la direccion y velocidad del scroll realizado.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos y logica comunes entre las interfaces de contactos y salas.
 * \param eventoScroll Variable de evento que contiene datos sobre el scroll.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool recursosComunesContactosSalas_manejarScrollAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoScroll);


#endif // RECURSOSCOMUNESCONTACTOSSALAS_CONTROLADORES_H_INCLUDED
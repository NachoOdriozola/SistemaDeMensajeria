/**
 * \file   interfazContactos_controladores.h
 * \brief  Contiene funciones controladoras.
 */


#ifndef INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
#define INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../../../../external/csfml/include/SFML/System.h"
#include "../../../../external/csfml/include/SFML/Window.h"
#include "../../../../external/csfml/include/SFML/Graphics.h"

#include "../../estructuras.h"
#include "../../comunicacion.h"
#include "../../utiles.h"

#include "interfazContactos_estructuras.h"
#include "interfazContactos_recursos.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


void _interfazContactos_deshabilitarFocos (t_interfazContactos *interfazContactos);


/*
 * Verifica que no sea un mensaje vacio.
 * Contempla los casos de envio de un comando para seleccion de un chat y para el envio de un mensaje.
 * En caso de seleccion de chat: verifica que sea un comando valido, envia la solicitud, y si esta es respondida con exito, setea el nuevo chat logicamente y graficamente.
 * En caso de envio de un mensaje: envia la solicitud, y si esta es respondida con exito, inserta el mensaje en la lista de mensajes para mostrar.
*/
bool _interfazContactos_manejarClickEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);

/*
 * Verifica que no sea un mensaje vacio.
 * Contempla los casos de envio de un comando para seleccion de un chat y para el envio de un mensaje.
 * En caso de seleccion de chat: verifica que sea un comando valido, envia la solicitud, y si esta es respondida con exito, setea el nuevo chat logicamente y graficamente.
 * En caso de envio de un mensaje: envia la solicitud, y si esta es respondida con exito, inserta el mensaje en la lista de mensajes para mostrar.
*/
bool _interfazContactos_manejarEnterEnviarMensaje (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);


void _interfazContactos_resetearBarraDeEscritura (t_interfazContactos *interfazContactos);


/*
 * Manejar el error de conexion para cualquier tipo de solicitud enviada de la interfaz de contactos.
*/
void _interfazContactos_manejarErrorConexion (t_contextoAplicacion *contextoAplicacion, t_interfazContactos *interfazContactos);









void interfazContactos_resetear (sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);

/** \brief Manejar el evento de redimensionamiento de la ventana.
 *
 * Verificar que el nuevo tamanio de la ventana no exceda los valores de ancho y alto minimos, establecer los valores que correspondan a la ventana de renderizado,
 * y fijar los valores logicos de la vista UI.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param Vistas Puntero a la estructura que contiene las vistas comunes de la interfaz de contactos.
 * \param eventoRedimensionamiento Variable de evento que contiene los nuevos valores de la ventana redimensionada.
 *
 */
void _interfazContactos_manejarRedimensionamientoVentana (sfRenderWindow *renderizado, t_interfazContactosVistas *vistas, sfEvent eventoRedimensionamiento);


/** \brief Establecer el nombre de usuario en un texto grafico.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 * \param nombreUsuario Puntero al nombre de usuario.
 *
 */
void _interfazContactoss_establecerNombreUsuario (t_interfazContactos *interfazContactos, const char *nombreUsuario);

/** \brief Posicionar el nombre de usuario sobre la interfaz.
 *
 * Si el nombre de usuario no entra dentro del area establecida, se achica el tamanio del texto hasta que quede centrado.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 */
void _interfazContactos_posicionarNombreUsuario (t_interfazContactos *interfazContactos);


/** \brief Manejar el evento de click en la barra de escritura para escribir mensaje.
 *
 * Establece el foco en escribir mensaje y osiciona el punto de insercion.
 * 
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool _interfazContactos_manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);

/** \brief Manejar el evento de click en el area de mensajes.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool _interfazContactos_manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_interfazContactos *interfazContactos);


/** \brief Manejar el evento de escribir mensaje.
 *
 * Si se encuentra el foco en escribir mensaje, verifica que el caracter ingresado es valido.
 * En caso de exito, actualiza visualmente el caracter ingresado en la barra de escritura y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool _interfazContactos_manejarEscribirMensaje (t_interfazContactos *interfazContactos, sfEvent eventoChar);


/** \brief Manejar el evento de pegar desde el portapapeles al buffer de escribir mensaje.
 *
 * Si se encuentra el foco en escribir mensaje, intenta pegar el texto desde el portapapeles al mensaje.
 * En caso de exito, actualiza visualmente el caracter ingresado en la barra de escritura y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_MANEJADO sin realizar ninguna accion.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool _interfazContactos_manejarPegarTextoDesdePortapapelesAEscribirMensaje (t_interfazContactos *interfazContactos);


/** \brief Manejar el evento de desplazar arriba el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia arriba por la velocidad del scroll.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool _interfazContactos_manejarDesplazarArribaAreaMensajes (t_interfazContactos *interfazContactos);

/** \brief Manejar el evento de desplazar abajo el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia abajo por la velocidad del scroll.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool _interfazContactos_manejarDesplazarAbajoAreaMensajes (t_interfazContactos *interfazContactos);


/** \brief Manejar el evento de scroll en el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes segun la direccion y velocidad del scroll realizado.
 *
 * \param interfazContactos Puntero a la estructura base de los recursos graficos y logica de la interfaz de contactos.
 * \param eventoScroll Variable de evento que contiene datos sobre el scroll.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool _interfazContactos_manejarScrollAreaMensajes (t_interfazContactos *interfazContactos, sfEvent eventoScroll);







#endif // INTERFAZCONTACTOS_CONTROLADORES_H_INCLUDED
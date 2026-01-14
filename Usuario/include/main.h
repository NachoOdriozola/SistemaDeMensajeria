/**
 * \file   main.h
 * \brief  Une las interfaces graficas y contiene las funciones estructurales base de ejecucion principal.
 */



#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include "../../Constantes/constantes.h"
#include "../../EstructurasDeDatos/include/listaSimple.h"
#include "../../EstructurasDeDatos/include/listaCircular.h"
#include "logicaUsuario.h"

#include "interfaces/interfazAutenticacion.h"
#include "interfaces/interfazConfig.h"
#include "interfaces/interfazContactos.h"
#include "interfaces/interfazRegistro.h"
#include "interfaces/interfazSalas.h"



/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_interfaces
 * \brief Une todas las interfaces graficas y los recursos graficos comunes.
 */
typedef struct
{
    t_interfazAutenticacion autenticacion;
    t_interfazConfig config;
    t_interfazContactos contactos;
    t_interfazRegistro registro;
    t_interfazSalas salas;
    t_recursosComunesAutenticacionRegistro recursosComunesAutenticacionRegistro;
    t_recursosComunesContactosSalas recursosComunesContactosSalas;
} t_interfaces;



/* ============================
   FUNCIONES ESTRUCTURALES BASE
   ============================ */



/** \brief Inicializar los recursos de la aplicacion.
 *
 * Iniciar la API de Winsock y crear el socket del usuario y conectarlo con el servidor, el renderizado de la ventana, los recursos graficos comunes esenciales (contactos y salas),
 * las interfaces graficas esenciales, las fuentes para las letras y la lista de mensajes y de notificaciones.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int inicializarAplicacion (t_aplicacion *aplicacion, t_interfaces *interfaces);

/** \brief Configurar los recursos de la aplicacion.
 *
 * Configurar el renderizado, los recursos graficos comunes esenciales (contactos y salas), las interfaces graficas esenciales,
 * la lista de mensajes, y ademas establecerles un tamanio y una posicion sobre la ventana.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void configurarAplicacion (t_aplicacion *aplicacion, t_interfaces *interfaces);

/** \brief Liberar los recursos de la aplicacion.
 *
 * Liberar la lista de mensajes y la lista de notificaciones, las interfaces graficas esenciales y de autenticacion, los recursos graficos comunes esenciales (contactos y salas) y de autenticacion (autenticacion y registro),
 * las fuentes de los textos graficos, el socket del usuario junto con la API de Winsock y el renderizado de la ventana. En orden contrario a como se crearon.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void liberarAplicacion (t_aplicacion *aplicacion, t_interfaces *interfaces);



/* ============================
   FUNCIONES DE INICIO
   ============================ */



/** \brief Preparar la aplicacion para iniciar el menu principal.
 *
 * Maximizar la ventana y seleccionar la interfaz de contactos como interfaz de menu principal.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void iniciarMenuPrincipal (t_aplicacion *aplicacion, t_interfaces *interfaces);

/** \brief Inicializar y configurar las interfaces graficas de autenticacion.
 *
 * Seleccionar la interfaz de autenticacion como interfaz principal e inicializar, configurar y establecer un tamanio y una posicion sobre la ventana
 * a los recursos graficos comunes de autenticacion (autenticacion y registro) y las interfaces de autenticacion y registro.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int iniciarAutenticacionManual (t_aplicacion *aplicacion, t_interfaces *interfaces);



#endif // MAIN_H_INCLUDED


















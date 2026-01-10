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
 * \brief Une todas las interfaces graficas.
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
 * Configurar el renderizado, los recursos graficos comunes esenciales (contactos y salas), las interfaces graficas esenciales, el renderizado y la lista de mensajes.
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



/** \brief Configurar la aplicacion y las interfaces graficas esenciales para iniciar el menu principal.
 *
 * Seleccionar la interfaz de contactos como menu principal, maximizar la ventana y almacenar valores sobre ella en la estructura ventana, establecer un tamanio a las vistas
 * de los recursos graficos comunes de las interfaces de contactos y salas, y configurar el tamanio y la posicion de los mensajes de la lista de mensajes sobre la ventana,
 * y los recursos graficos comunes de las interfaces de contactos y salas.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 */
void iniciarMenuPrincipal (t_aplicacion *aplicacion, t_interfaces *interfaces);

/** \brief Inicializar y configurar las interfaces graficas de autenticacion.
 *
 * Seleccionar la interfaz de autenticacion como principal e inicializar y configurar los recursos graficos comunes e interfaces de autenticacion y registro.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param interfaces Puntero a la estructura unificadora de interfaces graficas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int iniciarAutenticacionManual (t_aplicacion *aplicacion, t_interfaces *interfaces);



#endif // MAIN_H_INCLUDED


















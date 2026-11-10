/**
 * \file   autenticacion.h
 * \brief 
 */


#ifndef AUTENTICACION_H_INCLUDED
#define AUTENTICACION_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sodium.h"

#include "constantes.h"
#include "mensajes.h"

#include "bd/bd.h"
#include "servicios/contexto_servicios.h"


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/*
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudAutenticacion.
 * 
 * Consultar en la base de datos si las credenciales del usuario existen y son validas.
 * Verificar que el usuario no se encuentre conectado.
 * Si el usuario no se encuentra conectado, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaAutenticacion.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_EXITO|ID del usuario #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_ERROR_OPERACION_INVALIDA|ID invalido #En caso de que el usuario ya se encuentre conectado.
 * RESPUESTA_SOLICITUD_AUTENTICACION|SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido #En caso de que sean datos de usuario invalidos, el usuario no exista o que la contrasenia sea incorrecta.
 */
CodigoRetorno autenticacion_procesar (Servicios *servicios, Cliente *cliente, const SolicitudAutenticacion *solicitudAutenticacion);


#endif // AUTENTICACION_H_INCLUDED
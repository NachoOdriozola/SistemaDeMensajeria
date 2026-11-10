/**
 * \file   registro.h
 * \brief 
 */


#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED


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
 * Recibe los datos del usuario que envio la solicitud con la estructura SolicitudRegistro.
 * 
 * Verificar en la base de datos si ya existe un usuario registrado con el mismo nombre de usuario o correo electronico.
 * Si el usuario se puede registrar, lo conecta mediante recuperar su ID, guardarlo en el nodo del cliente y moverlo de la lista doble de clientes no autenticados a la tabla hash de clientes autenticados.
 * 
 * Responde los datos del procesamiento de la solicitud al cliente con la estructura RespuestaRegistro.
 * 
 * Posibles respuestas:
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_EXITO|ID del usuario #En caso de procesamiento exitoso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_CREDENCIALES_INVALIDAS|ID invalido #En caso de que sean datos de usuario invalidos.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_NOMBRE_YA_EXISTENTE|ID invalido #En caso de que el nombre de usuario ya se encuentre en uso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_CORREO_YA_EXISTENTE|ID invalido #En caso de que el correo electronico ya se encuentre en uso.
 * RESPUESTA_SOLICITUD_REGISTRO|SOLICITUD_ERROR_SERVIDOR|ID invalido #En caso de problemas al hashear la contrasenia.
 */
CodigoRetorno registro_procesar (Servicios *servicios, Cliente *cliente, SolicitudRegistro *solicitudRegistro);


#endif // REGISTRO_H_INCLUDED
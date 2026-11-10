/**
 * \file   registro_clientes.h
 * \brief  
 */


#ifndef REGISTRO_CLIENTES_H_INCLUDED
#define REGISTRO_CLIENTES_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include "lista_doble.h"
#include "tabla_hash.h"

#include "constantes.h"

#include "logs.h"

#include "clientes/cliente.h"


/* ============================================================================================================================================
   DEFINES
   ============================================================================================================================================ */


/**
 * \def TABLA_HASH_CANT_BUCKETS_USUARIOS
 * \brief Cantidad de buckets que tiene la tabla hash de clientes autenticados.
 */
#define TABLA_HASH_CANT_BUCKETS_USUARIOS 1000


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


typedef struct
{
   ListaDoble noAutenticados;                   /**< Lista doble que contiene a los clientes conectados pero no autenticados. */
   TablaHash autenticados;                        /**< Tabla hash que contiene a los clientes conectados y autenticados. */
} RegistroClientes;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


CodigoRetorno registro_clientes_inicializar (RegistroClientes *registroClientes);
CodigoRetorno registro_clientes_insertar_no_autenticado (RegistroClientes *registroClientes, const Cliente *cliente);
CodigoRetorno registro_clientes_promover_cliente (RegistroClientes *registroClientes, Cliente **cliente, int idCliente);
bool registro_clientes_buscar_autenticado (RegistroClientes *registroClientes, int id, Cliente **returnCliente);
void registro_clientes_eliminar_desconectados (RegistroClientes *registroClientes);
CodigoRetorno registro_clientes_por_cada (RegistroClientes *registroClientes, CodigoRetorno accion (void *cliente, void *contexto), void *contexto);
void registro_clientes_mostrar_no_autenticados (RegistroClientes *registroClientes);
void registro_clientes_mostrar_autenticados (RegistroClientes *registroClientes);
void registro_clientes_vaciar (RegistroClientes *registroClientes);


#endif // REGISTRO_CLIENTES_H_INCLUDED
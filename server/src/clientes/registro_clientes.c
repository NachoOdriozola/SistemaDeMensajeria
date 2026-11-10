#include "clientes/registro_clientes.h"


/* ============================================================================================================================================
   DECLARACION DE FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static int hash_id_cliente (const void *idCliente);
static int cmp_id_cliente (const void *cliente, const void *id);
static bool clientes_conectados (const void *cliente);
static void mostrar_cliente (void *cliente);
static void liberar_cliente (void *cliente);


/* ============================================================================================================================================
   FUNCIONES PUBLICAS
   ============================================================================================================================================ */


CodigoRetorno registro_clientes_inicializar (RegistroClientes *registroClientes)
{
    lista_doble_crear (&(registroClientes->noAutenticados));
    if (tabla_hash_crear (&(registroClientes->autenticados), TABLA_HASH_CANT_BUCKETS_USUARIOS) != EXITO)
    {
        logs_escribir (LOG_ERROR, "registro_clientes", "Inicializacion fallida.");
        return ERROR_INICIALIZACION;
    }
    return EXITO;
}

CodigoRetorno registro_clientes_insertar_no_autenticado (RegistroClientes *registroClientes, const Cliente *cliente)
{
    if (lista_doble_insertar_al_inicio (&(registroClientes->noAutenticados), cliente, sizeof (Cliente)) != EXITO)
    {
        logs_escribir (LOG_ERROR, "registro_clientes", "Insercion de cliente no autenticado.");
        return ERROR_SIN_MEMORIA;
    }
    return EXITO;
}

CodigoRetorno registro_clientes_promover_cliente (RegistroClientes *registroClientes, Cliente **cliente, int idCliente)
{
    cliente_asignar_id (*cliente, idCliente);
    if (tabla_hash_insertar (&(registroClientes->autenticados), &idCliente, hash_id_cliente, *cliente, sizeof (Cliente)) != EXITO)
    {
        logs_escribir (LOG_ERROR, "registro_clientes", "Promocion de cliente.");
        return ERROR_SIN_MEMORIA;
    }
    lista_doble_eliminar_elemento_con_clave (&(registroClientes->noAutenticados), &idCliente, NULL, 0, cmp_id_cliente);
    tabla_hash_buscar_elemento_con_clave (&(registroClientes->autenticados), &idCliente, hash_id_cliente, (void**)cliente, cmp_id_cliente);

    return EXITO;
}

bool registro_clientes_buscar_autenticado (RegistroClientes *registroClientes, int id, Cliente **returnCliente)
{
    return tabla_hash_buscar_elemento_con_clave (&(registroClientes->autenticados), &id, hash_id_cliente, (void**)returnCliente, cmp_id_cliente);
}

void registro_clientes_eliminar_desconectados (RegistroClientes *registroClientes)
{
    lista_doble_filter_con_accion (&(registroClientes->noAutenticados), clientes_conectados, liberar_cliente);
    tabla_hash_filter_con_accion (&(registroClientes->autenticados), clientes_conectados, liberar_cliente);
}

CodigoRetorno registro_clientes_por_cada (RegistroClientes *registroClientes, CodigoRetorno accion (void *cliente, void *contexto), void *contexto)
{
    CodigoRetorno resultado;

    resultado = lista_doble_map_con_contexto_y_error (&(registroClientes->noAutenticados), accion, contexto);
    if (resultado != EXITO)
        return resultado;
    return tabla_hash_map_con_contexto_y_error (&(registroClientes->autenticados), accion, contexto);
}

void registro_clientes_mostrar_no_autenticados (RegistroClientes *registroClientes)
{
    lista_doble_map (&(registroClientes->noAutenticados), mostrar_cliente);
    puts ("\n");
}

void registro_clientes_mostrar_autenticados (RegistroClientes *registroClientes)
{
    tabla_hash_map (&(registroClientes->autenticados), mostrar_cliente);
    puts("\n");
}

void registro_clientes_vaciar (RegistroClientes *registroClientes)
{
    lista_doble_vaciar_con_accion (&(registroClientes->noAutenticados), liberar_cliente);
    tabla_hash_eliminar_con_accion (&(registroClientes->autenticados), liberar_cliente);
}


/* ============================================================================================================================================
   FUNCIONES PRIVADAS
   ============================================================================================================================================ */


static int hash_id_cliente (const void *idCliente)
{
    return *((int*)idCliente) % TABLA_HASH_CANT_BUCKETS_USUARIOS;
}

static int cmp_id_cliente (const void *cliente, const void *id)
{
    if (cliente_obtener_id ((Cliente*)cliente) == *((int*)id))
        return 0;
    return 1;
}

static bool clientes_conectados (const void *cliente)
{
    return cliente_esta_conectado ((const Cliente*)cliente);
}

static void mostrar_cliente (void *cliente)
{
    cliente_mostrar ((const Cliente*)cliente);
}

static void liberar_cliente (void *cliente)
{
    cliente_liberar ((Cliente*)(cliente));
}

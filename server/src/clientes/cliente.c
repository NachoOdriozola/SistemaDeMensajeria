#include "clientes/cliente.h"


void cliente_inicializar (Cliente *cliente, Socket socket)
{
    cliente->socket = socket;
    cliente->id = ID_NO_AUTENTICADO;
    cliente->estado = CONECTADO;
}

void cliente_asignar_id (Cliente *cliente, int idCliente)
{
    cliente->id = idCliente;
}

int cliente_obtener_id (const Cliente *cliente)
{
    return (cliente->id);
}

void cliente_marcar_desconectado (Cliente *cliente)
{
    cliente->estado = DESCONECTADO;
}

bool cliente_esta_conectado (const Cliente *cliente)
{
    return cliente->estado;
}

void cliente_mostrar (const Cliente *cliente)
{
    printf ("ID: %d\t", cliente->id);
}

void cliente_liberar (Cliente *cliente)
{
    if (socket_es_valido (cliente->socket))
        socket_cerrar (&(cliente->socket));
}

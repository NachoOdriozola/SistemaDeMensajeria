#include "logica/utiles.h"


int aplicar_hash_id_cliente (const void *clave)
{
    return *((int*)clave) % CANT_BUCKETS_TABLA_HASH;
}

int cmp_id_cliente (const void *cliente, const void *clave)
{
    return (*((Cliente*)cliente)).id - *((int*)clave);
}

void mostrar_cliente (void *cliente)
{
    printf ("%d\n", (*((Cliente*)cliente)).id);
}

void liberar_cliente (void *cliente)
{
    socket_cerrar (&(((Cliente*)cliente)->sock));
}


#include "../include/utiles.h"



int funcionHash (const void *clave)
{
    return *((int*)clave) % CANT_BUCKETS_TABLA_HASH;
}

int cmpIdCliente (const void *cliente, const void *clave)
{
    return (*((t_cliente*)cliente)).id - *((int*)clave);
}

void mostrarCliente (void *cliente)
{
    printf ("%d\n", (*((t_cliente*)cliente)).id);
}

void liberarCliente (void *cliente)
{
    closesocket (((t_cliente*)cliente)->sock);
}
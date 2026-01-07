#include <stdio.h>
#include <stdlib.h>
#include "../../EstructurasDeDatos/include/listaSimple.h"
#include "../../EstructurasDeDatos/include/tablaHash.h"

#define CANT_BUCKETS_TABLA_HASH 1000

typedef struct
{
    int id;
    char nombre;
} s_cliente;

int funcionHash (const void *dato);
void mostrarCliente (void *dato);
int cmpCliente (const void *A, const void *B);

int main()
{
    s_tablaHash tablaHash;
    s_cliente cliente;
    int i;

    crearTablaHash (&tablaHash, CANT_BUCKETS_TABLA_HASH);

    cliente.nombre = 'c';
    for (i = 0; i < CANT_BUCKETS_TABLA_HASH; i ++)
    {
        cliente.id = i;
        insertarEnTablaHash (&tablaHash, &(cliente.id), funcionHash, &cliente, sizeof (s_cliente));
    }

    for (i = 0; i < CANT_BUCKETS_TABLA_HASH; i ++)
    {
        cliente.id = i + 1000;
        insertarEnTablaHash (&tablaHash, &(cliente.id), funcionHash, &cliente, sizeof (s_cliente));
    }

    //mapTablaHash (&tablaHash, mostrarCliente);

    int id = 1999;
    if (buscarClaveEnTablaHash (&tablaHash, &id, funcionHash, &cliente, sizeof (s_cliente), cmpCliente))
        printf ("Encontro %d\n", cliente.id);
    else
        printf ("No encontron.\n");

    return 0;
}

int funcionHash (const void *dato)
{
    return *((int*)dato) % CANT_BUCKETS_TABLA_HASH;
}

void mostrarCliente (void *dato)
{
    printf ("%d\t%c\n", (*((s_cliente*)dato)).id, (*((s_cliente*)dato)).nombre);
}

int cmpCliente (const void *A, const void *B)
{
    s_cliente a = *((s_cliente*)A);
    int b = *((int*)B);

    return a.id - b;
}

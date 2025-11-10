#include "TablaHash.h"

void crearTablaHash (s_tablaHash *tablaHash, unsigned short int cantBuckets)
{
    unsigned short int i;

    if (cantBuckets <= 0)
        return;

    tablaHash->cantBuckets = cantBuckets;
    tablaHash->buckets = (s_lista*) malloc (cantBuckets * sizeof (s_lista));
    if (!tablaHash->buckets)
    {
        perror ("ERROR - Sin memoria.\n");
        return;
    }

    for (i = 0; i < cantBuckets; i++)
        crearLista (&(tablaHash->buckets[i]));
}

bool insertarEnTablaHash (s_tablaHash *tablaHash, s_cliente *cliente)
{
    unsigned short int indice;

    indice = funcionHash (tablaHash->cantBuckets, cliente->id);
    if (insertarAlInicioLista (&(tablaHash->buckets[indice]), cliente, sizeof (s_cliente)) == SIN_MEMORIA)
        return false;
    return true;
}

bool buscarIdEnTablaHash (s_tablaHash *tablaHash, int id)
{
    unsigned short int indice;
    s_cliente cliente;

    indice = funcionHash (tablaHash->cantBuckets, id);
    if (buscarClaveUnicaEnLista (&(tablaHash->buckets[indice]), &id, &cliente, sizeof (s_cliente), cmpIdCliente) == ENCONTRO)
    {
        printf ("Encontro: %u: %d\t%s\n", indice, cliente.id, cliente.nombre);
        return true;
    }
    printf ("No encontro id %u\n", id);
    return false;
}

void mostrarTablaHash (s_tablaHash *tablaHash, void mostrar (void*))
{
    unsigned short int i;

    if (tablaHash->buckets == NULL)
        return;

    printf ("EMPIEZA\n");
    for (i = 0; i < tablaHash->cantBuckets; i ++)
    {
        if (tablaHash->buckets[i] == NULL)
            printf ("%u\t---\n", i);
        else
        {
            printf ("%u\t", i);
            mapLista (&(tablaHash->buckets[i]), mostrar);
            printf ("\n");
        }
    }
    printf ("TERMINA\n");
}

void eliminarTablaHash (s_tablaHash *tablaHash)
{
    unsigned short int i;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        vaciarListaConAccion (&(tablaHash->buckets[i]), accionInutil);

    free (tablaHash->buckets);
    tablaHash->buckets = NULL;
}

unsigned short int funcionHash (unsigned short int cantBuckets, int id)
{
    return id % cantBuckets;
}

void mostrarCliente (void *cliente)
{
    s_cliente x = *(s_cliente*)cliente;

    printf ("%d\t%s\t\t", x.id, x.nombre);
}

int cmpIdCliente (const void *A, const void *B)
{
    int a = *(int*)A;
    int b = *(int*)B;

    return a - b;
}

void accionInutil (void *dato)
{
    //liberar socket
}











































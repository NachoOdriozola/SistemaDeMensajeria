#include "../include/tablaHash.h"


int crearTablaHash (t_tablaHash *tablaHash, int cantBuckets)
{
    int i;

    if (cantBuckets <= 0)
        return 0;

    tablaHash->cantBuckets = cantBuckets;
    tablaHash->buckets = (t_listaSimple*) malloc (cantBuckets * sizeof (t_listaSimple));
    if (!tablaHash->buckets)
    {
        perror ("ERROR - Sin memoria.\n");
        return 1;
    }

    for (i = 0; i < cantBuckets; i++)
        crearListaSimple (&(tablaHash->buckets[i]));

    return 0;
}

int insertarEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), const void *dato, unsigned tamDato)
{
    if (insertarAlInicioListaSimple (&(tablaHash->buckets[funcionHash(clave)]), dato, tamDato) == 1)
        return 1;
    return 0;
}

void vincularNodoATablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), t_nodo *nodoAVincular)
{
    vincularNodoAlInicioListaSimple (&(tablaHash->buckets[funcionHash(clave)]), nodoAVincular);
}

int buscarClaveUnicaEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), void *returnDato, unsigned tamDato, int cmp (const void*, const void*))
{
    if (buscarClaveUnicaEnListaSimple (&(tablaHash->buckets[funcionHash(clave)]), clave, returnDato, tamDato, cmp) == 1)
        return 1;
    return 0;
}

void mapTablaHash (t_tablaHash *tablaHash, void accion (void*))
{
    int i;

    if (tablaHash->buckets == NULL)
        return;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        mapListaSimple (&(tablaHash->buckets[i]), accion);
}

void eliminarTablaHashConAccion (t_tablaHash *tablaHash, void accion (void*))
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        vaciarListaSimpleConAccion (&(tablaHash->buckets[i]), accion);

    free (tablaHash->buckets);
    tablaHash->buckets = NULL;
}



























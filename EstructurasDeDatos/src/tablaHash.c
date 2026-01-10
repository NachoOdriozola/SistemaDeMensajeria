#include "../include/tablaHash.h"


int crearTablaHash (t_tablaHash *tablaHash, int cantBuckets)
{
    int i;

    if (cantBuckets <= 0)
        return EXITO;

    tablaHash->cantBuckets = cantBuckets;
    tablaHash->buckets = (t_listaSimple*) malloc (cantBuckets * sizeof (t_listaSimple));
    if (!tablaHash->buckets)
    {
        perror ("ERROR - Sin memoria.\n");
        return ERROR_SIN_MEMORIA;
    }

    for (i = 0; i < cantBuckets; i++)
        crearListaSimple (&(tablaHash->buckets[i]));

    return EXITO;
}

bool insertarEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), const void *dato, unsigned tamDato)
{
    if (insertarAlInicioListaSimple (&(tablaHash->buckets[funcionHash(clave)]), dato, tamDato) == ERROR_SIN_MEMORIA)
        return false;
    return true;
}

void vincularNodoATablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), t_nodo *nodoAVincular)
{
    vincularNodoAListaSimple (&(tablaHash->buckets[funcionHash(clave)]), nodoAVincular);
}

bool buscarClaveEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), void *returnDato, unsigned tamDato, int cmp (const void*, const void*))
{
    if (buscarClaveUnicaEnListaSimple (&(tablaHash->buckets[funcionHash(clave)]), clave, returnDato, tamDato, cmp) == ENCONTRO_CLAVE)
        return ENCONTRO_CLAVE;
    return NO_ENCONTRO_CLAVE;
}

void mapTablaHash (t_tablaHash *tablaHash, void accion (void*))
{
    int i;

    if (tablaHash->buckets == NULL)
        return;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
    {
        printf ("Bucket %d:\n", i);
        mapListaSimple (&(tablaHash->buckets[i]), accion);
    }
}

void eliminarTablaHashConAccion (t_tablaHash *tablaHash, void accion (void*))
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        vaciarListaSimpleConAccion (&(tablaHash->buckets[i]), accion);

    free (tablaHash->buckets);
    tablaHash->buckets = NULL;
}



























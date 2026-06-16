#include "../include/tablaHash.h"


int crearTablaHash (t_tablaHash *tablaHash, int cantBuckets)
{
    int i;

    if (cantBuckets <= 0)
        return 0;

    tablaHash->cantBuckets = cantBuckets;
    tablaHash->buckets = (t_listaDoble*) malloc (cantBuckets * sizeof (t_listaDoble));
    if (!tablaHash->buckets)
    {
        perror ("ERROR - Sin memoria.\n");
        return 1;
    }

    for (i = 0; i < cantBuckets; i++)
        crearListaDoble (&(tablaHash->buckets[i]));

    return 0;
}

int insertarEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), const void *dato, unsigned tamDato)
{
    return insertarAlInicioListaDoble (&(tablaHash->buckets[funcionHash(clave)]), dato, tamDato);
}

void vincularNodoATablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), t_nodoListaDoble *nodoAVincular)
{
    vincularNodoAlInicioListaDoble (&(tablaHash->buckets[funcionHash(clave)]), nodoAVincular);
}

int buscarClaveUnicaEnTablaHash (t_tablaHash *tablaHash, const void *clave, int funcionHash (const void*), void *returnDato, unsigned tamDato, int cmp (const void*, const void*))
{
    return buscarClaveUnicaEnListaDoble (&(tablaHash->buckets[funcionHash(clave)]), clave, returnDato, tamDato, cmp);
}

void mapTablaHash (t_tablaHash *tablaHash, void accion (void*))
{
    int i;

    if (tablaHash->buckets == NULL)
        return;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        mapListaDoble (&(tablaHash->buckets[i]), accion);
}

void eliminarTablaHashConAccion (t_tablaHash *tablaHash, void accion (void*))
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        vaciarListaDobleConAccion (&(tablaHash->buckets[i]), accion);

    free (tablaHash->buckets);
    tablaHash->buckets = NULL;
}



























#include "../include/tablaHash.h"


int crearTablaHash (s_tablaHash *tablaHash, unsigned short int cantBuckets)
{
    unsigned short int i;

    if (cantBuckets <= 0)
        return EXITO;

    tablaHash->cantBuckets = cantBuckets;
    tablaHash->buckets = (s_listaSimple*) malloc (cantBuckets * sizeof (s_listaSimple));
    if (!tablaHash->buckets)
    {
        perror ("ERROR - Sin memoria.\n");
        return ERROR_SIN_MEMORIA;
    }

    for (i = 0; i < cantBuckets; i++)
        crearListaSimple (&(tablaHash->buckets[i]));

    return EXITO;
}

bool insertarEnTablaHash (s_tablaHash *tablaHash, const void *clave, unsigned short int funcionHash (const void*), const void *dato, unsigned tamDato)
{
    unsigned short int indice;

    indice = funcionHash (clave);
    if (insertarAlInicioListaSimple (&(tablaHash->buckets[indice]), dato, tamDato) == ERROR_SIN_MEMORIA)
        return false;
    return true;
}

void vincularNodoATablaHash (s_tablaHash *tablaHash, const void *clave, unsigned short int funcionHash (const void*), s_nodo *nodoAVincular)
{
    unsigned short int indice;

    indice = funcionHash (clave);
    vincularNodoAListaSimple (&(tablaHash->buckets[indice]), nodoAVincular);
}

bool buscarClaveEnTablaHash (s_tablaHash *tablaHash, const void *clave, unsigned short int funcionHash (const void*), void *dato, unsigned tamDato, int cmp (const void*, const void*))
{
    unsigned short int indice;

    indice = funcionHash (clave);
    if (buscarClaveUnicaEnListaSimple (&(tablaHash->buckets[indice]), clave, dato, tamDato, cmp) == ENCONTRO)
        return ENCONTRO;
    return NO_ENCONTRO;
}

void mapTablaHash (s_tablaHash *tablaHash, void accion (void*))
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
            mapListaSimple (&(tablaHash->buckets[i]), accion);
            printf ("\n");
        }
    }
    printf ("TERMINA\n");
}

void eliminarTablaHashConAccion (s_tablaHash *tablaHash, void accion (void*))
{
    unsigned short int i;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        vaciarListaSimpleConAccion (&(tablaHash->buckets[i]), accion);

    free (tablaHash->buckets);
    tablaHash->buckets = NULL;
}



























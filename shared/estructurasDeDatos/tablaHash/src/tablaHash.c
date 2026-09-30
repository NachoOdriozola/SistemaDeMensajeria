#include "tablaHash.h"


int tabla_hash_crear (TablaHash *tablaHash, int cantBuckets)
{
    int i;

    if (cantBuckets <= 0)
        return 0;

    tablaHash->cantBuckets = cantBuckets;
    tablaHash->buckets = (ListaDoble*) malloc (cantBuckets * sizeof (ListaDoble));
    if (!tablaHash->buckets)
    {
        perror ("ERROR - Sin memoria.\n");
        return 1;
    }

    for (i = 0; i < cantBuckets; i++)
        lista_doble_crear (&(tablaHash->buckets[i]));

    return 0;
}

int tabla_hash_insertar (TablaHash *tablaHash, const void *clave, int hash (const void*), const void *dato, unsigned tamDato)
{
    return lista_doble_insertar_al_inicio (&(tablaHash->buckets[hash(clave)]), dato, tamDato);
}

void tabla_hash_vincular_nodo (TablaHash *tablaHash, const void *clave, int hash (const void*), NodoListaDoble *nodoAVincular)
{
    lista_doble_vincular_nodo_al_inicio (&(tablaHash->buckets[hash(clave)]), nodoAVincular);
}

int tabla_hash_buscar_clave_unica (TablaHash *tablaHash, const void *clave, int hash (const void*), void *returnDato, unsigned tamDato, int cmp (const void*, const void*))
{
    return lista_doble_buscar_clave_unica (&(tablaHash->buckets[hash(clave)]), clave, returnDato, tamDato, cmp);
}

void tabla_hash_map (TablaHash *tablaHash, void accion (void*))
{
    int i;

    if (tablaHash->buckets == NULL)
        return;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        lista_doble_map (&(tablaHash->buckets[i]), accion);
}

void tabla_hash_eliminar_con_accion (TablaHash *tablaHash, void accion (void*))
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        lista_doble_vaciar_con_accion (&(tablaHash->buckets[i]), accion);

    free (tablaHash->buckets);
    tablaHash->buckets = NULL;
}



























#include "tabla_hash.h"


CodigoRetorno tabla_hash_crear (TablaHash *tablaHash, unsigned short int cantBuckets)
{
    int i;

    if (cantBuckets <= 0)
    {
        logs_escribir (LOG_ERROR, "tabla hash", "Creacion: cantidad de buckets invalida.");
        return ERROR_OPERACION_INVALIDA;
    }

    tablaHash->cantBuckets = cantBuckets;
    tablaHash->buckets = (ListaDoble*) malloc (cantBuckets * sizeof (ListaDoble));
    if (!tablaHash->buckets)
    {
        logs_escribir (LOG_ERROR, "tabla hash", "Creacion: sin memoria.");
        return ERROR_SIN_MEMORIA;
    }

    for (i = 0; i < cantBuckets; i++)
        lista_doble_crear (&(tablaHash->buckets[i]));

    return EXITO;
}

CodigoRetorno tabla_hash_insertar (TablaHash *tablaHash, const void *clave, int hash (const void*), const void *dato, size_t tamDato)
{
    if (lista_doble_insertar_al_inicio (&(tablaHash->buckets[hash(clave)]), dato, tamDato) != EXITO)
    {
        logs_escribir (LOG_ERROR, "tabla hash", "Insercion de dato: sin memoria.");
        return ERROR_SIN_MEMORIA;
    }

    return EXITO;
}

bool tabla_hash_buscar_elemento_con_clave (TablaHash *tablaHash, const void *clave, int hash (const void*), void **returnDato, int cmp (const void *a, const void *b))
{
    return lista_doble_buscar_elemento_con_clave (&(tablaHash->buckets[hash(clave)]), clave, returnDato, cmp);
}

void tabla_hash_map (TablaHash *tablaHash, void accion (void *dato))
{
    int i;

    if (tablaHash->buckets == NULL)
        return;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        lista_doble_map (&(tablaHash->buckets[i]), accion);
}

CodigoRetorno tabla_hash_map_con_contexto_y_error (TablaHash *tablaHash, CodigoRetorno accion (void *dato, void *contexto), void *contexto)
{
    CodigoRetorno resultado;
    int i;

    if (tablaHash->buckets == NULL)
        return EXITO;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
    {
        resultado = lista_doble_map_con_contexto_y_error (&(tablaHash->buckets[i]), accion, contexto);
        if (resultado != EXITO)
            return resultado;
    }

    return EXITO;
}

void tabla_hash_filter_con_accion (TablaHash *tablaHash, bool filtro (const void *dato), void accion (void *dato))
{
    int i;

    if (tablaHash->buckets == NULL)
        return;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        lista_doble_filter_con_accion (&(tablaHash->buckets[i]), filtro, accion);
}

void tabla_hash_mostrar (TablaHash *tablaHash, void mostrar (void *dato))
{
    int i;

    if (tablaHash->buckets == NULL)
        return;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
    {
        printf ("Bucket %d: ", i);
        lista_doble_map (&(tablaHash->buckets[i]), mostrar);
        puts ("");
    }
}

void tabla_hash_eliminar_con_accion (TablaHash *tablaHash, void accion (void *dato))
{
    int i;

    for (i = 0; i < tablaHash->cantBuckets; i ++)
        lista_doble_vaciar_con_accion (&(tablaHash->buckets[i]), accion);

    if (tablaHash->buckets != NULL)
    {
        free (tablaHash->buckets);
        tablaHash->buckets = NULL;
    }
}



























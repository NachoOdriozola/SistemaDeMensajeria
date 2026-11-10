#include "cola.h"

void cola_crear (Cola *cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}

CodigoRetorno cola_insertar (Cola *cola, const void *dato, size_t tamDato)
{
    NodoCola *nuevoNodo;

    nuevoNodo = malloc (sizeof (NodoCola));
    if (!nuevoNodo)
    {
        logs_escribir (LOG_ERROR, "cola", "Insercion de dato: sin memoria.");
        return ERROR_SIN_MEMORIA;
    }

    nuevoNodo->dato = malloc (tamDato);
    if (!nuevoNodo->dato)
    {
        free (nuevoNodo);
        logs_escribir (LOG_ERROR, "cola", "Insercion de dato: sin memoria.");
        return ERROR_SIN_MEMORIA;
    }

    memcpy (nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;
    nuevoNodo->sig = NULL;

    if (cola->pri == NULL)
        cola->pri = nuevoNodo;

    if (cola->ult == NULL)
        cola->ult = nuevoNodo;
    else
    {
        cola->ult->sig = nuevoNodo;
        cola->ult = nuevoNodo;
    }

    return EXITO;
}

void cola_sacar (Cola *cola, void *returnDato, size_t tamDato)
{
    NodoCola *nodoElim;

    if (cola->pri == NULL)
        return;

    nodoElim = cola->pri;
    cola->pri = nodoElim->sig;
    if (cola->pri == NULL)
        cola->ult = NULL;
    memcpy (returnDato, nodoElim->dato, ((tamDato < nodoElim->tam) ? tamDato : nodoElim->tam));
    free (nodoElim->dato);
    free (nodoElim);
}

bool cola_no_esta_vacia (Cola *cola)
{
    return (cola->pri != NULL);
}

void cola_vaciar (Cola *cola)
{
    NodoCola *nodoElim;

    while (cola->pri != NULL)
    {
        nodoElim = cola->pri;
        cola->pri = nodoElim->sig;
        free (nodoElim->dato);
        free (nodoElim);
    }
    cola->ult = NULL;
}

#include "cola.h"

void cola_crear (Cola *c)
{
    c->pri = NULL;
    c->ult = NULL;
}

int cola_insertar (Cola *c, void *dato, unsigned tamDato)
{
    NodoCola *nuevoNodo;

    nuevoNodo = malloc (sizeof (NodoCola));
    if (!nuevoNodo)
        return 1;

    nuevoNodo->dato = malloc (tamDato);
    if (!nuevoNodo->dato)
        return 1;

    memcpy (nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;
    nuevoNodo->sig = NULL;

    if (c->pri == NULL)
        c->pri = nuevoNodo;

    if (c->ult == NULL)
        c->ult = nuevoNodo;
    else
    {
        c->ult->sig = nuevoNodo;
        c->ult = nuevoNodo;
    }

    return 0;
}

void cola_sacar (Cola *c, void *returnDato, unsigned tamDato)
{
    NodoCola *nodoElim;

    if (c->pri == NULL)
        return;

    nodoElim = c->pri;
    c->pri = nodoElim->sig;
    if (c->pri == NULL)
        c->ult = NULL;
    memcpy (returnDato, nodoElim->dato, ((tamDato < nodoElim->tam) ? tamDato : nodoElim->tam));
    free (nodoElim->dato);
    free (nodoElim);
}

bool cola_no_esta_vacia (Cola *c)
{
    return (c->pri != NULL);
}

void cola_vaciar (Cola *c)
{
    NodoCola *nodoElim;

    while (c->pri != NULL)
    {
        nodoElim = c->pri;
        c->pri = nodoElim->sig;
        free (nodoElim->dato);
        free (nodoElim);
    }
    c->ult = NULL;
}

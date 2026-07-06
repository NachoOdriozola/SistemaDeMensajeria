#include "../include/cola.h"

void crearCola (t_cola *c)
{
    c->pri = NULL;
    c->ult = NULL;
}

int insertarACola (t_cola *c, void *dato, unsigned tamDato)
{
    t_nodoCola *nuevoNodo;

    nuevoNodo = malloc (sizeof (t_nodoCola));
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

void desacolar (t_cola *c, void *returnDato, unsigned tamDato)
{
    t_nodoCola *nodoElim;

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

bool noEsColaVacia (t_cola *c)
{
    return (c->pri != NULL);
}

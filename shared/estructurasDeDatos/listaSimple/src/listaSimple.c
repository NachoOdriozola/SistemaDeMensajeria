#include "../include/listaSimple.h"


void crearListaSimple (t_listaSimple *pl)
{
    *pl = NULL;
}

int insertarAlInicioListaSimple (t_listaSimple *pl, const void *dato, unsigned tamDato)
{
    t_nodo *nuevoNodo;

    nuevoNodo = malloc (sizeof (t_nodo));
    if (!nuevoNodo)
    {
        perror ("ERROR - Sin memoria.\n");
        return 1;
    }
    nuevoNodo->dato = malloc (tamDato);
    if (!nuevoNodo->dato)
    {
        perror ("ERROR - Sin memoria.\n");
        free (nuevoNodo);
        return 1;
    }

    memcpy (nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;
    nuevoNodo->sig = *pl;
    *pl = nuevoNodo;

    return 0;
}

void vincularNodoAlInicioListaSimple (t_listaSimple *pl, t_nodo *nodoAVincular)
{
    nodoAVincular->sig = *pl;
    *pl = nodoAVincular;
}

void mapListaSimple (t_listaSimple *pl, void accion (void *dato))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato);
        pl = &((*pl)->sig);
    }
}

void mapListaSimpleConComplemento (t_listaSimple *pl, void *complemento, void accion (void *dato, void *complemento))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato, complemento);
        pl = &((*pl)->sig);
    }
}

int buscarClaveUnicaEnListaSimple (t_listaSimple *pl, const void *key, void *returnDato, unsigned tamDato, int cmp (const void *a, const void *b))
{
    while (*pl != NULL)
    {
        if (cmp ((*pl)->dato, key) == 0)
        {
            memcpy (returnDato, (*pl)->dato, MINIMO ((*pl)->tam, tamDato));
            return 1;
        }
        pl = &((*pl)->sig);
    }

    return 0;
}

t_nodo* desvincularNodoDeListaSimple (t_nodo **nodoADesvincular)
{
    t_nodo *nodo = *nodoADesvincular;

    *nodoADesvincular = nodo->sig;

    return nodo;
}

void eliminarNodoConAccionListaSimple (t_listaSimple *pl, void *returnDato, unsigned tamDato, void accion (void *dato))
{
    t_nodo *nodoElim = *pl;

    *pl = nodoElim->sig;
    if (returnDato != NULL)
        memcpy (returnDato, nodoElim->dato, MINIMO (nodoElim->tam, tamDato));
    accion (nodoElim->dato);
    free (nodoElim->dato);
    free (nodoElim);
}

void vaciarListaSimpleConAccion (t_listaSimple *pl, void accion (void *dato))
{
    t_nodo *nodoElim;

    while (*pl != NULL)
    {
        nodoElim = *pl;
        *pl = nodoElim->sig;
        accion (nodoElim->dato);
        free (nodoElim->dato);
        free (nodoElim);
    }
}

































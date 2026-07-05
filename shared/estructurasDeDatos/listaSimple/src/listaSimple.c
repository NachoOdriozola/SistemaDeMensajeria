#include "../include/listaSimple.h"


void crearListaSimple (t_listaSimple *pl)
{
    *pl = NULL;
}

int insertarAlInicioListaSimple (t_listaSimple *pl, const void *dato, unsigned tamDato)
{
    t_nodoListaSimple *nuevoNodo;

    nuevoNodo = malloc (sizeof (t_nodoListaSimple));
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
            if (returnDato != NULL)
                memcpy (returnDato, (*pl)->dato, ((tamDato < (*pl)->tam) ? tamDato : (*pl)->tam));
            return 1;
        }
        pl = &((*pl)->sig);
    }

    return 0;
}

void eliminarNodoConAccionListaSimple (t_listaSimple *pl, void *returnDato, unsigned tamDato, void accion (void *dato))
{
    t_nodoListaSimple *nodoElim = *pl;

    *pl = nodoElim->sig;
    if (returnDato != NULL)
        memcpy (returnDato, nodoElim->dato, ((tamDato < (*pl)->tam) ? tamDato : (*pl)->tam));
        
    accion (nodoElim->dato);
    free (nodoElim->dato);
    free (nodoElim);
}

void vaciarListaSimpleConAccion (t_listaSimple *pl, void accion (void *dato))
{
    t_nodoListaSimple *nodoElim;

    while (*pl != NULL)
    {
        nodoElim = *pl;
        *pl = nodoElim->sig;
        accion (nodoElim->dato);
        free (nodoElim->dato);
        free (nodoElim);
    }
}


#include "lista_simple.h"


void lista_simple_crear (ListaSimple *pl)
{
    *pl = NULL;
}

int lista_simple_insertar_al_inicio (ListaSimple *pl, const void *dato, unsigned tamDato)
{
    NodoListaSimple *nuevoNodo;

    nuevoNodo = malloc (sizeof (NodoListaSimple));
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

void lista_simple_map (ListaSimple *pl, void accion (void *dato))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato);
        pl = &((*pl)->sig);
    }
}

void lista_simple_map_con_complemento (ListaSimple *pl, void *complemento, void accion (void *dato, void *complemento))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato, complemento);
        pl = &((*pl)->sig);
    }
}

int lista_simple_buscar_clave_unica (ListaSimple *pl, const void *key, void *returnDato, unsigned tamDato, int cmp (const void *a, const void *b))
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

void lista_simple_eliminar_nodo (ListaSimple *pl, void *returnDato, unsigned tamDato)
{
    NodoListaSimple *nodoElim = *pl;

    *pl = nodoElim->sig;
    if (returnDato != NULL)
        memcpy (returnDato, nodoElim->dato, ((tamDato < (*pl)->tam) ? tamDato : (*pl)->tam));
        
    free (nodoElim->dato);
    free (nodoElim);
}

void lista_simple_eliminar_nodo_con_accion (ListaSimple *pl, void *returnDato, unsigned tamDato, void accion (void *dato))
{
    NodoListaSimple *nodoElim = *pl;

    *pl = nodoElim->sig;
    if (returnDato != NULL)
        memcpy (returnDato, nodoElim->dato, ((tamDato < (*pl)->tam) ? tamDato : (*pl)->tam));
        
    accion (nodoElim->dato);
    free (nodoElim->dato);
    free (nodoElim);
}

void lista_simple_vaciar (ListaSimple *pl)
{
    NodoListaSimple *nodoElim;

    while (*pl != NULL)
    {
        nodoElim = *pl;
        *pl = nodoElim->sig;
        free (nodoElim->dato);
        free (nodoElim);
    }
}

void lista_simple_vaciar_con_accion (ListaSimple *pl, void accion (void *dato))
{
    NodoListaSimple *nodoElim;

    while (*pl != NULL)
    {
        nodoElim = *pl;
        *pl = nodoElim->sig;
        accion (nodoElim->dato);
        free (nodoElim->dato);
        free (nodoElim);
    }
}


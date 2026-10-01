#include "lista_doble.h"


void lista_doble_crear (ListaDoble *pl)
{
    *pl = NULL;
}

int lista_doble_insertar_al_inicio (ListaDoble *pl, const void *dato, unsigned tamDato)
{
    NodoListaDoble *nuevoNodo;

    nuevoNodo = malloc (sizeof(NodoListaDoble));
    if (!nuevoNodo)
        return 1;

    nuevoNodo->dato = malloc (tamDato);
    if (!(nuevoNodo->dato))
        return 1;

    nuevoNodo->tam = tamDato;
    memcpy (nuevoNodo->dato, dato, tamDato);

    if (*pl != NULL)
        (*pl)->ant = nuevoNodo;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = *pl;
    *pl = nuevoNodo;

    return 0;
}

void lista_doble_vincular_nodo_al_inicio (ListaDoble *pl, NodoListaDoble *nodoAVincular)
{
    if (*pl != NULL)
        (*pl)->ant = nodoAVincular;
    nodoAVincular->ant = NULL;
    nodoAVincular->sig = *pl;
    *pl = nodoAVincular;
}

void lista_doble_map (ListaDoble *pl, void accion (void*))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato);
        pl = &((*pl)->sig);
    }
}

void lista_doble_map_con_complemento (ListaDoble *pl, void accion (void*, void*), void *complemento)
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato, complemento);
        pl = &((*pl)->sig);
    }
}

int lista_doble_buscar_clave_unica (ListaDoble *pl, const void *key, void *returnDato, unsigned tamDato, int cmp (const void *a, const void *b))
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

void lista_doble_desvincular_nodo (ListaDoble *pl, NodoListaDoble *nodoADesvincular)
{
    NodoListaDoble *ant = nodoADesvincular->ant, *sig = nodoADesvincular->sig;

    if (ant != NULL)
        ant->sig = sig;
    else
        *pl = sig;
    if (sig != NULL)
        sig->ant = ant;

    nodoADesvincular->ant = NULL;
    nodoADesvincular->sig = NULL;
}

void lista_doble_eliminar_nodo_con_accion (ListaDoble *pl, void *returnDato, unsigned tamDato, void accion (void*))
{
    NodoListaDoble *nodoElim, *ant, *sig;

    if (*pl == NULL)
        return;

    nodoElim = *pl;
    ant = (*pl)->ant;
    sig = (*pl)->sig;

    if (returnDato != NULL)
        memcpy (returnDato, nodoElim->dato, ((tamDato < (*pl)->tam) ? tamDato : (*pl)->tam));
    
    if (ant != NULL)
        ant->sig = sig;
    else
        *pl = sig;
    if (sig != NULL)
        sig->ant = ant;

    accion (nodoElim->dato);
    free (nodoElim->dato);
    free (nodoElim);
}

void lista_doble_vaciar_con_accion (ListaDoble *pl, void accion (void *dato))
{
    NodoListaDoble *nodoElim;

    while (*pl != NULL)
    {
        nodoElim = *pl;
        *pl = (*pl)->sig;
        accion (nodoElim->dato);
        free (nodoElim->dato);
        free (nodoElim);
    }
}


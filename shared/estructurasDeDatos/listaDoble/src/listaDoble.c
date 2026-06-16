#include "../include/listaDoble.h"


void crearListaDoble (t_listaDoble *pl)
{
    *pl = NULL;
}

int insertarAlInicioListaDoble (t_listaDoble *pl, const void *dato, unsigned tamDato)
{
    t_nodoListaDoble *nuevoNodo;

    nuevoNodo = malloc (sizeof(t_nodoListaDoble));
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

void vincularNodoAlInicioListaDoble (t_listaDoble *pl, t_nodoListaDoble *nodoAVincular)
{
    if (*pl != NULL)
        (*pl)->ant = nodoAVincular;
    nodoAVincular->ant = NULL;
    nodoAVincular->sig = *pl;
    *pl = nodoAVincular;
}

void mapListaDoble (t_listaDoble *pl, void accion (void*))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato);
        pl = &((*pl)->sig);
    }
}

int buscarClaveUnicaEnListaDoble (t_listaDoble *pl, const void *key, void *returnDato, unsigned tamDato, int cmp (const void *a, const void *b))
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

void desvincularNodoDeListaDoble (t_listaDoble *pl, t_nodoListaDoble *nodoADesvincular)
{
    t_nodoListaDoble *ant = nodoADesvincular->ant, *sig = nodoADesvincular->sig;

    if (ant != NULL)
        ant->sig = sig;
    else
        *pl = sig;
    if (sig != NULL)
        sig->ant = ant;

    nodoADesvincular->ant = NULL;
    nodoADesvincular->sig = NULL;
}

void eliminarNodoConAccionListaDoble (t_listaDoble *pl, void *returnDato, unsigned tamDato, void accion (void*))
{
    t_nodoListaDoble *nodoElim, *ant, *sig;

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

void vaciarListaDobleConAccion (t_listaDoble *pl, void accion (void *dato))
{
    t_nodoListaDoble *nodoElim;

    while (*pl != NULL)
    {
        nodoElim = *pl;
        *pl = (*pl)->sig;
        accion (nodoElim->dato);
        free (nodoElim->dato);
        free (nodoElim);
    }
}
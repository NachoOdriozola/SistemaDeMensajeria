#include "listaCircular.h"

void crearListaCircular (s_listaCircular *pl)
{
    *pl = NULL;
}

int insertarSegundoCircular (s_listaCircular *pl, const void *dato, unsigned tamDato)
{
    s_nodo *nuevoNodo;

    nuevoNodo = malloc (sizeof (s_nodo));
    if (!nuevoNodo)
    {
        perror ("ERROR - Sin memoria.\n");
        return SIN_MEMORIA;
    }
    nuevoNodo->dato = malloc (tamDato);
    if (!nuevoNodo->dato)
    {
        perror ("ERROR - Sin memoria.\n");
        free (nuevoNodo);
        return SIN_MEMORIA;
    }
    memcpy (nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;

    if (*pl == NULL)
    {
        nuevoNodo->sig = nuevoNodo;
        *pl = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = (*pl)->sig;
        (*pl)->sig = nuevoNodo;
    }

    return OK;
}

void mapListaCircular (s_listaCircular *pl, void accion (void *dato))
{
    s_nodo *nodoInicio = *pl;

    if (*pl != NULL)
    {
        accion ((*pl)->dato);
        pl = &((*pl)->sig);
    }
    while (*pl != nodoInicio)
    {
        accion ((*pl)->dato);
        pl = &((*pl)->sig);
    }
}

void mapListaCircularConComplemento (s_listaCircular *pl, void *complemento, void accion (void *dato, void *complemento))
{
    s_nodo *nodoInicio = *pl;

    if (*pl != NULL)
    {
        accion ((*pl)->dato, complemento);
        pl = &((*pl)->sig);
    }
    while (*pl != nodoInicio)
    {
        accion ((*pl)->dato, complemento);
        pl = &((*pl)->sig);
    }
}

void mapListaCircularConDobleComplemento (s_listaCircular *pl, void *primerComplemento, void *segundoComplemento, void accion (void *dato, void *primerComplemento, void *segundoComplemento))
{
    s_nodo *nodoInicio = *pl;

    if (*pl != NULL)
    {
        accion ((*pl)->dato, primerComplemento, segundoComplemento);
        pl = &((*pl)->sig);
    }
    while (*pl != nodoInicio)
    {
        accion ((*pl)->dato, primerComplemento, segundoComplemento);
        pl = &((*pl)->sig);
    }
}

void vaciarListaCircularConAccion (s_listaCircular *pl, void accion (void *dato))
{
    s_listaCircular *ptrMain = pl;
    s_nodo *nodoElim;

    if (*pl != NULL)
    {
        nodoElim = *pl;
        accion (nodoElim->dato);
        pl = &((*pl)->sig);
        free (nodoElim->dato);
        free (nodoElim);
    }
    while (*pl != *ptrMain)
    {
        nodoElim = *pl;
        accion (nodoElim->dato);
        pl = &((*pl)->sig);
        free (nodoElim->dato);
        free (nodoElim);
    }
    *ptrMain = NULL;
}











































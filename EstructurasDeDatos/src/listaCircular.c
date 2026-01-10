#include "../include/listaCircular.h"


void crearListaCircular (t_listaCircular *pl)
{
    *pl = NULL;
}

int insertarSegundoCircular (t_listaCircular *pl, const void *dato, unsigned tamDato)
{
    t_nodo *nuevoNodo;

    nuevoNodo = malloc (sizeof (t_nodo));
    if (!nuevoNodo)
    {
        perror ("ERROR - Sin memoria.\n");
        return ERROR_SIN_MEMORIA;
    }
    nuevoNodo->dato = malloc (tamDato);
    if (!nuevoNodo->dato)
    {
        perror ("ERROR - Sin memoria.\n");
        free (nuevoNodo);
        return ERROR_SIN_MEMORIA;
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

    return EXITO;
}

void mapListaCircular (t_listaCircular *pl, void accion (void *dato))
{
    t_nodo *nodoInicio = *pl;

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

void mapListaCircularConComplemento (t_listaCircular *pl, void *complemento, void accion (void *dato, void *complemento))
{
    t_nodo *nodoInicio = *pl;

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

void vaciarListaCircularConAccion (t_listaCircular *pl, void accion (void *dato))
{
    t_listaCircular *ptrMain = pl;
    t_nodo *nodoElim;

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











































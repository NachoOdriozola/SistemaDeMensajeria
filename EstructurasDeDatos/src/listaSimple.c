#include "../include/listaSimple.h"


void crearListaSimple (s_listaSimple *pl)
{
    *pl = NULL;
}

int insertarAlInicioListaSimple (s_listaSimple *pl, const void *dato, unsigned tamDato)
{
    s_nodo *nuevoNodo;

    nuevoNodo = malloc (sizeof (s_nodo));
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
    nuevoNodo->sig = *pl;
    *pl = nuevoNodo;

    return EXITO;
}

void vincularNodoAListaSimple (s_listaSimple *pl, s_nodo *nodoAVincular)
{
    nodoAVincular->sig = *pl;
    *pl = nodoAVincular;
}

void mapListaSimple (s_listaSimple *pl, void accion (void *dato))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato);
        pl = &((*pl)->sig);
    }
}

void mapListaSimpleConComplemento (s_listaSimple *pl, void *complemento, void accion (void *dato, void *complemento))
{
    while (*pl != NULL)
    {
        accion ((*pl)->dato, complemento);
        pl = &((*pl)->sig);
    }
}

int buscarClaveUnicaEnListaSimple (s_listaSimple *pl, const void *key, void *dato, unsigned tamDato, int cmp (const void *a, const void *b))
{
    while (*pl != NULL)
    {
        if (cmp ((*pl)->dato, key) == 0)
        {
            memcpy (dato, (*pl)->dato, MINIMO ((*pl)->tam, tamDato));
            return ENCONTRO;
        }
        pl = &((*pl)->sig);
    }

    return NO_ENCONTRO;
}

s_nodo* desvincularNodoDeListaSimple (s_nodo **nodo)
{
    s_nodo *nodoADesvincular = *nodo;

    *nodo = nodoADesvincular->sig;

    return nodoADesvincular;
}

void eliminarNodoConAccionListaSimple (s_listaSimple *pl, void *dato, unsigned tamDato, void accion (void *dato))
{
    s_nodo *nodoElim = *pl;

    *pl = nodoElim->sig;
    if (dato != NULL)
        memcpy (dato, nodoElim->dato, MINIMO (nodoElim->tam, tamDato));
    accion (nodoElim->dato);
    free (nodoElim->dato);
    free (nodoElim);
}

void vaciarListaSimpleConAccion (s_listaSimple *pl, void accion (void *dato))
{
    s_nodo *nodoElim;

    while (*pl != NULL)
    {
        nodoElim = *pl;
        *pl = nodoElim->sig;
        accion (nodoElim->dato);
        free (nodoElim->dato);
        free (nodoElim);
    }
}

































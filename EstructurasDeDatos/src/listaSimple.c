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

void vincularNodoAListaSimple (t_listaSimple *pl, t_nodo *nodoAVincular)
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
            return ENCONTRO_CLAVE;
        }
        pl = &((*pl)->sig);
    }

    return NO_ENCONTRO_CLAVE;
}

t_nodo* desvincularNodoDeListaSimple (t_nodo **nodo)
{
    t_nodo *nodoADesvincular = *nodo;

    *nodo = nodoADesvincular->sig;

    return nodoADesvincular;
}

void eliminarNodoConAccionListaSimple (t_listaSimple *pl, void *dato, unsigned tamDato, void accion (void *dato))
{
    t_nodo *nodoElim = *pl;

    *pl = nodoElim->sig;
    if (dato != NULL)
        memcpy (dato, nodoElim->dato, MINIMO (nodoElim->tam, tamDato));
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

































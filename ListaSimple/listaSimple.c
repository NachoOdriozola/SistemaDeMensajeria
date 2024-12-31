#include "listaSimple.h"

void crearLista (s_lista *pl)
{
    *pl = NULL;
}

int insertarAlInicioLista (s_lista *pl, const void *dato, unsigned tamDato)
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
    nuevoNodo->sig = *pl;
    *pl = nuevoNodo;

    return OK;
}

void eliminarNodoConAccion (s_lista *pl, void *dato, unsigned tamDato, void accion (void *dato))
{
    s_nodo *nodoElim = *pl;

    *pl = nodoElim->sig;
    if (dato != NULL)
        memcpy (dato, nodoElim->dato, MINIMO (nodoElim->tam, tamDato));
    accion (nodoElim->dato);
    free (nodoElim->dato);
    free (nodoElim);
}

void vaciarListaConAccion (s_lista *pl, void accion (void *dato))
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

































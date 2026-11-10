#include "lista_doble.h"


void lista_doble_crear (ListaDoble *listaDoble)
{
    *listaDoble = NULL;
}

CodigoRetorno lista_doble_insertar_al_inicio (ListaDoble *listaDoble, const void *dato, size_t tamDato)
{
    NodoListaDoble *nuevoNodo;

    nuevoNodo = malloc (sizeof(NodoListaDoble));
    if (!nuevoNodo)
    {
        logs_escribir (LOG_ERROR, "lista doble", "Insercion de dato: sin memoria.");
        return ERROR_SIN_MEMORIA;
    }

    nuevoNodo->dato = malloc (tamDato);
    if (!(nuevoNodo->dato))
    {
        free (nuevoNodo);
        logs_escribir (LOG_ERROR, "lista doble", "Insercion de dato: sin memoria.");
        return ERROR_SIN_MEMORIA;
    }

    nuevoNodo->tam = tamDato;
    memcpy (nuevoNodo->dato, dato, tamDato);

    if (*listaDoble != NULL)
        (*listaDoble)->ant = nuevoNodo;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = *listaDoble;
    *listaDoble = nuevoNodo;

    return EXITO;
}

void lista_doble_map (ListaDoble *listaDoble, void accion (void *dato))
{
    while (*listaDoble != NULL)
    {
        accion ((*listaDoble)->dato);
        listaDoble = &((*listaDoble)->sig);
    }
}

void lista_doble_map_con_contexto (ListaDoble *listaDoble, void accion (void *dato, void *contexto), void *contexto)
{
    while (*listaDoble != NULL)
    {
        accion ((*listaDoble)->dato, contexto);
        listaDoble = &((*listaDoble)->sig);
    }
}

CodigoRetorno lista_doble_map_con_contexto_y_error (ListaDoble *listaDoble, CodigoRetorno accion (void *dato, void *contexto), void *contexto)
{
    CodigoRetorno resultado;

    while (*listaDoble != NULL)
    {
        resultado = accion ((*listaDoble)->dato, contexto);
        if (resultado != EXITO)
            return resultado;
        listaDoble = &((*listaDoble)->sig);
    }
    return EXITO;
}

void lista_doble_filter_con_accion (ListaDoble *listaDoble, bool filtro (const void *dato), void accion (void *dato))
{
    NodoListaDoble *actual, *auxAnt, *auxSig;

    while (*listaDoble != NULL)
    {
        if (!filtro ((*listaDoble)->dato))
        {
            actual = *listaDoble;
            auxAnt = actual->ant;
            auxSig = actual->sig;

            if (auxAnt)
                auxAnt->sig = auxSig;
            else
                *listaDoble = auxSig;
            if (auxSig)
                auxSig->ant = auxAnt;

            accion (actual->dato);
            free (actual->dato);
            free (actual);
        }
        else
            listaDoble = &((*listaDoble)->sig);
    }
}

bool lista_doble_buscar_elemento_con_clave (ListaDoble *listaDoble, const void *key, void **returnDato, int cmp (const void *a, const void *b))
{
    while (*listaDoble != NULL)
    {
        if (cmp ((*listaDoble)->dato, key) == 0)
        {
            if (returnDato != NULL)
                *returnDato = (*listaDoble)->dato;
            return 1;
        }
        listaDoble = &((*listaDoble)->sig);
    }

    return 0;
}

bool lista_doble_eliminar_elemento_con_clave (ListaDoble *listaDoble, const void *key, void *returnDato, size_t tamDato, int cmp (const void *a, const void *b))
{
    NodoListaDoble *actual = *listaDoble;

    while (actual != NULL)
    {
        if (cmp (actual->dato, key) == 0)
        {
            NodoListaDoble *auxAnt = actual->ant;
            NodoListaDoble *auxSig = actual->sig;

            if (returnDato != NULL)
                memcpy (returnDato, actual->dato, ((tamDato < actual->tam) ? tamDato : actual->tam));

            if (auxAnt)
                auxAnt->sig = auxSig;
            else
                *listaDoble = auxSig;
            if (auxSig)
                auxSig->ant = auxAnt;

            free (actual->dato);
            free (actual);

            return 1;
        }
        actual = actual->sig;
    }

    return 0;
}

bool lista_doble_eliminar_elemento_con_clave_y_accion (ListaDoble *listaDoble, const void *key, void *returnDato, size_t tamDato, int cmp (const void *a, const void *b), void accion (void *dato))
{
    NodoListaDoble *actual = *listaDoble;

    while (actual != NULL)
    {
        if (cmp (actual->dato, key) == 0)
        {
            NodoListaDoble *auxAnt = actual->ant;
            NodoListaDoble *auxSig = actual->sig;

            if (returnDato != NULL)
                memcpy (returnDato, actual->dato, ((tamDato < actual->tam) ? tamDato : actual->tam));

            if (auxAnt)
                auxAnt->sig = auxSig;
            else
                *listaDoble = auxSig;
            if (auxSig)
                auxSig->ant = auxAnt;

            accion (actual->dato);
            free (actual->dato);
            free (actual);

            return 1;
        }
        actual = actual->sig;
    }

    return 0;
}

void lista_doble_vaciar_con_accion (ListaDoble *listaDoble, void accion (void *dato))
{
    NodoListaDoble *nodoElim;

    while (*listaDoble != NULL)
    {
        nodoElim = *listaDoble;
        *listaDoble = (*listaDoble)->sig;
        accion (nodoElim->dato);
        free (nodoElim->dato);
        free (nodoElim);
    }
}


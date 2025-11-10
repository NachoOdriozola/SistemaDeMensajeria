#include "TablaHash.h"

void crearTablaHash (s_cliente **tablaHash)
{
    unsigned short int i;

    for (i = 0; i < TAM_TABLA; i ++)
        tablaHash [i] = NULL;
}

bool insertarEnTablaHash (s_cliente **tablaHash, s_cliente *cliente)
{
    unsigned int indice;

    if (cliente == NULL)
        return false;

    indice = funcionHash (cliente->id);
    if (tablaHash[indice] != NULL)
    {
        printf ("Espacio ya ocupado.\n");
        return false;
    }
    tablaHash [indice] = cliente;
    printf ("Inserto correctamente.\n");

    return true;
}

void mostrarTablaHash (s_cliente **tablaHash)
{
    unsigned short int i;

    printf ("Empieza\n");

    for (i = 0; i < TAM_TABLA; i ++)
    {
        if (tablaHash [i] == NULL)
            printf ("%u\t---\n", i + 1);
        else
            printf ("%u\t%d\t%s\n", i + 1, tablaHash[i]->id, tablaHash[i]->nombre);
    }
    printf ("Termina\n");
}

bool buscarIdEnTablaHash (s_cliente **tablaHash, int id)
{
    unsigned int indice;

    indice = funcionHash (id);
    if (tablaHash[indice] == NULL)
    {
        printf ("No se encontro el id %d.\n", id);
        return false;
    }
    printf ("Encontrado: %d\t%s\n", tablaHash[indice]->id, tablaHash[indice]->nombre);

    return true;
}

bool eliminarIdEnTablaHash (s_cliente **tablaHash, int id)
{
    unsigned int indice;

    indice = funcionHash (id);
    if (tablaHash[indice] == NULL)
    {
        printf ("No se encontro el id %d.\n", id);
        return false;
    }
    printf ("Encontrado: %d\t%s\n", tablaHash[indice]->id, tablaHash[indice]->nombre);
    tablaHash [indice] = NULL;

    return true;
}

unsigned int funcionHash (int id)
{
    return id % TAM_TABLA;
}






































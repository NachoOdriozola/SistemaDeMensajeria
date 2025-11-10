#include "TablaHash.h"

int main()
{
    s_cliente *tablaHash [TAM_TABLA];

    crearTablaHash (tablaHash);
    mostrarTablaHash (tablaHash);

    s_cliente nacho = {10, "nacho"};
    insertarEnTablaHash (tablaHash, &nacho);

    mostrarTablaHash (tablaHash);

    s_cliente fabri = {11, "fabri"};
    insertarEnTablaHash (tablaHash, &fabri);
    s_cliente jara = {15, "jara"};
    insertarEnTablaHash (tablaHash, &jara);
    s_cliente rama = {19, "rama"};
    insertarEnTablaHash (tablaHash, &rama);

    mostrarTablaHash (tablaHash);

    s_cliente lopa = {20, "lopa"};
    insertarEnTablaHash (tablaHash, &lopa);

    mostrarTablaHash (tablaHash);

    buscarIdEnTablaHash (tablaHash, 15);
    buscarIdEnTablaHash (tablaHash, 19);
    buscarIdEnTablaHash (tablaHash, 17);

    eliminarIdEnTablaHash (tablaHash, 17);
    eliminarIdEnTablaHash (tablaHash, 19);

    mostrarTablaHash (tablaHash);

    /*
    printf ("id: 10 - hash: %u\n", funcionHash (10));
    printf ("id: 11 - hash: %u\n", funcionHash (11));
    printf ("id: 12 - hash: %u\n", funcionHash (12));
    printf ("id: 13 - hash: %u\n", funcionHash (13));
    printf ("id: 14 - hash: %u\n", funcionHash (14));
    printf ("id: 15 - hash: %u\n", funcionHash (15));
    printf ("id: 16 - hash: %u\n", funcionHash (16));
    printf ("id: 17 - hash: %u\n", funcionHash (17));
    printf ("id: 18 - hash: %u\n", funcionHash (18));
    printf ("id: 19 - hash: %u\n", funcionHash (19));
    printf ("id: 20 - hash: %u\n", funcionHash (20));
    */

    return 0;
}


























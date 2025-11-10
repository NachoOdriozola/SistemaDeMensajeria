#include "TablaHash.h"

int main()
{
    s_tablaHash tabla;

    crearTablaHash (&tabla, TAM_TABLA);
    mostrarTablaHash (&tabla, mostrarCliente);


    s_cliente nacho = {10, "nacho"};
    insertarEnTablaHash (&tabla, &nacho);

    mostrarTablaHash (&tabla, mostrarCliente);

    s_cliente fabri = {11, "fabri"};
    insertarEnTablaHash (&tabla, &fabri);
    s_cliente jara = {15, "jara"};
    insertarEnTablaHash (&tabla, &jara);
    s_cliente rama = {19, "rama"};
    insertarEnTablaHash (&tabla, &rama);

    mostrarTablaHash (&tabla, mostrarCliente);

    s_cliente lopa = {20, "lopa"};
    insertarEnTablaHash (&tabla, &lopa);
    s_cliente lopa2 = {30, "lopa2"};
    insertarEnTablaHash (&tabla, &lopa2);
    s_cliente lopa3 = {40, "lopa3"};
    insertarEnTablaHash (&tabla, &lopa3);

    mostrarTablaHash (&tabla, mostrarCliente);

    buscarIdEnTablaHash (&tabla, 40);
    buscarIdEnTablaHash (&tabla, 10);
    buscarIdEnTablaHash (&tabla, 19);
    buscarIdEnTablaHash (&tabla, 14);
    buscarIdEnTablaHash (&tabla, 11);
    buscarIdEnTablaHash (&tabla, 30);

    eliminarTablaHash (&tabla);
    mostrarTablaHash (&tabla, mostrarCliente);

    return 0;
}


















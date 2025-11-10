#ifndef TABLAHASH_H_INCLUDED
#define TABLAHASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NOMBRE 26
#define TAM_TABLA 10

typedef struct
{
    int id;
    char nombre [MAX_NOMBRE];
} s_cliente;


/** \brief Crea la tabla hash.
 *
 * Se realiza un for del tamano de la tabla y se inicializa en 0 a cada vector perteneciente a ella.
 *
 * \param tablaHash doble puntero a matriz de tabla hash.
 *
 */
void crearTablaHash (s_cliente **tablaHash);

bool insertarEnTablaHash (s_cliente **tablaHash, s_cliente *cliente);
void mostrarTablaHash (s_cliente **tablaHash);
bool buscarIdEnTablaHash (s_cliente **tablaHash, int id);
bool eliminarIdEnTablaHash (s_cliente **tablaHash, int id);
unsigned int funcionHash (int id);

#endif // TABLAHASH_H_INCLUDED

#ifndef TABLAHASH_H_INCLUDED
#define TABLAHASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../../../EstructurasDeDatos/Nodo/nodo.h"
#include "../../../../EstructurasDeDatos/ListaSimple/listaSimple.h"

#define MAX_NOMBRE 26
#define TAM_TABLA 10

typedef struct
{
    s_lista *buckets;
    unsigned short int cantBuckets;
} s_tablaHash;

typedef struct
{
    int id;
    char nombre [MAX_NOMBRE];
} s_cliente;

void crearTablaHash (s_tablaHash *tablaHash, unsigned short int cantBuckets);
bool insertarEnTablaHash (s_tablaHash *tablaHash, s_cliente *cliente);
bool buscarIdEnTablaHash (s_tablaHash *tablaHash, int id);
void mostrarTablaHash (s_tablaHash *tablaHash, void mostrar (void*));
void eliminarTablaHash (s_tablaHash *tablaHash);

unsigned short int funcionHash (unsigned short int cantBuckets, int id);
void mostrarCliente (void *cliente);
int cmpIdCliente (const void *A, const void *B);
void accionInutil (void *dato);

#endif // TABLAHASH_H_INCLUDED

















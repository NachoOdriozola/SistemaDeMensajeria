/**
 * \file   cola.h
 * \brief  Contiene las funciones primitivas de cola.
 */


#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED


/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_nodoCola
 * \brief Define la estructura base de un nodo de una cola. Utiliza el s_nodoCola como recursivo.
 */
typedef struct s_nodoCola
{
    void *dato;
    unsigned tam;
    struct s_nodoCola *sig;
} t_nodoCola;

typedef struct
{
    t_nodoCola *pri;
    t_nodoCola *ult;
} t_cola;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Crear la cola apuntandola a NULL;
 *
 * \param c Direccion de la cola.
 *
 */
void crearCola (t_cola *c);

/** \brief Insertar a la cola.
 *
 * Crea un nuevo nodo y le asigna espacio en el dato del tamanio del dato con memoria dinamica, le copia el dato al nodo y lo ubica en la cola.
 *
 * \param c Direccion de la cola.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
int insertarACola (t_cola *c, void *dato, unsigned tamDato);

/** \brief Desacolar el primer elemento de la cola.
 *
 * Elimina el nodo desacolado con su dato almacenado.
 *
 * \param c Direccion de la cola.
 * \param returnDato Puntero donde se retorna el dato que contenia el nodo.
 * \param tamDato tamanio en bytes del dato.
 *
 */
void desacolar (t_cola *c, void *returnDato, unsigned tamDato);

/** \brief Verificar si la cola no esta vacia.
 *
 * \param c Direccion de la cola.
 *
 */
bool noEsColaVacia (t_cola *c);


#endif // COLA_H_INCLUDED
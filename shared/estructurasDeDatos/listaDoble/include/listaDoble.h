/**
 * \file   listaDoble.h
 * \brief  Contiene las funciones primitivas de lista doblemente enlazada.
 */


#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED



/* ============================================================================================================================================
   INCLUDES
   ============================================================================================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ============================================================================================================================================
   ESTRUCTURAS
   ============================================================================================================================================ */


/** \struct t_nodoListaDoble
 * \brief Define la estructura base de un nodo de una lista doblemente enlazada. Utiliza el s_nodoListaDoble como recursivo.
 */
typedef struct s_nodoListaDoble
{
    void *dato;
    unsigned tam;
    struct s_nodoListaDoble *sig;
    struct s_nodoListaDoble *ant;
} t_nodoListaDoble;

typedef t_nodoListaDoble *t_listaDoble;


/* ============================================================================================================================================
   FUNCIONES
   ============================================================================================================================================ */


/** \brief Crear la lista doble apuntandola a NULL.
 *
 * \param pl Direccion de la lista doble.
 *
 */
void crearListaDoble (t_listaDoble *pl);

/** \brief Insertar al inicio de la lista doble.
 *
 * Crea un nuevo nodo y le asigna espacio en el dato del tamanio del dato con memoria dinamica, le copia el dato al nodo y lo ubica al inicio de la lista doble.
 *
 * \param pl Direccion de la lista doble.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return 0 si se ejecuto correctamente, 1 en caso de no poder asignar memoria.
 *
 */
int insertarAlInicioListaDoble (t_listaDoble *pl, const void *dato, unsigned tamDato);

/** \brief Vincula un nodo ya creado al inicio de la lista doble.
 *
 * \param pl Direccion de la lista doble.
 * \param nodoAVincular Puntero al nodo a vincular.
 *
 */
void vincularNodoAlInicioListaDoble (t_listaDoble *pl, t_nodoListaDoble *nodoAVincular);

/** \brief Funcion map sobre la lista doble.
 *
 * \param pl Direccion de la lista doble.
 * \param accion Funcion de accion a realizar sobre la lista doble.
 *
 */
void mapListaDoble (t_listaDoble *pl, void accion (void*));

/** \brief Funcion map con un complemento sobre la lista doble.
 *
 * \param pl Direccion de la lista doble.
 * \param accion Funcion de accion a realizar sobre la lista doble.
 * \param complemento Complemento que se utilizara en la funcion de accion.
 *
 */
void mapListaDobleConComplemento (t_listaDoble *pl, void accion (void*, void*), void *complemento);

/** \brief Buscar una clave unica en la lista doble.
 *
 * Devolver en returnDato el dato si es encontrado por su clave en la lista doble.
 * Retorna en returnDato el tamanio minimo entre el argumento enviado y el tamanio almacenado en el nodo.
 * returnDato puede ser NULL si no se necesita almacenar el dato buscado.
 *
 * \param pl Direccion de la lista doble.
 * \param key Puntero a la clave a buscar.
 * \param returnDato Puntero donde se guardara el dato del nodo encontrado por la clave.
 * \param tamDato tamanio en bytes del dato a guardar.
 * \param cmp Funcion de comparacion que se debe realizar para encontrar el nodo con la clave.
 *
 * \return 1 si encontro la clave, 0 en caso contrario.
 *
 */
int buscarClaveUnicaEnListaDoble (t_listaDoble *pl, const void *key, void *returnDato, unsigned tamDato, int cmp (const void *a, const void *b));

/** \brief Desvincular un nodo de la lista doble.
 *
 * No borra su dato ni el nodo, solo lo desliga de la lista doble.
 * Asegura mantener el orden de la lista doble.
 *
 * \param nodoADesvincular Doble puntero al nodo a desvincular.
 *
 */
void desvincularNodoDeListaDoble (t_listaDoble *pl, t_nodoListaDoble *nodoADesvincular);

/** \brief Eliminar el nodo, realizando una accion sobre el dato previamente, apuntado por la lista doble.
 *
 * Libera la memoria dinamica creada para el dato y para el nodo.
 * Devolver en returnDato el dato del nodo a eliminar.
 * returnDato puede ser NULL si no se necesita almacenar el dato eliminado.
 *
 * \param pl Direccion de la lista doble.
 * \param returnDato Puntero donde se guardara el dato antes de eliminarse.
 * \param tamDato tamanio en bytes del dato.
 * \param accion Funcion de accion a realizar sobre el dato del nodo antes de eliminarlo.
 *
 */
void eliminarNodoConAccionListaDoble (t_listaDoble *pl, void *returnDato, unsigned tamDato, void accion (void*));

/** \brief Vaciar la lista doble, realizando una accion sobre los datos previamente.
 *
 * Libera la memoria dinamica creada para el dato y para el nodo.
 *
 * \param pl Direccion de la lista doble.
 * \param accion Funcion de accion a realizar sobre los datos de los nodos antes de eliminarlos.
 *
 */
void vaciarListaDobleConAccion (t_listaDoble *pl, void accion (void *dato));


#endif // LISTADOBLE_H_INCLUDED
/**
 * \file   listaSimple.h
 * \brief  Contiene las funciones primitivas de lista circular.
 */


#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED


/* ============================
   INCLUDES
   ============================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nodo.h"
#include "../../Constantes/constantes.h"


/* ============================
   DEFINES
   ============================ */


typedef t_nodo *t_listaCircular;


/* ============================
   FUNCIONES
   ============================ */


/** \brief Crear la lista circular apuntandola a NULL.
 *
 * \param pl Direccion de la lista circular.
 *
 */
void crearListaCircular (t_listaCircular *pl);

/** \brief Insertar en la segunda posicion de la lista circular.
 *
 * Crea un nuevo nodo y le asigna espacio en el dato del tamanio del dato con memoria dinamica, le copia el dato al nodo y lo ubica en el segundo lugar de la lista circular.
 *
 * \param pl Direccion de la lista circular.
 * \param dato Puntero al dato que se quiere guardar.
 * \param tamDato tamanio en bytes del dato.
 *
 * \return EXITO si se ejecuto correctamente, ERROR_SIN_MEMORIA en caso de no poder asignar memoria.
 *
 */
int insertarSegundoCircular (t_listaCircular *pl, const void *dato, unsigned tamDato);

/** \brief Funcion map sobre la lista circular.
 *
 * \param pl Direccion de la lista circular.
 * \param accion Funcion de accion a realizar sobre la lista circular.
 *
 */
void mapListaCircular (t_listaCircular *pl, void accion (void *dato));

/** \brief Funcion map utilizando un complemento sobre la lista circular.
 *
 * \param pl Direccion de la lista circular.
 * \param complemento Puntero al complemento a utilizar en la funcion de accion.
 * \param accion Funcion de accion a realizar sobre la lista circular utilizando el complemento.
 *
 */
void mapListaCircularConComplemento (t_listaCircular *pl, void *complemento, void accion (void *dato, void *complemento));

/** \brief Vaciar la lista circular, realizando una accion sobre los datos previamente.
 *
 * Libera la memoria dinamica creada para el dato y para el nodo.
 *
 * \param pl Direccion de la lista circular.
 * \param accion Funcion de accion a realizar sobre los datos de los nodos antes de eliminarlos.
 *
 */
void vaciarListaCircularConAccion (t_listaCircular *pl, void accion (void *dato));


#endif // LISTACIRCULAR_H_INCLUDED


























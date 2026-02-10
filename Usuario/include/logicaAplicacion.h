/**
 * \file   logicaAplicacion.h
 * \brief  Contiene funciones logicas, defines y macros globales de la aplicacion.
 */



#ifndef LOGICAUSUARIO_H_INCLUDED
#define LOGICAUSUARIO_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../EstructurasDeDatos/include/listaSimple.h"
#include "../../EstructurasDeDatos/include/listaCircular.h"
#include "../../Constantes/constantes.h"
#include "utiles.h"
#include "estructuras.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def ANCHO_LOGICO_VENTANA
 * \brief Ancho/tamanio en x, logico de la ventana.
 */
#define ANCHO_LOGICO_VENTANA 1920

/**
 * \def ALTO_LOGICO_VENTANA
 * \brief Alto/tamanio en y, logico de la ventana.
 */
#define ALTO_LOGICO_VENTANA 1009


/**
 * \def INTERFAZ_AUTENTICACION
 * \brief Identificador de la interfaz de autenticacion.
 */
#define INTERFAZ_AUTENTICACION 1

/**
 * \def INTERFAZ_CONFIG
 * \brief Identificador de la interfaz de configuraciones.
 */
#define INTERFAZ_CONFIG 2

/**
 * \def INTERFAZ_CONTACTOS
 * \brief Identificador de la interfaz de contactos.
 */
#define INTERFAZ_CONTACTOS 3

/**
 * \def INTERFAZ_REGISTRO
 * \brief Identificador de la interfaz de registro.
 */
#define INTERFAZ_REGISTRO 4

/**
 * \def INTERFAZ_SALAS
 * \brief Identificador de la interfaz de salas.
 */
#define INTERFAZ_SALAS 5


/**
 * \def MAX_MENSAJES_MEMORIA
 * \brief Cantidad maxima de mensajes que se guardan en memoria en la lista circular de mensajes.
 */
#define MAX_MENSAJES_MEMORIA 25


/**
 * \def EVENTO_MANEJADO
 * \brief Codigo de retorno para indicar que el evento fue manejado.
 */
#define EVENTO_MANEJADO 1

/**
 * \def EVENTO_NO_MANEJADO
 * \brief Codigo de retorno para indicar que el evento no fue manejado.
 */
#define EVENTO_NO_MANEJADO 0



/* ============================
   MACROS
   ============================ */



/**
 * \brief Libera de forma segura un objeto de tipo vista (sfView) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfView_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfView` a destruir.
 */
#define DESTRUCTOR_SEGURO_VISTA(x) if(x) {sfView_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo texto (sfText) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfText_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfText` a destruir.
 */
#define DESTRUCTOR_SEGURO_TEXTO(x) if(x) {sfText_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo rectangulo (sfRectangleShape) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfRectangleShape_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfRectangleShape` a destruir.
 */
#define DESTRUCTOR_SEGURO_RECTANGULO(x) if(x) {sfRectangleShape_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo circulo (sfCircleShape) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfCircleShape_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfCircleShape` a destruir.
 */
#define DESTRUCTOR_SEGURO_CIRCULO(x) if(x) {sfCircleShape_destroy(x); x = NULL;}

/**
 * \brief Libera de forma segura un objeto de tipo fuente (sfFont) si existe.
 *
 * Verifica si el puntero es valido (no nulo) antes de llamar a `sfFont_destroy()`.
 * Luego, lo asigna a NULL.
 * Garantiza un cierre seguro de recursos graficos.
 *
 * \param x Puntero al objeto `sfFont` a destruir.
 */
#define DESTRUCTOR_SEGURO_FUENTE(x) if(x) {sfFont_destroy(x); x = NULL;}



/* ============================
   FUNCIONES DE FUENTES
   ============================ */



/** \brief Inicializar los recursos graficos de las fuentes graficas para texto.
 *
 * Establecer todas las variables graficas de fuentes en NULL y luego crearlas desde archivos .ttf.
 *
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas para los textos.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int inicializarFuentes (t_fuentes *fuentes);

/** \brief Liberar todos los recursos graficos de fuentes creados.
 *
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas para los textos.
 *
 */
void liberarFuentes (t_fuentes *fuentes);



/* ============================
   FUNCIONES LOGICAS DE GRAFICOS
   ============================ */



/** \brief Posicionar y centrar el nombre de usuario.
 *
 * Si el nombre de usuario no entra dentro del area establecida, se achica el tamanio del texto hasta que quede centrado.
 *
 * \param nombre Puntero al texto del nombre sfText a posicionar.
 *
 */
void posicionarNombreUsuario (sfText *nombre);



/* ============================
   FUNCIONES DE LISTA DE MENSAJES
   ============================ */



/** \brief Configurar un mensaje.
 *
 * Establecerle un color y la fuente enviada como parametro.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param fuente Puntero a fuente sfFont.
 *
 */
void configurarMensaje (void *mensaje, void *fuente);

/** \brief Establecer un tamanio a un mensaje. Ademas, agrega un espaciado de linea.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void tamMensaje (void *mensaje);

/** \brief Renderizar un mensaje.
 *
 * No se limpia ni muestra la ventana, solo lo renderiza.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 *
 */
void renderizarMensaje (void *mensaje, void *renderizado);

/** \brief Liberar un mensaje sfText.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void liberarMensaje (void *mensaje);

/** \brief Modificar la posicion de un mensaje.
 *
 * Unicamente modifica la posicion en Y del mensaje.
 *
 * \param mensaje Doble puntero a mensaje sfText.
 * \param desplazamientoY Puntero a la cantidad de desplazamiento en Y que se desea modificar.
 *
 */
void modificarPosMensaje (void *mensaje, void *desplazamientoY);

/** \brief Establecer los saltos de linea necesarios a un mensaje sfText.
 *
 * Establecer una cadena valida al texto sfText, con saltos de linea incorporados, que las lineas no sobrepasen el ancho maximo enviado como parametro.
 *
 * \param texto Puntero al mensaje sfText.
 * \param bufferMensaje Buffer que almacena el mensaje completo (sin saltos de linea).
 * \param anchoMax Ancho maximo que no debe sobrepasar los limites del mensaje.
 *
 */
void establecerSaltoDeLineaMensaje (sfText *texto, const char *bufferMensaje, float anchoMax);

/** \brief Insertar un mensaje a la lista circular de mensajes.
 *
 * Trabaja sobre el puntero al nodo del primer mensaje de la lista circular.
 * Establecer los saltos de linea necesarios para que el mensaje no sobrepase los limites establecidos.
 * Desplazar en Y a toda la lista circular de mensajes. El desplazamiento depende del alto del mensaje a insertar.
 * Dependiendo del origen del mensaje, se establece una posicion u otra al mismo.
 * Actualizar correspondientemente los punteros a nodo del primer y ultimo mensaje de la lista circular de mensajes.
 *
 * \param mensajes Puntero a la estructura que almacena datos sobre los mensajes.
 * \param bufferMensaje Buffer que almacena el mensaje completo.
 * \param origen Origen de quien envio mensaje.
 *
 */
void insertarMensaje (t_mensajes *mensajes, const char *bufferMensaje, t_origenMensaje origen);



/* ============================
   FUNCIONES DE NOTIFICACIONES
   ============================ */



/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
int crearNotificacion (t_notificacion *notificacion);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
void setupNotificacion (t_notificacion *notificacion, t_fuentes fuentes);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
int agregarNotificacion (t_listaSimple *listaNotificaciones, char *bufferNotificacion, t_fuentes fuentes);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
void liberarNotificacion (void *notificacion);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
void renderizarListaNotificaciones (void *notificacion, void *renderizado);



#endif // LOGICAUSUARIO_H_INCLUDED





































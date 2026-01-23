/**
 * \file  recursosComunesContactosSalas.h
 * \brief Declaracion de funciones y estructuras para recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */



#ifndef RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED
#define RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED



/* ============================
   INCLUDES
   ============================ */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdbool.h>

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"
#include "SFML/Audio.h"

#include "../../../Constantes/constantes.h"
#include "../logicaUsuario.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def VELOCIDAD_SCROLL
 * \brief Constante que determina que tan rapido se mueve el scroll.
 */
#define VELOCIDAD_SCROLL 35.0f


/**
 * \def ANCHO_MINIMO_VENTANA
 * \brief Ancho/tamanio en x, minimo que puede tomar la ventana.
 */
#define ANCHO_MINIMO_VENTANA 800

/**
 * \def ALTO_MINIMO_VENTANA
 * \brief Alto/tamanio en y, minimo que puede tomar la ventana.
 */
#define ALTO_MINIMO_VENTANA 600


/**
 * \def HABILITAR_AREA_MENSAJES
 * \brief Codigo para indicar que el area de mensajes fue seleccionado (clickeado) por el usuario.
 */
#define HABILITAR_AREA_MENSAJES 1

/**
 * \def DESHABILITAR_AREA_MENSAJES
 * \brief Codigo para indicar que el area de mensajes fue deseleccionado (no clickeado) por el usuario.
 */
#define DESHABILITAR_AREA_MENSAJES 0


/**
 * \def HABILITAR_ESCRIBIR_MENSAJE
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir un mensaje se encuentra habilitado.
 */
#define HABILITAR_ESCRIBIR_MENSAJE 1

/**
 * \def DESHABILITAR_ESCRIBIR_MENSAJE
 * \brief Codigo para indicar que el ingreso de texto por parte del usuario para escribir un mensaje se encuentra deshabilitado.
 */
#define DESHABILITAR_ESCRIBIR_MENSAJE 0


/**
 * \def HABILITAR_NOTIFICACIONES
 * \brief Codigo para abrir la ventana emergente de notificaciones.
 */
#define HABILITAR_NOTIFICACIONES 1

/**
 * \def DESHABILITAR_NOTIFICACIONES
 * \brief Codigo para cerrar la ventana emergente de notificaciones.
 */
#define DESHABILITAR_NOTIFICACIONES 0



/* ============================
   ESTRUCTURAS
   ============================ */



/** \struct t_recursosComunesContactosSalasTextos
 * \brief Contiene todos los textos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfText *alertaNotificaciones;       /**< Signo de alerta cuando se recibe una nueva notificacion no leida. */
    sfText *auxEscribirMensaje;         /**< Muestra el mensaje que escribe el usuario. */
    sfText *cerrarVentanaEmergente;     /**< Cruz para cerrar la ventana emergente. */
    sfText *configuraciones;            /**< Boton para dirigirse a la interfaz de configuraciones. */
    sfText *proximaInterfaz;            /**< Muestra el nombre de la interfaz disponible para cambiar, esta ubicado sobre la solapaCambiarInterfaz. */
    sfText *nombreUsuario;              /**< Muestra el nombre del usuario. */
    sfText *notificaciones;             /**< Boton para abrir la ventana emergente de notificaciones. */
    sfText *textoBotonEnviar;           /**< Texto encontrado dentro del boton para enviar mensaje. */
    sfText *tituloInterfaz;             /**< Titulo de la interfaz sobre la que se encuentra ubicado el usuario. */
    sfText *tituloVentanaEmergente;     /**< Titulo de la ventana emergente. */
} t_recursosComunesContactosSalasTextos;

/** \struct t_recursosComunesContactosSalasElementos
 * \brief Contiene todos los elementos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfRectangleShape *areaMensajes;             /**< Area donde se muestran los mensajes enviados y recibidos. */
    sfRectangleShape *barraEscribirMensaje;     /**< Barra donde el usuario escribe el mensaje. */
    sfRectangleShape *botonEnviar;              /**< Boton para enviar mensaje. */
    sfCircleShape *ojalilloArriba;              /**< Ojalillo decorativo superior. */
    sfCircleShape *ojalilloAbajo;               /**< Ojalillo decorativo inferior. */
    sfRectangleShape *separacionNombre;         /**< Barra decorativa que separa el panel del nombre de usuario. */
    sfRectangleShape *separacionTitulo;         /**< Barra decorativa que separa el panel del titulo de la interfaz. */
    sfRectangleShape *panelInterfaz;            /**< Panel principal de la interfaz ubicado a la izquierda de la ventana. */
    sfRectangleShape *puntoInsercion;           /**< Punto de insercion para escritura de texto. */
    sfRectangleShape *solapaCambiarInterfaz;    /**< Solapa para cambiar de interfaz encontrada en el panel. */
    sfRectangleShape *ventanaEmergente;         /**< Rectangulo de la ventana emergente. */
} t_recursosComunesContactosSalasElementos;

/** \struct t_recursosComunesContactosSalasVistas
 * \brief Contiene todas las vistas comunes (compartidas) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfView *UI;                            /**< Vista fija que muestra la interfaz del usuario. */
    sfView *mensajes;                      /**< Vista movil que navega sobre el historial de mensajes. */
} t_recursosComunesContactosSalasVistas;

/** \struct t_recursosComunesContactosSalasHabilitaciones
 * \brief Contiene todas las habilitaciones comunes (compartidas) entre las interfaces de contactos y salas.
 */
typedef struct
{
    bool areaMensajes;                          /**< Indicar si el area de mensajes fue seleccionado/deseleccionado por el usuario. */
    bool escribirMensaje;                       /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir un mensaje. */
    bool notificaciones;                        /**< Abrir/cerrar la ventana emergente de notificaciones. */
    bool puntoInsercion;                        /**< Activar/desactivar el punto de insercion. */
    unsigned short int contadorPuntoInsercion;  /**< Contador para determinar el tiempo en el que se activa/desactiva el punto de insercion. */
} t_recursosComunesContactosSalasHabilitaciones;

/** \struct t_recursosComunesContactosSalas
 * \brief Estructura base que contiene los buffers, habilitaciones y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    t_recursosComunesContactosSalasTextos textos;
    t_recursosComunesContactosSalasElementos elementos;
    t_recursosComunesContactosSalasHabilitaciones habilitaciones;
    t_recursosComunesContactosSalasVistas vistas;
    char bufferMensaje [MAX_BUFFER_MENSAJE];                         /**< Buffer donde se guarda el mensaje escrito por el usuario. */
} t_recursosComunesContactosSalas;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar los recursos graficos y vistas comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Establecer todas las variables graficas y vistas en NULL y luego crear cada recurso y vista.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int recursosComunesContactosSalas_inicializar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Configurar los recursos graficos, habilitaciones y buffers comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Deshabilitar todas las banderas habilitadoras, apuntar los buffers a NULL y configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param fuentes Puntero a la estructura que contiene las fuentes graficas de texto cargadas para utilizar.
 *
 */
void recursosComunesContactosSalas_configurar (t_recursosComunesContactosSalas *recursosComunesContactosSalas, const t_fuentes *fuentes);

/** \brief Renderizar los recursos graficos de textos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasTextos *textos);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura base de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasElementos *elementos);

/** \brief Liberar, de manera segura, todos los recursos graficos y vistas comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_liberar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);



/* ============================
   FUNCIONES LOGICAS
   ============================ */



/** \brief Intentar enviar un mensaje a otro usuario.
 *
 * Genera una cadena de solicitud valida que incluye el indice de la solicitud, el ID del emisor, el ID del receptor y el texto del mensaje.
 * Envia la solicitud al servidor y espera su respuesta para saber su estado.
 * Se comunican a traves del socket de la aplicacion.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 * \return EXITO si se pudo enviar correctamente, ERROR_INICIALIZACION en caso contrario.
 */
int intentarEnvioMensaje (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el recibo de un mensaje por parte de otro usuario.
 *
 * Parsea la cadena de respuesta para obtener el ID del emisor y el texto de mensaje, luego asigna el mensaje a la lista circular de mensajes.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param bufferRespuesta Buffer donde se recibio la respuesta del servidor.
 *
 */
void manejarReciboMensaje (t_aplicacion *aplicacion, char *bufferRespuesta);

/** \brief Renderizar la vista de mensajes.
 *
 * Establecer la vista de mensajes en el renderizado, y renderizar la lista de mensajes.
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void renderizarVistaMensajes (t_aplicacion *aplicacion, const t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Renderizar los recursos graficos de las notificaciones.
 *
 * Si se encuentra habilitada la ventana emergente de notificaciones, renderizar los elementos y textos graficos, y la lista de notificaciones.
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void renderizarNotificaciones (t_aplicacion *aplicacion, const t_recursosComunesContactosSalas *recursosComunesContactosSalas);



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de redimensionamiento de la ventana.
 *
 * Verificar que el nuevo tamanio de la ventana no exceda los valores de ancho y alto minimos, establecer los valores que correspondan a la ventana de renderizado,
 * y fijar los valores logicos de la vista UI.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 * \param eventoRedimensionamiento Variable de evento que contiene los nuevos valores de la ventana redimensionada.
 *
 */
void manejarRedimensionamientoVentanaContactosSalas (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoRedimensionamiento);

/** \brief Manejar el evento de click en el boton para enviar mensaje.
 *
 * Intentar enviar el mensaje al destinatario.
 * Si resulto en exito, asigna el mensaje a la lista circular de mensajes y lo muestra por pantalla.
 * Reestablecer el buffer de escribir mensaje.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarClickEnviarMensaje (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de escribir mensaje.
 *
 * Si se encuentra habilitado el escribir mensaje, se agrega el caracter al buffer del mensaje, lo muestra por pantalla y modifica el punto de insercion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoChar);

/** \brief Manejar el evento de enviar mensaje.
 *
 * Intentar enviar el mensaje al destinatario.
 * Si resulto en exito, asigna el mensaje a la lista circular de mensajes y lo muestra por pantalla.
 * Reestablecer el buffer de escribir mensaje.
 *
 * \param aplicacion Puntero a la estructura base de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarEnterEnviarMensaje (t_aplicacion *aplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de desplazar arriba el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia arriba por la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarDesplazarArribaAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de desplazar abajo el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia abajo por la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarDesplazarAbajoAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de scroll en el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes segun el scroll realizado y la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene los buffers, habilitacion y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarScrollAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoScroll);



#endif // RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED
























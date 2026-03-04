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

#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/System.h"

#include "../../../Constantes/constantes.h"
#include "../utiles.h"
#include "../../../EstructurasDeDatos/include/listaSimple.h"
#include "../../../EstructurasDeDatos/include/listaCircular.h"
#include "../estructuras.h"



/* ============================
   DEFINES
   ============================ */



/**
 * \def MAX_MENSAJES_MEMORIA
 * \brief Cantidad maxima de mensajes que se guardan en memoria en la lista circular de mensajes.
 */
#define MAX_MENSAJES_MEMORIA 25


/**
 * \def VELOCIDAD_SCROLL
 * \brief Constante que determina que tan rapido se mueve el scroll.
 */
#define VELOCIDAD_SCROLL 35.0f


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
 * \def ANCHO_MINIMO_VENTANA
 * \brief Ancho/tamanio en x, minimo que puede tomar la ventana.
 */
#define ANCHO_MINIMO_VENTANA 800

/**
 * \def ALTO_MINIMO_VENTANA
 * \brief Alto/tamanio en y, minimo que puede tomar la ventana.
 */
#define ALTO_MINIMO_VENTANA 600



/* ============================
   ESTRUCTURAS
   ============================ */



/**
 * \struct t_recursosComunesContactosSalasFuentes
 * \brief  Contiene las fuentes graficas de textos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    sfFont *ui;             /**< Fuente utilizada en textos de la interfaz grafica. */
    sfFont *cuerpo;         /**< Fuente utilizada en mensajes y areas en donde el usuario escribe texto. */
} t_recursosComunesContactosSalasFuentes;

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
    sfRectangleShape *carpetaDecorativaFondo1;  /**< Carpeta decorativa ubicada al fondo.*/
    sfRectangleShape *carpetaDecorativaFondo2;  /**< Carpeta decorativa ubicada al fondo.*/
    sfCircleShape *ojalilloArriba;              /**< Ojalillo decorativo superior. */
    sfCircleShape *ojalilloAbajo;               /**< Ojalillo decorativo inferior. */
    sfCircleShape *ojalilloSelecInterfaz;       /**< Ojalillo decorativo situado en la carpeta para cambiar de interfaz. */
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

/** \enum t_recursosComunesContactosSalasFoco
 * \brief Contiene los estados de foco comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef enum
{
    AREA_MENSAJES,                          /**< Indicar si el area de mensajes fue seleccionado/deseleccionado por el usuario. */
    ESCRIBIR_MENSAJE,                       /**< Habilitar/deshabilitar el ingreso de texto por parte del usuario para escribir un mensaje. */
    NOTIFICACIONES,                         /**< Abrir/cerrar la ventana emergente de notificaciones. */
    RCCS_NINGUNO                            /**< Ningun foco establecido. */
} t_recursosComunesContactosSalasFoco;

/**
 * \struct t_contextoMensajes
 * \brief Contexto sobre el manejo y el estado de los mensajes.
 */
typedef struct
{
    t_listaCircular listaMensajes;               /**< Lista circular de mensajes. */
    t_nodo *primerMensaje;                       /**< Puntero al primer mensaje de la lista circular de mensajes. */
    t_nodo *ultimoMensaje;                       /**< Puntero al ultimo mensaje de la lista circular de mensajes. */
    char bufferMensaje [MAX_BUFFER_MENSAJE];     /**< Buffer donde se guarda el mensaje escrito por el usuario. */
} t_contextoMensajes;

/**
 * \enum t_origenMensaje
 * \brief Indica el origen de un mensaje dentro de la aplicacion.
 */
typedef enum
{
    MENSAJE_PROPIO,     /**< Mensaje enviado por el usuario local. */
    MENSAJE_REMOTO      /**< Mensaje recibido por otro usuario. */
} t_origenMensaje;

/**
 * \struct t_notificacion
 * \brief  Estructura que contiene los elementos de una notificacion.
 * \note Estructura NO ACTIVA en el Incremento 1.
 */
typedef struct
{
    sfRectangleShape *recuadro;
    sfRectangleShape *botonAceptar;
    sfRectangleShape *botonRechazar;
    sfText *textoNotificacion;
    sfText *textoBotonAceptar;
    sfText *textoBotonRechazar;
} t_notificacion;

/** \struct t_recursosComunesContactosSalas
 * \brief Estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 */
typedef struct
{
    t_recursosComunesContactosSalasFuentes fuentes;
    t_recursosComunesContactosSalasTextos textos;
    t_recursosComunesContactosSalasElementos elementos;
    t_recursosComunesContactosSalasVistas vistas;
    t_recursosComunesContactosSalasFoco estadoFoco;
    t_contextoMensajes contextoMensajes;
    t_puntoInsercion puntoInsercion;
} t_recursosComunesContactosSalas;



/* ============================
   FUNCIONES ESTRUCTURALES
   ============================ */



/** \brief Inicializar todas las variables graficas en NULL y crear la lista de mensajes de los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_inicializarValoresNulos (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Inicializar los recursos graficos, la lista de mensajes y vistas comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Para la lista circular de mensajes, se crea un vector de punteros sfText que primero se inicializan en NULL y luego se crean los sfText y se insertan a la lista circular.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EXITO si se inicializo correctamente, ERROR_INICIALIZACION en caso de error.
 *
 */
int recursosComunesContactosSalas_inicializar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Configurar los recursos graficos, la lista de mensajes, contexto de mensajes y focos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * Deshabilitar el estado de foco, apuntar los buffers a NULL y configurar y establecer un tamanio y una posicion sobre la ventana a cada recurso grafico y a la lista de mensajes.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_configurar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Renderizar los recursos graficos de textos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param textos Puntero a la estructura que contiene las variables de los textos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarTextos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasTextos *textos);

/** \brief Renderizar los recursos graficos de elementos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param elementos Puntero a la estructura que contiene las variables de los elementos graficos de los recursos graficos comunes entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_renderizarElementos (sfRenderWindow *renderizado, const t_recursosComunesContactosSalasElementos *elementos);

/** \brief Liberar, de manera segura, todos los recursos graficos y vistas comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 */
void recursosComunesContactosSalas_liberar (t_recursosComunesContactosSalas *recursosComunesContactosSalas);



/* ============================
   FUNCIONES LOGICAS
   ============================ */



/** \brief Activar la interfaz de contactos.
 *
 * Modificar los estados de foco, los buffers, vaciar la lista de mensajes, resetear el punto de insercion y los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de contactos.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 */
void activarInterfazContactos (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Activar la interfaz de salas.
 *
 * Modificar los estados de foco, los buffers, vaciar la lista de mensajes, resetear el punto de insercion y los recursos graficos de texto y/o elementos que se necesiten adaptar para activar la interfaz de salas.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 */
void activarInterfazSalas (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Renderizar la vista de mensajes.
 *
 * Establecer la vista de mensajes en el renderizado, y renderizar la lista de mensajes.
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 */
void renderizarVistaMensajes (sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Renderizar los recursos graficos de las notificaciones.
 *
 * Si se encuentra habilitada la ventana emergente de notificaciones, renderizar los elementos y textos graficos, y la lista de notificaciones.
 * No se limpia ni muestra la ventana, solo los renderiza.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 *
 */
void renderizarNotificaciones (sfRenderWindow *renderizado, const t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Posicionar y centrar el nombre de usuario.
 *
 * Si el nombre de usuario no entra dentro del area establecida, se achica el tamanio del texto hasta que quede centrado.
 *
 * \param nombre Puntero al texto del nombre sfText a posicionar.
 *
 */
void posicionarNombreUsuario (sfText *nombre);

/** \brief Preparar la aplicacion para iniciar la interfaz del menu principal.
 *
 * Seleccionar la interfaz de contactos como la interfaz del menu principal, establecer y posicionar el nombre de usuario en las interfaces y maximizar la ventana.
 *
 * \param contextoAplicacion Puntero a la estructura que provee contexto (estados y recursos) global de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base de los recursos graficos, buffers y habilitaciones comunes entre las interfaces de contactos y salas.
 *
 */
void iniciarInterfazMenuPrincipal (t_contextoAplicacion *contextoAplicacion, t_recursosComunesContactosSalas *recursosComunesContactosSalas);



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

/** \brief Vaciar (resetear) un mensaje sfText. Setear su string a "".
 *
 * \param mensaje Doble puntero a mensaje sfText.
 *
 */
void vaciarMensaje (void *mensaje);

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
 * \param contextoMensajes Puntero a la estructura que provee contexto sobre el manejo y el estado de los mensajes.
 * \param bufferMensaje Buffer que almacena el mensaje completo.
 * \param origen Origen de quien envio mensaje.
 *
 */
void insertarMensaje (t_contextoMensajes *contextoMensajes, const char *bufferMensaje, t_origenMensaje origen);



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
void setupNotificacion (t_notificacion *notificacion, const t_recursosComunesContactosSalasFuentes *fuentes);

/**
 * \note Funcionalidad NO ACTIVA en el Incremento 1.
 *
 * \warning No invocar desde produccion.
 */
int agregarNotificacion (t_listaSimple *listaNotificaciones, char *bufferNotificacion, const t_recursosComunesContactosSalasFuentes *fuentes);

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



/* ============================
   FUNCIONES MANEJADORAS DE EVENTOS
   ============================ */



/** \brief Manejar el evento de redimensionamiento de la ventana.
 *
 * Verificar que el nuevo tamanio de la ventana no exceda los valores de ancho y alto minimos, establecer los valores que correspondan a la ventana de renderizado,
 * y fijar los valores logicos de la vista UI.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param eventoRedimensionamiento Variable de evento que contiene los nuevos valores de la ventana redimensionada.
 *
 */
void manejarRedimensionamientoVentanaContactosSalas (sfRenderWindow *renderizado, t_recursosComunesContactosSalasVistas *vistas, sfEvent eventoRedimensionamiento);

/** \brief Manejar el evento de click en la barra para escribir mensaje.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarClickEscribirMensaje (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de click en el area de mensajes.
 *
 * \param renderizado Puntero al renderizado de la estructura que provee contexto de la aplicacion.
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarClickAreaMensajes (const sfRenderWindow *renderizado, t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de escribir mensaje.
 *
 * Si se encuentra el foco en escribir mensaje, intenta agregar el caracter al buffer del mensaje.
 * En caso de exito, analiza si se habilita el ingreso del usuario, actualiza visualmente el caracter ingresado en la UI y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_NO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param eventoChar Variable de evento que contiene el caracter de la letra ingresada.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoChar);

/** \brief Manejar el evento de pegar desde el portapapeles al buffer de escribir mensaje.
 *
 * Si se encuentra el foco en escribir mensaje, intenta agregar el caracter al buffer del mensaje.
 * En caso de exito, analiza si se habilita el ingreso del usuario, actualiza visualmente el caracter ingresado en la UI y modifica el punto de insercion.
 * En caso de falla, retorna EVENTO_NO_MANEJADO sin realizar ninguna accion.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarPegarPortapapelesEscribirMensaje (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de desplazar arriba el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia arriba por la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarDesplazarArribaAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de desplazar abajo el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes hacia abajo por la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarDesplazarAbajoAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas);

/** \brief Manejar el evento de scroll en el area de mensajes.
 *
 * Si se encuentra seleccionada el area de mensajes, mueve la vista de mensajes segun el scroll realizado y la velocidad del scroll.
 *
 * \param recursosComunesContactosSalas Puntero a la estructura base que contiene contexto de los mensajes, focos y une todos los recursos graficos comunes (compartidos) entre las interfaces de contactos y salas.
 * \param eventoScroll Variable de evento que contiene datos sobre el scroll.
 *
 * \return EVENTO_MANEJADO en caso de que el evento se manejo, EVENTO_NO_MANEJADO en caso contrario.
 *
 */
bool manejarScrollAreaMensajes (t_recursosComunesContactosSalas *recursosComunesContactosSalas, sfEvent eventoScroll);



#endif // RECURSOSCOMUNESCONTACTOSSALAS_H_INCLUDED























